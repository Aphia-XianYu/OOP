#include "Fraction.h"
#include<numeric>
#include<iostream>
#include<string>
#include<sstream>
//function
//using gcd function to simplify a fraction
void Fraction::simplify(){
	int gcd = std::gcd(deno, nume);
	deno = deno / gcd;
	nume = nume / gcd;
}
/*Separate a decimal into a whole number part and a fractional part, 
reduce the fractional part to a fraction plus the whole number part, 
and finally simplify
*/
void Fraction::conver_from_finite_decimal(const std::string& demi) {
	
	std::string num = demi;
	if (num.find(".")!= std::string::npos) {

		auto it = num.find(".");
		std::string int_num = num.substr(0, it);//interger part
		std::string demi_num = num.substr(it+1, num.size());// fractional part
		//convert to fraction
		nume = std::stoi(int_num) * std::pow(10, demi_num.size()) + std::stoi(demi_num);
		deno = std::pow(10, demi_num.size());

		simplify();
	}
}
std::string Fraction::To_string() {
	return std::to_string(nume) + "/" + std::to_string(deno);
}
//ctor
Fraction::Fraction(const Fraction& item) {
	if (item.deno != 0) {
		nume = item.nume;
		deno = item.deno;
		simplify();
	}
	else {
		throw std::invalid_argument("Invalid denominator");
	}
}
//compound assignment operator
Fraction Fraction::operator= (const Fraction& other) {
	deno = other.deno;
	nume = other.nume;
	return *this;
}
Fraction Fraction::operator+=(const Fraction& other) {
	nume = nume * other.deno + other.nume * deno;
	deno = deno * other.deno;
	simplify();//化简
	return *this;
}
Fraction Fraction::operator-=(const Fraction& other) {
	nume = nume * other.deno - other.nume * deno;
	deno = deno * other.deno;
	simplify();//化简
	return *this;
}
Fraction Fraction::operator/=(const Fraction& other) {
	deno = deno * other.nume;
	nume = nume * other.deno;
	simplify();//化简
	return *this;

}
Fraction Fraction::operator*=(const Fraction& other) {
	deno = deno * other.deno;
	nume = nume * other.nume;
	simplify();//化简
	return *this;
}
//stream inserter and extractor
std::ostream& operator<<(std::ostream& os, const Fraction&item) {
	os << item.nume << "/" << item.deno;
	return os;
}
std::istream& operator>>(std::istream& is, Fraction& item) {
	std::string line;
	is >> line;
	auto pos =line.find("/");
	if (pos != std::string::npos) {
		item.nume = std::stoi(line.substr(0, pos));
		item.deno = std::stoi(line.substr(pos + 1, line.length()));
	}
	return is;
}
//Arithmetical operators
Fraction operator+(const Fraction& rhs, const Fraction& lhs) {
	Fraction item = rhs;
	item += lhs;
	return item;
}
Fraction operator-(const Fraction& rhs, const Fraction& lhs) {
	Fraction item = rhs;
	item -= lhs;
	return item;
}
Fraction operator*(const Fraction& rhs, const Fraction& lhs) {
	Fraction item = rhs;
	item *= lhs;
	return item;
}
Fraction operator/(const Fraction& rhs, const Fraction& lhs) {
	Fraction item = rhs;
	item /= lhs;
	return item;
}
//Relational operators
bool operator< (const Fraction& rhs, const Fraction& lhs) {
	Fraction item1 = rhs;
	Fraction item2 = lhs;

	return (item1.nume * item2.deno )< (item2.nume * item1.deno);
		
}
bool operator<=(const Fraction& rhs, const Fraction& lhs) {
	return rhs < lhs || rhs == lhs;
}
bool operator==(const Fraction& rhs, const Fraction& lhs) {
	Fraction item1 = rhs;
	Fraction item2 = lhs;

	return (item1.deno == item2.deno) && (item1.nume == item1.nume);
}
bool operator!=(const Fraction& rhs, const Fraction& lhs) {
	return !(rhs == lhs);
}
bool operator>=(const Fraction& rhs, const Fraction& lhs) {
	return !(rhs < lhs);
}
bool operator> (const Fraction& rhs, const Fraction& lhs) {
	return !(rhs <= lhs);
}

