struct charNode{
	char chr;
	charNode* nextCharNode;
	union{
		GraphNode* graphNode;
		charNode* prevNode;
	};
	 
};