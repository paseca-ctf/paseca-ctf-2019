#include "Day.h"

Day::Day(const std::string &dayname, int num)
{
	this->name = dayname;
	this->day_num = num;
	
	day_notes = new std::vector<Note *>();
	this->day_notes->reserve(13);
}

Day::~Day()
{
	for (size_t i = 0; i < day_notes->size(); ++i)
		delete day_notes->at(i);
	delete day_notes;
}

int Day::get_day_num()
{
	return day_num;
}

int Day::get_notes_count()
{
	return day_notes->size();
}

std::string Day::get_day_name()
{
	return name;
}

std::vector<Note*>* Day::get_day_notes()
{
	return day_notes;
}

void Day::add_note(Note *note)
{
	day_notes->push_back(note);
#if DEBUG == 1
	std::cout << "day_notes capacity: " << day_notes->capacity() << std::endl; 
#endif
}