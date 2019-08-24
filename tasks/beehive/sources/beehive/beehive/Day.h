#pragma once

#include <vector>
#include <string>

#include "Note.h"

class Day
{
private:
	int day_num;
	int notes_count = 0;
	std::string name;
	std::vector<Note *> *day_notes;
public:
	Day(const std::string &dayname, int num);
	~Day();
	
	int get_day_num();
	int get_notes_count();
	std::string get_day_name();
	std::vector<Note*>* get_day_notes();
	void add_note(Note *note);
};