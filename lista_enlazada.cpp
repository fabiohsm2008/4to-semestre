#include <iostream>

using namespace std;

template <typename T>

class nodo{
public:
    T Dato;
    nodo* next;
    nodo(){};
    nodo(T s, nodo* sgt){
        Dato = s;
        next = sgt;
    };
    ~nodo(){};
};

template <typename Q>
class lista{
private:
    nodo <Q> *head;
public:
    lista(nodo <Q> x){
        head = &x;
    };
    void imprimir(){
        nodo<Q> *temp = head;
        while(temp != NULL){
            cout << (temp)->Dato << " ";
            temp = (temp)->next;
        }
    };
    bool buscar(Q a, nodo<Q>**& p){
        nodo<Q> *guardar = head;
        while(a > (*p)->Dato && (*p)->next != NULL){
            *p = (*p)->next;
        }
        head = guardar;
        if((*p)->Dato == a){
            return 1;
        }
        else{
            return 0;
        }
    };
    void insertar(Q a){
        nodo<Q> **temp = &head;
        if(!buscar(a,temp)){
            nodo<Q> *nuevo = new nodo<Q>(a,(*temp)->next);
            (*temp)->next = nuevo;
        }
    };
    void borrar(Q a){

    };
};

int main(){
    nodo<int> head(0,NULL);
    lista<int> prueba(head);
    prueba.insertar(2);
    prueba.insertar(3);
    prueba.insertar(4);
    prueba.insertar(5);
    prueba.imprimir();
    return 0;
}
