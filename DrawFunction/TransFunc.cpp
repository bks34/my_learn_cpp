#define _CRT_SECURE_NO_WARNINGS
#include "TransFunc.h"

using namespace std;

bool Check(char* f)
{
	for (int i = 0; i < strlen(f); i++)
	{
		if (!(isnum(f[i]) || (f[i] >= '#' && f[i] <= '/') || (f[i] >= 'a' && f[i] <= 'z')||(f[i]=='^')))
			return false;
	}
	return true;
}

int prio(char op1,char op2)
{
	int res = 0;
	switch (op1)
	{
	case '+':
		switch (op2)
		{
		case '+':
			res = 1;
			break;
		case '-':
			res = 1;
			break;
		case '*':
			res = -1;
			break;
		case '/':
			res = -1;
			break;
		case '^':
			res = -1;
			break;
		case 'l':
			res = -1;
			break;
		case '(':
			res = -1;
			break;
		case ')':
			res = 1;
			break;
		case '#':
			res = 1;
			break;
		}
		break;
	case '-':
		switch (op2)
		{
		case '+':
			res = 1;
			break;
		case '-':
			res = 1;
			break;
		case '*':
			res = -1;
			break;
		case '/':
			res = -1;
			break;
		case '^':
			res = -1;
			break;
		case 'l':
			res = -1;
			break;
		case '(':
			res = -1;
			break;
		case ')':
			res = 1;
			break;
		case '#':
			res = 1;
			break;
		}
		break;
	case '*':
		switch (op2)
		{
		case '+':
			res = 1;
			break;
		case '-':
			res = 1;
			break;
		case '*':
			res = 1;
			break;
		case '/':
			res = 1;
			break;
		case '^':
			res = -1;
			break;
		case 'l':
			res = -1;
			break;
		case '(':
			res = -1;
			break;
		case ')':
			res = 1;
			break;
		case '#':
			res = 1;
			break;
		}
		break;
	case '/':
		switch (op2)
		{
		case '+':
			res = 1;
			break;
		case '-':
			res = 1;
			break;
		case '*':
			res = -1;
			break;
		case '/':
			res = -1;
			break;
		case '^':
			res = -1;
			break;
		case 'l':
			res = -1;
			break;
		case '(':
			res = -1;
			break;
		case ')':
			res = 1;
			break;
		case '#':
			res = 1;
			break;
		}
		break;
	case '^':
		switch (op2)
		{
		case '+':
			res = 1;
			break;
		case '-':
			res = 1;
			break;
		case '*':
			res = 1;
			break;
		case '/':
			res = 1;
			break;
		case '^':
			res = -1;
			break;
		case '(':
			res = -1;
			break;
		case ')':
			res = 1;
			break;
		case '#':
			res = 1;
			break;
		}
		break;
	case 'l':
		switch (op2)
		{
		case '+':
			res = 1;
			break;
		case '-':
			res = 1;
			break;
		case '*':
			res = 1;
			break;
		case '/':
			res = 1;
			break;
		case 'l':
			res = -1;
			break;
		case '(':
			res = -1;
			break;
		case ')':
			res = 1;
			break;
		case '#':
			res = 1;
			break;
		}
		break;
	case 's':
		switch (op2)
		{
		case '+':
			res = 1;
			break;
		case '-':
			res = 1;
			break;
		case '*':
			res = 1;
			break;
		case '/':
			res = 1;
			break;
		case '(':
			res = -1;
			break;
		case ')':
			res = 1;
			break;
		case '#':
			res = 1;
			break;
		}
		break;
	case 'c':
		switch (op2)
		{
		case '+':
			res = 1;
			break;
		case '-':
			res = 1;
			break;
		case '*':
			res = 1;
			break;
		case '/':
			res = 1;
			break;
		case '(':
			res = -1;
			break;
		case ')':
			res = 1;
			break;
		case '#':
			res = 1;
			break;
		}
		break;
	case '(':
		switch (op2)
		{
		case '+':
			res = -1;
			break;
		case '-':
			res = -1;
			break;
		case '*':
			res = -1;
			break;
		case '/':
			res = -1;
			break;
		case '^':
			res = -1;
			break;
		case 'l':
			res = -1;
			break;
		case 's':
			res = -1;
			break;
		case 'c':
			res = -1;
			break;
		case '(':
			res = -1;
			break;
		case ')':
			res = 0;
			break;
		}
		break;
	case ')':
		switch (op2)
		{
		case '+':
			res = 1;
			break;
		case '-':
			res = 1;
			break;
		case '*':
			res = 1;
			break;
		case '/':
			res = 1;
			break;
		case '^':
			res = 1;
			break;
		case 'l':
			res = 1;
			break;
		case 's':
			res = 1;
			break;
		case 'c':
			res = 1;
			break;
		case ')':
			res = 1;
			break;
		case '#':
			res = 1;
			break;
		}
		break;
	case '#':
		switch (op2)
		{
		case '+':
			res = -1;
			break;
		case '-':
			res = -1;
			break;
		case '*':
			res = -1;
			break;
		case '/':
			res = -1;
			break;
		case '^':
			res = -1;
			break;
		case 'l':
			res = -1;
			break;
		case 's':
			res = -1;
			break;
		case 'c':
			res = -1;
			break;
		case '(':
			res = -1;
			break;
		case '#':
			res = 0;
			break;
		}
		break;
	}
	return res;
}

