#pragma once

#include <vector>
#include <string>
#include <iomanip>
#include <string.h>

#include "Day.h"
#include "Note.h"

class Calender
{
private:
	struct Month
	{
		std::string month_name;
		std::vector <Day*> days;
	};
	struct Selected
	{
		Month *currentMonth = nullptr;
		Day   *currentDay = nullptr;
		
		int selected_day   = 1;
		int selected_month = 1;
	};
	std::vector<Month*> months;
	Selected selected;
	
	public:
	Calender();
	~Calender();
	void print();
	void set_date(int day, int month);
	Day* get_day(int day, int month);
	int get_selected_day();
	int get_selected_month();
	void copy_notes(int old_day, int old_month, int new_day, int new_month);
	void create_note(int selected_day, int selected_month, char *note_name, char *note_content);
	std::vector<Note> get_notes(int selected_day, int selected_month);
};