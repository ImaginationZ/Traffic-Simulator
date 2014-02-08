//
//  car.cpp
//  Transport
//
//  Created by Huang Zen on 2/7/14.
//  Copyright (c) 2014 Huang Zen. All rights reserved.
//

#include "car.h"
#include "rule.h"

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

car* car::getLastPass(){
    return lastPass;
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

int car::getMaxVelosity(){
    return maxVelosity;
}

void car::setVelosity(int arg){
    if (arg > maxVelosity) maxVelosity = arg;
    velosity = arg;
}

void car::crash(int arg){
    crashed = true;
    countdown = arg;
}

bool car::askCrashed(){
    return crashed;
}

bool car::askChanging(){
    return changing;
}

void car::setChange(int arg, car* argLastPass){
    if(changing) return;
    changing = true;
    lastPass = argLastPass;
    countdown = arg;
}

void car::quitChange(){
    ++changes;
    changing = false;
}

int car::setCountDown(){
    countdown--;
    return countdown;
}

void car::clear(){
    velosity = 0;
    maxVelosity = 0;
    changing = 0;
    changes = 0;
    position = 0;
    countdown = 0;
    crashed = 0;
    lastPass = NULL;
}