#include <iostream>
#include <cmath>
#include <string>
using namespace std;

template <typename T, size_t row_size, size_t col_size>
class matrix{
    private:
        T M[row_size][col_size];
    public:
        
        matrix(T l=(T)0){  
            for (size_t i=0; i<row_size; i++){
                for(size_t j=0;j<col_size;j++){
                    if(i==j){
                        M[i][j]=l;
                    }else{
                        M[i][j]=(T)0;
                    }
                }
            }
        }
        
        matrix(T A[row_size]){
            for(size_t i=0;i<row_size;i++){
                M[i][0]=A[i];
            }
        }
        matrix(T A[row_size][col_size]){
            for(size_t i=0;i<row_size;i++){
                for(size_t j=0;j<col_size;j++){
                    M[i][j]=A[i][j];
                }
            }
        }
        matrix(T **A){
            for(size_t i=0;i<row_size;i++){
                for (size_t j = 0; j < col_size; j++){
                    M[i][j]=A[i][j];
                }
            }
        }
        matrix(matrix<T,row_size,col_size> &m){
            for(size_t i=0;i<row_size;i++){
                for (size_t j = 0; j < col_size; j++){
                    this->M[i][j]=m.M[i][j];
                }
            }
        }
        ~matrix(){}
 
        matrix<T,row_size,col_size> operator+(matrix<T,row_size,col_size>& m){
            matrix<T,row_size,col_size> result;
            for(size_t i=0;i<row_size;i++){
                for (size_t j=0;j<col_size;j++){
                    result.M[i][j]=this->M[i][j]+m.M[i][j];
                }
                
            }
            return result;
        }
        matrix<T,row_size,col_size> operator*(const long& l){
            matrix<T,row_size,col_size> result;
            for(int i=0;i<row_size;i++){
                for(int j=0;j<col_size;j++){
                    result.M[i][j]=this->M[i][j]*l;
                }
            }
            return result;
        } 
        template<size_t new_col_size>
        matrix<T,row_size,new_col_size> operator*(matrix<T,row_size,new_col_size>& m){
            matrix<T,row_size,new_col_size> result;
            T temp=(T)0;
            for(size_t i=0;i<row_size;i++){
                for(size_t j=0;j<new_col_size;j++){
                    for (size_t k = 0; k <col_size; k++){
                        temp+=this->M[i][k]*m(k,j);
                    }
                    result(i,j,temp);
                    temp=(T)0;
                } 
            }
            return result;
        }
        matrix<T,row_size,col_size>& operator=(const matrix<T,row_size,col_size>& m){
            if (this == &m) {
                return *this;
            }
            for(size_t i=0;i<row_size;i++){
                for(size_t j=0;j<col_size;j++){
                    this->M[i][j]=m.M[i][j];
                }
            }
            return *this;
        }
        T operator()(size_t i,size_t j){
            if(i<row_size&&j<col_size){
                return M[i][j];
            }else{
                return (T)0;
            }
        }
        void operator()(size_t i,size_t j,T element){
            if(i<row_size&&j<col_size){
                M[i][j]=element;
            }
        }

        matrix<T,col_size,row_size> transponce(){
            matrix<T,col_size,row_size> result;
            for(size_t i=0;i<col_size;i++){
                for (size_t j=0;j<row_size;j++){
                    result(i,j,this->M[j][i]);
                }
            }
            return result;
        }

        T find_max_element_over_diagonal(size_t& i_max,size_t& j_max){
            T max=abs(M[0][1]);
            i_max=0;
            j_max=1;
            for(int i=0;i<row_size;i++){
                for(int j=i+1;j<col_size;j++){
                    if(abs(M[i][j])>max){
                        max=M[i][j];
                        i_max=i;
                        j_max=j;
                    }
                }
            }
            return max;
        }

        void print(){
            for(size_t i=0; i<row_size; i++){
                for(size_t j=0; j<col_size; j++){
                    cout<<"     ";
                    cout << M[i][j];
                }
                cout << endl;
            }
        }
        
        void print_to_file(string filename){
            fstream fout(filename,ios::app);
            for(size_t i=0; i<row_size; i++){
                for(size_t j=0; j<col_size; j++){
                    fout<<"     ";
                    fout << M[i][j];
                }
                fout << endl;
            }
        }

        //the sum of diagonal elements
        T trace(){
            T sum=(T)0;
            if(row_size==col_size){
                for(size_t i=0;i<row_size;i++){
                    sum+=M[i][i];
                }
            }
            return sum;
        }

        //the sum of non diagonal elements;
        T calculate_non_diagonal_elements(){
            T sum=(T)0;
            for(size_t i=0;i<row_size;i++){
                for(size_t j=i;j<col_size;j++){
                    if(i==j){
                        continue;
                    }
                    sum+=M[i][j];
                }
            }
            return sum;
        }
        //the sum of square of elements;
        T spherical_norm(){
            T sum=(T)0;
            for(size_t i=0;i<row_size;i++){
                for(size_t j=i;j<col_size;j++){
                    sum+=M[i][j]*M[i][j];
                }
            }
            return sum;
        }
        
};