#ifndef SIMULATION_H
#define SIMULATION_H

#include "ListADT.h"
#include "student.h"
#include "window.h"

/*
Header for the bulk of the program.
Has many private variables to keep track of various tasks.
Has many public methods/functions to do various tasks.
*/

class Simulation{
    private:
        string filename;
        int studentWait;
        int openWindow;
        LinkedList<Window> *office;
        Queue<Student> *youth;
        ListADT<int> *fileText;
        int time;
        int lines;
        int totalStudents;
        LinkedList<Student> *allStudents;
    public:
        Simulation();
        void setFile(string a);
        void text();
        string runSimulation();
};

#endif