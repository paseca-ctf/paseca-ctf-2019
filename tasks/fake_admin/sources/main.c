/*
* @Author: m4drat
* @Date:   2019-08-23 12:54:11
* compile: gcc main.c -o fake_admin
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char fname[] = "/tmp/logfile.log";
unsigned long long admin_pin = 0x133713370000;

FILE* init_log_file(char *file_path)
{
    FILE *fp = fopen(file_path, "a");
    return fp;
}

void log_msg(FILE *fp, char *msg)
{
    // printf("Logged message: ");
    // printf(msg);
    fprintf(fp, msg);
    fflush(NULL);
}

void print_banner()
{
    puts(R"(   _____                              _   
  / ____|                            | |  
 | (___  _   _ _ __  _ __   ___  _ __| |_ 
  \___ \| | | | '_ \| '_ \ / _ \| '__| __|
  ____) | |_| | |_) | |_) | (_) | |  | |_ 
 |_____/ \__,_| .__/| .__/ \___/|_|   \__|
              | |   | |                   
              |_|   |_|  )");
    fflush(NULL);
}

void print_hello()
{
    puts("Welcome to tech-support!)");
    puts("Write your message if you experience any problems");
    puts("options: ");
    puts(" - [w]rite message");
    puts(" - [v]iew messages (only for admin)");
    puts(" - [h]elp");
    puts(" - [e]xit");
    fflush(NULL);
}

int main(int argc, const char *argv[])
{
    FILE *fp = init_log_file(fname);

    char *choice = (char *)calloc(32, sizeof(char));

    print_banner();
    print_hello();
    
    for (;;)
    {
        printf("%s", "> ");
        fflush(NULL);

        scanf("%31s", choice);

        if (strncmp("write", choice, 5) == 0 || choice[0] == 'w')
        {
            char msg[128];
            memset(msg, 0x0, 128);
            printf("Write your message\n> ");
            fflush(NULL);
            read(0, msg, 128);
            log_msg(fp, msg);
            puts("Thank's for your message! It was logged, and later will be checked.");
            fflush(NULL);
        } 
        else if (strncmp("view", choice, 4) == 0 || choice[0] == 'v') 
        {
            if (admin_pin == 0x133713371338)
            {
                puts("Welcome back, here is your messages.");
                fflush(NULL);
                
                FILE *fpr = fopen(fname, "r");

                char *line = NULL;
                size_t len = 0;
                ssize_t read;

                while ((read = getline(&line, &len, fpr)) != -1) 
                {
                    printf("%s", line);
                }

                fclose(fpr);
            } 
            else 
            {
                printf("Your password is wrong!\nOnly admin can view messages!");
                fflush(NULL);
            }
        }
        else if (strncmp("help", choice, 4) == 0 || choice[0] == 'h') 
        {
            print_hello();
        }
        else if (strncmp("exit", choice, 4) == 0 || choice[0] == 'e') 
        {
            fclose(fp);
            puts("Goodbye!");
            fflush(NULL);
            exit(0);
        } 
        else 
        {
            puts("Wrong option!");
            fflush(NULL);
        }
    }
    
    fclose(fp);
    return 0;
}