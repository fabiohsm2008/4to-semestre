#include <iostream>
#include <vector>

using namespace std;

template <typename G>
struct CNode{
    typedef typename G::Edge Edge;
    typedef typename G::N N;
    N m_data;
    vector<Edge*> m_edges;
};

template <class G>
struct CEdge{
    typedef typename G:: Node Node;
    typedef typename G::E E;
    Node* m_nodes[2];
    E m_data;
    bool m_dir;
};

template <class N, class E>
class CGraph{
public:
    typedef CGraph<N,E> Self;
    typedef CNode<Self> Node;
    typedef CEdge<Self> Edge;
    typedef N n;
    typedef E e;
    vector<Node*> m_node;
    bool insertNode(n dato){

    }
    bool deleteNode(n dato){

    }
    bool removeEdge()
};

int main(){
    CGraph<int,char> hola;
    return 0;
}
