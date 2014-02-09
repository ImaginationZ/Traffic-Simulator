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

int speedLimit = 30;
int sigma = 10;
int times = 20000;
int interval = 20;
ofstream fout("output.txt");

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

void test(road *way){
    way->clear();
    int totalCar = 0;

    for (int i=1; i<times; ++i) {
        if((i+rand()%3)%(interval+1+(int)(interval*0.1)) == 0){
            way->addCar(1, rand()%2, rrrrr());
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
    double U=0,D=0,d=0,m=0;
    for (int j=0; j<way->getCarNum(); ++j){
        D += (double)way->getCar(j)->lowTime/(double)way->getCar(j)->time;
        d += (double)way->getCar(j)->getPosition() / (double) way->getCar(j)->time;
        m += way->getCar(j)->getMaxVelosity();
    }
    fout /*<< "speedlimit: " */<< speedLimit <<' ';
    fout /*<< "safedistance: "*/<< 50 << ' ';
    fout /*<< "totalCar: " */<< (int)(1.2*totalCar) <<' ';
    fout /*<< "times: " */<< times << ' ';
    fout /*<< "time interval: " */<< interval << ' ';
    fout /*<< "Average Max speed: " */<< m / way->getCarNum() << ' ';
    fout /*<< "Average speed: " */<< d / way->getCarNum() << ' ';
    fout /*<< "totalChange: "*/<< way->totalChange <<' ';
    fout /*<< "totalDecelerate: "*/<< way->diffV <<' ';
    fout /*<< "hard decelerate Num: "*/<< way->crashNum <<' ';
    fout /*<< "totalDelay Rate: "*/<< D / way->getCarNum()<< '*';
}
int main(int argc, const char * argv[])
{
    srand(time(0));
    road* way = new road(3,10000000);
    for (speedLimit=25; speedLimit<50; speedLimit+=5) {
        interval = 5;
        test(way);
        cout << speedLimit <<' '<<interval<< endl;
        interval = 10;
        test(way);
                cout << speedLimit <<' '<<interval<< endl;
        
        interval = 20;
        test(way);
        
                cout << speedLimit <<' '<<interval<< endl;
        interval = 30;
        test(way);
        
                cout << speedLimit <<' '<<interval<< endl;
        interval = 60;
        test(way);
                cout << speedLimit <<' '<<interval<< endl;
        
    }
    return 0;
}

