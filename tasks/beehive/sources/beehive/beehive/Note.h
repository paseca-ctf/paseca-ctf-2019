#pragma once

#include <iostream>
#include <string>

class Note
{
private:
	char *name;
	char *content;
	bool is_free;
public:
	Note(char *name, char *content);
	~Note();
	void print();
	void set_name(char *name);
	void set_content(char *content);
	void set_is_free(bool is_free);
	char *get_name();
	char *get_content();
	bool get_is_free();
};