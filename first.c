#include<stdio.h>
#include<ctype.h>
#include<string.h>

FILE *fr, *fa, *symbolTable;
char buffer[50], previousData[10], check[10], dataType[10];
int id = 0, moreVariable = 0;

int addVariable(void)
{
	if(strcmp(previousData,"integer") == 0)
	{
		strcpy(dataType,previousData);
		return 1;
	}
	else if (strcmp(previousData,"real") == 0)
	{
		strcpy(dataType,previousData);
		return 1;
	}
	else
		return 0;
}

void addInSymbolTable(char variable[])
{
	char ch;
	int i = 0;
	fa = fopen("symbolTable.txt","a+");
	if(fa == NULL)
		printf("File can't be open");
	
	fprintf(fa,"%d, %s, %s\n",id,variable,dataType);
	fclose(fa);
}

void isVariable(char variable[])
{
	char ch;
	int i = 0;
	symbolTable = fopen("symbolTable.txt","r");
	if(symbolTable == NULL)
		printf("File can't be open");
	
	while(1)
	{
		ch = fgetc(symbolTable);
		if(ch == EOF)
			break;
		
		printf("%c",ch);
	}
	fclose(symbolTable);
}

void keywords(char isKeyword[])
{
	int i = 0;
	if(strcmp(isKeyword,"start") == 0)
		printf("<start>");
	else if(strcmp(isKeyword,"end") == 0)
		printf("<end>");
	else if(strcmp(isKeyword,"integer") == 0)
		printf("<integer>");
	else if(strcmp(isKeyword,"real") == 0)
		printf("<real>");
	else if(strcmp(isKeyword,"read") == 0)
		printf("<read>");
	else if(addVariable() == 1 || moreVariable == 1)
	{
		printf("<id,%d>",++id);
		for(i = 0; isKeyword[i] != '\0';i++);
		if(isKeyword[i-1] == ',')
		{
			moreVariable = 1;
			isKeyword[i-1] = '\0';
		}
		else
			moreVariable = 0;
		addInSymbolTable(isKeyword);
	}
	
		//isVariable(isKeyword);
	
	strcpy(previousData,isKeyword);
} 

void main()
{
	char ch;
	int i = 0, store = 0;
	fr = fopen("myProgram.txt","r");
	if(fr == NULL)
		printf("File can't be open");
	
	while(1)
	{
		ch = fgetc(fr);
		if(ch == EOF)
			break;
		/*else if(ch == '"' || store == 1)
		{
			store = 1;
			if(fgetc(fr) == '"')
			{
				store = 0;
				printf("<Constant>");
			}
		}*/
		else if(isspace(ch)|| ch == ';' || ch == ',' || ch == '(' || ch == ')')
		{
			if (ch == ',') buffer[i] = ',';
			keywords(buffer);
			bzero(buffer,sizeof(buffer));
			i = 0;
			if(ch == '(') 
			{
				printf("<LP>");
				//buffer[i++] = ch;
			}
			if(ch == ')')
			{
				printf("<RP>");
				//buffer[i++] = ch;
			}
			if(ch == 32) printf("<WS>");
			if(ch == '\n') printf("\n");
		}
		
		else
		{
			buffer[i] = ch;
			i++;
		}
	}
	fclose(fr);
}