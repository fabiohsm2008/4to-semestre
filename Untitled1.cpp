#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void swap(int *a, int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

void generar(int *a, int tam){
    srand(time(NULL));
    for(int i = 0; i < tam; i++){
        a[i] = rand()%100000;
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

template <class T>
class comparaciones{
public:
    bool menor(T *a, T *b){
        return (*a > *b);
    }

    bool mayor(T *a, T *b){
        return (*a < *b);
    }
};


class cocktail{
public:
    comparaciones<int> w;
    bool (comparaciones<int>:: *comparar)(int *a, int *b);
    cocktail(bool (comparaciones<int>::*orden)(int *a, int *b)){comparar = orden;};
    void ordenar(int *p, int *q){
        int *temp=p;
        bool intercambio=1;
        while(intercambio==1&&q>p){
            intercambio=0;
            for(;p<q;p++){
                if((w.*comparar)(p,p+1)){
                    swap(p,p+1);
                    intercambio=1;
                }
            }
            for(;q>temp;q--){
                if((w.*comparar)(q-1,q)){
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


int main()
{
    srand(time(NULL));
    int *a = new int[10000];

    generar(a,10000);
    //imprimir(a,100000);
    comparaciones<int> w;
    cocktail prueba(w.menor);
    prueba.ordenar(a,a+10000-1);
    //imprimir(a,100000);

    return 0;
}
