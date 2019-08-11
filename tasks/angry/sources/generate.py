# -*- coding: utf-8 -*-
# @Author: madrat
# @Date:   2019-08-11 22:43:01

import random

flag = 'paseca{d1d_th1s_t4st_mak3_y0u_angr9}'

c_template = '''int check{}(char chr) // valid: {}
{{
    if (((((((((chr * {}) + {}) << {}) ^ {}) * {}) + {}) - {}) ^ {}) == {})
        return 1;
    return 0;
}}'''
h_template = '''#ifndef check{}_h__
#define check{}_h__
 
extern int check{}(char chr);
 
#endif  // check{}_h__'''

def generate_c(idx, valid_char):
    f = open('check{}.c'.format(idx), 'w+')
    val1 = random.randint(1, 10)
    val2 = random.randint(1, 2000)
    val3 = random.randint(1, 5)
    val4 = random.randint(1, 0x1000)
    val5 = random.randint(1, 2000)
    val6 = random.randint(1, 2000)
    val7 = random.randint(1, 2000)
    val8 = random.randint(1, 0x1000)

    ans = ((((((((valid_char * val1) + val2) << val3) ^ val4) * val5) + val6) - val7) ^ val8)
    assert(ans < 2_130_000_000)

    formatted = c_template.format(idx, valid_char, val1, val2, val3, val4, val5, val6, val7, val8, ans)
    f.write(formatted)
    f.close()

def generate_h(idx):
    f = open('check{}.h'.format(idx), 'w+')
    f.write(h_template.format(idx, idx, idx, idx))
    f.close()

def main():
    print('Generating .c and .h files...')
    for idx in range(1, len(flag) + 1):
        generate_h(idx)
        generate_c(idx, ord(flag[idx - 1]))

    print('Comleted!')
    

if __name__ == "__main__":
    main()