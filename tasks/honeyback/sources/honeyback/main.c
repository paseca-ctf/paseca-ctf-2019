/*
* @Author: m4drat
* @Date:   2019-07-25 17:54:23
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

long int saved_cookie = 0;

#define DEBUG 1
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
}

int main(int argc, const char *argv[])
{
	
#ifdef DEBUG
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
	scanf("%127s", choice);
	getchar();
	set_name(user, choice);
	
	printf("Nice to meet you, %s.\nHere (in bee store) you can buy different items\n", user->name);
	printf("Also by default you have 20 coins and 1 percent cashback.\nMenu items:\n");
	
	for (;;)
	{
		print_help_store();
		printf("%s", PROMPT);
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
			
			fgets(choice, 127, stdin);
			switch (atoi(choice))
			{
			case 1:
				if (user->money >= 200)
				{
					if (user->cookie != saved_cookie)
					{
						puts("Cookie corrupted! We cant approve you're transaction.");
						exit(2);
					}
					user->money -= (100 - user->cashback * 100) * 200 / 100;
					user->cashback += 0.008;
					default_honey = (Honey *)malloc(sizeof(Honey)); 
					init_honey(default_honey);
					add_item_honey(user, default_honey);
					puts("Yo've just bought some honey.");
					printf("+ cashback incresed! Current: %f%%\n", user->cashback * 100);
				}
				else
				{
					puts("You dont have enough money :(");	
				}
				break;
			case 2:
				if (user->money >= 100)
				{
					if (user->cookie != saved_cookie)
					{
						puts("Cookie corrupted! We cant approve you're transaction.");
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
				}
				else
				{
					puts("You dont have enough money :(");	
				}
				break;
			case 3:
				if (user->money >= 4800000)
				{
					if (user->cookie != saved_cookie)
					{
						puts("Cookie corrupted! We cant approve you're transaction.");
						exit(2);
					}
					user->money -= 4800000;
					printf("%s", "Congratulations! Here is your flag: ");
					read_flag();
					return 0;
				}
				else
				{
					puts("You dont have enough money :(");	
				}
				break;
			case 4:
				break;
			default:
				puts("Unrecognised option :(");
				break;
			}
		}
		else if (strncmp(choice, "s", 1) == 0 || strncmp(choice, "sell", 4) == 0) 
		{
			puts("Which one do you want to sell?");
			for (int i = 0; i < MAX_ITEMS; ++i)
			{
				if (!(user->items[i].is_free))
				{
					switch (user->items[i].type)
					{
					case WAX:
						printf("%d. Wax. Price: %d\n", i + 1, ((Wax *)user->items[i].item)->price / 2);
						break;
					case HONEY:
						printf("%d. Honey. Price: %d\n", i + 1, ((Honey *)user->items[i].item)->price / 2);
						break;
					default:
						puts("Impossible item type!");
						exit(1);
						break;
					}
				}
			}
			
			printf("%s", PROMPT);
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
							exit(2);
						}
						user->free_space += 1;
						user->money += ((Wax *)user->items[atoi(choice) - 1].item)->price / 2;
						printf("Your wax selled successfully! You've earned: %d\n> ", ((Wax *)user->items[atoi(choice) - 1].item)->price / 2);
						free(user->items[atoi(choice) - 1].item);
						break;
					case HONEY:
						if (user->cookie != saved_cookie)
						{
							puts("Cookie corrupted! We cant approve you're transaction.");
							exit(2);
						}
						user->free_space += 1;
						user->money += ((Honey *)user->items[atoi(choice) - 1].item)->price / 2;
						printf("Your honey selled successfully! You've earned: %d\n> ", ((Honey *)user->items[atoi(choice) - 1].item)->price / 2);
						free(user->items[atoi(choice) - 1].item);
						break;
					default:
						puts("Impossible item type!");
						exit(1);
						break;
					}
				}
				else
				{
					puts("You dont have this item...");	
				}
			}
			else
			{
				printf("Wrong item index.\n> ");
			}
		}
		else if (strncmp(choice, "v", 1) == 0 || strncmp(choice, "view", 4) == 0)
		{
			printf("Your balance: %d\n", user->money);
			printf("Your cashback: %f%%\n", user->cashback * 100);
			puts("Your items: ");
			for (int i = 0; i < MAX_ITEMS; ++i)
			{
				if (!(user->items[i].is_free))
				{
					switch (user->items[i].type)
					{
					case WAX:
						printf("%d. Wax. Price: %d\n", i + 1, ((Wax *)user->items[i].item)->price);
						printf("    Description: %s\n", ((Wax *)user->items[i].item)->desc);
						break;
					case HONEY:
						printf("%d. Honey. Price: %d\n", i + 1, ((Honey *)user->items[i].item)->price);
						printf("    Description: %s\n", ((Honey *)user->items[i].item)->desc);
						break;
					default:
						puts("Impossible item type!");
						exit(1);
						break;
					}
				}
			}
		}
		else if (strncmp(choice, "c", 1) == 0 || strncmp(choice, "change", 6) == 0) 
		{
			puts("Description for which item you want to change?");
			for (int i = 0; i < MAX_ITEMS; ++i)
			{
				if (!(user->items[i].is_free))
				{
					switch (user->items[i].type)
					{
					case WAX:
						printf("%d. Wax. Price: %d\n", i + 1, ((Wax *)user->items[i].item)->price / 2);
						break;
					case HONEY:
						printf("%d. Honey. Price: %d\n", i + 1, ((Honey *)user->items[i].item)->price / 2);
						break;
					default:
						puts("Impossible item type!");
						exit(1);
						break;
					}
				}
			}
			
			printf("%s", PROMPT);
			fgets(choice, 127, stdin);
			int idx = atoi(choice);
			if(idx > 0 && idx < 11)
			{
				if (!(user->items[idx - 1].is_free))
				{
					switch (user->items[idx - 1].type)
					{
					case WAX:
						printf("Current description: %s\nEnter new description (1-127): ", ((Wax *)user->items[idx - 1].item)->desc);
						fgets(choice, 127, stdin);
						strncpy(((Wax *)(user->items[idx - 1].item))->desc, choice, 127);
						break;
					case HONEY:
						printf("Current description: %s\nEnter new description (1-63): ", ((Honey *)user->items[idx - 1].item)->desc);
						fgets(choice, 63, stdin);
						strncpy(((Honey *)(user->items[idx - 1].item))->desc, choice, 63);
						break;
					default:
						puts("Impossible item type!");
						exit(1);
						break;
					}
				}
			}
			else
			{
				puts("Incorrect index!");
			}
				
			
		} 
		else if (strncmp(choice, "l", 1) == 0 || strncmp(choice, "leave", 5) == 0)
		{
			printf("Goodbye! See you later, %s\n", user->name);
			break;
		}
	}
	
	free(choice);
    return 0;
}