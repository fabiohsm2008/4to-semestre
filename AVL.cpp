#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct node{
    T valor;
    node<T>* hijos[2];
    int nivel = 0;
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
    void actu_altura(node<T>* hola){
        int izq = 0;
        int der = 0;
        if(hola->hijos[0]) izq += hola->hijos[0]->nivel + 1;
        if(hola->hijos[1]) der += hola->hijos[1]->nivel + 1;
        if(izq>der) hola->nivel = izq;
        else hola->nivel = der;
    }
    bool balanceo(node<T> *hola){

    }
    bool buscar(T x, node<T> **&p, vector<node<T>*> &res){
        for(p = &raiz; (*p) && ((*p)->valor != x); p = &((*p)->hijos[comparacion((*p)->valor,x)])){
            res.push_back(*p);
        };
        return (*p) != 0;
    };
    bool insertar(T x){
        node<T> **p;
        vector<node<T>*> recorrido;
        if(buscar(x, p, recorrido)) return 0;
        *p = new node<T>(x);
        for(int i = recorrido.size()-1; i >= 0; i--){
            actu_altura(recorrido[i]);
        }
        return 1;
    };
    bool eliminar(T x){
        node<T> **p;
        vector<node<T>*> recorrido;
        if(!buscar(x, p, recorrido)) return 0;
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
            if(p->hijos[1]) cout << p->hijos[1]->valor << " ";
            else cout << "NULO ";
            cout << p->nivel << endl;
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
    arbol.insertar(7);
    arbol.insertar(8);
    arbol.insertar(9);
    arbol.imprimir();
    return 0;
}
