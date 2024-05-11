#include"Diarybook.h"
#include"Diary.h"
#include<iostream>
#include<string>
#include<regex>

bool check_date(const std::string& date) {
	std::regex date_regex(R"(\d{4}-\d{2}-\d{2})");
	return std::regex_match(date, date_regex);
}
//get the date belong to the diary you want to print
std::string get_date() {
	std::string date;
	std::cout << "Input date: E.g1897-05-20\n";
	std::cin >> date;
	if (check_date(date))
		return date;
	else
		std::cout << "Invalid date";
		return date;
}
//print the diary
void show_diary(Diarybook* book) {
	std::string date;

	book->show_diary_list();
	std::cout << "Input date: E.g1897-05-20\n";
	std::cin >> date;
	if (book->check_date(date)){
		auto diary = book->get_certain_Diary(date, date);
		diary[date]->print_Diary();
	}
	else {
		std::cout << "Invalid Input";
	}
}

int main() {
	Diarybook book;
	book.init_book();
	show_diary(&book);
	system("pause");
}