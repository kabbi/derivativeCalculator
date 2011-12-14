

#ifndef __C_CALC_ANALYZER_H
#define __C_CALC_ANALYZER_H

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <cmath>
using namespace std;

#include "CCalcExpression.h"

const long double PI=3.1415926535897932384626433832795;
inline double degToRad(double a)
{
	//return a*PI/180;
	return a;
}
inline double radToDeg(double a)
{
	//return a/PI*180;
	return a;
}
inline double sinDeg(double a)
{
	return sin(degToRad(a));
}
inline double cosDeg(double a)
{
	return cos(degToRad(a));
}
inline double tanDeg(double a)
{
	return tan(degToRad(a));
}
inline double ctgDeg(double a)
{
	return 1/tan(degToRad(a));
}
inline double asinDeg(double a)
{
	return radToDeg(asin(a));
}
inline double acosDeg(double a)
{
	return radToDeg(acos(a));
}
inline double atanDeg(double a)
{
	return radToDeg(atan(a));
}
inline double fac(double a)
{
	double rez=1;
	for (int i=1;i<a+1;i++)
		rez*=i;
	return rez;
}
inline double exitt(double a)
{
	exit((int)a);
}

class CCalcAnalyzer
{
private:
	enum Token_value {
		NAME,
		NUMBER,
		END,
		PLUS='+',
		MINUS='-',
		MUL='*',
		DIV='/',
		POWER='^',
		PRINT=';',
		ASSIGN='=',
		FACTORIAL='!',
		LP='(',
		RP=')',
		LSQ='[',
		RSQ=']',
		LCQ='{',
		RCQ='}'
	};
	Token_value curr_tok;
	double number_value;
	string string_value;
	int no_of_errors;
	map<string,double> table;
	typedef double (*pfun) (double);
	map<string,pfun> ftable;

	istringstream str;
public:
	CCalcAnalyzer();
	~CCalcAnalyzer();

	CCalcNode *error(const string&);
	CCalcNode *expr(bool);
	CCalcNode *term(bool);
	CCalcNode *pwr(bool);
	CCalcNode *prim(bool);
	Token_value get_token();

	// analyze and return the root node
	CCalcNode *analyze();

	void setString(string str);
};

#endif