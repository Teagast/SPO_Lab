// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
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
	cout << "Пишите код в открывшемся файле. Программу следует заключить в скобки: {Тело программы}" << '\n';
	cout << "Доступные операторы:" << '\n';
	cout << "Если/если-тоже самое что и if" << '\n';
	cout << "Пока/пока-тоже самое что и While" << '\n';
	cout << "Делать/делать-тоже самое что и do" << '\n';
	cout << "Иначе/иначе-тоже самое что и else" << '\n';
	cout << "Переменные - любое слово на русском. Обязательно инициализировать переменную в начале следующим образом:" << '\n';
	cout << "Число /*название переменной*/=/*значение переменной*/"<<'\n';
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
	cout << "Токены:\n" << "№  | Лексемы\n============\n";

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


	cout << "Задействованные переменные:\n";

	for (int i = 1; i < Variable.size(); i++)
	{
		cout << Variable_Name[i] << " | " << Variable[i] << '\n';
	}
	system("pause");
	cout << "Полиз:\n";

	for (int i = 1; i < Pars.size(); i++) 
	{
		cout << Pars[i] << " || ";
	}
	cout << '\n';
	system("pause");

	Stack_Mac Mac;
	vector <int> Mac_Var = Mac.Output_RAM(Pars, Variable_Name, Variable);

	cout << "\n\nПеременные:\n";

	for (int n = 1; n < Mac_Var.size(); n++) //Вывод значений в консоль после расчетов
	{
		cout << Variable_Name[n] << " | " << Mac_Var[n] << '\n';
	}

	cout << '\n';

	system("pause");
	return;
}


