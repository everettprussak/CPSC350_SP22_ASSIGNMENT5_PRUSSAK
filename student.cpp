#include "student.h"

Student::Student(){
    timeNeed = 0;
    timeAdded = 0;
    wait = 0;
}

Student::Student(int a, int b, int c){
    timeNeed = a;
    timeAdded = b;
    wait = 0;
    id = c;
}

int Student::getAdded(){
    return timeAdded;
}

int Student::getNeeded(){
    return timeNeed;
}

void Student::changeNeeded(int a){
    timeNeed = a;
}

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