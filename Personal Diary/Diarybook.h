#pragma once
#include"Diary.h"
#include<map>
/*This class is used to store the diary I have written.
* And it provide method to add, delete and show the diary
*/

class Diarybook
{
public:
	Diarybook()=default;
	~Diarybook();
	void init_book();//get the exsited dirays from the file
	bool delete_Diary(const std::string&);//delete a diary entity
	bool write_Diary();//add diary to Diarys
	bool rewrite_book();//store the diarys in a data file
	bool check_date(const std::string& date);//check if the date is in the diary 
	std::map<std::string, Diary*>& get_all_Diary() { return Diarys; };
	std::map<std::string, Diary*> get_certain_Diary
		(const std::string&,const std::string&);
	void show_diary_list();//show the diarys in the book
	
private:
	std::map<std::string, Diary*>Diarys;
};
