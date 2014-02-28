#include "NFA.h"
#include "polish.h"
using namespace std;

int main(){
	int inputNumb;
	cin >> inputNumb;
	cin.get();
	vector<token> tokens;
	for (int i = 0; i < inputNumb; i++){
		cout << "(" << i<< ") ";
		char input[256];
		cin.getline(input, 256);
		string pInput = polisher().Change(input, strlen(input));
//		cout << "polish changed:" << pInput << endl;
		token& t = DFA().createDFA(pInput);
		tokens.push_back(t);
		cout << "DFA change complete,Waitting for new Input("<<i+1<<")"<< endl;
	}


	NFASet result = NFA().changeToNFA(tokens);
	cout << "NFA change complete" << endl;
	cout << "receiving input:" << endl;
	while (true){
		char input[256];
		cin.getline(input, 256);
		string inp(input, strlen(input));
		vector<int>*rest = isRight(inp, &result);
		if (rest){
			for (vector<int>::iterator it = rest->begin(); it != rest->end(); ++it){
				cout << "(";
				cout << *it;
				cout << ")  ";
			}
			cout << endl;
		}
		else{
			cout << "ERROR INPUT" << endl;
		}
		
	}

}