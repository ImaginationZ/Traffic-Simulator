//
//  main.cpp
//  Transport
//
//  Created by Huang Zen on 2/7/14.
//  Copyright (c) 2014 Huang Zen. All rights reserved.
//

#include <iostream>
#include "fstream"
#include "road.h"
#include "ctime"
#include "cmath"
using namespace std;

static int totalCar = 0;
int speedLimit = 20;
int sigma = 10;
int times = 100000;
int interval = 10;

double gaussrand(){
    static double V1,
    V2, S;
    static int phase= 0;
    double X;
    if (phase == 0 ) {
        do {
            double U1 = (double)rand()/ RAND_MAX;
            double U2 = (double)rand()/ RAND_MAX;
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        }
        while(S >= 1 || S == 0);
        X= V1 * sqrt(-2 * log(S) / S);
    }
    else
        X = V2 * sqrt(-2 * log(S) / S);
    phase = 1 - phase;
    return X;
}

int rrrrr(){
    double ans;
    while(abs(ans = gaussrand()*sigma) > 0.5 * sigma){}
    return (int)ans + speedLimit;
}
int main(int argc, const char * argv[])
{
    srand(time(0));
    fstream fout;
    fout.open("output.txt");
    road* way = new road(10,100000);
    way->addCar(1, 0, rrrrr());
    for (int i=1; i<times; ++i) {
        if((i+rand()%3)%interval == 0){
            way->addCar(1, 0, rrrrr());
            totalCar++;
        }
        way->update();
        /*
        cout << way->getCarNum()<<' ';
        for (int j=0; j<way->getCarNum(); ++j) {
            if(way->getCar(j)->cleared)
                cout << "clr"<<' ';
            else
            cout << j<<":"<<way->getCar(j)->getPosition() <<':'<<way->getCar(j)->getLane() <<' ';
        }
        cout << endl;
        */
    }
    for (int i=0; i<way->getCarNum(); ++i){
        if(!way->getCar(i)->cleared)
            way->remove(way->getCar(i));
    }
    cout << "speedlimit: " << speedLimit*2 << endl;
    cout << "safedistance: "<< 50 << endl;
    cout << "totalCar: " << totalCar <<endl;
    cout << "Average speed: " << (double) way->totalV / totalCar * 2 << endl;
    cout << "times: " << times << endl;
    cout << "time interval: " << interval << endl;
    cout << "totalCrash: " << way->crashNum << endl;
    cout << "totalChange: "<< way->totalChange <<endl;
    cout << "totalDecelerate: "<< way->diffV*2 <<endl;
    cout << "passed p1: " << way->n1 <<endl;
    cout << "passed p2: " << way->n2 <<endl;
    cout << "passed p3: " << way->n3 <<endl;

    
    return 0;
}

