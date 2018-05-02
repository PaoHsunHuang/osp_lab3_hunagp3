#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
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
	int errorreturn = 0;
	while(1){
	//print the current directory befoe each line
	getcwd(outputText,lineSize);
	printf("%s:$ ",outputText);
	getline(&inputText,&lineSize,stdin);

	//read and parse user input
	//use any space and tab to seperate each argument
	//every upper case letter will be change to lower case
	while(ch != '\n'){
	ch = inputText[stringindex];
		if(ch > 'A' && ch < 'Z'){
		ch += 32;
		}
		if(ch == '\n'){
		}else if(ch == '	'){
		spacecheck = 1;
		}else if(ch == ' '){
		spacecheck = 1;
		}else{

		if(spacecheck == 1){
			if(index != 0){
			argvindex++;
			}
			spacecheck = 0;
			index = 0;
		}
		newArgv[argvindex][index] = ch;
		index++;
		}
		stringindex++;
	}




	//compare user input with comand
	//if argument 1 is exit
	if(strcmp(newArgv[0],"exit") == 0){
	exit(0);
	}
	if(strcmp(newArgv[0],"clean") == 0){
	system("clear");
	}
	//compare user input with comand
	//if argument 1 is cd
	if(strcmp(newArgv[0],"pwd") == 0){
	printf("Current Directory:%s\n ",outputText);
	}
	//compare user input with comand
	if(strcmp(newArgv[0],"cd") == 0){
		//if there is only one argument
		//change directory to home directory
		if(argvindex == 0){
		inputText = getenv("HOME");
		chdir(inputText);
		}else{
		//else use second argument
		// to change the working directory
		inputText = newArgv[1];
		chdir(inputText);
		}


	}

	for(int j = 0;j < lineSize; j++){
	inputText[j] = '\0';
	}

	//compare user input with comand
	if(strcmp(newArgv[0],"setpath") == 0){
		if(argvindex < 1){
		printf("setpath need to have more than 1 argument\n");

		}else{

		for(int i = 1; i < (argvindex + 1); i++){
			stringindex = 0;
			ch= ' ';
			index = 0;

			while(ch != '\0'){
			ch = newArgv[i][stringindex];
			if(ch == '/'){
			if(stringindex != 0 ){
			errorreturn = mkdir(inputText,S_IRWXG|S_IRWXU);
			if(errorreturn == -1){
			rmdir(inputText);
			}
			printf("make direction:%s\nError %d\n",
						inputText,errorreturn);
			chdir(inputText);
			for(int j = 0;j < lineSize; j++){
			inputText[j] = '\0';
			}
			}
			index = -1;
				}else{
				inputText[index] = ch;
				}
				index++;
				stringindex++;
			}
			errorreturn = mkdir(inputText,S_IRWXG|S_IRWXU);
			if(errorreturn == -1){
			rmdir(inputText);
			}
			printf("make direction:%s\nError %d\n",inputText,errorreturn);

			chdir(outputText);
		}

		}
	}
	//compare user input with comand
	//if argument 1 is help
	if(strcmp(newArgv[0],"help") == 0){
	printf("Built-In Command:\n");
	printf("exit\n\n");
	printf("leave shell falsh, back to bash\n\n");
	printf("clean\n\n");
	printf("clean all screen\n\n");
	printf("pwd\n\n");
	printf("print out current working directoy \n\n");
	printf("cd <dir>\n\n");
	printf("move current working directoy\n");
	printf("back to home directoty if there is no argument\n");
	printf("if there is a argument, ");
	printf("use argument as directory \n\n");
	printf("setpath <dir> [dir]... [dir]\n\n");
	printf("set a path in the current working directory\n");
	printf("directory name is the argument\n");
	printf("if there is more than one argument create all of them\n\n");
	printf("help\n\n");
	printf("print the short description about built in command\n");


	}

	//reset all argument into null
	//reset index number and read in ch for next line
	for(int i = 0; i < (argvindex + 1); i ++){
		for(int k = 0; k < lineSize; k ++){
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
