

#include <iostream>
using namespace std;

#include "CCalcAnalyzer.h"

int main()
{
	CCalcAnalyzer calc;

	char line[1000];
	while (cin.getline(line, 1000))
	{
		int lineSize=strlen(line);
		line[lineSize]='\n';
		line[lineSize+1]='\0';

		calc.setString(string(line));
		cout<<"Result: "<<calc.calc()<<endl<<endl;
	}

	return 0;
}