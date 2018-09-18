#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

template <typename T>
vector<vector<T> > suma(vector<vector<T> > A, vector<vector<T> > B){
    for(size_t i = 0; i < A.size(); ++i){
        for(size_t j = 0; j < A[0].size(); ++j){
            A[i][j] = A[i][j] + B[i][j];
        }
    }
    return A;
}

template <typename T>
vector<vector<T> > resta(vector<vector<T> > A, vector<vector<T> > B){
    for(size_t i = 0; i < A.size(); ++i){
        for(size_t j = 0; j < A[0].size(); ++j){
            A[i][j] = A[i][j] - B[i][j];
        }
    }
    return A;
}

template <typename T, typename E>
vector<vector<T> > escalar(vector<vector<T> > A, E B){
    for(size_t i = 0; i < A.size(); ++i){
        for(size_t j = 0; j < A[0].size(); ++j){
            A[i][j] = A[i][j] * B;
        }
    }
    return A;
}

template <typename T>
vector<vector<T> > producto(vector<vector<T> > A, vector<vector<T> > B){
    vector<vector<T> > rpta;
    vector<T> temp(B[0].size());
    for(size_t i = 0; i < A.size(); ++i){
        rpta.push_back(temp);
    }
    int temp_suma;
    for(size_t i = 0; i < A.size(); ++i){
        for(size_t j = 0; j < B[0].size(); ++j){
            temp_suma = 0;
            for(size_t k = 0; k < B.size(); ++k){
                temp_suma += A[i][k] * B[k][j];
            }
            rpta[i][j] = temp_suma;
        }
    }
    return rpta;
}

template <typename T>
vector<vector<T> > trampuesta(vector<vector<T> > A){
    vector<vector<T> > rpta;
    vector<T> temp(A.size());
    for(size_t i = 0; i < A[0].size(); ++i){
        rpta.push_back(temp);
    }
    for(size_t i = 0; i < A.size(); ++i){
        for(size_t j = 0; j < A[0].size(); ++j){
            rpta[j][i] = A[i][j];
        }
    }
    return rpta;
}

template <typename T>
T determinante(vector<vector<T> > A){
    if(A.size() == 1){
        return A[0][0];
    }

    T rpta = 0;
    vector<vector<T> > mat_temp;
    vector<T> temp(A.size()-1);
    for(size_t i = 0; i < A.size()-1; ++i){
        mat_temp.push_back(temp);
    }

    int l = 0;
    int m = 0;
    int signo = 1;

    for(size_t i = 0; i < A.size(); ++i){
        for(size_t j = 0; j < A.size(); ++j){
            for(size_t k = 0; k < A.size(); ++k){
                if(k != i){
                    mat_temp[l][m] = A[j][k];
                    ++m;
                }
            }
            ++l;
            m = 0;
        }
        l = 0;
        rpta = rpta + (A[0][i] * determinante(mat_temp) * signo);
        signo = signo * (-1);
    }
    return rpta;
}

template <typename T, typename E>
vector<vector<T> > potencia(vector<vector<T> > A, E x){
    vector<vector<T> > rpta = A;
    for(size_t i = 1; i < x; ++i){
         rpta = producto(rpta, A);
    }
    return rpta;
}

template <typename T>
vector<vector<T> > cofactor(vector<vector<T> > A, size_t i, size_t j){
    vector<vector<T> > rpta;
    vector<T> temp(A.size()-1);
    for(size_t a = 0; a < A.size()-1; ++a){
        rpta.push_back(temp);
    }
    int m = 0;
    int n = 0;
    for(size_t k = 0; k < A.size(); ++k){
        for(size_t l = 0; l < A.size(); ++l){
            if(k != i && l != j){
                rpta[m][n] = A[k][l];
                ++n;
            }
        }
        if(n = rpta.size()) ++m;
        n = 0;
    }
    return rpta;
}

template <typename T>
vector<vector<T> > inversa(vector<vector<T> > A){
    T det = determinante(A);
    if (det != 0){
        vector<vector<T> > rpta;
        vector<T> temp(A.size());
        for(size_t a = 0; a < A.size(); ++a){
            rpta.push_back(temp);
        }
        for(size_t i = 0; i < A.size(); ++i){
            for(size_t j = 0; j < A.size(); ++j){
                if((i+j)%2 == 0){
                    rpta[i][j] = determinante(cofactor(A,i,j));
                }
                else{
                    rpta[i][j] = determinante(cofactor(A,i,j)) * (-1);
                }
            }
        }
        rpta = trampuesta(rpta);
        rpta = escalar(rpta, (1/det));
        return rpta;
    }
}

template <typename T>
vector<vector<T> > division(vector<vector<T> > A, vector<vector<T> > B){
    return producto(A, inversa(B));
}

template <typename T>
T traza(vector<vector<T> > A){
    T rpta = 0;
    for(size_t i = 0; i < A.size(); ++i) rpta += A[i][i];
    return rpta;
}

template <typename T>
T producto_interno(vector<vector<T> > A, vector<vector<T> > B){
    return traza( producto( trampuesta(A), B) );
}

void imprimir(vector<vector<int>> rpta){
    for(size_t i = 0; i < rpta.size(); ++i){
        for(size_t j = 0; j < rpta[0].size(); ++j){
            cout << rpta[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    vector<int> A;
    vector<int> B;
    vector<int> C;
    vector<int> D;
    vector<int> E;
    vector<int> F;

    A.push_back(3);
    A.push_back(-1);

    B.push_back(2);
    B.push_back(0);

    C.push_back(5);
    C.push_back(-2);

    D.push_back(1);
    D.push_back(-1);

    E.push_back(0);
    E.push_back(1);

    F.push_back(4);
    F.push_back(-3);

    vector<vector<int>> primero;
    vector<vector<int>> segundo;

    primero.push_back(A);
    primero.push_back(B);
    primero.push_back(C);

    segundo.push_back(D);
    segundo.push_back(E);
    segundo.push_back(F);

    cout << producto_interno(primero, segundo);

    return 0;
}
