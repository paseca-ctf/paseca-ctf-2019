#include "User.h"

int call_cnt = 0;

void add_item_honey(User *user, Honey *honey)
{
	if (user->free_space > 0)
	{
		for (int i = 0; i < MAX_ITEMS; ++i)
		{
			if (user->items[i].is_free) // if cell is empty
			{
				user->items[i].is_free = 0;
				user->items[i].type = HONEY;
				user->items[i].item = honey;
				user->free_space -= 1;
				break;
			}
		}
	}
	else {
		puts("Not enough space for new item :(\nYou need to sell something. Bzzzzz.\n");
		fflush(NULL);
	}
}

void add_item_wax(User *user, Wax *wax)
{
	if (user->free_space > 0)
	{
		for (int i = 0; i < MAX_ITEMS; ++i)
		{
			if (user->items[i].is_free) // if cell is empty
			{
				user->items[i].is_free = 0;
				user->items[i].type = WAX;
				user->items[i].item = wax;
				user->free_space -= 1;
				break;
			}
		}
	}
	else {
		puts("Not enough space for new item :(\nYou need to sell something. Bzzzzz.\n");
		fflush(NULL);
	}
}

void change_item_description(ItemBlock *cell)
{
	if (!(cell->is_free))
	{
		if (cell->item != NULL)
		{
			
		}
		else {
			
		}
	}
}

long int generate_cookie()
{
	call_cnt++;
	// will generate same cookie, so you need to guess (or calculate) just 1 byte.
	char *iv = calloc(260, sizeof(char));
	strncpy(iv, "L>t_sKd>H[j\"A<P0>O\rDPaPb<$t!Q)|FcK|Sj\n=)FYUcrw&T2\rIT&\n4^CT{lCXxX3ru&\'5=FA64V\"rq.2=r9\x0bI\x0b\'kta/RAD@Z]z~0O%ccV!6|l4^_oQHY}j?vsM\rtsbX}PpVDN,]N{,4PC`|!O&|9xzO\n.a&BFHPKmr(5OL\"1j{G}Xc!$bHF$Awt<P|6f\r^qr{kDzjgv\\nPPOY~I\']^nDt\rJ{B-Q1<S\'ccW\\[|@JbAN/c\nGB:GlxLjLw\'viRKl*-", 256);
	initstate(time(NULL) + call_cnt, iv, 256);
	srandom(time(NULL) + call_cnt);
	return random();
}

User* init_user()
{
	User *user = (User *)malloc(sizeof(User));
	*((char *)&(user->cookie) + 0) = generate_cookie() & 0xff;
	*((char *)&(user->cookie) + 1) = generate_cookie() & 0xff;
	*((char *)&(user->cookie) + 2) = generate_cookie() & 0xff;
	*((char *)&(user->cookie) + 3) = generate_cookie() & 0xff;
	saved_cookie = user->cookie;
	
	user->money = 1000;
	user->cashback = 0.01;
	user->name = NULL;
	user->free_space = MAX_ITEMS;
	for (int i = 0; i < MAX_ITEMS; ++i)
	{
		user->items[i].is_free = 1;
		user->items[i].type = NONE;
		user->items[i].item = NULL;
	}
	
	return user;
}

void set_name(User *user, char *newname)
{
	if (user->name != NULL)
		free(user->name);
	
	user->name = (char *)calloc(128, sizeof(char));
	strncpy(user->name, newname, 127);
}