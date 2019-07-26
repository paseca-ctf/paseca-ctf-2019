#pragma once

#include <string.h>

typedef struct
{
	int price;
	int is_selled;
	char desc[128];
} Wax;

void init_wax(Wax *wax);