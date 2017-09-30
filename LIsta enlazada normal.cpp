#include <iostream>

using namespace std;

template <typename T>
class nodo{
public:
    T valor;
    nodo<T> *next;
    nodo(T a){
        valor = a;
        next = NULL;
    };
};

template <typename T>
class lista{
private:
    nodo<T> *head;
public:
    lista(){head = NULL;};
    bool insertar(T a){
        nodo<T> *nuevo = new nodo<T>(a);
        nodo<T> *temp = head;
        if(head == NULL){
            head = nuevo;
            return 1;
        }
        if(a < head->valor){
            nuevo->next = head;
            head = nuevo;
            return 1;
        }
        nodo<T> *p = temp->next;
        while(p != NULL && p->valor < a){
            temp = p;
            p = p->next;
        }
        if(p == NULL){
            if(temp->valor == a){
                return 0;
            }
        }
        if(temp->valor < a){
            temp->next = nuevo;
            nuevo->next = p;
            return 1;
        }
    }
    bool borrar(T a){
        if(head == NULL){
            return 0;
        }
        if(head->valor == a){
            nodo<T> *elim = head;
            head= head->next;
            delete elim;
            return 1;
        }
        nodo<T> *temp = head;
        nodo<T> *p = temp->next;
        while(p != NULL && p->valor < a){
            temp = p;
            p = p->next;
        }
        if(p == NULL){
            if(temp->valor == a){
                delete temp;
                return 1;
            }
            return 0;
        }
        if(p->valor == a){
            nodo<T> *elim = p;
            temp->next = p->next;
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
    prueba.insertar(1);
    prueba.insertar(3);
    prueba.insertar(4);
    prueba.insertar(2);
    prueba.insertar(6);
    prueba.insertar(5);
    prueba.insertar(7);

    prueba.imprimir();

    prueba.borrar(10);
    prueba.borrar(0);
    prueba.borrar(3);
    prueba.borrar(2);
    prueba.borrar(7);

    prueba.imprimir();

    prueba.borrar(6);
    prueba.borrar(4);
    prueba.borrar(5);
    prueba.borrar(1);

    prueba.imprimir();

    return 0;
}
