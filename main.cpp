#include "squareMethod.cpp"
#include "zeydelMethod.cpp"
#include "jacobiMethod.cpp"

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

int main(){
    //lab2();
    //lab3();
    lab4();
    
    return 0;
}


