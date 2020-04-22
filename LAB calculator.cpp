#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
struct Node{
 char data;
 PtrToNode next;
};

Status create(Stack &top)
{
 top=(PtrToNode)malloc(sizeof(Node));
 if(!top) exit(OVERFLOW);
 top->next=NULL;
 return OK;
}

Status push(Stack &top,char e)
{
 Stack temp;
 temp=(PtrToNode)malloc(sizeof(Node));
 if(!temp) exit(OVERFLOW);
 temp->data=e;
 temp->next=top->next;
 top->next=temp;
 return OK;
}
Status pop(Stack &top,char &e)
{
 if(top->next==NULL) return ERROR;
 Stack temp;
 temp=(PtrToNode)malloc(sizeof(Node));
 temp=top->next;
 e=temp->data;
 top->next=top->next->next;
 free(temp);
 return OK;
}
char top(Stack top)
{
	if(top->next==NULL) return ERROR;
	
	return top->next->data;
}
char comparison(char cal1,char cal2)
{
	char re;
	switch(cal1)
	{
		case ('+'):
			switch(cal2)
			{
				case ('+'):
					re='>';
					break;
				case ('-'):
				    re='>'; 
				    break;
				case ('*'):
					re='<';
					break;
				case ('/'):
					re='<';
					break;
				case ('('):
				    re='<';
					break;
				case (')'):
				    re='>';
					break;	
			}
			break;
		case ('-'):
			switch(cal2)
			{
				case ('+'):
					re='>';
					break;
				case ('-'):
				    re='>'; 
				    break;
				case ('*'):
					re='<';
					break;
				case ('/'):
					re='<';
					break;
				case ('('):
				    re='<';
					break;
				case (')'):
				    re='>';
					break;
			}
			break;
		case ('*'):
			switch(cal2)
			{
				case ('*'):
					re='>';
					break;
				case ('/'):
					re='>';
					break;
				case ('+'):
					re='>';
					break;
				case ('-'):
					re='>';
					break;
				case ('('):
				    re='<';
					break;
				case (')'):
				    re='>';
					break;
			}
			break;
		case ('/'):
			switch(cal2)
			{
				case ('*'):
					re='>';
					break;
				case ('/'):
					re='>';
					break;
				case ('+'):
					re='>';
					break;
				case ('-'):
					re='>';
					break;
				case ('('):
				    re='<';
					break;
				case (')'):
				    re='>';
					break;
			}
			break;
		case ('('):
			switch(cal2)
			{
				case ('*'):
					re='<';
					break;
				case ('/'):
					re='<';
					break;
				case ('+'):
					re='<';
					break;
				case ('-'):
					re='<';
					break;
				case(')'):
					re='=';
					break;
			}
			break;
	}
	return re;
}
Status InfixToPost(char *infix,Stack &optr,char *&postfix)
{
	create(optr);
	postfix=(char *)malloc(sizeof(char));
	int j,k=0;
	char e;
	for(j=0;infix[j]!='\0';j++)
	{
		if(infix[j]!='+'&&infix[j]!='-'&&infix[j]!='*'&&infix[j]!='/'&&infix[j]!='('&&infix[j]!=')')
		{
			postfix[k]=infix[j];
			k++;
		}
		else
		{
			if(optr->next==NULL) push(optr,infix[j]);
	        else
			{
				switch(comparison(top(optr),infix[j]))
				{
					case ('<'):
						push(optr,infix[j]);
						break;
					case ('>'):
						do
						{
							pop(optr,e);
						    postfix[k]=e;
						    k++;
						}while(comparison(top(optr),infix[j])=='>'&&optr->next!=NULL);
						if(comparison(top(optr),infix[j])=='=') pop(optr,e);
						else push(optr,infix[j]);
						break;
				}
			}
		}
	}
	while(optr->next!=NULL)
	{
		pop(optr,postfix[k]);
		k++;
	}
	printf("The postfix expression is %s",postfix);
	return OK;
}
char calpostfix(Stack &opnd,char *postexp)
{
	create(opnd);
	int i,num1,num2;
	char ch1,ch2;
	for(i=0;postexp[i]!='\0';i++)
	{
		if(postexp[i]!='+'&&postexp[i]!='-'&&postexp[i]!='*'&&postexp[i]!='/')
		{
			push(opnd,postexp[i]);
		}
		else
		{
			pop(opnd,ch1);
			num1=ch1-'0';
			pop(opnd,ch2);
			num2=ch2-'0';
			if(postexp[i]=='+')
			{
				push(opnd,(num2+num1)+'0');
			}
		    if(postexp[i]=='*')
			{	
				push(opnd,(num2*num1)+'0');
			}
			if(postexp[i]=='-')
			{
				push(opnd,(num2-num1)+'0');
			}
			if(postexp[i]=='/')
			{
				push(opnd,(num2/num1)+'0');
			}
		}
    }
	return opnd->next->data;
}
int main()
{
	Stack opnd;
	Stack optr;
	char *infixexp;
	char *postfixexp;
	infixexp=(char *)malloc(sizeof(char));
	printf("Enter the expression you want to calculate: ");
	gets(infixexp);

	InfixToPost(infixexp,optr,postfixexp);

	printf("\nThe result is %d",calpostfix(opnd,postfixexp)-'0');
	return 0;
}
