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
    CNode(N valor){m_data = valor;};
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
struct Recorrido{
    typedef typename G::Node Node;
    typedef typename G::e E;
    vector<Node*> nodos_recorrido;
    E peso_actual;
    Recorrido(Node *actual){nodos_recorrido.push_back(actual); peso_actual = 0;};
    imprimir(){
        int i;
        for(i = 0; i < nodos_recorrido.size()-1; i++){
            cout << nodos_recorrido[i]->m_data << "------>";
        }
        cout << nodos_recorrido[i]->m_data << " " << peso_actual << endl;
    }
};

template <class N, class E>
class CGraph{
public:
    typedef CGraph<N,E> Self;
    typedef CNode<Self> Node;
    typedef CEdge<Self> Edge;
    typedef Recorrido<Self> Recorrido;
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
                if(m_node[i]->m_edges[j]->m_dir && (m_node[i]->m_edges[j]->m_nodes[0] == m_node[i])){
                    cout << m_node[i]->m_edges[j]->m_data << ": " << m_node[i]->m_edges[j]->m_nodes[0]->m_data << " " << m_node[i]->m_edges[j]->m_nodes[1]->m_data << endl;
                }
                else if(!m_node[i]->m_edges[j]->m_dir && m_node[i]->m_edges[j]->m_nodes[0] == m_node[i]){
                    cout << m_node[i]->m_edges[j]->m_data << ": " << m_node[i]->m_edges[j]->m_nodes[0]->m_data << " " << m_node[i]->m_edges[j]->m_nodes[1]->m_data << endl;
                }
            }
        }
    }
    void busqueda(Recorrido &temp, Node* buscado){
        for(int i = 0; i < temp->nodos_recorrido[0]->m_edges.size(); i++){
            Recorrido actual(temp->nodos_recorrido[0]);

        }
    }
    void Dikjstra(n nombre){
        vector<Recorrido> resultado;
        int pos;
        if(buscar_nodo(nombre,pos)){
            for(int i = 0; i < m_node.size(); i++){
                Recorrido in(m_node[pos]);
                busqueda(in, m_node[i]);
                in.imprimir();
            }
        }
    }
};

int main(){
    CGraph<char,int> hola;
    hola.insertNode('A');
    hola.insertNode('B');
    hola.insertNode('C');
    hola.insertNode('D');
    hola.insertNode('E');
    hola.insertNode('F');
    hola.imprimir_nodos();
    cout << endl;

    hola.insertEdge('A', 'B', 3, 1);
    hola.insertEdge('A', 'C', 4, 1);
    hola.insertEdge('B', 'C', 5, 1);
    hola.insertEdge('C', 'D', 1, 1);
    hola.insertEdge('B', 'E', 1, 1);
    hola.insertEdge('E', 'F', 3, 1);
    hola.insertEdge('D', 'F', 2, 1);
    hola.imprimir_edge();
    return 0;
}

