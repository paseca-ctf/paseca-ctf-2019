#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ItemBlock.h"
#include "Wax.h"
#include "Honey.h"

extern int saved_cookie;

typedef struct
{
	int cookie;
	float cashback;
	int money;
	char *name;
	int free_space;
	ItemBlock items[MAX_ITEMS];
} User;

void add_item_honey(User *user, Honey *honey);
void add_item_wax(User *user, Wax *wax);
User* init_user();
void set_name(User *user, char *newname);