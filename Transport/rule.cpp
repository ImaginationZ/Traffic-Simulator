//
//  rule.cpp
//  Transport
//
//  Created by Huang Zen on 2/8/14.
//  Copyright (c) 2014 Huang Zen. All rights reserved.
//

#include "rule.h"
#include "fstream"

rightRule::rightRule(road *arg){
    std::queue<car*> carQueue[10];
    std::set<car*,cmp> carList[10];
    for (int i=0; i<10; ++i) {
        carQueue[i].empty();
        carList[i].empty();
    }
    for (int i=0; i<arg->getCarNum(); ++i) {
        car* tmp = arg->getCar(i);
        //get get
        //get change
        if(tmp->askChanging()){
            bool flag = true;
            for (int k=0; k < tmp->getVelosity(); ++k){
                if(arg->getId(tmp->getLane()+1, tmp->getPosition()+k)!= -1
                   ||
                   arg->getId(tmp->getLane()+1, tmp->getPosition()-k)!= -1
                   ){
                    flag = false;
                    if(!flag)break;
                }
            }
            if(flag){
                arg->getId(tmp->getLane()+1, tmp->getPosition()) = tmp->getId();
                arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                tmp->setLane(tmp->getLane()+1);
                arg->totalChange++;
                //cout << arg->totalChange << " : "<<i <<" change to Lane "<<tmp->getLane()<<endl;
                tmp->quitChange();
            }
        }
        //get back
        if(tmp->getLane()>0){
            bool flag;
            if(tmp->getLane()>1) flag = true;
            if(tmp->getLastPass()!=NULL)
                flag = (tmp->getPosition() > tmp->getLastPass()->getPosition());
            if(tmp->getLane()==1 && rand()%200000==0) flag=true;
            for (int k=0; k < tmp->getVelosity(); ++k){
                if(arg->getId(tmp->getLane()-1, tmp->getPosition()+k)!= -1
                   ||
                   arg->getId(tmp->getLane()-1, tmp->getPosition()-k)!= -1
                   ){
                    flag = false;
                    if(!flag)break;
                }
            }
            if(flag){
                arg->getId(tmp->getLane()-1, tmp->getPosition()) = tmp->getId();
                if(arg->getLanes()==0 && rand()%10==0)
                arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                tmp->setLane(tmp->getLane()-1);
            }
        }
        //get order
        carList[tmp->getLane()].insert(tmp);
    }
    //set car-follow rules
    for (int i=0; i<arg->getLanes(); ++i) {
        for (std::set<car*,cmp>::iterator iter = carList[i].begin(); iter != carList[i].end();) {
            car* front = *iter;
            ++iter;
            if(iter == carList[i].end()) break;
            car* now = *iter;
            int diffV = now->getVelosity() - front->getVelosity();
            int diffP = front->getPosition() - now->getPosition();
            if(diffV > 0 && diffP<safeDist && askChange(diffV, diffP) && now->getLane() < arg->getLanes()-1){
                now->setChange(front);
            }
            if(now->getVelosity() >= diffP){
                arg->diffV += now->getVelosity() - diffP + 1;
                if(now->getVelosity() - diffP + 1 > now->getVelosity()*0.15)
                    arg->crashNum++;
                now->setVelosity(diffP-1);
            }
        }
    }
    for (int i=0; i<arg->getCarNum() ; ++i){
        car* tmp = arg->getCar(i);
        tmp->time++;
        arg->getId(tmp->getLane(), tmp->getPosition())= -1;
        tmp->setPosition(tmp->getPosition()+tmp->getVelosity());
        arg->getId(tmp->getLane(), tmp->getPosition())= i;
        if(tmp->getVelosity()<tmp->getMaxVelosity()){
            tmp->setVelosity(tmp->getVelosity()+1);
        }
        if(tmp->getVelosity() < tmp->getMaxVelosity()*0.75)
            tmp->lowTime++;
    }
}

