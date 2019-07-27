#pragma once

#define MAX_ITEMS 10

enum storeItems
{
	NONE,
	WAX,
	HONEY
};

typedef struct
{
	int is_free;
	enum storeItems type;
	void *item;
} ItemBlock;