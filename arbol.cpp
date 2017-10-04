#include <iostream>

using namespace std;

template <typename T>
void change(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
class nodo{
public:
    T valor;
    nodo<T> *izq;
    nodo<T> *der;
    nodo(T dato){valor = dato; izq = NULL; der = NULL;};
    nodo(T dato, nodo<T> *left, nodo<T> *right){valor = dato; izq = left; der = right;};
};

template <typename T>
class arbol{
public:
    nodo<T> *raiz;
    arbol(nodo<T> *x){raiz = x;};
    bool buscar(T dato, nodo<T> **&p){
        while((*p) && (*p)->valor != dato){
            cout << (*p)->valor << endl;
            if(dato < (*p)->valor){
                p = &((*p)->izq);
            }
            else {
                p = &((*p)->der);
            }
        }
        return (*p) && (*p)->valor == dato;
    };
    bool insertar(T dato){
        nodo<T> **p = &raiz;
        if(buscar(dato,p)) return 0;
        nodo<T> *nuevo = new nodo<T>(dato);
        *p = nuevo;
        return 1;

    };
    bool borrar(T dato){
        nodo<T> **p = &raiz;
        if(!buscar(dato,p)) return 0;
        if((*p)->izq == NULL){
            if((*p)->der == NULL){
                nodo<T> *elim = *p;
                delete elim;
                *p = NULL;
                return 1;
            }
            nodo<T> **temp = &((*p)->der);
            while((*temp)->izq != NULL){
                temp = &((*temp)->izq);
            }
            change((*temp)->valor, (*p)->valor);
            delete temp;
            *temp = NULL;
            return 1;
        }
        if((*p)->der == NULL){
            nodo<T> **temp = &((*p)->izq);
            while((*temp)->der != NULL){
                temp = &((*temp)->der);
            }
            change((*temp)->valor, (*p)->valor);
            delete temp;
            *temp = NULL;
            return 1;
        }

    };
    void imprimir(){

    };
};

int main(){

    nodo<int> *n1 = new nodo<int>(1);
    nodo<int> *n2 = new nodo<int>(2);
    nodo<int> *n3 = new nodo<int>(3);
    nodo<int> *n4 = new nodo<int>(4);
    nodo<int> *n5 = new nodo<int>(5);
    nodo<int> *n6 = new nodo<int>(6);
    nodo<int> *n7 = new nodo<int>(7);

    n4->izq = n2;
    n4->der = n6;
    n2->izq = n1;
    n2->der = n3;
    n6->izq = n5;
    n6->der = n7;

    arbol<int> prueba(n4);

    nodo<int> **p = &(prueba.raiz);
    prueba.insertar(8);
    cout << endl;
    prueba.borrar(7);
    cout << prueba.buscar(9,p) << endl;
    return 0;
}
