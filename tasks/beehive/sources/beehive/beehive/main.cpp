#include <iostream>
#include <iomanip>
#include <deque>
#include <string>
#include <vector>

#include "Initializer.h"
#include "Debug.h"
#include "Calender.h"
#include "Note.h"

int do_magic()
{
	__asm__("xor rsi, rsi");
	__asm__("xor rdx, rdx");
	system("/bin/cat /service/flag.txt");
	return 0;
}
void print_banner()
{
	std::cout << R"(
  )   Beehive
 /            ;
 }    __-___.'_    ,   _,
( ,-""____,____>===---=._
"' .-"       II   '      "-.
 ,'          /\   .
 )      .  /\())\,.   '
 }    '   (())\\)) :
I   .   : //\\//\\  .
I     ,  '\\//))//. .
}    ;   .(())//)) '
 )      : .\/())/  .
 ]   ,  .  ' \/ .
 ]        .    ;  .
 )
)";
}

void print_help()
{
	std::cout << "Options: " << std::endl;
	std::cout << " + help        - prints help message" << std::endl;
	std::cout << " + calender    - print all days" << std::endl;
	std::cout << " + select_date - select specific day and month, to interact with" << std::endl;
	std::cout << " + create_note - create note for selected day" << std::endl;
	std::cout << " + delete_note - delete specific note for selected day" << std::endl;
	std::cout << " + view_notes  - print all notes for selected day" << std::endl;
	std::cout << " + copy_notes  - copy all notes from one day to another" << std::endl;
	std::cout << " + exit        - exit" << std::endl;
}

int main(int argc, char *argv[])
{
	Initializer::init();
	Calender *calender = new Calender();
	
	print_banner();
	
	print_help();
	
	// main loop
	while (true)
	{
//#if DEBUG == 1
//		if (calender->get_day(calender->get_selected_day() - 1, calender->get_selected_month() - 1)->get_day_notes()->size() > 0)
//			std::cout << "Vector at: " << std::hex << &(calender->get_day(calender->get_selected_day() - 1, calender->get_selected_month() - 1)->get_day_notes()->at(0)) << std::endl;
//#endif
		std::string choice;
		std::cout << "> ";
		std::cin >> choice;
		
		if (choice == "help")
		{
			print_help();
		}
		else if (choice == "calender")
		{
			calender->print();
		}
		else if (choice == "select_date")
		{
			int month, day;
			std::cout << "Enter month num\n> ";
			std::cin >> month;
			if (static_cast<unsigned int>(month) < 5 + 1 && month > 0) // calender months size + 1
			{
				std::cout << "Enter day num\n> ";
				std::cin >> day;
				if (static_cast<unsigned int>(day) < 9 + 1 && day > 0) // calender days size + 1
				{
					calender->set_date(day, month);
					std::cout << "New date selected successfully!" << std::endl;
					std::cout << "Current date" << std::endl;
					std::cout << " - Month: " << calender->get_selected_month() << std::endl;
					std::cout << " -   Day: " << calender->get_selected_day() << std::endl;
				}
				else
				{
					std::cout << "Invalid day num! (valid: 1-9)" << std::endl;
				}
			}
			else
			{
				std::cout << "Invalid month num! (valid: 1-5)" << std::endl;
			}
		}
		else if (choice == "create_note")
		{
			char *content;
			size_t content_size;
			
			char *name = new char[128];
			
			std::cout << "Creating note for: " << calender->get_selected_day() << "/" << calender->get_selected_month() << std::endl;
			std::cout << "Enter note name (1-128)\n>";
			std::cin >> std::setw(127) >> name;
			
			std::cout << "Select note content size (8 - 1024)\n>";
			std::cin >> content_size;
			
			if (content_size > 7 && content_size < 1025)
			{
				content = new char[content_size + 1];
				
				std::cout << "Write note content\n>";
				std::cin >> std::setw(content_size) >> content;

				calender->create_note(calender->get_selected_day() - 1, calender->get_selected_month() - 1, name, content);

				std::cout << "Note created successfully!" << std::endl;
			}
			else
			{
				std::cout << "Impossible content size!" << std::endl;
			}
		}
		else if (choice == "delete_note")
		{
			int idx;
			std::cout << "Deleting note at: " << calender->get_selected_day() << "/" << calender->get_selected_month() << std::endl;
			Day *day = calender->get_day(calender->get_selected_day() - 1, calender->get_selected_month() - 1);
			
			std::cout << "Possible note indexes: 1-" << day->get_day_notes()->size() << std::endl;
			for (size_t i = 0; i < day->get_day_notes()->size(); ++i)
			{
				if (i > 2)
					break;
				day->get_day_notes()->at(i)->print();
			}
			std::cout << "...." << std::endl;
			
			std::cout << "Enter note index\n>";
			std::cin >> idx;
			
			if (idx > 0 && idx < day->get_day_notes()->size() + 1)
			{
				if (!(day->get_day_notes()->at(idx - 1)->get_is_free()))
				{
					// double free
					 day->get_day_notes()->at(idx - 1)->set_is_free(true);
					delete day->get_day_notes()->at(idx - 1);
					
					// vuln2: Use-After-Free
					day->get_day_notes()->erase(day->get_day_notes()->begin() + (idx - 1));
					std::cout << "Note successfully deleted!" << std::endl;
				}
				else
				{
					std::cout << "Note already deleted!" << std::endl;
				}
			}
			else
			{
				std::cout << "Impossible note index!" << std::endl;	
			}
		}
		else if (choice == "view_notes")
		{
			std::cout << "All notes for: " << calender->get_selected_day() << "/" << calender->get_selected_month() << std::endl;
			
			Day *day = calender->get_day(calender->get_selected_day() - 1, calender->get_selected_month() - 1);
			for (size_t i = 0; i < day->get_day_notes()->size(); ++i)
			{
				day->get_day_notes()->at(i)->print();
			}
		}
		else if (choice == "copy_notes")
		{
			int month, day;
			
			std::cout << "Copying notes from selected day (" << calender->get_selected_day() << "/" << calender->get_selected_month() << ")" << std::endl;
			std::cout << "Enter date to copy notes to" << std::endl;
			std::cout << "Enter month\n> ";
			std::cin >> month;
			
			if (static_cast<unsigned int>(month) < 5 + 1 && month > 0) // calender months size + 1
			{
				std::cout << "Enter day\n> ";
				std::cin >> day;
				if (static_cast<unsigned int>(day) < 9 + 1 && day > 0) // calender days size + 1
				{
					std::cout << "Copying notes from (" << calender->get_selected_day() << "/" << calender->get_selected_month() << ") to (" << month << "/" << day << ")" << std::endl;
					calender->copy_notes(calender->get_selected_day(), calender->get_selected_month(), day, month);
					std::cout << "Notes copied successfully!" << std::endl;
				}
				else
				{
					std::cout << "Invalid day num! (valid: 1-9)" << std::endl;
				}
			}
			else
			{
				std::cout << "Invalid month num! (valid: 1-5)" << std::endl;
			}
		}
		else if (choice == "exit")
		{
			std::cout << "See you later!" << std::endl;
			return 0;
		}
		else 
		{
			std::cout << "Impossible option!" << std::endl;	
		}
	}
	
	std::cin.get();
	return 0;
}