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
    int safeDist = 25; // a mulitipal of cell-length
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
        return 1;
        double p = (double)argV/10;
        return (std::rand() < RAND_MAX * p);
    };
    bool askDecelerate(int argV){
        return 1;
        return (std::rand() < RAND_MAX * std::exp(-lamda * argV ));
    }
public:
    rightRule(road *arg){
        std::queue<car*> carQueue[10];
        std::set<car*,cmp> carList[10];
        for (int i=0; i<10; ++i) {
            carQueue[i].empty();
            carList[i].empty();
        }
        for (int i=0; i<arg->getCarNum(); ++i) {
            car* tmp = arg->getCar(i);
            // get back
            if(tmp->getLane()>0 && !tmp->askChanging() && tmp->getLastPass()!=NULL){
                if(tmp->getPosition() > tmp->getLastPass()->getPosition() &&
                   arg->getId(tmp->getLane()-1, tmp->getPosition())==-1 && arg->getId(tmp->getLane()-1, tmp->getPosition()-1)==-1 &&
                arg->getId(tmp->getLane()-1, tmp->getPosition()+1)==-1
                   ){
                    bool flag = 1;
                    for (int k=0; k<safeDist; ++k) {
                        if(arg->getId(tmp->getLane()-1, tmp->getPosition()+k)!=-1 || arg->getId(tmp->getLane()+1, tmp->getPosition()-k)!=-1){
                            flag = 0;
                            break;
                        }
                    }
                    if(flag){
                        arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                        tmp->setLane(tmp->getLane()-1);
                        arg->getId(tmp->getLane(), tmp->getPosition()) = tmp->getId();

                    }
                    
                }
            }
            
            //get changed
            else if(tmp->askChanging()){
                if(tmp->setCountDown() <= 0){
                    if(arg->getId(tmp->getLane()+1, tmp->getPosition()) == -1){
                        bool flag = 1;
                        for (int k=0; k<safeDist; ++k) {
                            if(arg->getId(tmp->getLane()+1, tmp->getPosition()+k)!=-1 || arg->getId(tmp->getLane()+1, tmp->getPosition()-k)!=-1){
                                flag = 0;
                                break;
                            }
                        }
                        if(flag){
                            tmp->quitChange();
                            arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                            tmp->setLane(tmp->getLane()+1);
                            arg->getId(tmp->getLane(), tmp->getPosition()) = tmp->getId();
                            ++arg->totalChange;
                            /*
                            cout << tmp->getId()<<" changed to lane "<<tmp->getLane()<<endl;
                             */
                        }
                    }
                    else{
                        tmp->quitChange();
                    }
                }
            }
            //get order
            carList[tmp->getLane()].insert(tmp);
        }
        for (int i=0; i<arg->getLanes()-1; ++i) {
            for (std::set<car*,cmp>::iterator iter = carList[i].begin(); iter != carList[i].end();) {
                car* front = *iter;
                ++iter;
                if(iter == carList[i].end()) break;
                car* now = *iter;
                int diffV = now->getVelosity() - front->getVelosity();
                int diffP = front->getPosition() - now->getPosition();
                if(askChange(diffV, diffP)){
                    now->setChange(1, front);
                }
                if(diffV >= diffP){
                    now->setVelosity(front->getVelosity()-1);
                }
            }
        }
        for (int i=0; i<arg->getCarNum() ; ++i){
            car* tmp = arg->getCar(i);
            arg->getId(tmp->getLane(), tmp->getPosition())= -1;
            tmp->setPosition(tmp->getPosition()+tmp->getVelosity());
            arg->getId(tmp->getLane(), tmp->getPosition())= i;
            if(tmp->getVelosity()<tmp->getMaxVelosity())
                tmp->setVelosity(tmp->getVelosity()+1);
        }
    };
};

#endif /* defined(__Transport__rule__) */
