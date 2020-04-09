#include "matrix.cpp"
#include <fstream>


template<int N>
void jacobiMethod(double input_matrix[N][N],double epsilon=0.00001){
    string filename="iterations_lab4.txt";
    fstream fout(filename,ios::app);
    matrix<double,N,N> A(input_matrix);
    matrix<double,N,N> H(1.0);
    size_t i;
    size_t j;
    size_t k=0;;
    double phi;
    double a_max=A.find_max_element_over_diagonal(i,j);
    while(A.calculate_non_diagonal_elements()>epsilon){
        fout<<"k:"<<k<<endl;
        fout<<"Spherical norm:"<<A.spherical_norm()<<endl;
        fout<<"Sum of diagonal elements:"<<A.trace()<<endl;
        fout<<"Sum of non diagonal elements:"<<A.calculate_non_diagonal_elements()<<endl;
        phi=atan((2*A(i,j))/(A(i,i)-A(j,j)))/2;
        H(i,i,cos(phi));
        H(i,j,-sin(phi));
        H(j,i,sin(phi));
        H(j,j,cos(phi));
        A=(H.transponce()*A)*H;
        fout<<"T:"<<endl;
        H.print_to_file(filename);
        fout<<endl;
        fout<<"T transponce:"<<endl;
        H.transponce().print_to_file(filename);
        a_max=A.find_max_element_over_diagonal(i,j);
        H=matrix<double,N,N>(1.0);
        k++;
        fout<<"-----------------------------------"<<endl;
    }
    fout<<"matrix A:"<<endl;
    A.print_to_file(filename);
    fout<<endl;
    fout<<"values: ";
    for(size_t i=0;i<N;i++){
        fout<<A(i,i)<<" , ";
    }
}