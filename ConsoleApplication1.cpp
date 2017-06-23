// ConsoleApplication1.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "Lexer.h"
#include "Parser.h"
#include "StackMac.h"
#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");
	cout << "������ ��� � ����������� �����. ��������� ������� ��������� � ������: {���� ���������}" << '\n';
	cout << "��������� ���������:" << '\n';
	cout << "����/����-���� ����� ��� � if" << '\n';
	cout << "����/����-���� ����� ��� � While" << '\n';
	cout << "������/������-���� ����� ��� � do" << '\n';
	cout << "�����/�����-���� ����� ��� � else" << '\n';
	cout << "���������� - ����� ����� �� �������. ����������� ���������������� ���������� � ������ ��������� �������:" << '\n';
	cout << "����� /*�������� ����������*/=/*�������� ����������*/"<<'\n';
	system("pause");
	system("notepad.exe Code.txt");

	ifstream fin("Code.txt"); 
	string str, sbuff;   
	while (fin >> sbuff) str += sbuff; 
	fin.close(); 
	system("cls");
	LEXER lex;
	vector <string> token = lex.Lexem_o(str);
	vector <int> token_id = lex.Lexem_ID_o(str);
	bool token_err = lex.Error_o(str);
	cout << str << '\n';
	cout << "������:\n" << "�  | �������\n============\n";

	for (int i = 1; i < token_id.size(); i++) 
	{
		cout << token_id[i];
		if (token_id[i] < 10) cout << "  | ";
		else cout << " | ";
		cout << token[i] << '\n';
	}
	system("pause");
	system("cls");
	token_id.push_back(18);
	Parser PARSER;
	PARSER.Load(token, token_id);
	vector <string> Pars = PARSER.Output();
	vector <int> Variable = PARSER.Ret_Var();
	vector <string>  Variable_Name = PARSER.Ret_Var_N();


	cout << "��������������� ����������:\n";

	for (int i = 1; i < Variable.size(); i++)
	{
		cout << Variable_Name[i] << " | " << Variable[i] << '\n';
	}
	system("pause");
	cout << "�����:\n";

	for (int i = 1; i < Pars.size(); i++) 
	{
		cout << Pars[i] << " || ";
	}
	cout << '\n';
	system("pause");

	Stack_Mac Mac;
	vector <int> Mac_Var = Mac.Output_RAM(Pars, Variable_Name, Variable);

	cout << "\n\n����������:\n";

	for (int n = 1; n < Mac_Var.size(); n++) //����� �������� � ������� ����� ��������
	{
		cout << Variable_Name[n] << " | " << Mac_Var[n] << '\n';
	}

	cout << '\n';

	system("pause");
	return;
}


