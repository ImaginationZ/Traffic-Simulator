//
//  road.cpp
//  Transport
//
//  Created by Huang Zen on 2/7/14.
//  Copyright (c) 2014 Huang Zen. All rights reserved.
//

#include "road.h"
#include "rule.h"

car* road::getCar(int arg){
    return carPool[arg];
}

int road::getCarNum(){
    return carNum;
}

int road::addCar(int argLength, int argLane, int argVelosity){
    carPool.push_back(new car(argLength, argLane, argVelosity));
    carNum = (int)carPool.size();
    return carNum-1;
}

void road::update(){
    rightRule(this);
}

road::road(int argLanes, int argLength):
lanes(argLanes),length(argLength),carNum(0){
    carPool.clear();
    for (int i=0; i<lanes; ++i) {
        for (int j=0; j<length; ++j) {
            id[i][j] = -1;
        }
    }
}

int& road::getId(int argLane, int argLength){
    return id[argLane][argLength];
}