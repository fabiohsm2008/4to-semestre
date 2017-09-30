#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


void generar(int *a, long long tam){
    for(int i = 0; i < tam; i++){
        a[i] = rand()%10000;
    }
}

void imprimir(int *a, int tam){
    cout << "[";
    for(int i = 0; i < tam; i++){
        if(i != tam-1){
            cout << a[i] << ",";
        }
        else{
            cout << a[i];
        }
    }
    cout << "]" << endl;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

template <typename Q>
class cocktail{
private:
    Q m_c;
public:
    cocktail(){};;
    void ordenar(int *p, int *q){
        int *temp=p;
        bool intercambio=1;
        while(intercambio==1&&q>p){
            intercambio=0;
            for(;p<q;p++){
                if(m_c.comparar(p,p+1)){
                    swap(p,p+1);
                    intercambio=1;
                }
            }
            for(;q>temp;q--){
                if(m_c.comparar(q-1,q)){
                    swap(q-1,q);
                    intercambio=1;
                }
            }
            temp=q;
            q=p;
            temp++;
            p=temp;
            q--;
        }
    };

};

template <typename T>
class cmp_mayor{
public: inline bool comparar(T *a, T *b){
        return (*a > *b);
    }
};

template <typename T>
class cmp_menor{
public: inline bool comparar(T *a, T *b){
        return (*a < *b);
    }
};

int main(){
    srand(time(NULL));
    int *a = new int[100000];

    generar(a,100000);
    //imprimir(a,100000);
    cocktail <cmp_mayor<int> > prueba;
    prueba.ordenar(a,a+100000-1);
    //imprimir(a,100000);
    return 0;
}
