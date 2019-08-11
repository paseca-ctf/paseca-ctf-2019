/*
* @Author: madrat
* @Date:   2019-08-11 22:21:41
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "check1.h"
#include "check2.h"
#include "check3.h"
#include "check4.h"
#include "check5.h"
#include "check6.h"
#include "check7.h"
#include "check8.h"
#include "check9.h"
#include "check10.h"
#include "check11.h"
#include "check12.h"
#include "check13.h"
#include "check14.h"
#include "check15.h"
#include "check16.h"
#include "check17.h"
#include "check18.h"
#include "check19.h"
#include "check20.h"
#include "check21.h"
#include "check22.h"
#include "check23.h"
#include "check24.h"
#include "check25.h"
#include "check26.h"
#include "check27.h"
#include "check28.h"
#include "check29.h"
#include "check30.h"
#include "check31.h"
#include "check32.h"
#include "check33.h"
#include "check34.h"
#include "check35.h"
#include "check36.h"

int check(char *str)
{
    if (strlen(str) < 36)
        return 0;

    if (check1(str[0]) && check2(str[1]) && check3(str[2]) && check4(str[3]) && check5(str[4]) && check6(str[5]) && check7(str[6]) && check8(str[7]) && check9(str[8]) && check10(str[9]) && check11(str[10]) && check12(str[11]) && check13(str[12]) && check14(str[13]) && check15(str[14]) && check16(str[15]) && check17(str[16]) && check18(str[17]) && check19(str[18]) && check20(str[19]) && check21(str[20]) && check22(str[21]) && check23(str[22]) && check24(str[23]) && check25(str[24]) && check26(str[25]) && check27(str[26]) && check28(str[27]) && check29(str[28]) && check30(str[29]) && check31(str[30]) && check32(str[31]) && check33(str[32]) && check34(str[33]) && check35(str[34]) && check36(str[35]))
    {
        return 1;
    }

    return 0;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("usage: %s paseca{test_flag}\n", argv[0]);
        return 0;
    }

    if (check(argv[1]))
    {
        puts("Congrats! Flag is correct!");
    } 
    else {
        puts("Nope... Flag is incorrect!");
    }

    return 0;
}