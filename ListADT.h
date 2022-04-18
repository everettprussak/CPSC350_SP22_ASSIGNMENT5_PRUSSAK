#ifndef LISTADT_H
#define LISTADT_H

#include "Queue.h"

template <class T>
class ListADT{
    public:
        ListADT();
        bool isEmpty();
        T remove(T a);
        void append(T d);
        void prepend(T d);
        int getSize();
        string print();
        int getData(int a);

    private:
        int size;
        ListNode<T> *head;
        LinkedList<T> *list;
};

#endif

template <class T>
ListADT<T>::ListADT(){
    size = 0;
    list = new LinkedList<T>;
}

template <class T>
bool ListADT<T>::isEmpty(){
    return(size>0);
}

template <class T>
T ListADT<T>::remove(T a){
    int where = list->find(a);
    if(where!=-1){
        size--;
        return (list->deleteAtPos(where));
    }
    return NULL;
}

template <class T>
void ListADT<T>::append(T d){
    list->insertBack(d);
    size++;
}

template <class T>
void ListADT<T>::prepend(T d){
    list->insertFront(d);
    size++;
}


template <class T>
int ListADT<T>::getSize(){
    return size;
}

template <class T>
string ListADT<T>::print(){
    return (list->printList());
}

template <class T>
int ListADT<T>::getData(int a){
    return (list->findAtPos(a));
}

