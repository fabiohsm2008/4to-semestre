#include <iostream>

using namespace std;

template<class T>
struct nodo{
    T valor;
    nodo<T> *next, *prev;
    nodo(){};
    nodo(T dato){valor = dato; prev = NULL; next = NULL;};
    nodo(T dato, nodo<T> *ant, nodo<T> *sgt){valor = dato ;prev = ant; next = sgt;};
};

template<class T>
class circular{
public:
    nodo<T> *head;
    circular(){head = NULL;};
    bool buscar(T dato, nodo<T> *actual){
        if(head->valor == dato) return 1;
        while(actual != head && actual->valor < dato){
            actual = actual->next;
        }
        return (actual->valor == dato);
    }
    bool insertar(T dato){
        if (head == NULL){
            head = new nodo<T>(dato);
            head->next = head;
            head->prev = head;
            return 1;
        }
        nodo<T> *actual = head->next;
        if(buscar(dato, actual)) return 0;
        nodo<T> *nuevo = new nodo<T>(dato,actual->prev,actual);
        actual->prev->next = nuevo;
        actual->prev = nuevo;
        return 1;
    }
    void imprimir(){
        nodo<T> *actual = head;
        cout << actual->valor << " ";
        actual = actual->prev;
        while(actual != head){
            cout << actual->valor << " ";
            actual = actual->prev;
        }
        cout << endl;
    }
};

int main(){
    circular<int> temp;
    temp.insertar(1);
    temp.imprimir();
    temp.insertar(2);
    temp.imprimir();
    temp.insertar(3);
    temp.imprimir();
    temp.insertar(4);
    temp.imprimir();
    temp.insertar(5);
    temp.imprimir();
    temp.insertar(6);
    temp.imprimir();
    return 0;
}
