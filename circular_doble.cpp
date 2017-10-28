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
    bool buscar(T dato, nodo<T> *&actual){
        actual = head;
        if(head->valor == dato) return 1;
		actual = head->next;
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
        if (dato < head->valor){
            nodo<T> *nuevo = new nodo<T>(dato,head->prev,head);
            head->prev->next = nuevo;
            head->prev = nuevo;
            head = nuevo;
            return 1;
        }
        nodo<T> *actual;
        if(buscar(dato, actual)) return 0;
        nodo<T> *nuevo = new nodo<T>(dato,actual->prev,actual);
        actual->prev->next = nuevo;
        actual->prev = nuevo;
        return 1;
    }
	bool borrar(T dato){
		nodo<T> *actual;
		if(!buscar(dato,actual)) return 0;
		if(actual == head){
			head->prev->next = head->next;
			head->next->prev = head->prev;
			head = head->next;
			delete actual;
			return 1;
		}
		nodo<T> *temp = actual;
		actual->prev->next = actual->next;
		actual->next->prev = actual->prev;
		delete temp;
		return 1;
		
	}
    void imprimir(){
        nodo<T> *actual = head;
        cout << actual->valor << " ";
        actual = actual->next;
        while(actual != head){
            cout << actual->valor << " ";
            actual = actual->next;
        }
        cout << endl;
    }
};

void Josephus(circular<int> temp,int n, int k){
	for(int i = 1; i <= n; i++){
		temp.insertar(i);
	};
	nodo<int> *puntero = temp.head->prev;
	temp.imprimir();
	while(temp.head->next->next != temp.head){
		for(int j = 0; j < k; j++){
			puntero = puntero->next;
		}
		puntero = puntero->next;
		temp.borrar(puntero->prev->valor);
		puntero = puntero->prev;
		temp.imprimir();
	}
	cout << "Primer sobreviviente = " << temp.head->valor << endl;
	cout << "Segundo sobreviviente = " << temp.head->next->valor;
	
}

int main(){
    circular<int> temp;
	Josephus(temp, 40, 3);
    return 0;
}
