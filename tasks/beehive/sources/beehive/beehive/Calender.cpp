#include "Calender.h"

Calender::Calender()
{
	std::vector<std::string> month_names = {"January", "February", "March", "April", "May"};
	std::vector<std::string> day_names = { "Monday", "Tuesday", "Wednesday", "Thursday"};
	
	for (size_t i = 0; i < month_names.size(); ++i)
	{
		Month *currentMonth = new Month; 
		currentMonth->month_name = month_names[i % month_names.size()];
		
		for (size_t j = 0; j < 9; ++j)
		{
			currentMonth->days.push_back(new Day(day_names[j % day_names.size()], j + 1));
		}
		
		months.push_back(currentMonth);
	}
	
	this->selected.currentMonth = months[0];
	this->selected.currentDay   = months[0]->days[0];
}

Calender::~Calender()
{
	for (size_t i = 0; i < months.size(); ++i)
	{
		for (size_t j = 0; j < months[i]->days.size(); ++j)
			delete months[i]->days[j];
		delete months[i];
	}
}

void Calender::print()
{
	for (size_t j = 0; j < months.size(); ++j)
	{
		std::cout << "======== " << months[j]->month_name << " [" << j + 1 << "] ========" << std::endl;
		for (Day *day : months[j]->days)
		{
			if (j == (selected.selected_month - 1) && day->get_day_num() == selected.selected_day)
				std::cout << "** " << day->get_day_num() << ". " << std::left << std::setw(11) << ("\"" + day->get_day_name() + "\"") << " [" << day->get_notes_count() << "]" << " **" << std::endl;
			else
				std::cout << day->get_day_num() << ". " << std::left << std::setw(11) << ("\"" + day->get_day_name() + "\"") << " [" << day->get_notes_count() << "]" << std::endl;
		}
		std::cout << std::endl;
	}
}

void Calender::set_date(int day, int month)
{
	if (static_cast<unsigned int>(month) < months.size() + 1)
	{
		selected.currentMonth   = months[month - 1];
		selected.selected_month = month;
		
		if (static_cast<unsigned int>(day) < months[month - 1]->days.size() + 1)
		{
			selected.currentDay   = months[month - 1]->days[day - 1];
			selected.selected_day = day;
		}
	}
}

Day* Calender::get_day(int day, int month)
{
	return months[month]->days[day];
}

int Calender::get_selected_day()
{
	return selected.selected_day;
}


int Calender::get_selected_month()
{
	return selected.selected_month;
}

void Calender::copy_notes(int old_day, int old_month, int new_day, int new_month)
{
	Day *currentDay = months[old_month - 1]->days[old_day - 1];
	Day *newDay     = months[new_month - 1]->days[new_day - 1];
	
	// Vulnerability
	memcpy(newDay->get_day_notes(), currentDay->get_day_notes(), 24);
}

void Calender::create_note(int selected_day, int selected_month, char *note_name, char *note_content)
{
	months[selected_month]->days[selected_day]->add_note(new Note(note_name, note_content));
}

std::vector<Note> Calender::get_notes(int selected_day, int selected_month)
{
	return std::vector<Note>();
}
