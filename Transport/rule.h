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
    
    double mTime; // min simulation time
    int cell; // min simulation length
    int safeDist = 50; // a mulitipal of cell-length
    int crashTime=1;
    double lamda=0.1;
    int changeTime=1;
    int speedlimit = 20;
    
    struct cmp{
        bool operator()(car* a,car *b){
            return a->getPosition() > b->getPosition();
        }
    };
    bool askChange(int argV, int argP){
        double p = (double)argV/safeDist*exp(-argP/safeDist-argP);
        return (std::rand() < RAND_MAX * p);
    };
    bool askDecelerate(int argV){
        return (std::rand() < RAND_MAX * std::exp(-lamda * argV ));
    }
public:
        rightRule(road*);
};

#endif /* defined(__Transport__rule__) */
