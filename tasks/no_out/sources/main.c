/*
* @Author: m4drat
* @Date:   2019-08-09 22:11:14
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <seccomp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stddef.h>
#include <string.h>
#include <sys/mman.h>

char flag[64];

// gcc main.c -lseccomp -o noout

void read_flag()
{
    FILE *fp = fopen("./flag.txt", "r");
    if (fp == NULL) {
        perror("Unable to open file! Please contact administrator.");
        exit(1);
    }

    fgets(flag, sizeof(flag), fp);
    fclose(fp);
}

void seccomp_initializer()
{
    void *ctx = seccomp_init(SCMP_ACT_KILL);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
    seccomp_load(ctx);
}

void close_fds()
{
    // close(0);
    // close(1);
    // close(2);
}

int main(int argc, const char *argv[])
{
    read_flag();

    char *buf = mmap(NULL, 0x1000, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_SHARED|MAP_ANONYMOUS, -1, NULL);
    if (!buf)
        exit(1);

    puts("Enter your shellcode: ");
    read(0, buf, 0x1000);

    close_fds();
    seccomp_initializer();

    void (*sh)(void) = buf;
    sh();

    return 0;
}