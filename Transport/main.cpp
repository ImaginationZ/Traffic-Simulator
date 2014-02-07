//
//  main.cpp
//  Transport
//
//  Created by Huang Zen on 2/7/14.
//  Copyright (c) 2014 Huang Zen. All rights reserved.
//

#include <iostream>
#include "road.h"

int main(int argc, const char * argv[])
{
    road* way = new road(10,10000);
    way->addCar(1, 0, 5);
    for (int i=0; i<10; ++i) {
        way->update();
    }
    way->addCar(1,0,10);
    for (int i=0; i<20; ++i) {
        way->update();
    }
    std::cout<<way->getCar(0)->getPosition();
    return 0;
}

