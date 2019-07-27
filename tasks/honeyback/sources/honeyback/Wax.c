#include "Wax.h"

void init_wax(Wax *wax)
{
	wax->price = 100;
	wax->is_selled = 0;
	strncpy(wax->desc, "Perfect wax produced by bees.", 30); 
}