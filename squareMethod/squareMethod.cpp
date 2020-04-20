#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define dimension_of_matrix 4
namespace square{
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

void initTriangleMatrix(double a[dimension_of_matrix][dimension_of_matrix],double t[dimension_of_matrix][dimension_of_matrix]){
    t[0][0]=sqrt(a[0][0]);
    for(int k=1;k<dimension_of_matrix;k++){
        t[k][0]=a[k][0]/t[0][0];
        t[0][k]=0;
    }
    for(int i=1;i<dimension_of_matrix;i++){
        for(int j=1;j<dimension_of_matrix;j++){
            if(i>j){
                t[i][j]=a[i][j];
                for(int k=0;k<j;k++){
                    t[i][j]-=t[i][k]*t[j][k];
                }
                t[i][j]/=t[j][j];
                continue;
            }
            if(i==j){
                t[i][i]=a[i][i];
                for(int k=0;k<i;k++){
                    t[i][i]-=t[i][k]*t[i][k];
                }
                t[i][i]=sqrt(t[i][i]);
                continue;
            }
            else{
                t[i][j]=0;
            }
        }
    }


}
void transTriangleMatrix(double t[dimension_of_matrix][dimension_of_matrix],double trans[dimension_of_matrix][dimension_of_matrix]){
    for(int i=0;i<dimension_of_matrix;i++){
        for(int j=0;j<dimension_of_matrix;j++){
            if(i<=j){
                trans[i][j]=t[j][i];
            }
            else{
                trans[i][j]=0;
            }
        }
    }

}
void initY(double t[dimension_of_matrix][dimension_of_matrix],double b[dimension_of_matrix],double y[dimension_of_matrix]){
    y[0]=b[0]/t[0][0];
    for(int i=1;i<dimension_of_matrix;i++){
        y[i]=0;
        y[i]+=b[i];
        for(int j=0;j<i;j++){
            y[i]-=(t[i][j]*y[j]);
        }
        y[i]/=t[i][i];
    }
}
void initX(double trans[dimension_of_matrix][dimension_of_matrix],double y[dimension_of_matrix],double x[dimension_of_matrix]){
    x[dimension_of_matrix-1]=y[dimension_of_matrix-1]/trans[dimension_of_matrix-1][dimension_of_matrix-1];
    for(int i=dimension_of_matrix-2;i>=0;i--){
        x[i]=0;
        x[i]+=y[i];
        for(int j=dimension_of_matrix-1;j>i;j--){
            x[i]-=(trans[i][j]*x[j]);
        }
        x[i]/=trans[i][i];
    }

}
void checking(double a[dimension_of_matrix][dimension_of_matrix],double x[dimension_of_matrix],double b[dimension_of_matrix]){
    double* Ax=new double[dimension_of_matrix];
    cout<<"check А*х:"<<endl;
    for(int i=0;i<dimension_of_matrix;i++){
        for(int j=0;j<dimension_of_matrix;j++){
            Ax[i]+=a[i][j]*x[j];
        }
        cout<<Ax[i]<<endl;
    }
    cout<<"error:"<<endl;
    for(int i=0;i<dimension_of_matrix;i++){
        cout<<Ax[i]-b[i]<<endl;
    }
    
}
}
//should be rewritten
void squareMethod(double A[dimension_of_matrix][dimension_of_matrix],double b[dimension_of_matrix]){
    double T[dimension_of_matrix][dimension_of_matrix];
    square::initTriangleMatrix(A,T);
    cout<<"T:"<<endl;
    square::printMatrix(T);
    double y[dimension_of_matrix];
    square::initY(T,b,y);
    cout<<"y:"<<endl;
    square::printVector(y);
    double Trans[dimension_of_matrix][dimension_of_matrix];
    square::transTriangleMatrix(T,Trans);
    cout<<"T trans:"<<endl;
    square::printMatrix(Trans);
    double x[dimension_of_matrix];
    square::initX(Trans,y,x);
    cout<<"x:"<<endl;
    square::printVector(x);
    square::checking(A,x,b);
}