

#ifndef __C_CALC_EXPRESSION_H
#define __C_CALC_EXPRESSION_H

#include <string>
#include <vector>
using namespace std;

typedef double calcType;

enum CALC_NODE_TYPE
{
	NODE_DUMMY,
	NODE_CONSTANT,
	NODE_VARIABLE,
	//NODE_FUNCTION, not a node actually
	NODE_ACTION
};

enum CALC_ACTION_TYPE
{
	ACTION_ADD,
	ACTION_SUBTRACT,
	ACTION_MULTIPLY,
	ACTION_DIVIDE,
	ACTION_RAISE,
	ACTION_FUNCTION
};

class CCalcNode
{
public:
	CCalcNode() {}
	virtual ~CCalcNode() {}

	virtual CALC_NODE_TYPE getType() {return NODE_DUMMY;}
};

class CCalcActionNode : public CCalcNode
{
private:
	vector<CCalcNode *> arguments;
	CALC_ACTION_TYPE type;
	string fun;
public:
	CCalcActionNode(CALC_ACTION_TYPE type, string fun="") : type(type), fun(fun) {}
	~CCalcActionNode() {}

	void addArgument(CCalcNode *node) {arguments.push_back(node);}
	CCalcNode *getArgument(int index) {return arguments[index];}
	int getArgumentCout() {return arguments.size();}

	CALC_ACTION_TYPE getActionType() {return type;}

	void setFunction(string f) {fun=f;}
	string getFunction() {return fun;}

	CALC_NODE_TYPE getType() {return NODE_ACTION;}
};

class CCalcConstantNode : public CCalcNode
{
private:
	calcType constant;
public:
	CCalcConstantNode(calcType constant=0) : constant(constant) {}
	~CCalcConstantNode() {}

	void setConstant(calcType c) {constant=c;}
	calcType getConstant() {return constant;}

	CALC_NODE_TYPE getType() {return NODE_CONSTANT;}
};

class CCalcVariableNode : public CCalcNode
{
private:
	string var;
public:
	CCalcVariableNode(string var="") : var(var) {}
	~CCalcVariableNode() {}

	void setVariable(string v) {var=v;}
	string getVariable() {return var;}

	CALC_NODE_TYPE getType() {return NODE_VARIABLE;}
};



#endif