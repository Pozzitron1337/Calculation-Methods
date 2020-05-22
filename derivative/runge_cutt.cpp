#include <iostream>
#include <fstream>

using namespace std;

void runge_cutt(double (*f)(double,double),double leftSide,double rightSide,double step,double y_0){
    fstream fout("derivative/rungecutt.txt",ios::trunc|ios::out);
    int steps=(rightSide-leftSide)/step+1;
    double x=leftSide;
    double y[steps];
    y[0]=y_0;
    double k1,k2,k3,k4;
    for(int i=0;x<rightSide;i++){
        k1=step*f(x,y[i]);
        k2=step*f(x+0.5*step,y[i]+0.5*k1);
        k3=step*f(x+0.5*step,y[i]+0.5*k2);
        k4=step*f(x+steps,y[i]+k3);
        y[i+1]=y[i]+(k1+2*k2+2*k3+k4)/6;
        fout<<x<<" "<<y[i]<<endl;
        x+=step;
    }
    fout.close();


}
