#include "NFA.h"
#include "polish.h"
using namespace std;


	bool cmpNFAT::operator()(const NFAToken* a, const NFAToken* b) const
	{
			return a->nodList<b->nodList;
	}

	NFASet NFA::changeToNFA(vector<token> inputDFAs){
		token result;
		result.firstNode = new node();

		set <NFAToken*,cmpNFAT> nodList;

		node startNode;
		for (vector<token>::iterator it = inputDFAs.begin(); it != inputDFAs.end(); ++it){
			startNode.addEdge(*(it->firstNode), EPSOLON);
		}
		vector<node*> fnode = closure(&startNode);
		NFAToken* fToken = new NFAToken(fnode);
		nodList.insert(fToken);
		NFASet resultSet;
		resultSet.startToken = fToken;

		queue < NFAToken* > tokenNotDeal;
		tokenNotDeal.push(fToken);
		while (!tokenNotDeal.empty()){
			NFAToken* clist = tokenNotDeal.front();
			tokenNotDeal.pop();
			nodList.insert(clist);
			vector<node*>::iterator nod = clist->nodList.begin();
			while (nod < clist->nodList.end()){
				edge* edg = (*nod)->firstEdge;
				while (edg){
					if (edg->c != EPSOLON){
						if (clist->tokenTo.find(edg->c)==clist->tokenTo.end()){
							(clist->tokenTo).insert(map<char, NFAToken*>::value_type (edg->c, new NFAToken()));
							clist->tokenTo[edg->c]->nodList.push_back(edg->nodeTo);
						}
						else{
							clist->tokenTo[edg->c]->nodList.push_back(edg->nodeTo);
						}
					}
					edg = edg->nextEdge;
				}
				++nod;
			}
			map<char, NFAToken*>::iterator mapIter;
			for (mapIter = (clist->tokenTo).begin(); mapIter != clist->tokenTo.end(); ++mapIter){
				vector<node*>::iterator currentNod = mapIter->second->nodList.begin();
				vector<node*>::iterator endNode = mapIter->second->nodList.end();
				vector<vector<node*>> nodeList;
				for (; currentNod < endNode; ++currentNod){
					nodeList.push_back(closure(*currentNod));
				}
				set<node*> lastList;
				for (vector < vector < node* >> ::iterator it = nodeList.begin(); it < nodeList.end(); ++it){
					for (currentNod = it->begin(); currentNod < it->end(); ++currentNod){
						lastList.insert(*currentNod);
					}
				}
				vector<node*> tmpVector(lastList.begin(),lastList.end());
				NFAToken* nTok = new NFAToken(tmpVector);
				if (nodList.find(nTok) == nodList.end()){
					tokenNotDeal.push(nTok);
					mapIter->second = nTok;
				}
				else{
					mapIter->second = *(nodList.find(nTok));
					delete nTok;
					
				}
			}
		}
		set <NFAToken*, cmpNFAT>::iterator it;
		for (it = nodList.begin(); it != nodList.end(); ++it){
			int tcont = 0;
			for (vector<token>::iterator tokenIt = inputDFAs.begin(); tokenIt != inputDFAs.end(); ++tokenIt){
				if (find((*it)->nodList.begin(), (*it)->nodList.end(), tokenIt->lastNode) != (*it)->nodList.end()){
					(*it)->finalState.push_back(tcont);
				}
				++tcont;
			}

		}
		resultSet.resultSet = nodList;
		return resultSet;
	}

	vector<node*> NFA::closure(node* nod){
		vector<node*> nodClosure;
		queue<node*> nodNotDeal;
		nodNotDeal.push(nod);
		while (!nodNotDeal.empty()){
			node* nnod = nodNotDeal.front();
			nodNotDeal.pop();
			nodClosure.push_back(nnod);
			edge* edg = nnod->firstEdge;
			while (edg){
				if (edg->c == EPSOLON){
					vector<node*>::iterator pos = find(nodClosure.begin(), nodClosure.end(), edg->nodeTo);
					if (pos == nodClosure.end()){
						nodNotDeal.push(edg->nodeTo);
					}
				}
				edg = edg->nextEdge;
			}
		}
		return nodClosure;
	}



vector<int>* isRight(string input, NFASet* rule){
	NFAToken* currentState = rule->startToken;
	for (int i = 0; i < input.length(); i++){
		map<char, NFAToken*>::iterator f = currentState->tokenTo.find(input[i]);
		if (f != currentState->tokenTo.end()){
			currentState = f->second;
		}
		else{
			return 0;
		}
	}
	return &currentState->finalState;
}