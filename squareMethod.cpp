#include "header.h"

void initTriangleMatrix(double a[N][N],double t[N][N]){
    t[0][0]=sqrt(a[0][0]);
    for(int k=1;k<N;k++){
        t[k][0]=a[k][0]/t[0][0];
        t[0][k]=0;
    }
    for(int i=1;i<N;i++){
        for(int j=1;j<N;j++){
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
void transTriangleMatrix(double t[N][N],double trans[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(i<=j){
                trans[i][j]=t[j][i];
            }
            else{
                trans[i][j]=0;
            }
        }
    }

}
void initY(double t[N][N],double b[N],double y[N]){
    y[0]=b[0]/t[0][0];
    for(int i=1;i<N;i++){
        y[i]=0;
        y[i]+=b[i];
        for(int j=0;j<i;j++){
            y[i]-=(t[i][j]*y[j]);
        }
        y[i]/=t[i][i];
    }
}
void initX(double trans[N][N],double y[N],double x[N]){
    x[N-1]=y[N-1]/trans[N-1][N-1];
    for(int i=N-2;i>=0;i--){
        x[i]=0;
        x[i]+=y[i];
        for(int j=N-1;j>i;j--){
            x[i]-=(trans[i][j]*x[j]);
        }
        x[i]/=trans[i][i];
    }

}
void checking(double a[N][N],double x[N],double b[N]){
    double* Ax=new double[N];
    cout<<"check А*х:"<<endl;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            Ax[i]+=a[i][j]*x[j];
        }
        cout<<Ax[i]<<endl;
    }
    cout<<"error:"<<endl;
    for(int i=0;i<N;i++){
        cout<<Ax[i]-b[i]<<endl;
    }
    
}
void squareMethod(double A[N][N],double b[N]){

    double T[N][N];
    initTriangleMatrix(A,T);
    cout<<"T:"<<endl;
    printMatrix(T);
    double y[N];
    initY(T,b,y);
    cout<<"y:"<<endl;
    printVector(y);
    double Trans[N][N];
    transTriangleMatrix(T,Trans);
    cout<<"T trans:"<<endl;
    printMatrix(Trans);
    double x[N];
    initX(Trans,y,x);
    cout<<"x:"<<endl;
    printVector(x);
    checking(A,x,b);
}