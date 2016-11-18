//
//  Stimulation.cpp
//  ARAIG
//
//  Created by Alex Wang on 2016-11-17.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include <iostream>
#include "Stimulation.h"
namespace ARAIG {
  Stimulation::Stimulation (std::string name, ushort intensity, size_t duration): stimName_(name), duration_(duration){
    if (intensity <= 100){
      //Since intensity_ is unsigned short, it cannot be less than 0
      intensity_ = intensity;
    } else {
      intensity_ = 100;
    }
  };
}
