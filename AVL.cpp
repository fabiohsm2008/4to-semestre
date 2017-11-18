#include <iostream>

using namespace std;

template <class T>
struct node{
    T valor;
    node<T>* hijos[2];
    node(T dato){
        valor = dato;
        hijos[0] = hijos[1] = NULL;
    }
};

template <class T, class Q>
class AVL_Tree{
public:
    node<T>* raiz = NULL;
    Q comparacion;
    AVL_Tree(){};
    bool buscar(T x, node<T> **&p){
        for(p = &raiz; (*p) && ((*p)->valor != x); p = &((*p)->hijos[comparacion((*p)->valor,x)]));
        return (*p) != 0;
    };
    bool insertar(T x){
        node<T> **p;
        if(buscar(x, p)) return 0;
        *p = new node<T>(x);
        return 1;
    };
    bool eliminar(T x){
        node<T> **p;
        if(!buscar(x, p)) return 0;
        if((*p)->hijos[0] && (*p)->hijos[1]){
            node<T> **q = p;
            q = &((*q)->hijos[0]);
            while(*q){
                q = &((*q)->hijos[1]);
            }
            (*p)->valor = (*q)->valor;
            p = q;
        }
        node<T> *t = *p;
        *p = (*p)->hijos[(*p)->hijos[1] != 0];
        delete t;
        return 1;
    };
    void pre_orden(node<T> *p){
        if(p){
            cout << "Nodo " << p->valor << "->" << "Hijos: ";
            if(p->hijos[0]) cout << p->hijos[0]->valor << ", ";
            else cout << "NULO, ";
            if(p->hijos[1]) cout << p->hijos[1]->valor << endl;
            else cout << "NULO" << endl;
            pre_orden(p->hijos[0]);
            pre_orden(p->hijos[1]);
        }
    };
    void imprimir(){
        pre_orden(raiz);
    };
};

template <typename T>
class cmp_mayor{
public: inline bool operator()(T a, T b){
        return (a > b);
    }
};

template <typename T>
class cmp_menor{
public: inline bool operator()(T a, T b){
        return (a < b);
    }
};

int main(){
    AVL_Tree<int,cmp_menor<int> > arbol;
    arbol.insertar(1);
    arbol.insertar(2);
    arbol.insertar(3);
    arbol.insertar(4);
    arbol.insertar(5);
    arbol.insertar(6);
    arbol.imprimir();
    return 0;
}
