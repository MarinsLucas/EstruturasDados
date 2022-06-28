#ifndef HASH_H__
#define HASH_H__

#include <iostream>
#include "list.h"

using namespace std;

class Hash{
    
    private:
        
        int m;                              // tamanho do hash
        int n_colisoes;                     // numero de colisões
        LinkedList ** hashm;                // vetor da tabela hash  

    public:
    
        Hash(int tam);                      // inicializa a hash com um tamanho 
        ~Hash();                            // destrutor da hash

        void insere(string palavra, int (*hash)(string palavra, int tam));        // função de inserção
        void remove(string palavra, int (*hash)(string palavra, int tam));        // implementacao do remove
        void imprimeInfo();                                                       // implementacao do imprimeinfo
        int retornaTam(){return m;}
        void copyToVector(vector<hashVec>& vet); 
        int getColisoes();

        hashVec* busca(string palavra, int (*hash)(string palavra, int tam));     // implementaçao da busca
        LinkedList returnLinkedList(int index){ return *hashm[index]; };          // retorna lista encadeada da posição index
           
};

#endif