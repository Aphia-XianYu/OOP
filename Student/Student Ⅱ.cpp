#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<sstream>
#include<algorithm>
#include<numeric>
#include<iomanip>
#include<memory>
#include<set>
#include<fstream>

using std::vector; using std::map;
using std::string; using std::set;
using std::left; using std::setw;

class Student {
private:
	map<string, int> courses = { };
	string name;
	size_t id;

public:
	Student() = default;
	Student(map<string,int> stu_course,string stu_name,int stu_id):courses(stu_course),name(stu_name),id(stu_id){}
	~Student() { };

	using Ptr = std::shared_ptr<Student>;
	float get_average();
	map<string, int> get_courses();
	bool check_course(string&);
	int get_score(string&);
	void print_info();
	size_t get_name() { return name.size(); }

};
float Student::get_average() {
	int scores = 0;
	for (auto &it : courses) {
		scores += it.second;
	}
	return (scores * 1.0 / courses.size());
}
map<string, int> Student::get_courses() {
	return courses;
}
bool Student::check_course(string &s) {
	return (courses.find(s) != courses.end());
}
int Student::get_score(string& s) {
	if (check_course(s)) {
		return courses[s];
	}
	else {
		throw std::invalid_argument(s);
	}
}
void Student::print_info() {
	std::cout <<left<<setw(5)<< id << name;
}//print the id and name of each student

void print_title(const set<string> &course) {
	std::cout << "no" <<setw(8) << "name ";
	std::cout << setw(4)<<" ";
	for (auto &s : course) {
		std::cout <<left<<setw(10)<< s;
	}// print all courses
	std::cout <<setw(10)<<"average" << std::endl;
}

void print_student( vector<std::shared_ptr<Student>> &students,  const set<string> &course) {
	for (auto &it : students) {
		it->print_info();
		std::cout << setw(9-it->get_name()) << "";

		for (string obj : course) {//print socre
			if (it->check_course(obj)) {
				std::cout<< left<<setw(10) << it->get_score(obj);
			}
			else {
				std::cout << setw(10)<<"";
			}
		}

		std::cout<<setw(10) << left<<it->get_average()<<std::endl;
	}
}

void print_ave(const vector<float>&average) {
	std::cout <<setw(14)<< "     average"<<setw(10);
	for (auto it : average)
		std::cout << it<<setw(10);
	std::cout << std::endl;

}//print the average scores of each course
void print_min(const vector<vector<int>::iterator>& min) {
	std::cout <<setw(14)<< "     min"<<setw(10);
	for (auto &it : min) {
		std::cout << *it<<setw(10);
	}
	std::cout << std::endl;
}//print the minimum scores of each course
void print_max(const vector<vector<int>::iterator>& max) {
	std::cout <<setw(14)<< "     max" <<setw(10);
	for (auto& it : max) {
		std::cout << *it << setw(10);
	}
	std::cout << std::endl;
}//print the maximum scores of each course
void print_scores(set<string>&name,map<string,vector<int>>& score) {
	vector<vector<int>::iterator>max;
	vector<vector<int>::iterator>min;
	vector<float>average;

	for (auto &it : name) {
		max.emplace_back(std::max_element(score[it].begin(),score[it].end()));
		min.emplace_back(std::min_element(score[it].begin(), score[it].end()));
		average.emplace_back(
			std::accumulate(score[it].begin(), score[it].end(), 0)*1.0/ score[it].size());
	}

	print_ave(average);
	print_min(min);
	print_max(max);
}

int main_stu() {
	vector<std::shared_ptr<Student>> students;//record entered students
	set<string> course_name;//record entered courses
	map<string, vector<int>> course_score; //record all grades related to the respective courses.
	int i = 1;//student id

	std::ifstream file("student.txt");
	string line;

	while(std::getline(file,line)) {

		std::string name, subject;
		map<string, int> stu_courses;
		int score;

		if (line.empty())//break when stop inputing
			break;

		std::stringstream iss(line);
		iss >> name;
		while (iss >> subject >> score) {

			if (course_name.empty()) {
				course_name.insert(subject);
				course_score.insert({ subject, vector<int>() }); 
				stu_courses.insert({ subject, score });
				course_score[subject].emplace_back(score);
			}//basic case
			else {

				if (!course_name.count(subject)) {
					course_name.insert(subject);
					course_score.insert({ subject, vector<int>() });
				}//Create a new course if it doesn't exist

				stu_courses.insert({ subject, score });
				course_score[subject].emplace_back(score);
			}
		}
			
		students.emplace_back(std::make_shared<Student>(stu_courses, name, i++));

		}

	print_title(course_name);//print title
	print_student(students, course_name);//print student's infomation including name id and grades for each course
	print_scores(course_name,course_score);//print the maximum, minimum, and average scores for each course.



	return 0;
}

