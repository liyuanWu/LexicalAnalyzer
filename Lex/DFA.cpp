#include<iostream>
#include<string>
#include<stack>
#include"DFA.h"

using namespace std;



edge::edge(char chr, node* n1, node* n2, edge* ed){
	c = chr;
	nodeFrom = n1;
	nodeTo = n2;
	nextEdge = ed;
}

int node::count = 0;
void node::addEdge(node& nextNode, char c){
	if (!firstEdge){
		firstEdge = lastEdge = new edge( c, this, &nextNode, (edge*)0 );
	}
	else{
		edge* e = new edge( c, this, &nextNode, (edge*)0 );
		lastEdge->nextEdge = e;
		lastEdge = e;
	}
}


token DFA::createDFA(string input){
		stack<token> tokenStack;
		for (int i = 0; i < input.length(); i++){
			switch (input[i]){
			case '*':{
				token& t1 = tokenStack.top();
				t1.lastNode->addEdge(*t1.firstNode, EPSOLON);
				node* tmp = t1.firstNode;
				t1.firstNode = new node();
				t1.firstNode->addEdge(*tmp, EPSOLON);
				tmp = t1.lastNode;
				t1.lastNode = new node();
				tmp->addEdge(*t1.lastNode, EPSOLON);
				break; }
			case '|':{
				token t1 = tokenStack.top();
				tokenStack.pop();
				token t2 = tokenStack.top();
				tokenStack.pop();
				node* t1f = t1.firstNode,* t1l = t1.lastNode, *t2f = t2.firstNode, *t2l = t2.lastNode;
				t1.firstNode = new node();
				t1.firstNode->addEdge(*t1f, EPSOLON);
				t1.firstNode->addEdge(*t2f, EPSOLON);
				t1.lastNode = new node();
				t1l->addEdge(*t1.lastNode, EPSOLON);
				t2l->addEdge(*t1.lastNode, EPSOLON);
				tokenStack.push(t1);
				break; }
			case '`':{
				token t1 = tokenStack.top();
				tokenStack.pop();
				token t2 = tokenStack.top();
				tokenStack.pop();

				t2.lastNode->addEdge(*t1.firstNode, EPSOLON);
				t2.lastNode = t1.lastNode;
				tokenStack.push(t2);
				break; }
			default:{
				node* n1 = new node();
				node* n2 = new node();
				n1->addEdge(*n2, input[i]);
				token* t = new token{ n1, n2 };
				tokenStack.push(*t);
				break;
					}
			}
		}
		return tokenStack.top();
	}

