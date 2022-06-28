#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include<vector>

#include "node.h"

class LinkedList
{
    private:
        Node *primeiro;
    public:

        LinkedList();                        //construtor da lista encadeada
        ~LinkedList();                       //destrutor da lista encadeada

        template<typename T>
        void insereNode(T info);     //insere um novo nó
        
        template<typename T>
        void removeNode(T info, bool (*compare)(T&, T&));    //remove um nó da lista
        
        void imprimir();                     //imprime todos os nós da lista

        template<typename T>
        bool busca(T newData);     //verifica se a info já foi inserida na lista
        
        template<typename T>                                                     
        void getAllInfo(vector<T>& vet);
};


#endif // LIST_H_INCLUDED
