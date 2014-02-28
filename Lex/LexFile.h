#include <fstream>
#include <iostream>

using namespace std;

class LecFile{
public:
	bool loadFile(string filePath);
	string nextLine();
	char nextChar();

};