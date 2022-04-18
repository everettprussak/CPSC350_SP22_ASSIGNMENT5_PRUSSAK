#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>
using namespace std;

template <class T>
class ListNode{
    public:
        ListNode();
        ~ListNode();
        ListNode(T d);
        T data;
        ListNode *next;  //just an address
        ListNode *prev;
        void updateData(T d);
};

#endif


template <class T>
ListNode<T>::ListNode(){
}

template <class T>
ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}

template <class T>
ListNode<T>::~ListNode(){
    delete next;
}

template <class T>
void ListNode<T>::updateData(T d){
    data = d;
}