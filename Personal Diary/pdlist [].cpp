#include"Diarybook.h"
#include"Diary.h"
#include<iostream>
#include<string>
#include<regex>

/*The user choose to get all diarys or just a part of them
* If you choose the latter, then it requries you to enter the start date and end date.
* And you can get what you want.
* I set some condictions to make sure the input valid
*/
std::map<std::string, Diary*> get_diary(Diarybook* book) {
	//empty map used to return if something wrong
	std::map<std::string, Diary*> nodiary = {};

	//check if the book is empty
	if (book->get_all_Diary().empty()) {
		std::cout << "No diary!\n";
		return nodiary;
	}
	//choose show all diarys or the diarys between the given dates
	std::cout << "Do you want to get all diarys?\nEnter Yes or No\n"
		<< "Enter No to get a subset of diarys\n";
	std::string line;
	std::cin >> line;

	if (line == "Yes") {
		return book->get_all_Diary();
	}else if (line == "No") {//get the certain date.

		book->show_diary_list();

		std::string start_date, end_date;
		std::cout << "Please input date in form of yyyy-mm-dd ,E,g:1897-05-20\n" 
			<< "Input start date: ";
		std::cin >> start_date;

		//get the start and end dates;
		if(book->check_date(start_date)){
			std::cout << "Input end date:";		
			std::cin >> end_date;

			if (book->check_date(end_date)) {

				if (start_date <= end_date)//ensure the start and date are response
					return book->get_certain_Diary(start_date, end_date);
				else
					std::cout << "Invalid start and end dates!";

			}else {
				std::cout << "Invalid end date.";
			}

		}else {
			std::cout << "Invalid begin date.";
		}
	}else {//in case input something wrong
		std::cout << "Invalid Input";
		return nodiary;
	}
}

int main() {
	Diarybook book;
	book.init_book();
	std::map<std::string, Diary*> diarys = get_diary(&book);
	if (!diarys.empty()) {
		for (auto& it : diarys)
			it.second->print_Diary();
	}
	else {
		std::cout << "Failed to get the diarys" << std::endl;
	}
	system("pause");
}