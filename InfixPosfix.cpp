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
