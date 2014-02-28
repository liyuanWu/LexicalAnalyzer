#include "polish.h"
using namespace std;

	bool polisher::IsSign(char data)//判断是否为符号
	{
		if (data == '(' || data == ')' || data == '|' || data == '*' || data == '`')
			return true;
		else
			return false;
	}
	bool polisher::Priority(char fir, char sec)//比较运算符优先级
	{
		if ((fir == '|' || (fir == '`'))&&(sec == '*'))
			return true;
		else
			return false;
	}


	string polisher::Change(char str[], int n)//转化函数
	{
		stringBuffer strs;
		int i;
		stack<char> signStack;
		for (i = 0; i < n; i++)
		{
			if (!IsSign(str[i]))
				strs << str[i];
			else
			{
				if (str[i] == '(' || signStack.empty())//如果是'('则入栈，栈外的'('优先级高于一切符号，栈空的话也入栈
					signStack.push(str[i]);
				else if (str[i] == ')')//如果是')'则将栈中'('以前的全部出栈并输出，'('出栈但不输出
				{
					char signTmp;
					signTmp = signStack.top();
					signStack.pop();
					while (signTmp != '(')
					{
						strs << signTmp;
						signTmp = signStack.top();
						signStack.pop();
					}
				}
				else//当前符号不是括号
				{
					char signTmp;
					signTmp = signStack.top();
					if (signTmp == '(')//栈顶若是'('则当前符号入栈，栈内的'('低于一切符号
						signStack.push(str[i]);
					else//比较的两个符号都不是括号
					{
						if (Priority(signTmp, str[i]))//当前符号优先级高，则入栈
							signStack.push(str[i]);
						else//当前符号优先级低，则栈顶符号出栈，并输出，i--，重新比较新栈顶元素和当前符号
						{
							if (str[i] == '*'){
								strs << signTmp;
								i--;
							}
							else{
								strs << signTmp;
								signStack.pop();
								i--;
							}

						}
					}
				}
			}
		}
		while (!signStack.empty())//字符串扫描完毕后，将栈中元素依次输出
		{
			strs << signStack.top();
			signStack.pop();
		}
		string result;
		strs >> result;
		return result;
	}