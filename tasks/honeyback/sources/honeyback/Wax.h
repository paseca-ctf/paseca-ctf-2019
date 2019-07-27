#pragma once

#include <string.h>

typedef struct
{
	int price;
	int is_selled;
	char desc[84];
} Wax;

void init_wax(Wax *wax);