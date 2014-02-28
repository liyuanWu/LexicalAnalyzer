#include<stack>
#include<iostream>
#include<strstream>
#include<string>
#include<vector>
using namespace std;

class stringBuffer{
	vector<char> cr;
public:
	stringBuffer& operator<<(const char&  c){
		cr.push_back(c);
		return *this;
	}
	stringBuffer& operator<<(const string& s){
		for (int i = 0; i < s.length(); i++){
			cr.push_back(s[i]);
		}
		return *this;
	}
	string& operator>>(string& s){
		char* chr;
		chr = new char(cr.size());
		int pot = 0;
		for (vector<char>::iterator i = cr.begin(); i < cr.end(); ++i){
			chr[pot] = *i;
			++pot;
		}
		s = string(chr, chr + cr.size());
		return s;
	}
};
class polisher{
private:

	bool IsSign(char data);
	bool Priority(char fir, char sec);

public:
	string Change(char str[], int n);
};