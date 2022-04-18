#ifndef STUDENT_H
#define STUDENT_H



class Student{
    public:
        Student();
        Student(int a, int b, int c);
        int getNeeded();
        int getAdded();
        void changeNeeded(int a);
        void changeAdded(int a);
        int getWait();
        void addWaiting(int a);
        int getId();
    private:
        int timeNeed;
        int timeAdded;
        int wait;
        int id;
};

#endif