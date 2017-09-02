#include <iostream>

using namespace std;

template <typename T>

class nodo{
private:
    T Dato;
    nodo* next;
public:
    nodo(T s, nodo* sgt){
        Dato = s;
        next = sgt;
    };
    ~nodo(){};
    void imprimir(){
        nodo *temp = next;
        while(temp != NULL){
            cout << Dato << " ";
            temp = temp->next;
        }
    };
    bool buscar(T a, nodo** p){
        nodo *temp = next;
        while(temp != NULL){
            if(*temp->Dato == a){
                *p = temp;
                return true;
            }
        }
        return false;
    };
    void insertar(T a){

    };
    void borrar(T a){

    };
};

int main(){
    nodo<int> head(0,NULL);
    return 0;
}
