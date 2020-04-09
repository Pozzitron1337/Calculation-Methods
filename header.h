#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define dimension_of_matrix 4

void printMatrix(double a[dimension_of_matrix][dimension_of_matrix]){
    for(int i=0;i<dimension_of_matrix;i++){//row
        for(int j=0;j<dimension_of_matrix;j++){//column
            cout<<a[i][j]<<"   ";
        }    
        cout<<endl;
    }
    cout<<endl;
}

void printVector(double x[dimension_of_matrix]){
    for(int i=0;i<dimension_of_matrix;i++){
        cout<<x[i]<<endl;
    }
}