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
int speedLimit = 25;
int sigma = 5;
int times = 10000;
int interval = 5;

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
    while(abs(ans = gaussrand()*sigma) > sigma){}
    return (int)ans + speedLimit;
}
int main(int argc, const char * argv[])
{
    srand(time(0));
    fstream fout;
    fout.open("output.txt");
    road* way = new road(2,10000000);
    for (int i=1; i<times; ++i) {
        if((i+rand()%3)%interval == 0){
            way->addCar(1, 0, rrrrr());
            totalCar++;
        }
        way->update();
        /*
        cout << way->getCarNum()<<' ';
        for (int j=0; j<way->getCarNum(); ++j) {
            cout << j<<":"<<way->getCar(j)->getLane() <<':'<<way->getCar(j)->getPosition() <<' ';
        }
        cout << endl;
        */
    }
    double U,D,d,m;
    for (int j=0; j<way->getCarNum(); ++j) {
        U += way->getCar(j)->lowTime;
        D += way->getCar(j)->time;
        d += (double)way->getCar(j)->getPosition() / (double) way->getCar(j)->time;
        m += way->getCar(j)->getMaxVelosity();
    }
    cout << "speedlimit: " << speedLimit << endl;
    cout << "safedistance: "<< 50 << endl;
    cout << "totalCar: " << totalCar <<endl;
    cout << "times: " << times << endl;
    cout << "time interval: " << interval << endl;
    cout << "Average Max speed: " << m / way->getCarNum() << endl;
    cout << "Average speed: " << d / way->getCarNum() << endl;
    cout << "totalChange: "<< way->totalChange <<endl;
    cout << "totalDecelerate: "<< way->diffV <<endl;
    cout << "hard decelerate Num: "<< way->crashNum <<endl;
    cout << "totalDelay Rate: "<<(double) U / (double)D << endl;


    
    return 0;
}

