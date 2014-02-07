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

class rightRule{
private:
    
public:
    rightRule(road *arg){
        std::queue<car*> carQueue;
        carQueue.empty();
        int *tmpV = new int[arg->getCarNum()];
        for (int i=0; i<arg->getCarNum(); ++i) {
            tmpV[i] = arg->getCar(i)->getVelosity();
            if (arg->getCar(i)->getVelosity() > 0 && !arg->getCar(i)->askCrashed())
                carQueue.push(arg->getCar(i));
        }
        while(carQueue.size()){
            car* now = carQueue.front();
            if(tmpV[now->getId()]>0){
                int id;
                if((id = arg->getId(now->getLane(), now->getPosition()+1)) != -1){
                    car* front = arg->getCar(id);
                    tmpV[now->getId()] = 0;
                    tmpV[id] = 0;
                    front->crash();
                    now->crash();
                }
                else {
                    tmpV[now->getId()]--;
                    arg->getId(now->getLane(), now->getPosition()) = -1;
                    now->setPosition(now->getPosition()+1);
                    arg->getId(now->getLane(), now->getPosition()) = now->getId();
                }
            }
            carQueue.pop();
            if(tmpV[now->getId()] > 0)
                carQueue.push(now);
        }
    };
};

#endif /* defined(__Transport__rule__) */
