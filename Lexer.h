#include <iostream>
#include <vector>  
#include <string>  
#include <regex>   
#include <fstream>
using namespace std;
regex
	IF("[Е|е]+сли"),
	ELSE("[И|и]наче"),
	SYMBOL("[(]|[)]|[{]|[}]|[;]"),
	DO("[Д|д]елать"),
	WHILE("[П|п]ока"),
	EQUALS("="),
	PM("[+]|[-]"),
	DM("[/]|[*]"),
	LOGIC("[<]|[>]"),
	INTEGER("[0-9]+"),
	DIGIT("[0-9]+"),
	LETTER("[А-Яа-я]"),
	ID("[А-Яа-я0-9_]*"),
	INT("[Ч|ч]+исло");
class LEXER {

private:
	
	struct Lexer_token
	{
		vector <int> ID;
		vector <string> Lexem;
		bool Err;
	};
	vector <int> Lexem_ID;
	vector <string> Lexem;
	struct Lexer_token Lexer(string str)
	{
		Lexem_ID.resize(1, 0);
		Lexem.resize(1, "START");
		bool Err = false;
		for (int i = 1; i < str.size()+1; i++)
		{
			if (str[0] == ';') { Add(1, i, str); str.erase(0, i); i = 0; }
			else if (str[0] == '(') { Add(2, i, str); str.erase(0, i); i = 0; }
			else if (str[0] == ')') { Add(3, i, str); str.erase(0, i); i = 0; }
			else if (str[0] == '{') { Add(4, i, str); str.erase(0, i); i = 0; }
			else if (str[0] == '}') { Add(5, i, str); str.erase(0, i); i = 0; }
			else if (regex_match(str.substr(0, 1), PM)) { Add(6, i, str); str.erase(0, i); i = 0; }
			else if (regex_match(str.substr(0, 1), DM)) { Add(7, i, str); str.erase(0, i); i = 0; }
			else if (regex_match(str.substr(0, 1), LOGIC)) { Add(8, i, str); str.erase(0, i); i = 0; }
			else if (str[0] == '=')
			{
				if (str[1] == '=') { i = 2; Add(9, i, str); str.erase(0, i); i = 0; }
				else { Add(10, i, str); str.erase(0, i); i = 0; }
			}
			else if (regex_match(str.substr(0, 5), INT))
			{
				i = 5;
				Add(17, i, str);
				str.erase(0, i);
				i = 0;
			}

			else if (regex_match(str.substr(0, 4), IF))
			{
				if (str[4] == '(') { i = 4; Add(11, i, str); str.erase(0, i); i = 0; }
				else { i = Indef(str); str.erase(0, i); i = 0; }
			}

			else if (regex_match(str.substr(0, 6), DO))
			{
				if (str[6] == '{')
				{
					i = 6;
					Add(13, i, str);
					str.erase(0, i);
					i = 0;
				}
				else { i = Indef(str); str.erase(0, i); i = 0; }
			}

			else if (regex_match(str.substr(0, 5), ELSE))
			{
				if (regex_match(str.substr(5, 4), IF) | (str[5] == '{'))
				{
					i = 5;
					Add(14, i, str);
					str.erase(0, i);
					i = 0;
				}
				else { i = Indef(str); str.erase(0, i); i = 0; }
			}

			else if (regex_match(str.substr(0, 4), WHILE))
			{
				if (str[4] == '(')
				{
					i = 4;
					Add(15, i, str);
					str.erase(0, i);
					i = 0;
				}
				else {
					i = Indef(str); str.erase(0, i); i = 0;
				};
			}

			else if (regex_match(str.substr(0, i), DIGIT))
			{
				while (regex_match(str.substr(1, i), DIGIT))
				{
					i++;
				}
				Add(16, i, str);
				str.erase(0, i);
				i = 0;
			}

			else { i = Indef(str); str.erase(0, i); i = 0; }
		}
			Lexer_token Func_Ret;
			Func_Ret.ID = Lexem_ID;
			Func_Ret.Lexem = Lexem;
			Func_Ret.Err = Err;
			return Func_Ret;
	}
	void Add(int ID,int i, string str)
	{
		Lexem_ID.push_back(ID);
		Lexem.push_back(str.substr(0, i));	
	}
	int Indef(string str)
	{
		int n = 0;
		while (regex_match(str.substr(n, 1), LETTER))
		{
			n++;	
		}
		Add(12, n, str);
		return n;
	}
public:
	vector <string> Lexem_o(string str)
	{
		Lexer_token Out;
		Out.Lexem = Lexer(str).Lexem;
		return(Out.Lexem);
	}

	vector <int> Lexem_ID_o(string str)
	{
		Lexer_token Out;
		Out.ID = Lexer(str).ID;
		return(Out.ID);
	}

	bool Error_o(string str)
	{
		Lexer_token Out;
		Out.Err = Lexer(str).Err;
		return(Out.Err);
	}
	

};
