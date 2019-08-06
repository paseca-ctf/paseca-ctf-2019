/*
* @Author: madrat
* @Date:   2019-08-06 22:29:59
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef unsigned char BYTE;

typedef struct Wishes
{
    char buffer[24];
    BYTE wishes_count;
} Wishes;

void read_flag()
{
    FILE *fp = fopen("./flag.txt", "r");
    if (fp == NULL) {
        perror("Unable to open file! Please contact administrator.");
        exit(1);
    }
    
    char chunk[128];
    printf("%s", "Congratulations! Your flag: ");
    fgets(chunk, sizeof(chunk), fp);
    fputs(chunk, stdout);
    puts("");
    fclose(fp);
}

int main(int argc, const char *argv[])
{
    unsigned int cnt = 0;
    Wishes *wish = (Wishes *)calloc(sizeof(Wishes), sizeof(BYTE)); 
    wish->wishes_count = 3;

    puts("Hi stranger! Im genie. You can make 3 wishes.\nBut real reward can be obtained only after 4 wish...");

    for (;wish->wishes_count > 0; wish->wishes_count--)
    {
        printf("Wishes left: %u\n", wish->wishes_count);
        printf("Write your wish\n> ");
        scanf("%25s", wish->buffer);
        printf("Ok, your wish is: %s\n", wish->buffer);

        cnt++;
        if ((char)wish->wishes_count <= 3 && cnt > 3)
            read_flag();
        else if (cnt > 3)
        {
            puts("Better luck next time...");
            break;
        }
    }



    return 0;
}