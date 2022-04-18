#include "window.h"

Window::Window(){
    open = 0;
    inUse = 0;
    idle = 0;
}

Window::Window(int a){
    open = a;
    inUse = 0;
    idle = 0;
}

int Window::getOpen(){
    return open;
}

int Window::getInUse(){
    return inUse;
}

void Window::changeInUse(int a){
    inUse = inUse + a;
}

void Window::changeOpen(int a){
    open = a;
}

bool Window::isFull(){
    return inUse>0;
}

void Window::addIdle(int a){
    idle = idle + a;
}

int Window::getIdle(){
    return idle;
}


void Window::totalInUseChange(int a){
    inUse = a;
}