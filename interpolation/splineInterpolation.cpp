#include <iostream>
#include <cmath>
#include <fstream>
#include "../triagonalMatrixAlgorithm/triagonalMatrixAlgorithm.cpp"
using namespace std;

namespace splineFunctions{
    double calculateInterpolationPolynom(double x,double x_0,double *a,double *b,double *c,double *d,int i){
        return a[i]+b[i]*(x-x_0)+c[i]*(x-x_0)*(x-x_0)+d[i]*(x-x_0)*(x-x_0)*(x-x_0);
    }
    double findNearestNode(double x,double *nodes,int nodeSize,int &nearestIndex){
        double difference=abs(x-nodes[0]);
        for(int i=1;i<nodeSize;i++){
           if(abs(difference)<=abs(x-nodes[i])){
               nearestIndex=i-1;
               return nodes[i-1];
           }else{
               difference=x-nodes[i];
           }
        }
        nearestIndex=nodeSize-1;
        return nodes[nodeSize-1];
    }


}

void splineInterpolation(double (*f)(double),double leftSide,double rightSide,int steps){
    double step=(rightSide-leftSide)/((double)steps-1.0);
    double *nodes=new double[steps];
    double *a=new double[steps];
    double x=leftSide;
    int n=steps;
    for(int i=0;i<n;i++){
        a[i]=f(x);
        nodes[i]=x;
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
    fstream splinefunction("interpolation/splineFunction.txt",ios::trunc|ios::out);
    fstream splineinterpolation("interpolation/splineinterpolation.txt",ios::trunc|ios::out);
    fstream splineerror("interpolation/splineError.txt",ios::trunc|ios::out);
    fout<<"x : f(x) : interpolation : error"<<endl;
    x=leftSide;
    double valueOfInterpolationPolynom;
    double fx;
    double nearest;
    x=leftSide;

    //step=(rightSide-leftSide)/((double)iterations-1.0);
    int i;
    while(x<rightSide){
        fx=f(x);
        nearest=splineFunctions::findNearestNode(x,nodes,steps,i);
        valueOfInterpolationPolynom=splineFunctions::calculateInterpolationPolynom(x,nearest,a,b,c,d,i);
        fout<<x<<" : "<<fx<<" : "<<valueOfInterpolationPolynom<<" : "<<fx-valueOfInterpolationPolynom<<endl;
        splinefunction<<x<<" "<<fx<<endl;
        splineinterpolation<<x<<" "<<valueOfInterpolationPolynom<<endl;
        splineerror<<x<<" "<<100*(fx-valueOfInterpolationPolynom)<<endl;
        x+=0.001;
    }

}