//
//  car.cpp
//  Transport
//
//  Created by Huang Zen on 2/7/14.
//  Copyright (c) 2014 Huang Zen. All rights reserved.
//

#include "car.h"
#include "rule.h"
#include "constants.h"

int car::getId(){
    return id;
}

void car::setId(int arg){
    id = arg;
}

/*
road* car::getRoad(){
    return onRoad;
}

void car::setRoad(road *arg){
    onRoad = arg;
}
*/

int car::getLane(){
    return lane;
}

void car::setLane(int arg){
    lane = arg;
}

int car::getLength(){
    return length;
}

void car::setLength(int arg){
    length = arg;
}

void car::addChanges(){
    changes++;
}

int car::getChanges(){
    return changes;
}

int car::getPosition(){
    return position;
}

void car::setPosition(int arg){
    position = arg;
}

int car::getVelosity(){
    return velosity;
}

double car::askVelosity(){
    return velosity * cell / mTime;
}

int car::getMaxVelosity(){
    return maxVelosity;
}

void car::setVelosity(int arg){
    if (arg > maxVelosity) maxVelosity = arg;
    velosity = arg;
}

void car::crash(){
    crashed = true;
}

bool car::askCrashed(){
    return crashed;
}