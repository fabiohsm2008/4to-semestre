#include <iostream>
#include <vector>

using namespace std;

template <typename G>
struct CNode{
    typedef typename G::Edge Edge;
    typedef typename G::n N;
    N m_data;
    int id;
    vector<Edge*> m_edges;
    bool visitado;
    CNode(N valor){m_data = valor; visitado = 0;};
    void pintar(){visitado = 1;};
};

template <class G>
struct CEdge{
    typedef typename G::Node Node;
    typedef typename G::e E;
    Node* m_nodes[2];
    E m_data;
    bool m_dir;
    CEdge(E valor){m_data = valor;};
};

template <class G>
struct Cam{
    typedef typename G::Node Node;
    typedef typename G::e E;
    vector<Node*> nodos_recorrido;
    E peso_actual;
    Cam(Node *actual){nodos_recorrido.push_back(actual); peso_actual = 0;};
    void imprimir(){
        int i;
        for(i = 0; i < nodos_recorrido.size()-1; i++){
            cout << nodos_recorrido[i]->m_data << "---->";
        }
        cout << nodos_recorrido[i]->m_data << " " << peso_actual << endl;
    };
};

template <class N, class E>
class CGraph{
public:
    typedef CGraph<N,E> Self;
    typedef CNode<Self> Node;
    typedef CEdge<Self> Edge;
    typedef Cam<Self> Recorrido;
    typedef N n;
    typedef E e;
    vector<Node*> m_node;
    bool buscar_nodo(n dato, int &pos){
        for(int i = 0; i < m_node.size(); i++){
            if(m_node[i]->m_data == dato){
                pos = i;
                return 1;
            }
        }
        return 0;
    }
    bool buscar_arista(e dato, int indice, int &pos){
        for(int i = 0; i < m_node[indice]->m_edges.size(); i++){
            if(m_node[indice]->m_edges[i]->m_data == dato){
                pos = i;
                return 1;
            }
        }
        return 0;
    }
    bool search_arista(e dato, int indice){
        for(int i = 0; i < m_node[indice]->m_edges.size(); i++){
            if(m_node[indice]->m_edges[i]->m_data == dato){
                return 1;
            }
        }
        return 0;
    }
    bool insertNode(n dato){
        int pos;
        if(buscar_nodo(dato,pos)) return 0;
        Node *nuevo = new Node(dato);
        nuevo->id = m_node.size();
        m_node.push_back(nuevo);
        return 1;
    }
    bool insertEdge(n nodo1, n nodo2, e dato, bool direccion){
        int actual1, actual2;
        if(!(buscar_nodo(nodo1,actual1) && buscar_nodo(nodo2,actual2))) return 0;
        if(search_arista(dato, actual1) && search_arista(dato,actual2)) return 0;
        Edge *nuevo = new Edge(dato);
        nuevo->m_dir = direccion;
        nuevo->m_nodes[0] = m_node[actual1];
        nuevo->m_nodes[1] = m_node[actual2];
        m_node[actual1]->m_edges.push_back(nuevo);
        m_node[actual2]->m_edges.push_back(nuevo);
        return 1;
    }
    bool removeEdge(n nodo1, n nodo2, e dato){
        int actual1, actual2, pos1, pos2;
        if(!(buscar_nodo(nodo1,actual1) && buscar_nodo(nodo2,actual2))) return 0;
        if(!(buscar_arista(dato, actual1, pos1) && buscar_arista(dato, actual2, pos2))) return 0;
        m_node[actual1]->m_edges.erase(m_node[actual1]->m_edges.begin()+pos1);
        m_node[actual2]->m_edges.erase(m_node[actual2]->m_edges.begin()+pos2);
        return 1;
    }
    bool deleteNode(n dato){
        int actual;
        if(!buscar_nodo(dato,actual)) return 0;
        for(int i = 0; i < m_node[actual]->m_edges.size(); i++){
            removeEdge(m_node[actual]->m_edges[i]->m_nodes[0]->m_data,m_node[actual]->m_edges[i]->m_nodes[1]->m_data,m_node[actual]->m_edges[i]->m_data);
        }
        m_node.erase(m_node.begin()+actual);
        return 1;
    }
    void imprimir_nodos(){
        for(int i = 0; i < m_node.size(); i++){
            cout << m_node[i]->m_data << " " << m_node[i]->id << endl;
        }
    }
    void imprimir_edge(){
        for(int i = 0; i < m_node.size(); i++){
            for(int j = 0; j < m_node[i]->m_edges.size(); j++){
                if(!(pos_node(m_node[i]->m_edges[j],m_node[i]))){
                    cout << m_node[i]->m_edges[j]->m_data << ": " << m_node[i]->m_edges[j]->m_nodes[0]->m_data << " " << m_node[i]->m_edges[j]->m_nodes[1]->m_data << endl;
                }
            }
        }
    }
    bool pos_node(Edge *arista, Node *actual){
        if(arista->m_nodes[0] == actual) return 0;
        return 1;
    }
    Recorrido camino(vector<Recorrido> lerute, Node *actual){
        for(int i = 0; i < lerute.size(); i++){
            if(lerute[i].nodos_recorrido[lerute[i].nodos_recorrido.size()-1] == actual) return lerute[i];
        }
        return Recorrido(actual);
    }
    bool bus_rec(Recorrido r, Node *n){
        for(int i = 0; i < r.nodos_recorrido.size(); i++){
            if(r.nodos_recorrido[i] == n){
                return 1;
            }
        }
        return 0;
    }
    void nivelar(vector<Recorrido> &res){
        bool rpta = true;
        while(rpta){
            rpta = false;
            for(int i = 0; i < res.size(); i++){
                for(int j = i+1; j < res.size(); j++){
                    if(res[i].nodos_recorrido[0] == res[j].nodos_recorrido[0] && res[i].nodos_recorrido[res[i].nodos_recorrido.size()-1] == res[j].nodos_recorrido[res[j].nodos_recorrido.size()-1]){
                        if(res[i].peso_actual < res[j].peso_actual){
                            res.erase(res.begin()+j);
                        }
                        else{
                            res.erase(res.begin()+i);
                        }
                        rpta = true;
                    }
                }
            }
        }
    }
    void busqueda(vector<Recorrido> &res, Node *n, Edge *arista){
        Recorrido act = camino(res, arista->m_nodes[0]);
        act.nodos_recorrido.push_back(arista->m_nodes[1]);
        act.peso_actual += arista->m_data;
        res.push_back(act);
        for(int i = 0; i < n->m_edges.size(); i++){
                if(!(pos_node(n->m_edges[i],n) && n->m_edges[i]->m_dir)){
                    if(!bus_rec(act,n->m_edges[i]->m_nodes[1])){
                        nivelar(res);
                        busqueda(res, n->m_edges[i]->m_nodes[1], n->m_edges[i]);
                    }
                }
            }
    }
    void Dikjstra(n nombre){
        vector<Recorrido> resultado;
        int pos;
        if(buscar_nodo(nombre,pos)){
            Recorrido actual(m_node[pos]);
            resultado.push_back(actual);
            for(int i = 0; i < m_node[pos]->m_edges.size(); i++){
                if(!(pos_node(m_node[pos]->m_edges[i],m_node[pos]) && m_node[pos]->m_edges[i]->m_dir)){
                        busqueda(resultado, m_node[pos]->m_edges[i]->m_nodes[1], m_node[pos]->m_edges[i]);
                }
            }
        }
        nivelar(resultado);
        for(int i = 0; i < resultado.size(); i++){
            resultado[i].imprimir();
        }
    }
};

int main(){
    CGraph<char,int> hola;
    hola.insertNode('1');
    hola.insertNode('2');
    hola.insertNode('3');
    hola.insertNode('4');
    hola.insertNode('5');
    hola.insertNode('6');
    hola.imprimir_nodos();
    cout << endl;

    hola.insertEdge('1', '2', 7, 0);
    hola.insertEdge('1', '3', 9, 0);
    hola.insertEdge('1', '6', 14, 0);
    hola.insertEdge('2', '4', 15, 0);
    hola.insertEdge('2', '3', 10, 0);
    hola.insertEdge('3', '6', 2, 0);
    hola.insertEdge('3', '4', 11, 0);
    hola.insertEdge('6', '5', 9, 0);
    hola.insertEdge('4', '5', 6, 0);
    hola.imprimir_edge();
    cout << endl;

    hola.Dikjstra('1');
    return 0;
}

