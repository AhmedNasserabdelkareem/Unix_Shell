// some important headers
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <csignal>
#include <sys/types.h>

using namespace std;
void parseInstructions(string ins){

}
void executeInstructions(){

}

int main() {
    string instruction;
   while (1){
      printf("Ahmed>> ");
      getline(cin,instruction);//read
       if(instruction=="exit"){
           exit(0);
       }
      parseInstructions(instruction);
       executeInstructions();

   }
    return 0;
}
