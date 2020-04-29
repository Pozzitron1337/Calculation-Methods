#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

namespace newtonFunctions
{
    int factorial(int n){
        int result=1;
        for(int i=2;i<=n;i++){
            result*=i;
        }
        return result;
    }
    double C(double q,int i){
        double result=1;
        for(double j=0;j<i;j++){
            result*=(q-j);
        }
        result/=factorial(i);
        return result;
    }
    double calculateInterpolationPolynom(int n,double x,double *a,double x_0,double step){
        double sum=0.0;
        double q=(x-x_0)/step;
        for(int i=0;i<n;i++){
            sum+=a[i]*C(q,i);
        }
        return sum;
    }
} 

void newtonInterpolation(double (*f)(double),double leftSide,double rightSide,int steps){
    double step=(rightSide-leftSide)/((double)steps-1.0);
    double *y=new double[steps];
    double x=leftSide;
    for(int i=0;x<=rightSide;i++){
        y[i]=f(x);
        x+=step;
    }
    double *dy=y;//renamed array y;
    double *a=new double[steps];//resulted array
    a[0]=dy[0];
    int n=1;
    do{
        x=leftSide;
        for(int k=0;k<steps-n;k++){
            dy[k]=dy[k+1]-dy[k];
        }
        a[n]=dy[0];
        n++;
    }while((steps-n)>2);
    
    fstream fout("interpolation/NewtonInterpolationOutput.txt",ios::trunc|ios::out);
    fstream newtonfunction("interpolation/newtonFunction.txt",ios::trunc|ios::out);
    fstream newtoninterpolation("interpolation/newtoninterpolation.txt",ios::trunc|ios::out);
    fstream newtonerror("interpolation/newtonError.txt",ios::trunc|ios::out);
    fout<<"x : f(x) : interpolation : error"<<endl;
    x=leftSide;
    double valueOfInterpolationPolynom;
    double fx;
    for(int i=0;i<steps;i++){
        valueOfInterpolationPolynom=newtonFunctions::calculateInterpolationPolynom(steps,x,a,leftSide,step);
        fx=f(x);
        fout<<x<<" : "<<fx<<" : "<<valueOfInterpolationPolynom<<" : "<<fx-valueOfInterpolationPolynom<<endl;
        newtonfunction<<x<<" "<<fx<<endl;
        newtoninterpolation<<x<<" "<<valueOfInterpolationPolynom<<endl;
        newtonerror<<x<<" "<<fx-valueOfInterpolationPolynom<<endl;
        x+=step;
    }
    
}