#include <iostream>
using namespace std;

template <typename T, size_t row_size, size_t col_size>
class matrix{
    private:
        T M[row_size][col_size];
    public:
        T getElement(size_t i,size_t j){
            return M[i][j];
        }
        void setElement(size_t i,size_t j,T element){
            M[i][j]=element;
        }

        matrix(){  
            for (size_t i=0; i<row_size; i++){
                for(size_t j=0;j<col_size;j++){
                    M[i][j]=(T)0;
                }
            }
        }
        matrix(T A[row_size]){
            for(int i=0;i<row_size;i++){
                M[i][0]=A[i];
            }
        }
        matrix(T A[row_size][col_size]){
            for(int i=0;i<row_size;i++){
                for(int j=0;j<col_size;j++){
                    M[i][j]=A[i][j];
                }
            }
        }
        ~matrix(){}
 
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
            for(int i=0;i<row_size;i++){
                for(int j=0;j<new_col_size;j++){
                    for (int k = 0; k <col_size; k++){
                        temp+=this->M[i][k]*m.getElement(k,j);
                    }
                    result.setElement(i,j,temp);
                    temp=(T)0;
                } 
            }
            return result;
        }

        T find_max_over_diagonal(size_t& i_max,size_t& j_max){
            T max=M[0][1];
            for(int i=0;i<row_size;i++){
                for(int j=i+1;j<col_size;j++){
                    if(M[i][j]>max){
                        max=M[i][j];
                        i_max=i;
                        j_max=j;
                    }
                }
            }
            return max;
        }

        void print()
        {
            for(int i=0; i<row_size; i++){
                for(int j=0; j<col_size; j++){
                    cout<<"     ";
                    cout << M[i][j];
                }
                cout << endl;
            }
        }
 
        
};