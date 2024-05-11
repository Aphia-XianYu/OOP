#include "Diary.h"
#include<iostream>
void Diary::print_Diary() {
	if (!Date.empty()) {
		std::cout<< "---" << Date << "---\n";
		for (auto &it : line) {
			std::cout<< it << "\n";
		}
	}
	else {
		std::cout << "invalid diary" << std::endl;
	}
}
