#include <iostream>
#include <vector>  
#include <string>  
#include <regex>   
using namespace std;

class Stack_Mac
{
private:
	vector <int> Var, Machine_Stack;
	vector <string> Stack, ID;
	vector <bool> SRRF;
	int OP1, OP2, i= 1;

	void Main()
	{

		regex
			INT("[0-9]+"),
			ID("[�-��-�]*");

		for (i=1; i < Stack.size(); i++)
		{
			if (Stack[i] == "=") Equals();
			else if ((Stack[i] == "+") || (Stack[i] == "-") || (Stack[i] == "*") || (Stack[i] == "/")) OP();
			else if ((Stack[i] == "<") || (Stack[i] == ">") || (Stack[i] == "==")) LogicOP();
			else if (Stack[i] == "L") Goto_();
			else if (Stack[i] == "@") Goto();
			else if (regex_match(Stack[i], INT)) Integ();
			else if (regex_match(Stack[i], ID)) Integ_Name();
		}

	}




	void Equals()
	{
		OP1 = Stack_or_RAM();
		Var[Machine_Stack.back()] = OP1;
		Machine_Stack.pop_back();
		SRRF.pop_back();
		return;
	}

	void LogicOP()
	{
		OP1 = Stack_or_RAM();
		OP2 = Stack_or_RAM();
		Machine_Stack.push_back(Logic_ret(Stack[i][0]));
		SRRF.push_back(0);
		return;
	}

	bool Logic_ret(char Ch)
	{
		switch (Ch)
		{
		case '<': return (OP2 < OP1);
		case '>': return (OP2 > OP1);
		case '=': return (OP2 == OP1);
		}
	}

	void OP()
	{
		OP1 = Stack_or_RAM();
		OP2 = Stack_or_RAM();
		switch (Stack[i][0])
		{
		case '+': Machine_Stack.push_back(OP1 + OP2); break;
		case '-': Machine_Stack.push_back(OP2 - OP1); break;
		case '*': Machine_Stack.push_back(OP2 * OP1); break;
		case '/': Machine_Stack.push_back(OP2 / OP1); break;
		}
		SRRF.push_back(0);
		return;
	}

	int Stack_or_RAM() //���������� �������� �� ����� ��� RAM
	{
		int Buff = 0;

		if (SRRF.back() == 0) Buff = Machine_Stack.back();

		else Buff = Var[Machine_Stack.back()];

		Machine_Stack.pop_back();
		SRRF.pop_back();

		return Buff;
	}

	void Integ_Name() //������ �������� �� RAM � ����
	{
		for (int j = 1; j < ID.size(); j++)
		{
			if (ID[j] == Stack[i])
			{
				Machine_Stack.push_back(j);
				SRRF.push_back(1);
				return;
			}
		}
		cout << "������ ����������, ���������� �� ����������������"<<'\n';
		system("pause");
		exit(0);
	}

	void Integ() //������ ����� � ����
	{
		Machine_Stack.push_back(stoi(Stack[i]));
		SRRF.push_back(0);
		return;
	}


	void Goto() //����������� ������� �� �����
	{
		i = stoi(Stack[i + 1]);
		return;
	}

	void Goto_() //�������� ������� �� ���
	{
		if (Machine_Stack.back() == 0) Goto();
		else i++;
		Machine_Stack.pop_back();
		SRRF.pop_back();
		return;
	}

public:

	vector<int> Output_RAM(vector <string> In_Stack, vector <string> Variable_Name, vector <int> Variable)
	{
		Stack = In_Stack; ID = Variable_Name; Var = Variable;
		Main();
		return Var;
	}

};