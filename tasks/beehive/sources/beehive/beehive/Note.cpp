#include "Note.h"

Note::Note(char *name, char *content)
{
	this->name = name;
	this->content = content;
	this->is_free = false;
}

Note::~Note()
{
	delete name;
	delete content;
}

void Note::print()
{
	// note name
	std::cout << "-------- " << name << " --------" << std::endl; 
	// note conten
	std::cout << content << std::endl;
}
void Note::set_name(char *name)
{
	this->name = name;
}
void Note::set_content(char *content)
{
	this->content = content;
}

void Note::set_is_free(bool is_free)
{
	this->is_free = is_free;
}


char * Note::get_name()
{
	return name;
}


char * Note::get_content()
{
	return content;
}


bool Note::get_is_free()
{
	return is_free;
}
