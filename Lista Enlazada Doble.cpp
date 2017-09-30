#include <iostream>

using namespace std;

template <typename T>
class nodo{
public:
    T valor;
    nodo<T> *next;
    nodo<T> *prev;
    nodo(T a){
        valor = a;
        next = NULL;
        prev = NULL;
    };
};

template <typename T>
class lista{
private:
    nodo<T> *head;
    nodo<T> *tail;
public:
    lista(){head = NULL; tail = NULL;};
    bool insertar(T a){
        nodo<T> *nuevo = new nodo<T>(a);
        if(head == NULL){
            head = nuevo;
            tail = nuevo;
            return 1;
        }
        nodo<T> *temp = head;
        if(a < head->valor){
            nuevo->next = head;
            head->prev = nuevo;
            head = nuevo;
            tail = nuevo->next;
            return 1;
        }
        if(tail->valor <= a){
            if(tail->valor == a) return 0;
            tail->next = nuevo;
            nuevo->prev = tail;
            tail = nuevo;
            return 1;
        }
        if(temp->valor < a){
            temp = temp->next;
        }
        if(temp->valor == a)return 0;
        nuevo->next = temp;
        nuevo->prev = temp->prev;
        temp->prev->next = nuevo;
        temp->prev = nuevo;
        return 1;
    }
    bool borrar(T a){
        if(head == NULL){
            return 0;
        }
        if(head->valor == a){
            nodo<T> *elim = head;
            head = head->next;
            delete elim;
            return 1;
        }
        if(tail->valor == a){
            nodo<T> *elim = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete elim;
            return 1;
        }
        nodo<T> *temp = head;
        while(temp->valor < a && temp->next != NULL){
            temp = temp->next;
        }
        if(temp->valor == a){
            nodo<T> *elim = temp;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete elim;
            return 1;
        }
        return 0;
    }
    void imprimir(){
        if(head == NULL){
            cout << "Lista Vacia" << endl;
        }
        else{
            nodo<T> *temp = head;
            while(temp->next!=NULL){
                cout << temp->valor << " ";
                temp = temp->next;
            }
            cout << temp->valor << endl;
        }
    }
};

int main(){
    lista<int> prueba;
    prueba.insertar(0);
    prueba.imprimir();
    prueba.insertar(1);
    prueba.imprimir();
    prueba.insertar(2);
    prueba.imprimir();
    prueba.insertar(3);
    prueba.imprimir();
    prueba.insertar(8);
    prueba.imprimir();
    prueba.insertar(4);
    prueba.imprimir();
    prueba.insertar(8);
    prueba.imprimir();
    prueba.insertar(5);
    prueba.imprimir();
    prueba.insertar(6);

    prueba.imprimir();

    /*prueba.borrar(10);
    prueba.imprimir();
    prueba.borrar(0);
    prueba.imprimir();
    prueba.borrar(1);
    prueba.imprimir();
    prueba.borrar(2);
    prueba.imprimir();
    prueba.borrar(4);
    prueba.imprimir();
    prueba.borrar(3);
    prueba.imprimir();

    prueba.imprimir();

    prueba.borrar(5);
    prueba.imprimir();
    prueba.borrar(8);
    prueba.imprimir();
    prueba.borrar(6);
    prueba.imprimir();
    prueba.borrar(7);
    prueba.imprimir();*/

    return 0;
}
