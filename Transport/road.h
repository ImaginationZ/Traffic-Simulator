//
//  road.h
//  Transport
//
//  Created by Huang Zen on 2/7/14.
//  Copyright (c) 2014 Huang Zen. All rights reserved.
//

#ifndef __Transport__road__
#define __Transport__road__

#include "vector"
#include "car.h"
#include "queue"
#include <iostream>

class road{
private:
    int carNum;
    std::vector<car*> carPool;
    std::queue<int> carTrash;
    int lanes;
    int length;
    int error;
    int id[10][100000];
    int trashNum;
    
public:
    
    int crashNum = 0;
    int totalChange = 0;
    int n1=0, n2=0, n3=0;
    int diffV = 0;
    long long totalV = 0;
    
    car* getCar(int arg);
    int getCarNum();
    int getLanes();
    int getLength();
    int addCar(int argLength, int argLane, int argVelosity);
    void remove(car* arg);
    void update();
    road(int argLanes, int argLength);
    int& getId(int argLane, int argLength);
};

#endif /* defined(__Transport__road__) */
