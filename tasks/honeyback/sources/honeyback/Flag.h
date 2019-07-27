#pragma once

#include <stdlib.h>
#include <stdio.h>

void read_flag()
{
	FILE *fp = fopen("./flag.txt", "r");
	if (fp == NULL) {
		perror("Unable to open file! Please contact administrator.");
		exit(1);
	}
	
	char chunk[128];
	printf("%s", "Congratulations! Here is your flag: ");
	fgets(chunk, sizeof(chunk), fp);
	fputs(chunk, stdout);
	puts("");
	fclose(fp);
}