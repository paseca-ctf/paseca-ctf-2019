#include "Honey.h"

void init_honey(Honey *honey)
{
	honey->price = 200;
	honey->is_selled = 0;
	strncpy(honey->desc, "Perfect honey produced by bees.", 63); 
}
