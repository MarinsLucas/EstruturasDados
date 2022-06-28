#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>

using namespace std;

template<typename T>
class Node<T>
{
    public:
        Node(){
            proximo = nullptr; 
        };
        ~Node(){};
        T getInfo(){ return info;  };
        Node* getProx(){ return prox; };
        void setInfo(T nInfo) { info = nInfo; };
        void setProx(Node *p){ prox = p; };
        
    private:
        //TODA INFORMAÇÃO NECESSÁRIA INFORMAÇÃO AQUI!!
        T info;
        Node *proximo;
};

#endif // NODE_H_INCLUDED
