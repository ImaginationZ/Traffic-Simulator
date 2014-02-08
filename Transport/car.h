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
    bool changing;
    car* lastPass;
    int countdown;
    int position; // a mulitipal of cell-length
    int velosity; // a mulitipal of cell-length, per mTime
    int maxVelosity;
    //road *onRoad;
    
public:
    bool cleared;
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
    car* getLastPass();
    int getPosition();
    void setPosition(int arg);
    int getVelosity();
    double askVelosity(); // miles per minutes
    int getMaxVelosity();
    void setMaxVelosity(int arg);
    void setVelosity(int arg);
    void crash(int arg);
    bool askCrashed();
    bool askChanging();
    void setChange(int arg, car* argLastPass);
    void quitChange();
    int setCountDown();
    
    car();
    void clear();
    car(int argId, int argLength, int argLane, int argVelosity):cleared(0),
    id(argId),length(argLength),lane(argLane),velosity(argVelosity),maxVelosity(argVelosity),changes(0),position(0),countdown(0),lastPass(NULL),crashed(0){};
    
};

#endif /* defined(__Transport__car__) */
