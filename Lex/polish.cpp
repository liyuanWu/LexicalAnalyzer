#include "polish.h"
using namespace std;

	bool polisher::IsSign(char data)//�ж��Ƿ�Ϊ����
	{
		if (data == '(' || data == ')' || data == '|' || data == '*' || data == '`')
			return true;
		else
			return false;
	}
	bool polisher::Priority(char fir, char sec)//�Ƚ���������ȼ�
	{
		if ((fir == '|' || (fir == '`'))&&(sec == '*'))
			return true;
		else
			return false;
	}


	string polisher::Change(char str[], int n)//ת������
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
				if (str[i] == '(' || signStack.empty())//�����'('����ջ��ջ���'('���ȼ�����һ�з��ţ�ջ�յĻ�Ҳ��ջ
					signStack.push(str[i]);
				else if (str[i] == ')')//�����')'��ջ��'('��ǰ��ȫ����ջ�������'('��ջ�������
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
				else//��ǰ���Ų�������
				{
					char signTmp;
					signTmp = signStack.top();
					if (signTmp == '(')//ջ������'('��ǰ������ջ��ջ�ڵ�'('����һ�з���
						signStack.push(str[i]);
					else//�Ƚϵ��������Ŷ���������
					{
						if (Priority(signTmp, str[i]))//��ǰ�������ȼ��ߣ�����ջ
							signStack.push(str[i]);
						else//��ǰ�������ȼ��ͣ���ջ�����ų�ջ���������i--�����±Ƚ���ջ��Ԫ�غ͵�ǰ����
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
		while (!signStack.empty())//�ַ���ɨ����Ϻ󣬽�ջ��Ԫ���������
		{
			strs << signStack.top();
			signStack.pop();
		}
		string result;
		strs >> result;
		return result;
	}