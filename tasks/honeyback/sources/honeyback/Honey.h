#pragma once

#include <string.h>

typedef struct
{
	int price;
	int is_selled;
	char desc[64];
} Honey;

void init_honey(Honey *honey);