middleRule::middleRule(road *arg){
    std::queue<car*> carQueue[10];
    std::set<car*,cmp> carList[10];
    for (int i=0; i<10; ++i) {
        carQueue[i].empty();
        carList[i].empty();
    }
    for (int i=0; i<arg->getCarNum(); ++i) {
        car* tmp = arg->getCar(i);
        //get change
        if(tmp->askChanging()){
            bool flag = true;
            bool left = rand()%2;
            if(left && tmp->getLane()<arg->getLanes()-1){
                for (int k=0; k < tmp->getVelosity(); ++k){
                    if(arg->getId(tmp->getLane()+1, tmp->getPosition()+k)!= -1
                       ||
                       arg->getId(tmp->getLane()+1, tmp->getPosition()-k)!= -1
                       ){
                        flag = false;
                        if(!flag)break;
                    }
                }
                if(flag){
                    arg->getId(tmp->getLane()+1, tmp->getPosition()) = tmp->getId();
                    arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                    tmp->setLane(tmp->getLane()+1);
                    arg->totalChange++;
                    //cout << arg->totalChange << " : "<<i <<" change to Lane "<<tmp->getLane()<<endl;
                    tmp->quitChange();
                }
            }
            if((!flag || !left) && tmp->getLane()>0){
                flag = true;
                if(tmp->getLastPass()!=NULL)
                    flag = (tmp->getPosition() > tmp->getLastPass()->getPosition());
                for (int k=0; k < tmp->getVelosity(); ++k){
                    if(arg->getId(tmp->getLane()-1, tmp->getPosition()+k)!= -1
                       ||
                       arg->getId(tmp->getLane()-1, tmp->getPosition()-k)!= -1
                       ){
                        flag = false;
                        if(!flag)break;
                    }
                }
                if(flag){
                    arg->getId(tmp->getLane()-1, tmp->getPosition()) = tmp->getId();
                    arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                    tmp->setLane(tmp->getLane()-1);
                    arg->totalChange++;
                    tmp->quitChange();
                }
            }
        }
        
        //get back
        if(tmp->getLane()== 1 ){
            bool flag = true;
            if(tmp->getLastPass()!=NULL)
                flag = (tmp->getPosition() > tmp->getLastPass()->getPosition());
            else flag = false;
            bool left = rand()%2;
            if(left){
                for (int k=0; k < tmp->getVelosity(); ++k){
                    if(arg->getId(2, tmp->getPosition()+k)!= -1
                       ||
                       arg->getId(2, tmp->getPosition()-k)!= -1
                       ){
                        flag = false;
                        if(!flag)break;
                    }
                }
                if(flag){
                    arg->getId(2, tmp->getPosition()) = tmp->getId();
                    arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                    tmp->setLane(2);
                    //cout << arg->totalChange << " : "<<i <<" change to Lane "<<tmp->getLane()<<endl;
                }
            }
            if((!flag || !left)){
                flag = true;
                if(tmp->getLastPass()!=NULL)
                    flag = (tmp->getPosition() > tmp->getLastPass()->getPosition());
                for (int k=0; k < tmp->getVelosity(); ++k){
                    if(arg->getId(0, tmp->getPosition()+k)!= -1
                       ||
                       arg->getId(0, tmp->getPosition()-k)!= -1
                       ){
                        flag = false;
                        if(!flag)break;
                    }
                }
                if(flag){
                    arg->getId(0, tmp->getPosition()) = tmp->getId();
                    arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                    tmp->setLane(0);
                }
            }
        }
        
        //get order
        carList[tmp->getLane()].insert(tmp);
    }
    //set car-follow rules
    for (int i=0; i<arg->getLanes(); ++i) {
        for (std::set<car*,cmp>::iterator iter = carList[i].begin(); iter != carList[i].end();) {
            car* front = *iter;
            ++iter;
            if(iter == carList[i].end()) break;
            car* now = *iter;
            int diffV = now->getVelosity() - front->getVelosity();
            int diffP = front->getPosition() - now->getPosition();
            if(diffV > 0 && diffP<safeDist && askChange(diffV, diffP) && now->getLane()!=1){
                now->setChange(front);
            }
            if(now->getVelosity() >= diffP){
                arg->diffV += now->getVelosity() - diffP + 1;
                if(now->getVelosity() - diffP + 1 > now->getVelosity()*0.15)
                    arg->crashNum++;
                now->setVelosity(diffP-1);
            }
        }
    }
    for (int i=0; i<arg->getCarNum() ; ++i){
        car* tmp = arg->getCar(i);
        tmp->time++;
        arg->getId(tmp->getLane(), tmp->getPosition())= -1;
        tmp->setPosition(tmp->getPosition()+tmp->getVelosity());
        arg->getId(tmp->getLane(), tmp->getPosition())= i;
        if(tmp->getVelosity()<tmp->getMaxVelosity()){
            tmp->setVelosity(tmp->getVelosity()+1);
        }
        if(tmp->getVelosity() < tmp->getMaxVelosity()*0.75)
            tmp->lowTime++;
    }
}

