#pragma once
#include<string>
#include<stdexcept>
class Fraction;

Fraction operator+(const Fraction& rhs, const Fraction& lhs);
Fraction operator-(const Fraction& rhs, const Fraction& lhs);
Fraction operator*(const Fraction& rhs, const Fraction& lhs);
Fraction operator/(const Fraction& rhs, const Fraction& lhs);
bool operator< (const Fraction& rhs, const Fraction& lhs);
bool operator<=(const Fraction& rhs, const Fraction& lhs);
bool operator==(const Fraction& rhs, const Fraction& lhs);
bool operator!=(const Fraction& rhs, const Fraction& lhs);
bool operator>=(const Fraction& rhs, const Fraction& lhs);
bool operator> (const Fraction& rhs, const Fraction& lhs);
std::ostream& operator<<(std::ostream& os, const Fraction&);
std::istream& operator>>(std::istream& is, Fraction&);

class Fraction
{
	friend std::ostream& operator<<(std::ostream& os, const Fraction&);
	friend std::istream& operator>>(std::istream& is, Fraction&);

	friend Fraction operator+(const Fraction& rhs, const Fraction& lhs);
	friend Fraction operator-(const Fraction& rhs, const Fraction& lhs);
	friend Fraction operator*(const Fraction& rhs, const Fraction& lhs);
	friend Fraction operator/(const Fraction& rhs, const Fraction& lhs);

	friend bool operator< (const Fraction& rhs, const Fraction& lhs);
	friend bool operator<=(const Fraction& rhs, const Fraction& lhs);
	friend bool operator==(const Fraction& rhs, const Fraction& lhs);
	friend bool operator!=(const Fraction& rhs, const Fraction& lhs);
	friend bool operator>=(const Fraction& rhs, const Fraction& lhs);
	friend bool operator> (const Fraction& rhs, const Fraction& lhs);
public:
	Fraction() = default;
	Fraction(const Fraction&);
	// Ctor takes two integers as parameters
	Fraction(int nume, int deno) :nume(nume), deno(deno) {
		if (deno==0)
			throw std::invalid_argument("invalid denominator");//the denominator cannot be zero
		simplify();
	};
	//Default ctor
	~Fraction()= default;

	Fraction operator= (const Fraction&);
	Fraction operator+=(const Fraction&);
	Fraction operator-=(const Fraction&);
	Fraction operator/=(const Fraction&);
	Fraction operator*=(const Fraction&);

	inline void simplify();//化简
	void conver_from_finite_decimal(const std::string &);
	inline std::string To_string();
	operator double() const { return nume * 1.0 / deno; }//Typecast to double

private:
	int deno;//denominator分母
	int nume;//numerator分子
};


