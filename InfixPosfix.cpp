#include<iostream>
#include<stack>
#include<string>

using namespace std;

string InfixToPostfix(string expression); //Fungsi untuk mengkonversi infix ke posfix
int HasHigherPrecedence(char operator1, char operator2); //untuk mengecek operator mana yang harus didahulukan
bool IsOperator(char C); //untuk mengecek operator atau angka
bool IsOperand(char C);

int main() 
{
	string expression; 
	cout<<"Masukkan infix: \n";
	getline(cin,expression);
	string postfix = InfixToPostfix(expression);
	cout<<"Hasil = "<<postfix<<"\n";
}
string InfixToPostfix(string expression)
{
	stack<char> S; //deklarasi stack
	string postfix = "";//set awal posfix = string kosong
	for(int i = 0;i< expression.length();i++) {
		if(expression[i] == ' ' || expression[i] == ',') continue; 	// Scanning each character from left
		else if(IsOperator(expression[i])) //jika karakter adalah operator, maka pop dua elemen dari stack dan tampilkan hasil
		{
			while(!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(),expression[i]))
			{
				postfix+= S.top();
				S.pop();
			}
			S.push(expression[i]);
		}
		else if(IsOperand(expression[i])) //untuk karakter = operand
		{
			postfix +=expression[i];
		}

		else if (expression[i] == '(') 
		{
			S.push(expression[i]);
		}
		else if(expression[i] == ')') 
		{
			while(!S.empty() && S.top() !=  '(') {
				postfix += S.top();
				S.pop();
			}
			S.pop();
		}
	}

	while(!S.empty()) {
		postfix += S.top();
		S.pop();
	}

	return postfix;
}
//untuk mengecek apakah karakter merupakan alfabet atau numerik
//asumsikan operand adalah single character
bool IsOperand(char C) 
{
	if(C >= '0' && C <= '9') return true;
	if(C >= 'a' && C <= 'z') return true;
	if(C >= 'A' && C <= 'Z') return true;
	return false;
}

//untuk mengecek karakter adalah operator atau bukan
bool IsOperator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/' || C== '$')
		return true;

	return false;
}
 
//untuk mengecek asosiasi operator
int IsRightAssociative(char op)
{
	if(op == '$') return true;
	return false;
}

//fungsi untuk operator yang lebih tinggi
int GetOperatorWeight(char op)
{
	int weight = -1; 
	switch(op)
	{
	case '+':
	case '-':
		weight = 1;
	case '*':
	case '/':
		weight = 2;
	case '$':
		weight = 3;
	}
	return weight;
}

//fungsi untuk menampilkan operasi dan return output
int HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);
	
	//jika operasi memiliki nilai operator yang sama, return true jika asosiasinya berada di kiri
	//return false jika asosiasi berada di kanan
	//jika operator merupakan left-associative, yang kiri harus diproritaskan
	if(op1Weight == op2Weight)
	{
		if(IsRightAssociative(op1)) return false;
		else return true;
	}
	return op1Weight > op2Weight ?  true: false;
}
