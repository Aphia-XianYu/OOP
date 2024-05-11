#include"Diarybook.h"
#include<iostream>
/*The program need you to enter the date properly.
* And then you are allowed to input the contents of a diary unitil you enter "." or  EOF
* It you will ask if you intend to add more dairy.
*/

//ask if you need to add more diary

int main() {
	Diarybook book;

	book.init_book();
	//add a diary and after that determine if you need to add extra dairys.
	if (book.write_Diary()) {
		if(book.rewrite_book())
			std::cout << "add sucessful.\n";
	}
	else {
		std::cout << "add failed.\n" << std::endl;
	}
	system("pause");
	
}