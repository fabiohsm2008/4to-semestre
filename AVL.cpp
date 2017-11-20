#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>

using namespace std;

template <class T>
struct node{
    T valor;
    node<T>* hijos[2];
    int altura_izq = 0;
    int altura_der = 0;
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

    void actu_altura(node<T> **&hola){
        if((*hola)->hijos[0]){
            if((*hola)->hijos[0]->altura_izq < (*hola)->hijos[0]->altura_der){
                (*hola)->altura_izq = (*hola)->hijos[0]->altura_der + 1;
            }
            else{
                (*hola)->altura_izq = (*hola)->hijos[0]->altura_izq + 1;
            }
        }
        else{
            (*hola)->altura_izq = 0;
        }
        if((*hola)->hijos[1]){
            if((*hola)->hijos[1]->altura_izq < (*hola)->hijos[1]->altura_der){
                (*hola)->altura_der = (*hola)->hijos[1]->altura_der + 1;
            }
            else{
                (*hola)->altura_der = (*hola)->hijos[1]->altura_izq + 1;
            }
        }
        else{
            (*hola)->altura_der = 0;
        }
    }
    bool balanceo(node<T> **&hola){
        node<T> *nuevo;
        if((*hola)->altura_der - (*hola)->altura_izq == -2){
            if((*hola)->hijos[0]->altura_izq >= (*hola)->hijos[0]->altura_der){
                nuevo = (*hola)->hijos[0];
                (*hola)->hijos[0] = nuevo->hijos[1];
                nuevo->hijos[1] = (*hola);
                (*hola) = nuevo;
                node<T> **temp = &(*hola)->hijos[0];
                node<T> **temp1 = &(*hola)->hijos[1];
                actu_altura(temp);
                actu_altura(temp1);
                actu_altura(hola);
                return 1;
            }
            else{
                nuevo = (*hola)->hijos[0]->hijos[1];
                (*hola)->hijos[0]->hijos[1] = nuevo->hijos[0];
                nuevo->hijos[0] = (*hola)->hijos[0];
                (*hola)->hijos[0] = nuevo->hijos[1];
                nuevo->hijos[1] = (*hola);
                (*hola) = nuevo;
                node<T> **temp = &(*hola)->hijos[0];
                node<T> **temp1 = &(*hola)->hijos[1];
                actu_altura(temp);
                actu_altura(temp1);
                actu_altura(hola);
                return 1;
            }
        }
        else if((*hola)->altura_der - (*hola)->altura_izq == 2){
            if((*hola)->hijos[1]->altura_der >= (*hola)->hijos[1]->altura_izq){
                nuevo = (*hola)->hijos[1];
                (*hola)->hijos[1] = nuevo->hijos[0];
                nuevo->hijos[0] = (*hola);
                (*hola) = nuevo;
                node<T> **temp = &(*hola)->hijos[0];
                node<T> **temp1 = &(*hola)->hijos[1];
                actu_altura(temp);
                actu_altura(temp1);
                actu_altura(hola);
                return 1;
            }
            else{
                nuevo = (*hola)->hijos[1]->hijos[0];
                (*hola)->hijos[1]->hijos[0] = nuevo->hijos[1];
                nuevo->hijos[1] = (*hola)->hijos[1];
                (*hola)->hijos[1] = nuevo->hijos[0];
                nuevo->hijos[0] = (*hola);
                (*hola) = nuevo;
                node<T> **temp = &(*hola)->hijos[0];
                node<T> **temp1 = &(*hola)->hijos[1];
                actu_altura(temp);
                actu_altura(temp1);
                actu_altura(hola);
                return 1;
            }
        }
        return 0;
    }
    bool buscar(T x, node<T> **&p, vector<node<T>**> &res){
        for(p = &raiz; (*p) && ((*p)->valor != x); p = &((*p)->hijos[comparacion((*p)->valor,x)])){
            res.push_back(p);
        };
        return (*p) != 0;
    };
    bool insertar(T x){
        node<T> **p;
        vector<node<T>**> recorrido;
        if(buscar(x, p, recorrido)) return 0;
        *p = new node<T>(x);
        for(int i = recorrido.size()-1; i >= 0; i--){
            actu_altura(recorrido[i]);
            balanceo(recorrido[i]);
        }
        return 1;
    };
    bool eliminar(T x){
        node<T> **p;
        vector<node<T>**> recorrido;
        if(!buscar(x, p, recorrido)) return 0;
        if((*p)->hijos[0] && (*p)->hijos[1]){
            node<T> **q = p;
            q = &((*q)->hijos[1]);
            while((*q)->hijos[0]){
                q = &((*q)->hijos[0]);
            }
            (*p)->valor = (*q)->valor;
            p = q;
        }
        node<T> *t = *p;
        *p = (*p)->hijos[(*p)->hijos[1] != 0];
        delete t;
        for(int i = recorrido.size()-1; i >= 0; i--){
            actu_altura(recorrido[i]);
            balanceo(recorrido[i]);
        }
        return 1;
    };
    void pre_orden(node<T> *p){
        if(p){
            cout << "Nodo " << p->valor << "->" << "Hijos: ";
            if(p->hijos[0]) cout << p->hijos[0]->valor << ", ";
            else cout << "NULO, ";
            if(p->hijos[1]) cout << p->hijos[1]->valor << " ";
            else cout << "NULO ";
            cout << "(" << p->altura_izq << " " << p->altura_der << ")" << endl;
            pre_orden(p->hijos[0]);
            pre_orden(p->hijos[1]);
        }
    };
    void imprimir(){
        pre_orden(raiz);
        cout << endl;
    };
    void print(node <T> *p, int indent = 0)
    {
        if(p != NULL) {
            if(p->hijos[1])
            {
                print(p->hijos[1], indent + 4);
            }
            if(indent)
            {
                cout << setw(indent) << ' ';
            }
            if(p->hijos[1]) cout <<" /\n" << setw(indent) << ' ';
            cout << p->valor << "\n ";
            //cout << p->value << "(" << p->h_l << "," << p->h_r << ")" << "\n ";
            if(p->hijos[0])
            {
                cout << setw(indent) << ' ' << " \\\n";
                print(p->hijos[0], indent + 4);
            }
        }
    }
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
    arbol.insertar(8);
    arbol.insertar(3);
    arbol.insertar(7);
    arbol.insertar(2);
    arbol.insertar(9);
    arbol.insertar(4);
    arbol.insertar(5);
    arbol.insertar(6);
    //arbol.print(arbol.raiz);
    arbol.imprimir();
    cout << "------------------------------------" << endl;
    arbol.eliminar(2);
    arbol.imprimir();
    //arbol.print(arbol.raiz);

    return 0;
}

