#include <iostream>

using namespace std;

template <class T>
class nodo{
public:
    T valor;
    nodo<T> *next;
    nodo(T dato, nodo<T> *sgt){valor = dato; next = sgt;};
};

template <class T>
class lista{
public:
    nodo<T> *head;
    lista(){head = NULL;};
    bool buscar(T dato, nodo<T> **& p){
        if(!*p) return 0;
        while((*p)->valor < dato){
            p = &((*p)->next);
            cout << "flhnajkas";
            if(*p == head)  return 0;
        }
        cout << "flhnajkas";
        return (*p)->valor == dato;
    };
    bool insertar(T dato){
        nodo<T> **p = &head;
        if(buscar(dato, p)) return 0;
        cout << "flhnajkas";
        nodo<T> *nuevo = new nodo<T>(dato,*p);
        if(*p){
            head = nuevo;
            head->next = head;
            return 1;
        };
        p = &nuevo;
        return 1;
    }
    bool borrar(T dato){

    };
    void imprimir(){
        nodo<T> *p = head;
        if(p == NULL){
            cout << "Vacio" << endl;
        }
        else{
            cout << p->valor << " ";
            p = p->next;
            while(p != head){
                cout << p->valor << " ";
            }
        }
    }
};

int main(){
    lista<int> prueba;
    prueba.imprimir();
    prueba.insertar(0);
    prueba.imprimir();
    prueba.insertar(1);
    prueba.imprimir();
    return 0;
}
