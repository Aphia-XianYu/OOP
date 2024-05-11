/*
Write a program that asks you for 10 records of students. Each record consists of a name (w/o space) and scores for three courses (in integer, 1 to 5). 
Output a list as follows and calculate the average score (in float) of each student and each course. Output the lowest and highest score for each course.

no      name    score1  score2  score3  average
1       K.Weng  5       5       5       5
2       T.Dixon 4       3       2       3
3       V.Chu   3       4       5       4
4       L.Tson  4       3       4       3.66667
5       L.Lee   3       4       3       3.33333
6       I.Young 4       2       5       3.66667
7       K.Hiro  4       2       1       2.33333
8       G.Ping  4       4       4       4
9       H.Gu    2       3       4       3
10      J.Jon   5       4       3       4
		average 3.8     3.4     3.6
		min     2       2       1
		max     5       5       5
		*/
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<iomanip>
using std::left; using std::setw; 

struct Student {
	float ave_sco() const
	{
		return (score[0] + score[1] + score[2]) / 3.0f;
	}
	std::string name;
	std::vector<int> score = {0,0,0};
};
std::ostream& operator<<(std::ostream& os, const Student& item) {
	os <<left<<setw(8)<< item.name 
		<< left<<setw(8)<< item.score[0] 
		<<left << setw(8) << item.score[1]
		<< left << setw(8) << item.score[2] 
		<< left << setw(8) << item.ave_sco() << std::endl;
	return os;
}

void print_res(std::vector<int> max, std::vector<int>min, std::vector<float>ave,
	std::vector<Student> students) {
	std::cout << "no" << setw(8) << "name" <<setw(10)<< "score1" <<setw(8)<<
		"score2" <<setw(8) <<"score3"<<setw(9) << "average" << std::endl;
	for (int i = 1; i <= 10; i++) {
		std::cout << left << setw(6) << i << students[i - 1];
	}

	std::cout << setw(6) << "" << "average " << setw(8) << ave[0]
		<< left << setw(8) << ave[1] << left << setw(8) << ave[2] << std::endl;
	std::cout << setw(6) << "" << "min     " << setw(8) << min[0]
		<< left << setw(8) << min[1] << left << setw(8) << min[2] << std::endl;
	std::cout << setw(6) << "" << "max     " << setw(8) << max[0]
		<< left << setw(8) << max[1] << left << setw(8) << max[2] << std::endl;
	
}

int main_student_1() {

	std::cout << "Please Enter 10 students' records \n";

	std::vector<Student> students;
	std::vector<int>max_score = { 0,0,0 };
	std::vector<int>min_score = { 5,5,5 };
	std::vector<float>ave_score = { 0,0,0 };
	
	for (int i = 1; i <= 10; i++) {
		std::string s;
		std::getline(std::cin, s);
		std::stringstream iss(s);
		Student item;

		iss >> item.name >> item.score[0] >> item.score[1] >> item.score[2];
		students.emplace_back(item);

		for (int j = 0; j < 3; j++) {
			max_score[j] = std::max(max_score[j], item.score[j]);
			min_score[j] = std::min(min_score[j], item.score[j]);
			ave_score[j] += item.score[j];
		}

	}

	ave_score[0] = ave_score[0] / 10.0f;
	ave_score[1] = ave_score[1] / 10.0f;
	ave_score[2] = ave_score[2] / 10.0f;
	print_res(max_score, min_score, ave_score, students);

	return 0;

}