/* #include <iostream>
#include <string.h>

#include "list.h"

using namespace std;

LinkedList::LinkedList(){ primeiro = NULL; }

LinkedList::~LinkedList(){
    Node *p = primeiro;
    while(p != NULL) {
        primeiro = primeiro->getProx();
        delete p;
        p = primeiro;
    }
}

template<typename T>
void LinkedList::insereNode(T info) {
    Node *p = new Node();
    p->setInfo(info);
    p->setProx(primeiro);
    primeiro = p;
}

template<typename T>
void LinkedList::removeNode(T info, bool (*compare)(T&, T&)) {
    Node *p = primeiro;
    Node *q = primeiro;

    while(p != NULL) {

        if (compare(p->getInfo() == info) && p == primeiro){
            primeiro = primeiro->getProx();
            delete p;
            return;
        }

        q = q->getProx();

        if ((q != NULL) && compare(p->getInfo() == info)) {
            p = p->getProx();
            delete p;
            delete q;
            return; 
        }
        
        p = p->getProx();
    }

    delete p;
    delete q;
}

void LinkedList::imprimir(){
    Node *p = primeiro;
    while(p != NULL) {
        cout << p->getInfo()<<endl;
        p = p->getProx();
    }
}

template<typename T>
void LinkedList::getAllInfo(vector<T>& vet){
    Node *p = primeiro;
    while(p!=NULL){
        vet.push_back(p->getInfo());
        p = p->getProx();
    }
    delete p;
} */