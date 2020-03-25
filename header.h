#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define N 4

void printMatrix(double a[N][N]){
    for(int i=0;i<4;i++){//row
        for(int j=0;j<4;j++){//column
            cout<<a[i][j]<<"   ";
        }    
        cout<<endl;
    }
    cout<<endl;
}

void printVector(double x[N]){
    for(int i=0;i<N;i++){
        cout<<x[i]<<endl;
    }
}

