#include <cstdio>
#include <windows.h>
#include <iostream>
#include <chrono>
#include <ctime>  
int main(){
    auto start = std::chrono::system_clock::now();
    // Some computation here
    while(true){
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        if(elapsed_seconds.count() > 20) break;
    }
    printf("time up!\n");
}