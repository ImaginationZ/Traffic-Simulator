//
//  road.cpp
//  Transport
//
//  Created by Huang Zen on 2/7/14.
//  Copyright (c) 2014 Huang Zen. All rights reserved.
//

#include "road.h"
#include "rule.h"
#include "fstream"
#include<iomanip>
using namespace std;

ofstream fout("output.txt");


car* road::getCar(int arg){
    return carPool[arg];
}

int road::getCarNum(){
    return carNum;
}

int road::getLanes(){
    return lanes;
}

int road::getLength(){
    return length;
}

int road::addCar(int argLength, int argLane, int argVelosity){
    if(carTrash.size()){
        int p = carTrash.front();
        carTrash.pop();
        carPool[p]->clear();
        carPool[p]->setLength(argLength);
        carPool[p]->setLane(argLane);
        carPool[p]->setVelosity(argVelosity);
        carPool[p]->setMaxVelosity(argVelosity);
        carPool[p]->setPosition(0);
        carPool[p]->cleared = 0;
        return p;
    }
    else{
        carPool.push_back(new car(carNum,argLength, argLane, argVelosity));

        carNum = (int)carPool.size();
        return carNum-1;
    }
}

void road::remove(car* arg){
    id[arg->getLane()][arg->getPosition()] = -1;
    totalV += arg->getVelosity();
    //fout << arg->getMaxVelosity()*2 << ' '<<arg->getVelosity()*2 << endl;
    carTrash.push(arg->getId());
    arg->cleared = 1;
    arg->clear();
    trashNum++;
}

void road::update(){
    rightRule(this);
}

road::road(int argLanes, int argLength):
lanes(argLanes),length(argLength),carNum(0),trashNum(0){
    carPool.clear();
    carTrash.empty();
    for (int i=0; i<lanes; ++i) {
        for (int j=0; j<length; ++j) {
            id[i][j] = -1;
        }
    }
}

int& road::getId(int argLane, int argLength){
    return id[argLane][argLength];
}