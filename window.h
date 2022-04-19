#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
using namespace std;

/*
Simple Header file for Window Class.
This class has open, inUse, and idle.
*/

class Window{
    public:
        Window();
        Window(int a);
        int getOpen();
        int getInUse();
        void changeInUse(int a);
        void changeOpen(int a);
        bool isFull();
        void addIdle(int a);
        int getIdle();
        void totalInUseChange(int a);

    private:
        int open;
        int inUse;
        int idle;
};

#endif
