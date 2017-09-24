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

class cocktail{
public:
    cocktail(){};
    virtual bool comparar(int *a, int *b) = 0;
    void ordenar(int *p, int *q){
        int *temp=p;
        bool intercambio=1;
        while(intercambio==1&&q>p){
            intercambio=0;
            for(;p<q;p++){
                if(comparar(p,p+1)){
                    swap(p,p+1);
                    intercambio=1;
                }
            }
            for(;q>temp;q--){
                if(comparar(q-1,q)){
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

class mayor: public cocktail{
public:
    bool comparar(int *a, int *b){
        return (*a > *b);
    }
};

class menor: public cocktail{
public:
    bool comparar(int *a, int *b){
        return (*a < *b);
    }
};

int main(){
    srand(time(NULL));
    int *a = new int[100000];

    generar(a,100000);
    //imprimir(a,1000000);
    cout << endl;
    mayor valor;
    time_t inicio = time(NULL);
    valor.ordenar(a,(a+100000-1));
    time_t fin = time(NULL);
    cout << "Duracion del algoritmo: " << difftime(fin,inicio) << endl;
    //imprimir(a,100000);
    return 0;
}
