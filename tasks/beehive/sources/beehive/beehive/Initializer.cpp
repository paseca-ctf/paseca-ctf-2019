#include "Initializer.h"

void Initializer::init()
{
	setbuf(stdin, 0LL);
	setbuf(stdout, 0LL);
	setbuf(stderr, 0LL);
	alarm(120);
	signal(SIGALRM, (__sighandler_t)handler);
}

void Initializer::handler()
{
	std::cout << "Time is up!" << std::endl;
	exit(0);
}