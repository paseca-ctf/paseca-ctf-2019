/*
* @Author: m4drat
* @Date:   2019-07-25 17:54:23
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int saved_cookie = 0;

#define DEBUG 0
#if DEBUG
	#include "Debug.h"
#endif

#include "User.h"
#include "ItemBlock.h"
#include "Wax.h"
#include "Honey.h"
#include "Flag.h"

const char *PROMPT = "> ";

void print_banner()
{
	unsigned char __pic_txt[] = { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2f, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5c, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x20, 0x5e, 0x20, 0x6f, 0x20, 0x20, 0x20, 0x20, 0x2f, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5c, 0x20, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x29, 0x20, 0x2f, 0x0d, 0x0a, 0x20, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x28, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x29, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x0d, 0x0a, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2f, 0x20, 0x20, 0x20, 0x2f, 0x20, 0x20, 0x29, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x28, 0x20, 0x20, 0x5c, 0x20, 0x20, 0x20, 0x5c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x29, 0x0d, 0x0a, 0x28, 0x5f, 0x5f, 0x5f, 0x2f, 0x5f, 0x5f, 0x5f, 0x2f, 0x5f, 0x5f, 0x2f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5c, 0x5f, 0x5f, 0x5c, 0x5f, 0x5f, 0x5f, 0x5c, 0x5f, 0x5f, 0x5f, 0x29, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2f, 0x20, 0x20, 0x2f, 0x28, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x29, 0x5c, 0x20, 0x20, 0x5c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x29, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x28, 0x5f, 0x5f, 0x2f, 0x5f, 0x5f, 0x5f, 0x2f, 0x20, 0x28, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x29, 0x20, 0x5c, 0x5f, 0x5f, 0x5f, 0x5c, 0x5f, 0x5f, 0x29, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2f, 0x28, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x29, 0x5c, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2f, 0x20, 0x20, 0x20, 0x28, 0x25, 0x25, 0x25, 0x25, 0x25, 0x29, 0x20, 0x20, 0x20, 0x5c, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x25, 0x25, 0x25, 0x29, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x21, 0x0a }; 
	unsigned int __pic_txt_len = 345;
	for (int i = 0; i < __pic_txt_len; ++i)
		putchar(__pic_txt[i]);
}

void print_help_store()
{
	puts("* [b]uy items");
	puts("*  - Honey");
	puts("*  - Wax");
	puts("*  - Flag");
	puts("* [s]ell item");
	puts("* [v]iew your profile");
	puts("* [c]hange item description");
	puts("* [l]eave bee store");
	fflush(NULL);
}

int main(int argc, const char *argv[])
{
	
#if DEBUG
	printf("sizeof honey: %lu\n", sizeof(Honey));
	printf("sizeof wax: %lu\n", sizeof(Wax));
#endif
	
	Wax *default_wax = (Wax *)malloc(sizeof(Wax));
	init_wax(default_wax);
	Honey *default_honey = (Honey *)malloc(sizeof(Honey));
	init_honey(default_honey);
	
	User *user = init_user();
	add_item_wax(user, default_wax);
	add_item_honey(user, default_honey);
	
    char *choice = (char *)calloc(128, sizeof(char));
	print_banner();
	
	printf("%s", "Hello stanger!\nHow can i call you?\n> ");
	fflush(NULL);
	scanf("%127s", choice);
	getchar();
	set_name(user, choice);
	
	printf("Nice to meet you, %s.\nHere (in bee store) you can buy different items\n", user->name);
	printf("Also by default you have 20 coins and 1 percent cashback.\nMenu items:\n");
	fflush(NULL);
	
	for (;;)
	{
		print_help_store();
		printf("%s", PROMPT);
		fflush(NULL);
		
		fgets(choice, 127, stdin);
		
		if (strncmp(choice, "b", 1) == 0 || strncmp(choice, "buy", 3) == 0) 
		{
			printf("Your balance: %d\n", user->money);
			printf("Your cashback: %f%%\n", user->cashback * 100);
			printf("Your free slots: %d\n", user->free_space);
			puts("Available items in store:");
			puts("  1. Honey (200 gold)");
			puts("  2. Wax (100 gold)");
			puts("  3. Flag (4.800.000 gold)");
			puts("  4. Go back");
			printf("What do you want to buy [1-3]?\n> ");
			fflush(NULL);
			
			fgets(choice, 127, stdin);
			switch (atoi(choice))
			{
			case 1:
				if (user->money >= 200)
				{
					if (user->cookie != saved_cookie)
					{
						puts("Cookie corrupted! We cant approve you're transaction.");
						fflush(NULL);
						exit(2);
					}
					user->money -= (100 - user->cashback * 100) * 200 / 100;
					user->cashback += 0.008;
					default_honey = (Honey *)malloc(sizeof(Honey)); 
					init_honey(default_honey);
					add_item_honey(user, default_honey);
					puts("Yo've just bought some honey.");
					printf("+ cashback incresed! Current: %f%%\n", user->cashback * 100);
					fflush(NULL);
				}
				else
				{
					puts("You dont have enough money :(");	
					fflush(NULL);
				}
				break;
			case 2:
				if (user->money >= 100)
				{
					if (user->cookie != saved_cookie)
					{
						puts("Cookie corrupted! We cant approve you're transaction.");
						fflush(NULL);
						exit(2);
					}
					user->money -= (100 - user->cashback * 100) * 100 / 100;
					user->cashback += 0.005;
					// default_wax = (Wax *)malloc(sizeof(Wax)); 
					default_wax = (Wax *)malloc(sizeof(Honey));      // // Bug here
					init_wax(default_wax);
					add_item_wax(user, default_wax);
					puts("Yo've just bought some wax.");
					printf("+ cashback incresed! Current: %f%%\n", user->cashback * 100);
					fflush(NULL);
				}
				else
				{
					puts("You dont have enough money :(");
					fflush(NULL);
				}
				break;
			case 3:
				if (user->money >= 4800000)
				{
					if (user->cookie != saved_cookie)
					{
						puts("Cookie corrupted! We cant approve you're transaction.");
						fflush(NULL);
						exit(2);
					}
					user->money -= 4800000;
					read_flag();
					return 0;
				}
				else
				{
					puts("You dont have enough money :(");
					fflush(NULL);
				}
				break;
			case 4:
				break;
			default:
				puts("Unrecognised option :(");
				fflush(NULL);
				break;
			}
		}
		else if (strncmp(choice, "s", 1) == 0 || strncmp(choice, "sell", 4) == 0) 
		{
			puts("Which one do you want to sell?");
			fflush(NULL);
			for (int i = 0; i < MAX_ITEMS; ++i)
			{
				if (!(user->items[i].is_free))
				{
					switch (user->items[i].type)
					{
					case WAX:
						printf("%d. Wax. Price: %d\n", i + 1, ((Wax *)user->items[i].item)->price / 2);
						fflush(NULL);
						break;
					case HONEY:
						printf("%d. Honey. Price: %d\n", i + 1, ((Honey *)user->items[i].item)->price / 2);
						fflush(NULL);
						break;
					default:
						puts("Impossible item type!");
						fflush(NULL);
						exit(1);
						break;
					}
				}
			}
			
			printf("%s", PROMPT);
			fflush(NULL);
			
			fgets(choice, 127, stdin);
			
			if (atoi(choice) > 0 && atoi(choice) < 11)
			{
				if (!(user->items[atoi(choice) - 1].is_free))
				{
					user->items[atoi(choice) - 1].is_free = 1;
					
					switch (user->items[atoi(choice) - 1].type)
					{
					case WAX:
						if (user->cookie != saved_cookie)
						{
							puts("Cookie corrupted! We cant approve you're transaction.");
							fflush(NULL);
							exit(2);
						}
						user->free_space += 1;
						user->money += ((Wax *)user->items[atoi(choice) - 1].item)->price / 2;
						printf("Your wax selled successfully! You've earned: %d\n> ", ((Wax *)user->items[atoi(choice) - 1].item)->price / 2);
						fflush(NULL);
						free(user->items[atoi(choice) - 1].item);
						break;
					case HONEY:
						if (user->cookie != saved_cookie)
						{
							puts("Cookie corrupted! We cant approve you're transaction.");
							fflush(NULL);
							exit(2);
						}
						user->free_space += 1;
						user->money += ((Honey *)user->items[atoi(choice) - 1].item)->price / 2;
						printf("Your honey selled successfully! You've earned: %d\n> ", ((Honey *)user->items[atoi(choice) - 1].item)->price / 2);
						fflush(NULL);
						free(user->items[atoi(choice) - 1].item);
						break;
					default:
						puts("Impossible item type!");
						fflush(NULL);
						exit(1);
						break;
					}
				}
				else
				{
					puts("You dont have this item...");	
					fflush(NULL);
				}
			}
			else
			{
				printf("Wrong item index.\n> ");
				fflush(NULL);
			}
		}
		else if (strncmp(choice, "v", 1) == 0 || strncmp(choice, "view", 4) == 0)
		{
			printf("Your balance: %d\n", user->money);
			printf("Your cashback: %f%%\n", user->cashback * 100);
			puts("Your items: ");
			fflush(NULL);
			
			for (int i = 0; i < MAX_ITEMS; ++i)
			{
				if (!(user->items[i].is_free))
				{
					switch (user->items[i].type)
					{
					case WAX:
						printf("%d. Wax. Price: %d\n", i + 1, ((Wax *)user->items[i].item)->price);
						printf("    Description: %s\n", ((Wax *)user->items[i].item)->desc);
						fflush(NULL);
						break;
					case HONEY:
						printf("%d. Honey. Price: %d\n", i + 1, ((Honey *)user->items[i].item)->price);
						printf("    Description: %s\n", ((Honey *)user->items[i].item)->desc);
						fflush(NULL);
						break;
					default:
						puts("Impossible item type!");
						fflush(NULL);
						exit(1);
						break;
					}
				}
			}
		}
		else if (strncmp(choice, "c", 1) == 0 || strncmp(choice, "change", 6) == 0) 
		{
			puts("Description for which item you want to change?");
			fflush(NULL);
			
			for (int i = 0; i < MAX_ITEMS; ++i)
			{
				if (!(user->items[i].is_free))
				{
					switch (user->items[i].type)
					{
					case WAX:
						printf("%d. Wax. Price: %d\n", i + 1, ((Wax *)user->items[i].item)->price / 2);
						fflush(NULL);
						break;
					case HONEY:
						printf("%d. Honey. Price: %d\n", i + 1, ((Honey *)user->items[i].item)->price / 2);
						fflush(NULL);
						break;
					default:
						puts("Impossible item type!");
						fflush(NULL);
						exit(1);
						break;
					}
				}
			}
			
			printf("%s", PROMPT);
			fflush(NULL);
			
			fgets(choice, 127, stdin);
			int idx = atoi(choice);
			if(idx > 0 && idx < 11)
			{
				if (!(user->items[idx - 1].is_free))
				{
					switch (user->items[idx - 1].type)
					{
					case WAX:
						printf("Current description: %s\nEnter new description (1-85): ", ((Wax *)user->items[idx - 1].item)->desc);
						fflush(NULL);
						fgets(choice, 85, stdin);
						strncpy(((Wax *)(user->items[idx - 1].item))->desc, choice, 85);
						break;
					case HONEY:
						printf("Current description: %s\nEnter new description (1-63): ", ((Honey *)user->items[idx - 1].item)->desc);
						fflush(NULL);
						fgets(choice, 63, stdin);
						strncpy(((Honey *)(user->items[idx - 1].item))->desc, choice, 63);
						break;
					default:
						puts("Impossible item type!");
						fflush(NULL);
						exit(1);
						break;
					}
				}
			}
			else
			{
				puts("Incorrect index!");
				fflush(NULL);
			}
				
			
		} 
		else if (strncmp(choice, "l", 1) == 0 || strncmp(choice, "leave", 5) == 0)
		{
			printf("Goodbye! See you later, %s\n", user->name);
			fflush(NULL);
			break;
		}
	}
	
	free(choice);
    return 0;
}