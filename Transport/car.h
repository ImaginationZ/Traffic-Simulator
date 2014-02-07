//
//  car.h
//  Transport
//
//  Created by Huang Zen on 2/7/14.
//  Copyright (c) 2014 Huang Zen. All rights reserved.
//

#ifndef __Transport__car__
#define __Transport__car__

#include <iostream>
#include "vector"

class car{
private:
    bool crashed;
    int crashTime;
    
    int id;
    int length; // a mulitipal of min-length
    int lane;
    int changes; // times of lane changing
    int position; // a mulitipal of cell-length
    int velosity; // a mulitipal of cell-length, per mTime
    int maxVelosity;
    //road *onRoad;
    
public:
    int getId();
    void setId(int arg);
    //road* getRoad();
    //void setRoad(road *arg);
    int getLength();
    void setLength(int arg);
    int getLane();
    void setLane(int arg);
    void addChanges();
    int getChanges();
    int getPosition();
    void setPosition(int arg);
    int getVelosity();
    double askVelosity(); // miles per minutes
    int getMaxVelosity();
    void setVelosity(int arg);
    void crash();
    bool askCrashed();
    
    car();
    car(int argLength, int argLane, int argVelosity):
    length(argLength),lane(argLane),velosity(argVelosity),changes(0),position(0){};
    
};

#endif /* defined(__Transport__car__) */
