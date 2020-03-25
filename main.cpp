#include "squareMethod.cpp"
#include "zeydelMethod.cpp"

int main(){

    //varian 16
    double A[N][N]={{5.5,7.0,6.0,5.5},
                    {7.0,10.5,8.0,7.0},
                    {6.0,8.0,10.5,9.0},
                    {5.5,7.0,9.0,10.5}};
    double b[N]={23,32,33,31};
    //squareMethod(A,b);
    zeydelMethod(A,b);

    return 0;
}


