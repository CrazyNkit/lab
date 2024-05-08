#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isKeyword(char buffer[]){
        char keywords[5][10] = {"char","double","float","int","long"};
        int i, flag = 0;
        for(i = 0; i < 5; ++i){
                if(strcmp(keywords[i], buffer) == 0){
                        flag = 1;
                        break;
                }
        }
        return flag;
}

int check(char buffer[])
{
        if(isKeyword(buffer))return -1;
        int flag=0;

        for(int i=0;buffer[i]!='\0';i++)
        {
                if(flag==0)
                {
                        if(!(isalpha(buffer[i]) || buffer[i]=='_'))
                        {
                                if(isdigit(buffer[i]))return -2;
                                else return -3;
                        }
                        flag=1;
                }
                else
                {
                        if(!(isalnum(buffer[i]) || buffer[i]=='_'))return -4;
                }
        }
        return 1;
}

void main()
{
        FILE *fptr = fopen("sample.c","r");
        char word[100];
        char table[5][100]={"char->","double->","float->","int->","long->"};
        int flag=0,idx=0;

        if(fptr==NULL)
        {
                printf("Invalid file name");
                return;
        }

        while(fscanf(fptr, "%s", word) == 1)
        {
                if(strcmp(word,"{"))
                {
                        flag =1;
                }

                if(flag==1)
                {

                        if(isKeyword(word)==1)
                        {



                                if(!strcmp(word,"char"))idx=0;
                                if(!strcmp(word,"double"))idx=1;
                                if(!strcmp(word,"float"))idx=2;
                                if(!strcmp(word,"int"))idx=3;
                                if(!strcmp(word,"long"))idx=4;

                                printf("\n\n%s ",word);

                                while(strcmp(word,";"))
                                {

                                        fscanf(fptr, "%s", word);
                                        if(!strcmp(word,",") || !strcmp(word,";"))continue;
                                        if(check(word)==1)
                                        {
                                                printf("%s ",word);
                                                strcat(table[idx],word);
                                                strcat(table[idx]," ");
                                        }
                                        else
                                        {
                                                if(check(word)==-1) printf("\nError:%s is keyword\n",word);
                                                if(check(word)==-2) printf("\nError:%s 1st letter can't be a number\n",word);
                                                if(check(word)==-3) printf("\nError:%s 1st letter can't be a symbol\n",word);
                                                if(check(word)==-4) printf("\nError:%s can't have special symbol\n",word);
                                                if(check(word)==0) printf("\nError:%s ->Incorrect declaration\n",word);
                                        }
                                }
                        }
                }

                if(word == "}")flag =0;

        }
        printf("\n\nTable of Identifier\n");
        for(int i=0;i<5;i++)
        {
                printf("%s\n",table[i]);
        }
}
