

#include <iostream>
using namespace std;

#include "CCalcAnalyzer.h"

void printTabs(int count)
{
	while(count--)
		cout<<'\t';
}

const char *nodeTypes[]={"NODE_DUMMY", "NODE_CONSTANT", "NODE_VARIABLE", "NODE_ACTION"};
const char *actionTypes[]={"ACTION_ADD", "ACTION_SUBTRACT", "ACTION_MULTIPLY", "ACTION_DIVIDE", "ACTION_RAISE", "ACTION_FUNCTION"};


void printNode(CCalcNode *node, int level)
{
	printTabs(level);
	cout<<nodeTypes[node->getType()]<<endl;
	switch (node->getType())
	{
	case NODE_ACTION:
		{
			CCalcActionNode *act=dynamic_cast<CCalcActionNode*>(node);

			printTabs(level);
			cout<<actionTypes[act->getActionType()]<<endl;

			for (int i=0; i<act->getArgumentCout(); i++)
				printNode(act->getArgument(i), level+1);
		}
		break;
	}
}

int main()
{
	CCalcAnalyzer calc;

	char line[1000];
	while (cin.getline(line, 1000))
	{
		int lineSize=strlen(line);

		if (!lineSize)
			break;

		line[lineSize]='\n';
		line[lineSize+1]='\0';

		calc.setString(string(line));
		CCalcNode *root=calc.analyze();
		printNode(root, 0);
	}

	return 0;
}