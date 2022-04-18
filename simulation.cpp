#include "simulation.h"
#include <algorithm>
#include <array>
#include <fstream>

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

void Simulation::setFile(string a){
    filename = a;
}


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


string Simulation::runSimulation(){
    string ret = "";
    int currTime = 0;
    int allTime = 0;
    bool run = true;
    int al = fileText->getData(0);
    for(int i=0; i<al; i++){
        Window w = Window(0);
        office->insertBack(w);
    }

    int count = 1, forl = 0;
    int abc = 0, def = 0, currNed=0, maxTime = 0;
    while(count<lines){
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


    totalStudents = youth->getSize();
    int startTime = youth->peek().getAdded();
    int numWindows = office->getSize();
    allTime = currNed;


    int currMins=0, last = 0, alpha = 0, studNum = 0, cycle = 0, current =0;
    int totalWait = 0, currentwait = 0, lastWait = 0, add = 0, same=1;
    int holder[totalStudents];
    Student s = youth->peek();
    Student k = Student();
    bool theSame = false;

    while(current<maxTime){
        if(youth->isEmpty()){
            break;
        }
        cycle = 0;
        currTime = youth->peek().getAdded();
        currMins = youth->peek().getNeeded();
        alpha = currTime - last;
        if(same==0){
            currentwait = currentwait - alpha;
        }
        if(currentwait<0){
            currentwait=0;
        }
        if(currTime>current){
            for(int i=0; i<numWindows; i++){
                Window w1 = office->findAtPos(i);
                if(w1.isFull()==false){
                    w1.addIdle(1);
                }
                else{
                    w1.changeInUse(-1);
                }
                cout << i << " " << w1.getInUse() << " " << w1.getOpen() << " " << w1.getIdle() << endl;
                office->updateNodeData(w1,i);
            }
            add = 0;
            same = 1;
        }
        else if(current>=currTime){
            for(int i=0; i<numWindows; i++){
                Window w3 = office->findAtPos(i);
                cout << i << " " << w3.getInUse() << " " << w3.getOpen() << " " << w3.getIdle() << endl;
                if(w3.getInUse()==0){
                    w3.changeInUse(currMins);
                    w3.changeOpen(currTime);
                    office->updateNodeData(w3,i);
                    last = youth->peek().getAdded();
                    youth->remove();
                    holder[studNum] = currentwait;
                    studNum++;
                    lastWait = currentwait;
                    if(currentwait<0){
                        currentwait = 0;
                    }
                    add = 1;
                    if(youth->isEmpty()==false){
                        currMins = youth->peek().getNeeded();
                        currTime = youth->peek().getAdded();
                    }
                    cout << i << " " << w3.getInUse() << " " << w3.getOpen() << " " << w3.getIdle() << endl;
                    if(currTime==current){
                        current--;
                    }
                    same = 0;
                    break;
                }
                else{
                    cycle++;
                    add = 0;
                    same = 1;
                    if(cycle==numWindows){
                        currentwait++;
                        cycle = 0;
                        for(int i=0; i<numWindows; i++){
                            Window w3 = office->findAtPos(i);
                            w3.changeInUse(-1);
                            office->updateNodeData(w3,i);
                        }
                    }
                }
            }
        }
        current++;
    }

    for(int i=0; i<numWindows; i++){
        Window w2 = office->findAtPos(i);
        cout << "Pos: " << i <<" " << w2.getInUse() << " " << w2.getOpen() << " " << w2.getIdle() << endl;
    }


    sort(holder,holder+totalStudents);
    int max = 0, overTen = 0, sum = 0, middle=totalStudents/2;
    float median = 0.0, mean = 0.0;
    for(int a: holder){
        sum = sum + a;
        if(a>max){
            max = a;
        }
        if(a>10){
            overTen++;
        }
    }

    if(totalStudents%2==0){
         median = (holder[middle-1] + holder[middle]) / 2.0;
     }
     else{
         median = holder[middle];
     }

    mean = sum/float(totalStudents);

    int totalLeftOver = 0, maxLeftOver = 0;
     for(int y=0; y<numWindows; y++){
        if(office->findAtPos(y).getInUse()>maxLeftOver){
            maxLeftOver = office->findAtPos(y).getInUse();
        }
     }

    int windowTotal = 0, windowOver = 0, windowLong = 0;
    float windowMean = 0.0;
     for(int y=0; y<numWindows; y++){
         Window w4 = office->findAtPos(y);
        if(office->findAtPos(y).getInUse()<maxLeftOver){
            w4.addIdle(maxLeftOver-office->findAtPos(y).getInUse());
            if(w4.getIdle()>5){
                windowOver++;
            }
            if(w4.getIdle()>windowLong){
                windowLong = w4.getIdle();
            }
            office->updateNodeData(w4,y);
        }
        windowTotal =windowTotal + w4.getIdle();
        cout << office->findAtPos(y).getIdle() << endl;
     }

     windowMean = windowTotal/float(numWindows);


     ret = "The mean student wait: " + to_string(mean) + "\n";
     ret = ret + "The median student wait:" + to_string(median) + "\n";
     ret = ret + "The Longest Student wait time: " + to_string(max) + "\n";
     ret = ret + "The number of students who waited over ten minutes: " + to_string(overTen) + "\n";
     ret = ret + "The mean window Idle time: " + to_string(windowMean) + "\n";
     ret = ret + "The longest window Idle time: " + to_string(windowLong) + "\n";
     ret = ret + "The number of window Idle time over 5 minutes: " + to_string(windowOver) + "\n";
    return ret;
}