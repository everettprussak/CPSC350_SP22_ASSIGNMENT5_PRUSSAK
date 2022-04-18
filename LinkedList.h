#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ListNode.h"

/*
Header Class for LinkedList
*/
template <class T>
class LinkedList{
    private:
        ListNode<T> *front;
        ListNode<T> *back;
        unsigned int size;

    public:
        LinkedList();
        ~LinkedList();
        void insertFront(T d);
        void insertBack(T d);
        T removeFront();
        T removeBack();
        T find(T value); //value that we are looking for
        bool isEmpty();
        unsigned int getSize();
        T deleteAtPos(int pos); //the position of the node, and delete it
        T getFront();
        T getBack();
        string printList();
        T findAtPos(int val);
        void updateNodeData(T d, int a);

};

#endif

template <class T>
LinkedList<T>::LinkedList(){
    front = NULL;
    back = NULL;
    size = 0;
}

template <class T>
LinkedList<T>::~LinkedList(){
    ListNode<T> *node = front;
    ListNode<T> *temp;
    while(node!=NULL){
        temp = node->next;
        delete node;
        node = temp;
    }
}

template <class T>
void LinkedList<T>::insertFront(T d){
    ListNode<T> *node = new ListNode<T>(d);

    if(isEmpty()){
        back = node;
    }
    else{
        //not empty
        node->next = front;
        front->prev = node;
    }
    front = node;
    size++;
}

template <class T>
void LinkedList<T>::insertBack(T d){
    ListNode<T> *node = new ListNode<T>(d);

    if(isEmpty()){
        front = node;
    }
    else{
        node->prev = back;
        back->next = node;
    }
    back = node;
    size++;
}

template <class T>
bool LinkedList<T>::isEmpty(){
    return size == 0;
}

template <class T>
T LinkedList<T>::removeFront(){
    
    if(isEmpty()){
        throw runtime_error("List is empty");
    }

    ListNode<T> *temp = front;
    
    if(front->next == NULL){
        back = NULL;
    }
    else{
        //more than one node in the list
        front->next->prev = NULL;
    }

    front = front->next;
    temp->next = NULL;
    T data = temp->data;
    --size;
    delete temp;
    return data;
}


template <class T>
T LinkedList<T>::removeBack(){
    if(isEmpty()){
        throw runtime_error("List is empty");
    }
    ListNode<T> *temp = front;

    if(back->prev == NULL){
        //only node in the list
        front = NULL;
    }
    else{
        //more than one node in the list
        back->prev->next = NULL;
    }
    back = back->prev;
    temp->prev = NULL;
    int data = temp->data;
    --size;
    delete temp;
    return data;
    
}

template <class T>
T LinkedList<T>::find(T value){
    int pos = -1;
    ListNode<T> *curr = front;
    
    while(curr!=NULL){
        pos++;
        if(curr->data==value){
            break;
        }
        curr = curr->next;
    }

    if(curr==NULL){
        return -1; //the value was not found.
    }
    return curr->data;
}

template <class T>
T LinkedList<T>::deleteAtPos(int pos){
    
    //check if empty aand if value exists


    int idx = 0;
    ListNode<T> *curr = front;
    ListNode<T> *prev = front;

    while(idx!=pos){
        prev = curr;
        curr = curr->next;
        idx++;
    }

    //We found it, lets procees to delete, also check if it is front or back (if statement)
    prev->next = curr->next;
    curr->next = NULL;
    int d = curr->data;
    size--;

    delete curr;
    return d;
}

template <class T>
unsigned int LinkedList<T>::getSize(){
    return size;
}

template <class T>
T LinkedList<T>::getFront(){
    return front->data;
}

template <class T>
T LinkedList<T>::getBack(){
    if(isEmpty()==false){
        return back->data;
    }
}

template <class T>
string LinkedList<T>::printList(){
  ListNode<T> *current = front;
  string listString = "";

  while(current != NULL){
    listString = listString + to_string(current->data) + "\n";
    current = current->next;//listnode
  }
  return listString;
}

template <class T>
T LinkedList<T>::findAtPos(int val){
    int y = 0;
    ListNode<T> *current = front;
    while(y<val){
        current = current->next;
        y++;
    }
    return current->data;
}

template <class T>
void LinkedList<T>::updateNodeData(T d, int a){
    ListNode<T> *current = front;
    int y = 0;
    while(y<a){
        current = current->next;
        y++;
    }
    current->updateData(d);
}