//
//  rule.h
//  Transport
//
//  Created by Huang Zen on 2/7/14.
//  Copyright (c) 2014 Huang Zen. All rights reserved.
//

#ifndef __Transport__rule__
#define __Transport__rule__

#include <iostream>
#include "car.h"
#include "road.h"
#include "queue"
#include "cmath"
#include "ctime"
#include "cstdlib"
#include "set"
#include "fstream"

using namespace std;

class rightRule{
private:
    
    int safeDist = 50; // a mulitipal of cell-length
    
    struct cmp{
        bool operator()(car* a,car *b){
            return a->getPosition() > b->getPosition();
        }
    };
    bool askChange(int argV, int argP){
        double p = 1-5*(double)argP/argV/safeDist;
        return (std::rand() < RAND_MAX * p);
    };
    
public:
        rightRule(road*);
};

class middleRule{
private:
    
    double mTime; // min simulation time
    int cell; // min simulation length
    int safeDist = 200; // a mulitipal of cell-length
    int crashTime=1;
    double lamda=0.1;
    int changeTime=1;
    
    struct cmp{
        bool operator()(car* a,car *b){
            return a->getPosition() > b->getPosition();
        }
    };
    bool askChange(int argV, int argP){
        double p = 1-5*(double)argP/argV/safeDist;
        return (std::rand() < RAND_MAX * p);
    };
    bool askDecelerate(int argV){
        return (std::rand() < RAND_MAX * std::exp(-lamda * argV ));
    }
public:
    middleRule(road*);
};


class doubleRule{
private:
    
    double mTime; // min simulation time
    int cell; // min simulation length
    int safeDist = 50; // a mulitipal of cell-length
    int crashTime=1;
    double lamda=0.1;
    int changeTime=1;
    
    struct cmp{
        bool operator()(car* a,car *b){
            return a->getPosition() > b->getPosition();
        }
    };
    bool askChange(int argV, int argP){
        double p = 1-5*(double)argP/argV/safeDist;
        return (std::rand() < RAND_MAX * p);
    };

public:
    doubleRule(road*);
};

#endif /* defined(__Transport__rule__) */
