// Выполнил студент группы ИВБО-8-14 Лобоцкий А.В.
#include <iostream>
#include <vector>  
#include <string>  
#include <regex>   
#include <fstream>

using namespace std;

class Parser
{
private:
	int i;
	vector <int> Token_ID, Var,AdLabel,Label;
	vector <string> Token, Stack,OP_Stack, Var_N;
	bool Close=false;
	void Load_Stack() { Stack.resize(1, "START"); OP_Stack.resize(1, "START");Var_N.resize(1, "START"); Var.resize(1, 0); }
	void Load_i(int count) { i = count; }
	void main()
	{
		while ((Token_ID[i] != 5) && (Close == false)) { Body(); }
		Close = false;
		return;
	}

	void Body() 
	{
		i++;
		switch (Token_ID[i])
		{
		case 1: 
		{
			return;
		}
		case 2:
		{
			return;
		}
		case 3:
		{
			return;
		}
		case 4: 
		{
			main();
			return;
		}
		case 5:
		{
			Close = true;
			return;
		}
		case 11: 
		{
			IF();
			return;
		}
		case 12:
		{
			INDEF();
			return;
		}
		case 13: 
		{
			DO();
			return;
		}
		case 15: 
		{
			WHILE();
			return;
		}
		
		default:
		{
			cout << "Синтаксическая ошибка в ID=" << i;
			system("pause");
			exit(0);
		}
		}
	}
	void IF()
	{
		i++;
		if (Token_ID[i] == 2)
		{
			Logic(); 
			Stack.push_back("L");
			Stack.push_back("$");
			Label.push_back(Stack.size() - 1);
		}
		else
		{
			cout << "Синтаксическая ошибка в ID=" <<i<<". Ожидалось '('" << '\n';
			system("pause");
			exit(0);
		}
		Body(); 
		Stack.push_back("@");
		Stack.push_back("$");
		AdLabel.push_back(Stack.size() - 1);
		while (Token_ID[i + 1] == 14)
		{
			i++;
			ELSE(); 
		}
		Stack[AdLabel.back()] = to_string(Stack.size()-1);
		Stack[Label.back()] = to_string(AdLabel.back());
		AdLabel.pop_back();
		Label.pop_back();
		
		return;
	}
	void ELSE()
	{
		if (Token_ID[i + 1] == 11) 
		{
			i++;
			IF();
		}
		else Body();
		return;
	}
	void Logic()
	{
		i++;
		if ((Token_ID[i] == 12) || (Token_ID[i] == 16)) Stack.push_back(Token[i]);
		else
		{
			cout << "Синтаксическая ошибка в первом операнде логической операции. ID=" <<i<< '\n';
			cout << "Введено:" << Token[i];
			system("pause");
			exit(0);
		}
		i+=2;
		if ((Token_ID[i] == 12) || (Token_ID[i] == 16)) Stack.push_back(Token[i]);
		else
		{
			cout << "Синтаксическая ошибка во втором операнде логической операции. ID=" << i << '\n';
			system("pause");
			exit(0);
		}
		i--;
		if ((Token_ID[i] == 8)||(Token_ID[i]==9)) Stack.push_back(Token[i]);
		else
		{
			cout << "Синтаксическая ошибка в логическом знаке. ID=" << i << '\n';
			system("pause");
			exit(0);
		}
		
		i+=2;
		if (Token_ID[i] == 3);  
		else
		{
			cout << "Синтаксическая ошибка в ID=" << i << ". Ожидалось ')'" << '\n';
			system("pause");
			exit(0);
		}
		return;
	}
	void DO()
	{
		i++;
		if (Token_ID[i] == 4)
		{	
			Stack.push_back("D");
			AdLabel.push_back(Stack.size() - 1);
			main();
			if (Token_ID[i+1] == 15)
			{
				i+=2;
				
				Logic();
				Stack.push_back("L");
				Stack.push_back("$");
				Label.push_back(Stack.size() - 1);

				Stack.push_back("@");
				Stack.push_back(to_string(AdLabel.back()));
				AdLabel.pop_back();

				Stack[Label.back()] = to_string(Stack.size() - 1);
				Label.pop_back();

			}
			else
			{
				cout << "Синтаксическая ошибка в ID=" << i << ". Ожидалось 'пока'" << '\n';
				cout << "Введено:" << Token[i];
				system("pause");
				exit(0);
			}
		}
		else
		{
			cout << "Синтаксическая ошибка в ID=" << i << ". Ожидалось '('" << '\n';
			cout << "Введено:" << Token[i];
			system("pause");
			exit(0);
		}
		
		
		
		return;
	}
	void WHILE()
	{
		i++;
		if (Token_ID[i] == 2)
		{
			Stack.push_back("W");
			AdLabel.push_back(Stack.size() - 1);
			Logic(); 
			Stack.push_back("L");
			Stack.push_back("$");
			Label.push_back(Stack.size() - 1);
		}
		else
		{
			cout << "Синтаксическая ошибка в ID=" << i << ". Ожидалось '('" << '\n';
			system("pause");
			exit(0);
		}
		Body(); 
		Stack.push_back("@");
		Stack.push_back(to_string(AdLabel.back()));
		AdLabel.pop_back();

		Stack[Label.back()] = to_string(Stack.size() - 1);
		Label.pop_back();
		
		return;
	}
	void INDEF()
	{
			Stack.push_back(Token[i]);
			i++;
			if (Token_ID[i] == 10) EQ();
			else
			{
				cout << "Синтаксическая ошибка в [" << i<< "]"<< '\n';
				cout << "Ожидалось ="<<'\n';
				system("pause");
				exit(0);
			}
			return;
	}
	void EQ()
	{
		OP_Stack.push_back(Token[i]); 
		i++;
		if ((Token_ID[i] == 12) || (Token_ID[i] == 16) || (Token_ID[i] == 2))
		{
			OP();
		}
		else
		{
			cout << "Синтаксическая ошибка в [=]. ID=" << i<< '\n';
			system("pause");
			exit(0);
		}
		return;
	}
	void OP()
	{
		while (Token_ID[i] != 1)
		{
			switch (Token_ID[i])
			{
			case 2: 
			{
				OP_Stack.push_back("STOP");
				i++;
				OP();
				break;
			}
			case 3: 
			{
				while (OP_Stack.back() != "STOP")
				{
					Stack.push_back(OP_Stack.back());
					OP_Stack.pop_back();
				}
				OP_Stack.pop_back(); return;
			}
			case 6: 
			{
				if ((OP_Stack.back() == "/") || (OP_Stack.back() == "*"))
				{
					Stack.push_back(OP_Stack.back());
					OP_Stack.pop_back();
				}
				OP_Stack.push_back(Token[i]); break;
			}
			case 7: 
			{
				OP_Stack.push_back(Token[i]);
				break;
			}
			case 12: 
			{
				Stack.push_back(Token[i]);
				break;
			}
			case 16:  
			{
				Stack.push_back(Token[i]);
				break;
			}
			default: 
			{
				cout << "Синтаксическая ошибка в алгоритме Дейкстры. ID="<< i << '\n';
				system("pause");
				exit(0);
			}

			}
			i++;
		}

		{
			if (Token_ID[i] == 1) 
				while (OP_Stack.back() != "START")
				{
					Stack.push_back(OP_Stack.back());
					OP_Stack.pop_back();
				}
			else
			{
				cout << "Синтаксическая ошибка в алгоритме Дейкстры. ID=" << i << '\n';
				system("pause");
				exit(0);
			}
		}
		i--;
		return;
	}

	void Init()
	{
		while (Token_ID[i] != 18)
		{
			if ((Token_ID[i] == 17))
			{
				if ((Token_ID[i + 1] == 12) && (Token_ID[i + 2] == 10) && (Token_ID[i + 3] == 16))
				{
					Var_N.push_back(Token[i + 1]);
					Var.push_back(atoi(Token[i + 3].c_str()));
					Token_ID.erase(Token_ID.begin() + i, Token_ID.begin() + i + 4);
					Token.erase(Token.begin() + i, Token.begin() + i + 4);
				}
				else
				{
					cout << "Синтаксическая ошибка при инициализации переменной!" << '\n';
					system("pause");
					exit(0);
				}
			}		
			i++;
		}
		i = 1;
	}
public:
	void Load(vector <string> Token_Str, vector <int> Token_ID_Str)
	{
		Load_Stack();
		Token = Token_Str;
		Token_ID = Token_ID_Str;
	}
	vector <int> Ret_Var()
	{
		return Var;
	}

	vector <string> Ret_Var_N()
	{
		return Var_N;
	}
	vector <string> Output()
	{
		Load_i(1);
		Init();
		Load_i(0);
		main();
		return (Stack);
	}

};