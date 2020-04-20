#include <iostream>
#include <cmath>
#include "../triagonalMatrixAlgorithm/triagonalMatrixAlgorithm.cpp"
using namespace std;

namespace splineFunctions{
    double calculateInterpolationPolynom(double x,double x_0,double *a,double *b,double *c,double *d){
        return a[0]+b[0]*(x-x_0)+c[0]*(x-x_0)*(x-x_0)+d[0]*(x-x_0)*(x-x_0)*(x-x_0);
    }

}

void splineInterpolation(double (*f)(double),double leftSide,double rightSide,int steps){
    double step=(rightSide-leftSide)/((double)steps-1.0);
    double *a=new double[steps];
    double x=leftSide;
    int n=steps-1;
    for(int i=0;i<n;i++){
        a[i]=f(x);
        x+=step;
    }
    double *c=new double[n];
    double *h_up=new double[n];
    double *h_main=new double[n];
    double *h_down=new double[n];
    double *p=new double[n];
    h_up[0]=0;
    h_main[0]=1;
    h_down[0]=0;
    p[0]=0;
    for(int i=1;i<n-1;i++){
        h_up[i]=step;
        h_main[i]=2*(step+step);
        h_down[i]=step;
        p[i]=3*((a[i+1]-a[i])/step-(a[i]-a[i-1])/step);
    }
    h_down[n-1]=0;
    h_main[n-1]=1;
    h_up[n-1]=0;
    p[n-1]=0;
    triagonalMatrixAlgorithm(n,h_down,h_main,h_up,p,c);
    double *d=new double[n];
    double *b=new double[n];
    for(int i=0;i<n-1;i++){
        d[i]=(c[i+1]-c[i])/(3.0*step);
        b[i]=((a[i+1]-a[i])/step)-((step/3)*(c[i+1]+2.0*c[i]));
    }
    d[n-1]=-c[n-1]/(3.0*step);
    b[n-1]=(a[n-1]-a[n-2])/step-(2.0*step*c[n-1]/3.0);
    
    fstream fout("interpolation/SplineInterpolationOutput.txt",ios::trunc|ios::out);
    fout<<"x : f(x) : interpolation : error"<<endl;
    x=leftSide;
    double valueOfInterpolationPolynom;
    double fx;
    for(int i=0;i<steps;i++){
        valueOfInterpolationPolynom=splineFunctions::calculateInterpolationPolynom(x,leftSide,a,b,c,d);
        fx=f(x);
        fout<<x<<" : "<<fx<<" : "<<valueOfInterpolationPolynom<<" : "<<fx-valueOfInterpolationPolynom<<endl;
        x+=step;
    }
}