#include "squareMethod.cpp"
#include "zeydelMethod.cpp"
#include "matrix.cpp"


int main(){

    //varian 16
    double A[N][N]={{5.5,7.0,6.0,5.5},
                    {7.0,10.5,8.0,7.0},
                    {6.0,8.0,10.5,9.0},
                    {5.5,7.0,9.0,10.5}};
    double b[N]={23,32,33,31};
    matrix<double,4,4> a(A);
    matrix<double,4,1> d(b);
    a.print();
    //squareMethod(A,b);
    //zeydelMethod(A,b);
    (a*d).print();
    
    return 0;
}


