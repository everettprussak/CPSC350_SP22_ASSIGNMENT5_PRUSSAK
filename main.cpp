#include "simulation.h"

//Main simply takes a file from command line, then runs our simulation methods/functions.
int main(int argc, char** argv){
    if(argc!=2){
        cout << "Incorrect Command Line" << endl;
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
