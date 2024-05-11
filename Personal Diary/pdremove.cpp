#include"Diarybook.h";
#include<string>
#include<iostream>
/*find the diary and then delete it.
*/

bool delete_diary(Diarybook* book) {
	std::string line;
	book->show_diary_list();
	std::cout << "Input the date you want to delete\nE.g. 1897-05-20\n";
	std::cin >> line;
	if (book->check_date(line)) {
		if (book->delete_Diary(line)) {
			std::cout << "0\n";
			book->rewrite_book();//Store the new diary to the data file
			return true;
		}
		else {
			std::cout << "-1\n";
		}
	}
	else {
		std::cout << "Invalid Input\n-1\n";
	}
	return false;
}
int main() {
	Diarybook book;
	book.init_book();

	if (delete_diary(&book)) 
		return 0;
	else
		return -1;
}