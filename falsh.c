#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<dirent.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
size_t lineSize = 256;
int lineNum = 5;
int resettext(char *text){
	//use for reset string
	for(int j = 0;j < lineSize; j++){
	text[j] = '\0';
	}

return 0;
}

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
	int fileptr;
	int stdoutcopy = dup(STDOUT_FILENO);
	int redirect = 0;
	while(1){
	//reset index number and read in ch for next line
	//print the current directory befoe each line
	getcwd(outputText,lineSize);
	printf("%s:$ ",outputText);
	getline(&inputText,&lineSize,stdin);

	//read and parse user input
	//use any space and tab to seperate each argument
	while(ch != '\n'){
	ch = inputText[stringindex];

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


	//check if > is inside command line
	//if there is > use next word as address

	index = 0;
	for(int i = 0; i < (argvindex); i++ ){
	if(strcmp(newArgv[i],">") == 0){
	index = i;
	redirect = 1;
	}
	}
	//try to open the file, if there is no file
	//create one, if error still happen, 
	//either next word is empty or unknown error happen
	if(redirect == 1){
	if(fileptr = open(newArgv[index + 1], O_CREAT|O_TRUNC)){
	dup2(fileptr, STDOUT_FILENO);
	for(int i = 0; i < lineSize; i++){
		newArgv[index][i] = '\0';
		newArgv[index + 1][i] = '\0';
	}
	argvindex -= 2;
	}else{
		if(newArgv[index + 1][0] == '\0'){
		printf("> need to follow a directoy\n");
		}else{
		printf("Unknown error  happen \n");
		}
	}
	}



	//compare user input with comand
	//if argument 1 is exit
	if(strcmp(newArgv[0],"exit") == 0){
	exit(0);
	}else if(strcmp(newArgv[0],"clean") == 0){
	//extra feature cleanr window
	system("clear");
	}else if(strcmp(newArgv[0],"pwd") == 0){
	//compare user input with comand
	//if argument 1 is cd
	printf("Current Directory:%s\n ",outputText);
	}else if(strcmp(newArgv[0],"cd") == 0){
	//compare user input with comand
	//if there is only one argument
	//change directory to home directory
	if(argvindex == 0){
	inputText = getenv("HOME");
	chdir(inputText);
	}else{
	//else use second argument
	// to change the working directory
	inputText = newArgv[1];
	errorreturn = chdir(inputText);
	if(errorreturn == -1){
	printf("cannot find the directory\n");
	}
	}

	}else if(strcmp(newArgv[0],"setpath") == 0){
	//compare user input with comand
	resettext(inputText);
	if(argvindex < 1){
	//if there is only  argument which is setpath
	//print error string
	printf("setpath need to have more than 1 argument\n");
	}else{
	//more than 1 argument
	//if user enter more than 1 argument
	//run though all argument to create them
		for(int i = 1; i < (argvindex + 1); i++){
		stringindex = 0;
		ch= ' ';
		index = 0;
			while(ch != '\0'){
			ch = newArgv[i][stringindex];
			if(ch == '/'){
		//create directory by inputtext
		//move current directory into create one
		//ready to create directory inside the directory
			if(stringindex != 0 ){
			errorreturn = mkdir(inputText,S_IRWXG|S_IRWXU);
			}

			if(errorreturn == -1){
			rmdir(inputText);
			}

			chdir(inputText);
			resettext(inputText);
			index = -1;
			}else{
		//if read character is not /, input it into string
		//use string to create file
			inputText[index] = ch;
			}

			index++;
			stringindex++;
			}
			//create directory by /
			//and there will be the last argument being left
			//create the last directory
			errorreturn = mkdir(inputText,S_IRWXG|S_IRWXU);
			if(errorreturn == -1){
			rmdir(inputText);
			}
			chdir(outputText);
			}
		}
	}else if(strcmp(newArgv[0],"help") == 0){
	//compare user input with comand
	//if argument 1 is help

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


	}else{
	//copy data into other array string
	//array string different from original one
	//and put NULL at the last string
	char *callfunction[lineSize];

	for(int i = 0; i < (argvindex + 1); i++){
	callfunction[i] = newArgv[i];
	}
	callfunction[argvindex + 1] = NULL;

	int rc = fork();
	if(rc < 0){
	// fork fail, print error messeage
	printf("fail to fork\n");
	}else if(rc == 0){
	//fork success

		if(execv(callfunction[0],callfunction) < 0){
		printf("can't exec the function\n");
		printf("please enter the function by path\n");
		exit(0);
		}

	}else{
	//parent process
	//wait until child finish
	int wc = wait(NULL);
	}

	}
	//reset everything for next run
	fflush(stdout);
	stringindex = 0;
	argvindex = 0;
	index = 0;
	ch = '\0';
	resettext(inputText);
	resettext(outputText);
	for(int i = 0; i < lineSize; i ++){
		for(int k = 0; k < lineSize; k ++){
		newArgv[i][k] = '\0';
		}
	}
	//if already check stdout
	//change it back
	if(redirect == 1){
	dup2(stdoutcopy, STDOUT_FILENO);
	redirect = 0;
	}

	}
}
