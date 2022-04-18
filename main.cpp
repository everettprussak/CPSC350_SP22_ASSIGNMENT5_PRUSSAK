#include "simulation.h"

//Queue with DoublyLinkedList is now working
int main(int argc, char** argv){
    if(argc!=2){
        cout << "Incorrect Command Line";
        return -1;
    }
    else{
        string filename = argv[1];
        Simulation *sim = new Simulation();
        sim->setFile(filename);
        sim->text();
        cout <<sim->runSimulation() << endl;
    }
    return 0;
}

/*
Queue<int> *q = new Queue<int>();
    q->insert(4);
    q->insert(5);
    q->insert(6);
    q->insert(7);
    cout << q->getSize() << endl;
    
    while(q->isEmpty()==false){
        cout << q->remove() << endl;
    }

    q->insert(5);
    cout << q->peek() << endl;
    q->insert(14);
    cout << q->peek() << endl;

     while(q->isEmpty()==false){
        cout << q->remove() << endl;
    }
    cout << q->getSize() << endl;

    ListADT<int> *h = new ListADT<int>();
    h->append(4);
    h->append(5);
    cout << h->getSize() << endl;
    cout << h->print() << endl;

    Student *a = new Student(4,5);
    cout << a->getTime() << endl;
    cout << a->getNum() << endl;
    

    Window *w = new Window(5);
    cout << w->getOpen() << endl;

*/