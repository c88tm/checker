#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]){
    if(argc == 2){
        printf("this is player %s\n", argv[1]);
    }
    Sleep(5000);
    printf("this is a simple ai!\n");
    return 0;
}