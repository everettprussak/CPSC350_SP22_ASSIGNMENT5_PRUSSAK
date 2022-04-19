#include "student.h"

//default
Student::Student(){
    timeNeed = 0;
    timeAdded = 0;
    wait = 0;
}

//overloaded 
Student::Student(int a, int b, int c){
    timeNeed = a;
    timeAdded = b;
    wait = 0;
    id = c;
}

//returns timeadded
int Student::getAdded(){
    return timeAdded;
}

//returns timeNeed
int Student::getNeeded(){
    return timeNeed;
}

//changes the timeNeed to a
void Student::changeNeeded(int a){
    timeNeed = a;
}

//changes the timeAdded to a
void Student::changeAdded(int a){
    timeAdded = a;
}


void Student::addWaiting(int a){
    wait = wait + a;
}

int Student::getWait(){
    return wait;
}

int Student::getId(){
    return id;
}