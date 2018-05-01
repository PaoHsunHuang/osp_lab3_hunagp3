#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
size_t lineSize = 256;
int lineNum = 5;

int main(int argc, char *argv[]){
	char *inputText;
	char outputText[lineSize];
	char newArgv[lineSize][lineSize];
	char ch = '\0';
	int index = 0;
	int argvindex = 0;
	int stringindex = 0;
	int spacecheck = 0;
	while(1){
	//print the current directory befoe each line
	getcwd(outputText,lineSize);
	//printf("%s:$ ",outputText);
	getline(&inputText,&lineSize,stdin);
	while(ch != '\n'){

	ch = inputText[stringindex];

		if(ch == '\n'){
		}else if(ch == '	'){
		spacecheck = 1;

		}else if(ch == ' '){
		spacecheck = 1;

		}else{

		if(spacecheck == 1){
		argvindex++;
		index = 0;
		spacecheck = 0;
		}
		newArgv[argvindex][index] = ch;
		index++;
		}
		stringindex++;
	}
	for(int i = 0; i < (argvindex + 1); i ++){
	printf("argv[%d] = %s\n",i,newArgv[i]);
	}
	if(strcmp(newArgv[0],"exit") == 0){
	exit(0);
	}

	for(int i = 0; i < 10; i ++){
		for(int k = 0; k < 10; k ++){
		newArgv[i][k] = '\0';
		}
	}
	stringindex = 0;
	argvindex = 0;
	index = 0;
	ch = '\0';
	}
}
/*	if(ch != ' '){
	newArgv[argvindex][index] = ch;
	index++;
	printf("ch = %c\n",ch);
	}
	stringIndex++;
*/
	

/*
	//if user input text, exit program
	strcmpint = strcmp(inputText, "exit\n");
	if(strcmpint == 0 ){
	return 0;
	}

	//if user input pwd, print curremt directory
	strcmpint = strcmp(inputText,"pwd\n");
	if(strcmpint  == 0){
	printf("current directory: %s\n",outputText);
	}
*/

/*
*/
