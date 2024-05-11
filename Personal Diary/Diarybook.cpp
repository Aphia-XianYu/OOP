#include"Diarybook.h"
#include<fstream>
#include<sstream>
#include<regex>
#include<string>
#include<iostream>

Diarybook::~Diarybook() {
	//free memory
	for (auto& it : Diarys) {
		delete it.second;
		it.second = nullptr;
	}
	
}

void Diarybook::init_book() {
	std::ifstream file;
	std::regex date_regex("---(\\d{4}-\\d{2}-\\d{2})---");//it is used to find date.
	std::string line,date;
	std::vector<std::string> lines = {};
	std::smatch match;

	file.open("Diarybook.txt");

	if (file.is_open()) {
		//when it finds the date,then it create a new diary.
		while (std::getline(file, line)) {
			//it finds the line satisfy the regex expression but it is the first diary.
			//So it doesn't need to recreate a diary
			if (std::regex_search(line,match, date_regex)&&date.empty()) {
				date = match[1];
			}//when read other diarys
			else if (std::regex_match(line, date_regex) && !date.empty()) {
				Diary* diary = new Diary(date,lines);
				Diarys[date] = diary;//create a new diary contents.

				lines.clear();
				date = match[1];
			}
			else {
			lines.emplace_back(line);
			}
		}
		//record the last diary
		Diary* diary = new Diary(date, lines);
		Diarys[date] = diary;
	}
	else {
		std::cout << "Failed to open file" << std::endl;
	}

	if (file.is_open())
		file.close();

}

bool Diarybook::write_Diary() {
	std::string line,date;
	std::regex date_regex(R"(\d{4}-\d{2}-\d{2})");
	std::vector<std::string> lines;

	std::cout << "Please input date in form of yyyy-mm-dd, E,g:1897-05-20\n";
	std::cin >> date;
	//check the date if is valid
	if (!(std::regex_match(date, date_regex))) {
		std::cout << "Invalid input\n";
		return false;
	}
	else {
		//get a new diary

		std::cout << "Input contents:\n" ;
		std::cin.get();
		while (std::getline(std::cin, line)&&!line.empty()) {
			lines.emplace_back(line);
			if (line.back() == '.'||std::cin.eof())//find the end of a diary or enter EOF to end reading
				break;	
		}
		if (!(std::cin.eof())&&line.empty()) {//input empty
			std::cout << "Input invalid" << std::endl;
			return false;
		}//create a new diary
		Diary* diary = new Diary(date, lines);
		Diarys[date] = diary;
		return !Diarys[date]->Diaryempty();//retrun if the diary is successfully created
	}

	return false;
	
}

//find the diary needed to be delete, and then delete it
bool Diarybook::delete_Diary(const std::string& date) {
	delete Diarys[date];
	Diarys[date] = nullptr;
	return Diarys[date] == nullptr ? true : false;
}
//get the start date and end date. Then get the diarys between start date and end date
std::map<std::string, Diary*> Diarybook::get_certain_Diary
	(const std::string& startdate, const std::string&enddate) {

	auto Diary_begin = Diarys.lower_bound(startdate);
	auto Diary_end = Diarys.upper_bound(enddate);
	std::map<std::string, Diary*> sub_Diarybook;

	for (auto &it = Diary_begin; it != Diary_end; ++it)
		sub_Diarybook[it->first] = it->second;

	return sub_Diarybook;
}

bool Diarybook::rewrite_book() {
	std::ofstream out("Diarybook.txt");

	if (!out.is_open()) {
		std::cerr << "open file wrong" << std::endl;
		return false;
	}
	//format the date
	for (auto& it : Diarys) {
		if (!(it.second==nullptr)&&(!it.first.empty())) {
			out << "---" << it.first << "---\n";
			for (auto& content : it.second->get_contents()) {
				out << content << "\n";
			}
		}
	}

	out.close();
	return true;
}

bool Diarybook::check_date(const std::string& date) {
	auto& diary = get_all_Diary();
	return diary.find(date) != diary.end();
}

void Diarybook::show_diary_list() {
	auto &diarys = get_all_Diary();
	std::cout << "Diary List:\n";
	for (auto& it : diarys)
		std::cout << it.first << "\n";
}