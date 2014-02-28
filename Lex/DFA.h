#include<string>
#include<iostream>
#define EPSOLON 1
using namespace std;
class node;
struct edge{
public:
	char c;
	node*nodeFrom;
	node*nodeTo;
	edge*nextEdge;
	edge(char chr, node* n1, node* n2, edge* ed);
};
class node{
public:
	static int count;
	int numb;
	edge*firstEdge;
	edge*lastEdge;
	void addEdge(node& nextNode, char c);
	node(){
		numb = count++;
	}
};
struct token{
	node* firstNode;
	node* lastNode;

};
class DFA{
public:
	token createDFA(string input);
};