#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>

#include "hash.h"
#include "list.h"

using namespace std;

Hash::Hash(int tam){
    m = tam;
    n_colisoes = 0;
    hashm = new LinkedList*[m];
    for (int i = 0; i < m; i++)
        hashm[i] = new LinkedList();
}

Hash::~Hash(){
    /* for (int i = 0; i < m; i++)
        hashm[i]->~LinkedList(); */

    delete [] hashm;
};

void Hash::insere(string palavra,int (*hash)(string palavra, int tam)){
    hashVec aux;
    aux.palavra = palavra;
    aux.c = 0;
    int key = hash(palavra,m);
    if(!hashm[key]->verificaPalavra(aux, &n_colisoes))
        hashm[key]->insereNode(palavra);
}

void Hash::remove(string palavra,int (*hash)(string palavra,int tam)){  
    int key = hash(palavra,m);
    hashVec *aux = busca(palavra, hash);
    hashm[key]->removeNode(*aux);
};

int Hash::getColisoes(){
    return this->n_colisoes;
};

void Hash::imprimeInfo(){
    cout << "Numero de colisoes: " << getColisoes() << endl;
};

hashVec* Hash::busca(string palavra,int (*hash)(string palavra, int tam)){
    int key = hash(palavra,m);

    if (hashm[key]->buscaPalavra(palavra) != nullptr)
        return hashm[key]->buscaPalavra(palavra);

    return nullptr;
};

void Hash::copyToVector(vector<hashVec>& vet) {
    for(int i = 0; i < m; i++) {
        hashm[i]->getAllInfo(vet);
    }
}