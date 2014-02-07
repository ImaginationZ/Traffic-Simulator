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
#include <iostream>

class road{
private:
    int carNum;
    std::vector<car*> carPool;
    int lanes;
    int length;
    int error;
    int id[10][10000];
    
public:
    car* getCar(int arg);
    int getCarNum();
    int addCar(int argLength, int argLane, int argVelosity);
    void update();
    road(int argLanes, int argLength);
    int& getId(int argLane, int argLength);
};

#endif /* defined(__Transport__road__) */
