#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define dimension_of_matrix 4
namespace zeydel{
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

void transponseMatrix(double A[dimension_of_matrix][dimension_of_matrix],double T[dimension_of_matrix][dimension_of_matrix]){
    for(int i=0;i<dimension_of_matrix;i++){
        for(int j=0;j<dimension_of_matrix;j++){
            T[i][j]=A[j][i];
        }
    }

}

void multipleMatrix(double A[dimension_of_matrix][dimension_of_matrix],double B[dimension_of_matrix][dimension_of_matrix],double C[dimension_of_matrix][dimension_of_matrix]){   
    for(int i=0;i<dimension_of_matrix;i++){
        for(int j=0;j<dimension_of_matrix;j++){
            C[i][j]=0;
            for (int k = 0; k < dimension_of_matrix; k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
        } 
    }
}

void multipleMatrixOnVector(double A[dimension_of_matrix][dimension_of_matrix],double v[dimension_of_matrix],double result[dimension_of_matrix]){
    for(int i=0;i<dimension_of_matrix;i++){
        result[i]=0;
        for(int j=0;j<dimension_of_matrix;j++){
            result[i]+=A[i][j]*v[j];
        }
    }
}

void normalize(double A[dimension_of_matrix][dimension_of_matrix],double b[dimension_of_matrix]){
    double temp;
    for(int i=0;i<dimension_of_matrix;i++){
        temp=A[i][i];
        b[i]=b[i]/temp;
        for(int j=0;j<dimension_of_matrix;j++){
            A[i][j]=A[i][j]/temp;
        }
    }
}

void iterations(double AA[dimension_of_matrix][dimension_of_matrix],double d[dimension_of_matrix],double *x){
    double x_prev[dimension_of_matrix];
    bool e;
    double temp;
    int t=0;
    double AAx[dimension_of_matrix];
    double r[dimension_of_matrix];
    fstream fout("iteration_lab3.txt",ios::app);
    do{
        e=false;
        //main iterations:
        for(int i=0;i<dimension_of_matrix;i++){
            x_prev[i]=x[i];
            temp=d[i];
            for(int j=0;j<dimension_of_matrix;j++){
                if(i==j){
                    continue;
                }else{
                    temp-=x[j]*AA[i][j];
                }        
            }
            x[i]=temp;
            e|=abs(x_prev[i]-x[i])>0.0001;
        }
        //vector of error:
        multipleMatrixOnVector(AA,x,AAx);
        fout<<"iteration "<<(t++)<<":"<<endl<<"r: "<<endl;
        for(int i=0;i<dimension_of_matrix;i++){
            r[i]=(d[i]-AAx[i]);
            fout<<r[i]<<endl;//print to file
        }
        //printVector(r);
    }while(e);
}
}
//should be rewritten
void zeydelMethod(double A[dimension_of_matrix][dimension_of_matrix],double b[dimension_of_matrix]){
    cout<<"A:"<<endl;
    zeydel::printMatrix(A);
    double A_trans[dimension_of_matrix][dimension_of_matrix];
    zeydel::transponseMatrix(A,A_trans);
    cout<<"A transponce:"<<endl;
    zeydel::printMatrix(A_trans);
    double Atrans_A[dimension_of_matrix][dimension_of_matrix];
    zeydel::multipleMatrix(A_trans,A,Atrans_A);
    cout<<"A_trans * A:"<<endl;
    zeydel::printMatrix(Atrans_A);
    double d[dimension_of_matrix];
    zeydel::multipleMatrixOnVector(A_trans,b,d);
    cout<<"A_trans * d:"<<endl;
    zeydel::printVector(d);
    zeydel::normalize(Atrans_A,d);
    cout<<"Normalize:"<<endl;
    zeydel::printMatrix(Atrans_A);
    zeydel::printVector(d);
    double *x=new double[dimension_of_matrix];
    zeydel::iterations(Atrans_A,d,x);
    zeydel::printVector(x);
}