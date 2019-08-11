#pragma once

#include <stdlib.h>
#include <stdio.h>

void read_flag()
{
	FILE *fp = fopen("/service/flag.txt", "r");
	if (fp == NULL) {
		perror("Unable to open file! Please contact administrator.");
		fflush(NULL);
		exit(1);
	}
	
	char chunk[128];
	printf("%s", "Congratulations! Here is your flag: ");
	fflush(NULL);
	fgets(chunk, sizeof(chunk), fp);
	fputs(chunk, stdout);
	fflush(NULL);
	puts("");
	fflush(NULL);
	fclose(fp);
}