doubleRule::doubleRule(road *arg){
    std::queue<car*> carQueue[10];
    std::set<car*,cmp> carList[10];
    for (int i=0; i<10; ++i) {
        carQueue[i].empty();
        carList[i].empty();
    }
    for (int i=0; i<arg->getCarNum(); ++i) {
        car* tmp = arg->getCar(i);
        //get change
        if(tmp->askChanging()){
            bool flag = true;
            bool left = rand()%2;
            if(left && tmp->getLane()<arg->getLanes()-1){
                for (int k=0; k < tmp->getVelosity(); ++k){
                    if(arg->getId(tmp->getLane()+1, tmp->getPosition()+k)!= -1
                       ||
                       arg->getId(tmp->getLane()+1, tmp->getPosition()-k)!= -1
                       ){
                        flag = false;
                        if(!flag)break;
                    }
                }
                if(flag){
                    arg->getId(tmp->getLane()+1, tmp->getPosition()) = tmp->getId();
                    arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                    tmp->setLane(tmp->getLane()+1);
                    arg->totalChange++;
                //cout << arg->totalChange << " : "<<i <<" change to Lane "<<tmp->getLane()<<endl;
                    tmp->quitChange();
                }
            }
            if((!flag || !left) && tmp->getLane()>0){
                flag = true;
                if(tmp->getLastPass()!=NULL)
                    flag = (tmp->getPosition() > tmp->getLastPass()->getPosition());
                for (int k=0; k < tmp->getVelosity(); ++k){
                    if(arg->getId(tmp->getLane()-1, tmp->getPosition()+k)!= -1
                       ||
                       arg->getId(tmp->getLane()-1, tmp->getPosition()-k)!= -1
                       ){
                        flag = false;
                        if(!flag)break;
                    }
                }
                if(flag){
                    arg->getId(tmp->getLane()-1, tmp->getPosition()) = tmp->getId();
                    arg->getId(tmp->getLane(), tmp->getPosition()) = -1;
                    tmp->setLane(tmp->getLane()-1);
                    arg->totalChange++;
                    tmp->quitChange();
                }
            }
        }
        
        //get order
        carList[tmp->getLane()].insert(tmp);
    }
    //set car-follow rules
    for (int i=0; i<arg->getLanes(); ++i) {
        for (std::set<car*,cmp>::iterator iter = carList[i].begin(); iter != carList[i].end();) {
            car* front = *iter;
            ++iter;
            if(iter == carList[i].end()) break;
            car* now = *iter;
            int diffV = now->getVelosity() - front->getVelosity();
            int diffP = front->getPosition() - now->getPosition();
            if(diffV > 0 && diffP<safeDist && askChange(diffV, diffP)){
                now->setChange(front);
            }
            if(now->getVelosity() >= diffP){
                arg->diffV += now->getVelosity() - diffP + 1;
                if(now->getVelosity() - diffP + 1 > now->getVelosity()*0.15)
                    arg->crashNum++;
                now->setVelosity(diffP-1);
            }
        }
    }
    for (int i=0; i<arg->getCarNum() ; ++i){
        car* tmp = arg->getCar(i);
        tmp->time++;
        arg->getId(tmp->getLane(), tmp->getPosition())= -1;
        tmp->setPosition(tmp->getPosition()+tmp->getVelosity());
        arg->getId(tmp->getLane(), tmp->getPosition())= i;
        if(tmp->getVelosity()<tmp->getMaxVelosity()){
            tmp->setVelosity(tmp->getVelosity()+1);
        }
        if(tmp->getVelosity() < tmp->getMaxVelosity()*0.75)
            tmp->lowTime++;
    }
}