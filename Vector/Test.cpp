#include"Vector.h"
#include<string>
#include<iostream>
#include<sstream>


int main() {
	std::cout << "Test my Vector\n";
	std::cout << "-----------------\n";


	std::cout << "create a new Vector\n";
	Vector<std::string> V;//test creating a new empty Vector
	int i;
	std::string line,word;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	while (iss>>word) {
		V.push_back(word);//test push_back function
	}
	std::cout << "the size of V is " << V.size() << std::endl;//test size function
	std::cout << std::endl;


	Vector<std::string> V1(V);      //test copy constructor;
	std::cout << "V1 copys V ,Let's check what is in V1\n";
	for (i = 0; i < V1.size(); i++) {
		std::cout << V1[i] << " ";  //test the operator[];
	}
	std::cout << std::endl;
	V1.clear(); //test clear function;
	std::cout << "clear V1 ,Let's check whether V1 is empty \n";
	if (V1.empty())
		std::cout << "It is empty!:)\n";
	else
		std::cout << "No empty!!:(\n";
	std::cout << "let's check function at\nThe result of V.at(0): ";
	std::cout << V.at(0) << std::endl; //test the function of "at()";
	std::cout << std::endl;


	std::cout << "Let's create a vector with known size \nPlease input the size of a vector :";
	int size;
	std::cin >> size;
	Vector<std::string> V2(size);    //test the construct Vector with size;
	std::cout << "Input the contents: \n";
	for (i = 0; i < size;i++) {
		std::cin >> line;
		V2.push_back(line);      //push the value into V; test the "push_back(x)" function;
	}
	std::cout << "The size of V2 is " << V2.size() << std::endl;
	std::cout << "Output V2 " << std::endl;
	for (i = 0; i < V2.size(); i++) {
		std::cout << V2[i] << " ";
	}
	std::cout << std::endl;

	// test a Vector contains the object Vector
	std::cout << "\nThen let's test a Vector contains Vectors" << std::endl;
	Vector<Vector<std::string>>Vec;
	Vec.push_back(V);
	Vec.push_back(V2);
	for (int i = 0; i < Vec[0].size(); i++)
		std::cout << Vec[0][i] << " ";
	return 0;
}

