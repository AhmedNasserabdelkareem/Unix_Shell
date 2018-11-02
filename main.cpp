// some important headers
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <csignal>
#include <sys/types.h>
#include <vector>
#include <sys/wait.h>
#include <cstring>
#include <array>
#include <fstream>

using namespace std;
ofstream outfile; // global variable used to write in file

// handler function is overriden to know if child is terminated or not
void handler(int sig) {
    pid_t pid;
    pid = wait(nullptr);
    if(pid>0) {
        outfile << "CHILD IS TERMINATED  : " << pid << endl;
    }
}

// convert string to array of chars
void toCharArray(string &line, char *args) {
    for (int i=0;i<line.size();i++){
      args[i] = line.at(i);
    }
    args[line.size()] = '\0';
}
//parse the line to arguemnets
vector<char*> parseInstructions(char* chars) {
    vector<char*> args;
    char* token = strtok(chars, " ");
    while (token != nullptr) {
        args.push_back(token);
        token = strtok(nullptr, " ");
    }
    return args;
}
// execute the command
void executeInstructions(char** args, int size){
    pid_t  pid;
    int    status;
    // we have two cases first is normal command , second run aprograms under one parent

    if(strcmp(args[size-2],"&")==0){// First case if command contains "&"
        args[1]= nullptr;
        if ((pid = fork()) < 0) {// Try to fork a child
            printf("forking a child is failed\n");
            exit(1);
        } else if (pid == 0) {
            if (execvp(args[0], args) < 0) {//forked a child successful and execute the command
                printf("Your command is not true please try again !\n");
                exit(1);
            }
            // In this case we don't need to wait beacuse it runs in background
        }
    }else {// second case execute normal command

        if ((pid = fork()) < 0) {// Try to fork a child
            printf("forking a child is failed\n");
            exit(1);
        } else if (pid == 0) {
            if (execvp(args[0], args) < 0) {//forked a child successful and execute the command
                printf("Your command is not true please try again !\n");
                exit(1);
            }
        } else {// wait untill the execution is finished
            while (wait(&status) != pid);
        }
    }
}

int main() {
    string instruction;
   vector<char *> arguments;
    outfile.open("log.txt", std::ios_base::app);
    // Shell loop
    while (1){
        printf("Ahmed::Shell >> ");
      getline(cin,instruction);
        char argsChars[instruction.size()+1];
        toCharArray(instruction,argsChars);
        arguments=parseInstructions(argsChars);
        if(arguments.at(0)=="exit"){
            exit(0);
        }
        arguments.push_back(nullptr);
        char * args[arguments.size()];
        for(int i=0;i<arguments.size();i++){
            args[i]=arguments.at(i);
        }
        executeInstructions(args,arguments.size());
        signal(SIGCHLD, handler);

   }
    return 0;
}

