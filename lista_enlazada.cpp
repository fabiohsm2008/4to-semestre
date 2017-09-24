#include <iostream>

using namespace std;

template <typename T>

class nodo{
public:
    T Dato;
    nodo* next;
    nodo(){};
    nodo(T s){
        Dato = s;
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
        cout << endl;
    };
    bool buscar(Q a, nodo<Q>**& p){
        for(p = &head; *p && (*p)->Dato < a; p = &((*p)->next));
        return (*p) && (*p)->Dato == a;
    };
    bool insertar(Q a){
        nodo<Q> **p;
        if(buscar(a,p)) return 0;
        nodo<Q> *t = new nodo<Q>(a);
        t->next = (*p);
        *p = t;
        return 1;
    };
    bool borrar(Q a){
        nodo<Q> **p;
        if(!buscar(a,p)) return 0;
        nodo<Q>* t = *p;
        *p = (*p)->next;
        delete t;
        return 1;
    };
};

int main(){
    nodo<int> head(0);
    head.next = NULL;
    lista<int> prueba(head);
    prueba.insertar(1);
    prueba.insertar(2);
    prueba.insertar(3);
    prueba.insertar(4);
    prueba.insertar(5);
    prueba.imprimir();
    prueba.borrar(3);
    prueba.borrar(2);
    prueba.imprimir();
    return 0;
}
