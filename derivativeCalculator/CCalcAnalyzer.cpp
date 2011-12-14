// calc_analyze.cpp : Defines the entry point for the console application.
//

#include "CCalcAnalyzer.h"

CCalcAnalyzer::CCalcAnalyzer() : curr_tok(PRINT)
{
	ftable["sin"]=sinDeg;
	ftable["cos"]=cosDeg;
	ftable["tg"]=tanDeg;
	ftable["ctg"]=ctgDeg;
	ftable["asin"]=asinDeg;
	ftable["acos"]=acosDeg;
	ftable["atan"]=atanDeg;
	ftable["log"]=log;
	ftable["log10"]=log10;
	ftable["exp"]=exp;
	ftable["sqrt"]=sqrt;
	ftable["fac"]=fac;
	ftable["exit"]=exitt;
	table["pi"]=3.1415926535897932384626433832795;
	table["e"]=2.7182818284590452354;
}

CCalcAnalyzer::~CCalcAnalyzer()
{
}

CCalcNode *CCalcAnalyzer::error(const string &s)
{
	no_of_errors++;
	cerr<<"error: "<<s<<'\n';
	return new CCalcNode();
}
CCalcNode *CCalcAnalyzer::expr(bool get)
{
	CCalcNode *left=term(get);
	for (;;)
		switch (curr_tok)
	{
		case PLUS:
			{
				CCalcActionNode *cur=new CCalcActionNode(ACTION_ADD);
				cur->addArgument(left);
				cur->addArgument(term(true));
				return cur;
			}
			break;
		case MINUS:
			{
				CCalcActionNode *cur=new CCalcActionNode(ACTION_SUBTRACT);
				cur->addArgument(left);
				cur->addArgument(term(true));
				return cur;
			}
		default:
			return left;
	}
}
CCalcNode *CCalcAnalyzer::term(bool get)
{
	CCalcNode *left=pwr(get);
	for (;;)
		switch (curr_tok)
	{
		case MUL:
			{
				CCalcActionNode *cur=new CCalcActionNode(ACTION_MULTIPLY);
				cur->addArgument(left);
				cur->addArgument(pwr(true));
				return cur;
			}
			break;
		case DIV:
			{
				CCalcActionNode *cur=new CCalcActionNode(ACTION_DIVIDE);
				cur->addArgument(left);
				cur->addArgument(pwr(true));
				return cur;
			}
		default:
			return left;
	}
}
CCalcNode *CCalcAnalyzer::pwr(bool get)
{
	CCalcNode *left=prim(get);
	for (;;)
		switch (curr_tok)
	{
		case POWER:
			{
				CCalcActionNode *cur=new CCalcActionNode(ACTION_RAISE);
				cur->addArgument(left);
				cur->addArgument(prim(true));
				return cur;
			}
		default:
			return left;
	}
}
CCalcNode *CCalcAnalyzer::prim(bool get)
{
	if (get) get_token();

	switch (curr_tok)
	{
	case NUMBER:
		{
			double v=number_value;
			get_token();
			return new CCalcConstantNode(v);
		}
	case NAME:
		{
			Token_value cur_tok=get_token();
			if (cur_tok==LP)
			{
				string str=string_value;
				CCalcNode *e=expr(true);
				get_token();

				CCalcActionNode *cur=new CCalcActionNode(ACTION_FUNCTION, str);
				cur->addArgument(e);
				return cur;
			}
			//if (cur_tok==ASSIGN) v=expr(true);
			return new CCalcVariableNode(string_value);
		}
	/*case MINUS:
		return -prim(true);
	case FACTORIAL:
		{
			double arg=prim(true);
			double rez=1;
			for (int i=1;i<arg+1;i++)
				rez*=i;
			return rez;
		}
	case LP:
		{
			double e=expr(true);
			if (curr_tok!=RP) return error("no closing bracket");
			get_token();
			return e;
		}
	case LSQ:
		{
			double e=expr(true);
			if (curr_tok!=RSQ) return error("no closing bracket");
			get_token();
			return floor(e);
		}
	case LCQ:
		{
			double a=1;
			double e=expr(true);
			if (curr_tok!=RCQ) return error("no closing bracket");
			get_token();
			return modf(e,&a);
		}
		break;*/
	default:
		return error("primary expression required");
	}
}
CCalcAnalyzer::Token_value CCalcAnalyzer::get_token()
{
	char ch;
	do
	{
		if (!str.get(ch)) return curr_tok=END;
	}while (ch!='\n' && isspace(ch));
	switch (ch)
	{
	case ';':
	case '\n':
		return curr_tok=PRINT;
	case '!':
	case '^':
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
	case '[':
	case ']':
	case '{':
	case '}':
	case '=':
		return curr_tok=Token_value(ch);
	case '0': case '1': case '2': case '3': case '4':
	case '9': case '8': case '7': case '6': case '5':
	case '.':
		str.putback(ch);
		str>>number_value;
		return curr_tok=NUMBER;
	default:
		if (isalpha(ch))
		{
			string_value=ch;
			while (str.get(ch) && isalnum(ch)) string_value.push_back(ch);
			str.putback(ch);
			return curr_tok=NAME;
		}
		error("expression error");
		return curr_tok=PRINT;
	}
}

void CCalcAnalyzer::setString(string s)
{
	str.str();
	str.str(s);
}

CCalcNode *CCalcAnalyzer::analyze()
{
	get_token();
	return expr(false);
}

/*
int _tmain(int argc, _TCHAR* argv[])
{

	while (cin)
	{
		get_token();
		if (curr_tok==END) break;
		if (curr_tok==PRINT) continue;
		cout<<expr(false)<<'\n';
	}
	return no_of_errors;
}

*/