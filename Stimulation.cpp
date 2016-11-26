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
  Stimulation::Stimulation (std::string name, sint intensity, int duration): stimName_(name){
    
    try{
      if (!name.length()){
        Exceptions e ("Error: Empty Stimulation name detected. File may be corrupted. \nPlease ensure data conforms to format: exoskeleton <simulation name> intensity, duration.");
        throw e;
      }
    } catch (Exceptions& e){
      std::cerr << e.what() << '\n';
      std::cerr.flush();
      exit(1);
    }
    
    if (intensity > 0 && intensity <= max_intensity){
      intensity_ = intensity;
    }else if (intensity > max_intensity) {
      intensity_ = max_intensity;
    }
    
    if (duration > 0 && duration <= max_duration ) {
    duration_ = duration;
    } else if (duration > max_duration)
      duration_ = max_duration;
  };
}


