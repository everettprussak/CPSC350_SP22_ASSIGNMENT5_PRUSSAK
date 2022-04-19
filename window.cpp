#include "window.h"


//default
Window::Window(){
    open = 0;
    inUse = 0;
    idle = 0;
}

//overloaded constructor
Window::Window(int a){
    open = a;
    inUse = 0;
    idle = 0;
}

//returns open
int Window::getOpen(){
    return open;
}

//returns inUse
int Window::getInUse(){
    return inUse;
}

//adds (or subtracts) inUse
void Window::changeInUse(int a){
    inUse = inUse + a;
}

//changes Open to a
void Window::changeOpen(int a){
    open = a;
}

//checks if the Current Window is being Useds
bool Window::isFull(){
    return inUse>0;
}

//adds a to idle
void Window::addIdle(int a){
    idle = idle + a;
}

//returns idle
int Window::getIdle(){
    return idle;
}

//changes Inuse completely to a set value rather than adding it.
void Window::totalInUseChange(int a){
    inUse = a;
}