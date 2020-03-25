#include "header.h"

void transponseMatrix(double A[N][N],double T[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            T[i][j]=A[j][i];
        }
    }

}

void multipleMatrix(double A[N][N],double B[N][N],double C[N][N]){   
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            C[i][j]=0;
            for (int k = 0; k < N; k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
        } 
    }
}

void multipleMatrixOnVector(double A[N][N],double v[N],double result[N]){
    for(int i=0;i<N;i++){
        result[i]=0;
        for(int j=0;j<N;j++){
            result[i]+=A[i][j]*v[j];
        }
    }
}

void normalize(double A[N][N],double b[N]){
    double temp;
    for(int i=0;i<N;i++){
        temp=A[i][i];
        b[i]=b[i]/temp;
        for(int j=0;j<N;j++){
            A[i][j]=A[i][j]/temp;
        }
    }
}

void iterations(double AA[N][N],double d[N],double *x){
    double x_prev[N];
    bool e;
    double temp;
    int t=0;
    double AAx[N];
    double r[N];
    fstream fout("iteration.txt",ios::app);
    do{
        e=false;
        //main iterations:
        for(int i=0;i<N;i++){
            x_prev[i]=x[i];
            temp=d[i];
            for(int j=0;j<N;j++){
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
        for(int i=0;i<N;i++){
            r[i]=(d[i]-AAx[i]);
            fout<<r[i]<<endl;
        }
        printVector(r);
    }while(e);
}

void zeydelMethod(double A[N][N],double b[N]){
    cout<<"A:"<<endl;
    printMatrix(A);
    double A_trans[N][N];
    transponseMatrix(A,A_trans);
    cout<<"A transponce:"<<endl;
    printMatrix(A_trans);
    double Atrans_A[N][N];
    multipleMatrix(A_trans,A,Atrans_A);
    cout<<"A_trans * A:"<<endl;
    printMatrix(Atrans_A);
    double d[N];
    multipleMatrixOnVector(A_trans,b,d);
    cout<<"A_trans * d:"<<endl;
    printVector(d);
    normalize(Atrans_A,d);
    cout<<"Normalize:"<<endl;
    printMatrix(Atrans_A);
    printVector(d);
    double *x=new double[N];
    iterations(Atrans_A,d,x);//TODO think
    printVector(x);
}