bool isnum(char n)
{
	if ((n >= '0' && n <= '9') || n == '.'||n=='x'||n=='p'||n=='e')
		return true;
	return false;
}

bool isconst(char c)
{
	if (c == 'p'||c=='e')
		return true;
	return false;
}

double cal(double a, double b, char c)
{
	if (c == '+')
		return a + b;
	if (c == '-')
		return a - b;
	if (c == '*')
		return a * b;
	if (c == '/')
		return a / b;
	if (c == '^')
		return pow(a, b);
	if (c == 'l')
		return log(b) / log(a);
	if (c == 's')
		return a * sin(b);
	if (c == 'c')
		return a * cos(b);
	return 0;
}

double TransFunc(char* t, double x)
{
	char c[1024];
	strcpy(c, t);
	int len = strlen(c);
	c[len] = '#';
	c[len + 1] = '\0';
	stack<double> opnd;
	stack<char> optr;
	optr.push('#');
	char num[20];
	int i = 0;
	int j = 0;
	int num_end = 1;

	while(i<strlen(c))
	{
		if (isnum(c[i]))
		{
			num_end = 0;
			num[j] = c[i];
			i++;
			j++;
		}
		else
		{
			double a;
			if (num[0] == 'x')
			{
				a = x;
				num[j] =0;
				opnd.push(a);
				j = 0;
				num_end = 1;
				memset(num, 0, sizeof(num));
				
			}
			else if (isconst(num[0]))
			{
				if (num[0] == 'p')
					a = 3.1415926536;
				if (num[0] == 'e')
					a = 2.7182818285;
				num[j] = 0;
				opnd.push(a);
				j = 0;
				num_end = 1;
				memset(num, 0, sizeof(num));
			}
			else if(num_end==0)
			{
				num[j] = 0;
				a = atof(num);
				opnd.push(a);
				j = 0;
				num_end = 1;
				memset(num, 0, sizeof(num));
			}	
						
			switch (prio(optr.top(), c[i]))
			{
			case -1:
				optr.push(c[i]);
				i++;
				break;
			case 0:
				optr.pop();
				i++;
				break;
			case 1:
				char op = optr.top();
				optr.pop();

				double b = opnd.top();
				opnd.pop();
				double a = opnd.top();
				opnd.pop();
				double res = cal(a, b, op);
				opnd.push(res);
				break;
			}
			
		}
	}
	
	return opnd.top();
}
