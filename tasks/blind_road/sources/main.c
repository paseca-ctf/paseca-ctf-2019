/*
* @Author: madrat
* @Date:   2019-08-05 19:38:26
*/

// add Full RELRO, delete all imported functions. write your own using syscalls.

#include <unistd.h>
#include <stdio.h>
#include <string.h>

char buf[2048] = "Hi There! Get shell, if you can...\n";

void rop_it() 
{
    char buf[100];
    read(0, buf, 256);
}

__asm__("mov rdx, 0x8");
__asm__("ret");
__asm__("mov rsi, QWORD PTR [rsi]");
__asm__("ret");
__asm__("add rsi, rdi");
__asm__("ret");

int main() 
{
    rop_it();
    return 0;
}