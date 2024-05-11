#pragma once
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
/*
* The Diary class is used to store the class, it includes the date and the contents of a diary
* It can help check if the content is empty and get it
* It provide a function to print it. 
*/
class Diary
{
public:
	Diary()=default;
	Diary(const std::string& date, const std::vector<std::string>& para) :
		Date(date),line(para){};//create a diary entity
	std::vector<std::string> get_contents() { return line; }
	bool Diaryempty() { return line.empty(); }
	void print_Diary();


private:
	std::vector<std::string> line = {};//record the diary content
	std::string Date;//yyyy-mm-dd
};

