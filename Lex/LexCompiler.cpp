#include"LexCompiler.h"
#include<stack>
Node* LexCompiler::compileToDFA(string s,int state){
	Node* startNode = new Node();
	Node* preNode = startNode;
	Node* endNode = new Node();
	endNode->state = state;
	Node* pointerArray[s.length];
	stack<int> bracketStack;
		 
	for (int i = 0; i < s.length; i++){
		switch (s[i]){
		case '(':
			pointerArray[i] = i;
			bracketStack.push(i);
			break;
		case ')':
			pointerArray[i] = bracketStack.pop();
		case '*':
		case '|':
		default:
			if (!startNode->startEdge){
				startNode->lastEdge = startNode->startEdge = new edge(s[i]);
			}
			else{
				edge* nEdge = new edge(s[i]);
				nEdge->nextNode = 
				startNode->lastEdge->nextEdge = new edge(s[i]);

			}
				
		}
	}
}