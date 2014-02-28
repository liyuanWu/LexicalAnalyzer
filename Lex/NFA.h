#include"DFA.h"
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#include<set>
using namespace std;

class NFAToken{
public:
	vector<int> finalState;
	vector<node*> nodList;
	map<char, NFAToken*> tokenTo;
	NFAToken(){
	}
	NFAToken(vector<node*> nodl){
		nodList = nodl;
	}

};
struct cmpNFAT
{
	bool operator()(const NFAToken* a, const NFAToken* b) const;

};
struct NFASet{
public:
	NFAToken* startToken;
	set <NFAToken*, cmpNFAT> resultSet;
};

class NFA{
public:
	NFASet changeToNFA(vector<token> inputDFAs);

	vector<node*> closure(node* nod);
};

vector<int>* isRight(string input, NFASet* rule);