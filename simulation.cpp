#include "simulation.h"
#include <algorithm>
#include <array>
#include <fstream>

//default
Simulation::Simulation(){
    filename = "";
    office = new LinkedList<Window>;
    allStudents = new LinkedList<Student>;
    youth = new Queue<Student>;
    studentWait = 0;
    openWindow = 0;
    time = 0;
    lines = 0;
    fileText = new ListADT<int>;
}

//set filename with the name of the file
void Simulation::setFile(string a){
    filename = a;
}


//gets the contents from the file and stores them in the ListADT
void Simulation::text(){
    ifstream infile;
    string line;
    infile.open(filename);
    while(getline(infile,line)){
        int temp = stoi(line);
        fileText->append(temp);
        lines = lines + 1;
    }
}

//main program in this assignment
/*
This function creates the correct number of Students with correct Entry times and Time Needed, then adds them all to the queue.
It also creates the correct number of Windows using a LinkedList of type Window.

After this all it will go up in increments of one for each time, then will check a number of things
to either remove the student from the queue and increase each time needed in each window, or it will add idle and 
student waiting times.
*/
string Simulation::runSimulation(){
    string ret = "";
    int currTime = 0;
    int allTime = 0;
    bool run = true;
    int al = fileText->getData(0);
    for(int i=0; i<al; i++){ //creating the correct number of windows.
        Window w = Window(0);
        office->insertBack(w);
    }

    int count = 1, forl = 0;
    int abc = 0, def = 0, currNed=0, maxTime = 0;
    while(count<lines){ //adds individual students into the queue with correct student info.
        time = fileText->getData(count);
        count = count + 1;
        forl = fileText->getData(count);
        count = count + 1;
        for(int a=0; a<forl; a++){
            Student s = Student(fileText->getData(count),time,a);
            if(s.getAdded()+s.getNeeded()>maxTime){
                maxTime = maxTime + s.getAdded() + s.getNeeded();
            }
            currNed = currNed + s.getNeeded();
            count = count + 1;
            youth->insert(s);
        }
    }


    totalStudents = youth->getSize(); //number of students to start with
    int startTime = youth->peek().getAdded();
    int numWindows = office->getSize();
    allTime = currNed;


    //many variables that are used for calculating, or checking specific instances.
    int currMins=0, last = 0, alpha = 0, studNum = 0, cycle = 0, current =0;
    int totalWait = 0, currentwait = 0, lastWait = 0, add = 0, same=1;
    int holder[totalStudents]; //array to hold student Wait times
    bool theSame = false;

    while(current<maxTime+maxTime){ 
        if(youth->isEmpty()){ //will run until the queue is empty
            break;
        }
        cycle = 0;
        currTime = youth->peek().getAdded(); //times for each student (needed or time added)
        currMins = youth->peek().getNeeded();
        alpha = currTime - last; //important value to know how many minutes the student is awawy from the previous student
        if(same==0){
            currentwait = currentwait - alpha;
        }
        if(currentwait<0){
            currentwait=0; //nobody waits negative time...
        }

        if(currTime>current){ //this is for the start of the program, when the first student comes in at 2, each idle for each window is increased to 2, or whatevr the first student is.
            for(int i=0; i<numWindows; i++){
                Window w1 = office->findAtPos(i);
                if(w1.isFull()==false){
                    w1.addIdle(1); //increases idle
                  //  cout << w1.getIdle() << endl;
                    w1.changeOpen(1);
                }
                else{
                    w1.changeInUse(-1); //decreases the inUse by 1
                }
                office->updateNodeData(w1,i);
            }
            add = 0; //nothing was added
            same = 1; //it is the same variable
        }
        else if(current>=currTime){ //now the students are starting to roll into the office
            for(int i=0; i<numWindows; i++){ //iterating through the LinkedList of type Window
                Window w3 = office->findAtPos(i); //creates a window temporary that can be changed
                if(w3.getInUse()==0){ //checks if the current window has nobody using it
                    /*if(w3.getOpen()<current && currTime>=current){
                        cout << "ok" << endl;
                        w3.addIdle(alpha);
                        cout << w3.getIdle() << endl;
                    }*/
                    w3.changeInUse(currMins); //adds the current students minutes
                    w3.changeOpen(current); //adds the current students time they walked into the office
                    office->updateNodeData(w3,i); //changes the node to correct data on the LinkedList
                    last = youth->peek().getAdded();
                    youth->remove(); //that student is dealt with, remove them
                    holder[studNum] = currentwait; //adds current student wait time to the array at their specific student Numebr
                    studNum++;  // new student
                    lastWait = currentwait; //has to be checked for specific cases
                    if(currentwait<0){
                        currentwait = 0; //nobody waits negative time
                    }
                    add = i+1; //somethign was added to the window
                    int other = currTime;
                    if(youth->isEmpty()==false){ //makes sure that queue does not give error here
                        currMins = youth->peek().getNeeded();
                        currTime = youth->peek().getAdded();
                    }
                    if(currTime==current){
                        current--; //since the time will increase, if the time is the same, we decrease to even it out.
                    }
                    same = 0; //not the same variable now
                
                    break;
                }
                else{ //the current window in the loop is full
                    cycle++; 
                    add = 0; //nothing was added
                    same = 1; //the same variable
                    if(cycle==numWindows){ //if cycle is the same as the number of windows, then all are busy
                        if(current!=youth->peek().getAdded()){
                            currentwait++;
                        }
                        cycle = 0; //reset cycle for next time
                        for(int i=0; i<numWindows; i++){ //this basically decreases each inUse by 1 to simulate a minute has been passed
                            Window w3 = office->findAtPos(i);
                            if(w3.getOpen()==current){
                                continue;
                            }
                            w3.changeInUse(-1);
                            office->updateNodeData(w3,i);
                        }
                    }
                }
            }
        }
        current++; //increase the time
    }


    sort(holder,holder+totalStudents); //sorts the array for the median
    int noWait = 0;
    int max = 0, overTen = 0, sum = 0; //variables needed
    float median = 0.0, mean = 0.0;
    for(int a: holder){
        sum = sum + a; //sum for the mean
        if(a==0){
            noWait++;
        }
        if(a>max){
            max = a; //max
        }
        if(a>9){
            overTen++; //did the student wait over ten minutes?
        }
    }

    int waiters = totalStudents - noWait;
    if(waiters<1){
        waiters = totalStudents;
    }
    int middle=waiters/2;
    int newArray[waiters];
    int counterA = 0;

    for(int a: holder){
        if(a>0){
            newArray[counterA] = a;
            counterA++;
        }
    }



    if(waiters%2==0){ //if the number of students are even then median is average of the middle 2 values
         median = (newArray[middle-1] + newArray[middle]) / 2.0;
     }
     else{
         median = newArray[middle]; //odd students so just the middle value
     }

    mean = sum/float(waiters); //using float so we can have decimal points

    int totalLeftOver = 0, maxLeftOver = 0;
     for(int y=0; y<numWindows; y++){
        if(office->findAtPos(y).getInUse()>maxLeftOver){
            maxLeftOver = office->findAtPos(y).getInUse(); //checks for the windows that still have time left
        }
     }

    int windowTotal = 0, windowOver = 0, windowLong = 0;
    float windowMean = 0.0;
     for(int y=0; y<numWindows; y++){
         Window w4 = office->findAtPos(y);
        if(office->findAtPos(y).getInUse()<maxLeftOver){
            w4.addIdle(maxLeftOver-office->findAtPos(y).getInUse()); //adds more idle time to non-busy or less-busy windows once we ended the loop
           // cout << w4.getIdle() << endl;
        }
        int idleA = w4.getIdle();
        if(idleA>4){
            windowOver++; //checks for window idle times over 5 minutes
        }
        if(idleA>windowLong){
            windowLong = w4.getIdle(); //checks for longest idle window
        }
        office->updateNodeData(w4,y);
        windowTotal =windowTotal + w4.getIdle();
     }

     windowMean = windowTotal/float(numWindows);

     cout << endl;
     
     ret = "The mean student wait: " + to_string(mean) + " minutes \n";
     ret = ret + "The median student wait: " + to_string(median) + " minutes \n";
     ret = ret + "The Longest Student wait time: " + to_string(max) + " minutes \n";
     ret = ret + "The number of students who waited ten minutes or over: " + to_string(overTen) + " \n";
     ret = ret + "The mean window Idle time: " + to_string(windowMean) + " minutes \n";
     ret = ret + "The longest window Idle time: " + to_string(windowLong) + " minutes \n";
     ret = ret + "The number of window Idle time 5 minutes or over: " + to_string(windowOver) + " \n";
    return ret;
}