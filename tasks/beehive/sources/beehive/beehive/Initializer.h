#pragma once

#include <iostream>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

class Initializer
{
public:
	static void init();
	static void handler();
};