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


using namespace std;

static int crashNum = 0;


class rightRule{
private:
    
    double mTime; // min simulation time
    int cell; // min simulation length
    int safeDist = 50; // a mulitipal of cell-length
    int limit1;
    int limit2;
    int limit3;
    int crashTime=1;
    double lamda=0;
    int changeTime=1;
    
    struct cmp{
        bool operator()(car* a,car *b){
            return a->getPosition() > b->getPosition();
        }
    };
    bool askChange(int argV, int argP){
        double p = (double)argV / 20 * std::exp(-argP/(double)(20 - argP));
        return (std::rand() < RAND_MAX * p);
    };
    bool askDecelerate(int argV){
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
        int *tmpV = new int[arg->getCarNum()];
        for (int i=0; i<arg->getCarNum(); ++i) {
            car* tmp = arg->getCar(i);
            //process crashed
            if(tmp->askCrashed()){
                if(tmp->setCountDown() <=0 ){
                    arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                    arg->remove(tmp);
                }
            }
            // get back
            else if(tmp->getLane()>0 && !tmp->askChanging() && tmp->getLastPass()!=NULL){
                if(tmp->getPosition() > tmp->getLastPass()->getPosition() &&
                   arg->getId(tmp->getLane()-1, tmp->getPosition())==-1 && arg->getId(tmp->getLane()-1, tmp->getPosition()-1)==-1 &&
                arg->getId(tmp->getLane()-1, tmp->getPosition()+1)==-1
                   ){
                    arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                    tmp->setLane(tmp->getLane()-1);
                    arg->getId(tmp->getLane(), tmp->getPosition()) = tmp->getId();
                }
            }
            
            //get changed
            else if(tmp->askChanging()){
                if(tmp->setCountDown() <= 0){
                    if(arg->getId(tmp->getLane()+1, tmp->getPosition()) == -1){
                        tmp->quitChange();
                        arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                        tmp->setLane(tmp->getLane()+1);
                        arg->getId(tmp->getLane(), tmp->getPosition()) = tmp->getId();

                    }
                    else{
                        tmp->quitChange();
                    }
                }
            }
            //get order
            carList[tmp->getLane()].insert(tmp);
            //get velosity
            tmpV[i] = tmp->getVelosity();
            if (tmp->getVelosity() > 0 && !tmp->askCrashed())
                carQueue[tmp->getLane()].push(tmp);
        }
        for (int i=0; i<arg->getLanes()-1; ++i) {
            for (std::set<car*,cmp>::iterator iter = carList[i].begin(); iter != carList[i].end();) {
                car* front = *iter;
                ++iter;
                if(iter == carList[i].end()) break;
                car* now = *iter;
                int diffV = now->getVelosity() - front->getVelosity();
                int diffP = front->getPosition() - now->getPosition();
                if(diffV < 0){}
                else if(diffP > safeDist){}
                else if(askChange(diffV, diffP)){
                    now->setChange(changeTime, front);
                }
                else if(askDecelerate(now->getVelosity())){
                    now->setVelosity(front->getVelosity());
                }
            }
        }
        for (int i=0; i<arg->getLanes(); ++i){
            while(carQueue[i].size()){
                car* now = carQueue[i].front();
                if(tmpV[now->getId()]>0){
                    int id;
                    if((id = arg->getId(now->getLane(), now->getPosition()+1)) != -1){
                        car* front = arg->getCar(id);
                        tmpV[now->getId()] = 0;
                        tmpV[id] = 0;
                        front->crash(crashTime);
                        now->crash(crashTime);
                        ++crashNum;
                        cout << crashNum << ": " <<now->getId() << " crash " << front->getId()<<endl;
                    }
                    else {
                        tmpV[now->getId()]--;
                        arg->getId(now->getLane(), now->getPosition()) = -1;
                        now->setPosition(now->getPosition()+1);
                        arg->getId(now->getLane(), now->getPosition()) = now->getId();
                        if(now->getPosition() >= arg->getLength() - 2){
                            arg->remove(now);
                            tmpV[now->getId()] = 0;
                        }
                    }
                }
                carQueue[i].pop();
                if(tmpV[now->getId()] > 0)
                    carQueue[i].push(now);
            }
        }
    };
};

#endif /* defined(__Transport__rule__) */
