#include "squareMethod/squareMethod.cpp"
#include "zeydelMethod/zeydelMethod.cpp"
#include "jacobiMethod/jacobiMethod.cpp"
#include "interpolation/newtonInterpolation.cpp"
#include "interpolation/splineInterpolation.cpp"
#include "derivative/runge_cutt.cpp"
#include "derivative/adams_bashford.cpp"

void lab2(){
    cout<<"lab2,variant 16:"<<endl;
    double A[dimension_of_matrix][dimension_of_matrix]={{5.5,7.0,6.0,5.5},
                    {7.0,10.5,8.0,7.0},
                    {6.0,8.0,10.5,9.0},
                    {5.5,7.0,9.0,10.5}};
    double b[dimension_of_matrix]={23,32,33,31};
    squareMethod(A,b);

}

void lab3(){
    cout<<"lab3,variant 16:"<<endl;
    double A[dimension_of_matrix][dimension_of_matrix]={{5.5,7.0,6.0,5.5},
                    {7.0,10.5,8.0,7.0},
                    {6.0,8.0,10.5,9.0},
                    {5.5,7.0,9.0,10.5}};
    double b[dimension_of_matrix]={23,32,33,31};
    zeydelMethod(A,b);
}

void lab4(){
    const int N=4;
    double A[N][N] = {{7.0,0.88,0.93,1.21},
                    {0.88,4.16,1.3,0.15},
                    {0.93,1.3,6.44,2.0},
                    {1.21,0.15,2.0,9.0}};
    
    jacobiMethod<N>(A);
    // const int N=3;
    // double A[N][N] ={{5,1,2},
    // {1,4,1},
    // {2,1,3}};
    // jacobiMethod<N>(A);

}

namespace lab5data{
    double leftPoint=-M_PI/3;
    double rightPoint=M_PI/3;  
    double f(double x){
        return x*atan(x);
    }
}
void lab5(){
    newtonInterpolation(lab5data::f,lab5data::leftPoint,lab5data::rightPoint,11);
    splineInterpolation(lab5data::f,lab5data::leftPoint,lab5data::rightPoint,11);
}

void myTest(){
double a[8][4]={{1,50.78},
                {1,30.25},
                {1,81.03},
                {1,99.33},
                {1,50.42},
                {1,40.59},
                {1,91.01},
                {1,88.63}
                };
for(int j=0;j<8;j++){
    for(int i=2;i<4;i++){
        a[j][i]=a[j][i-1]*a[j][1];
    }
}
matrix<double,8,4> A(a);
A.print();
cout<<endl;
matrix<double,4,8> At;
At=A.transponce();
At.print();
matrix<double,4,4> B;
B=At*A;
B.print();

}


namespace lab6data{
    double y(double x){
        return tan(x);
    }
    double leftPoint=0;
    double rightPoint=1;  
    double step=0.09;
    double y_0=y(leftPoint);
    
    double f(double x,double y){
        return (1-x*x)*(y-tan(x))+1/(cos(x)*cos(x));
    }   
}
void lab6(){
    runge_cutt(lab6data::f,lab6data::leftPoint,lab6data::rightPoint,lab6data::step,lab6data::y_0);
    adams_bashford(lab6data::f);
    fstream fout("derivative/function.txt",ios::trunc|ios::out);
    double x=lab6data::leftPoint;
    while (x<lab6data::rightPoint){
        fout<<x<<" "<<lab6data::y(x)<<endl;
        x+=lab6data::step;
    }
    fout.close();
    fstream rungecutt("derivative/rungecutt.txt");
    fstream adamsbashford("derivative/adamsbashford.txt");
    string line;
    int lines=0;
    while (rungecutt>>line){
        lines++;
    }
    lines/=2;
    rungecutt.clear();
    rungecutt.seekg(0);
    double u[lines];
    double y1[lines];
    double y2[lines];
    int i=0;
    while (i<lines){
        rungecutt>>u[i];
        rungecutt>>y1[i];
        adamsbashford>>y2[i];
        adamsbashford>>y2[i];
        i++;
    }
    rungecutt.close();
    adamsbashford.close();
    fstream error("derivative/error.txt",ios::trunc|ios::out);
    for(int i=0;i<lines;i++){
        error<<u[i]<<" "<<abs(y1[i]-y2[i])<<endl;
    }
    error.close();
    
}

int main(){
    //lab2();
    //lab3();
    //lab4();
    //lab5();
    lab6();
    //myTest();
    return 0;
}
