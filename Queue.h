#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

template <class T>
class Queue{
    public:
        Queue();
        ~Queue();

        void insert(T d);
        T remove();

        T peek();
        bool isEmpty();
        int getSize();

    private:
        ListNode<T> *front;
        ListNode<T> *rear;
        int size;
        LinkedList<T> *queue;
};

#endif

template <class T>
Queue<T>::Queue(){
    queue = new LinkedList<T>;
    size = 0;
    front = NULL;
    rear = NULL;
} 

template <class T>
Queue<T>::~Queue(){
    delete queue;
}

template <class T>
void Queue<T>::insert(T d){
    ListNode<T> *node = new ListNode<T>(d);
    if(isEmpty()){
        front = node;
        rear = node;
    }
    else{
        rear->next = node;
        node->next = NULL;
        node->prev = rear;
        rear = node;
    }
    ++size;
    queue->insertBack(d);
}

template <class T>
T Queue<T>::remove(){
    if(isEmpty()){
        throw runtime_error("Queue is Empty");
    }
    front = front->next;
    T temp = queue->removeFront();
    size--;
    return temp;
}

template <class T>
T Queue<T>::peek(){
    return queue->getFront();
}

template <class T>
bool Queue<T>::isEmpty(){
    return(size==0);
}

template <class T>
int Queue<T>::getSize(){
    return size;
}