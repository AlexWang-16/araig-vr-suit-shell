//
//  MS4_tester.cpp
//
//  ARAIG - As Real As It Gets Augmented reality game suit final project
//  For BTP305 C++ course at Seneca
//
//  Created by Alex Wang on 2016-11-14.
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include "Stims.h"
#include "Exoskeleton.h"
#include "Task.h"
#include "ARAIG_sensors.h"
#include "profile.h"
using namespace ARAIG;
extern const int max_duration, max_intensity;

const void print_dash(int x = 30) {
  //Creates underline for titles
  std::cout.width(x);
  std::cout.fill('-');
  std::cout << '-' << '\n';
  std::cout.fill (' ');
}

const void new_line(int x = 1) {
  //Prints i number of newline characters
  for (int i = 0; i < x; i++){
    std::cout << '\n';
  }
}


int main(int argc, const char * argv[]) {
  
  ARAIG_sensors alpha ("StimulationConfig.csv", "TaskConfiguration2.csv");
  
  Profile ("SampleProfileConfiguration.csv", std::cout, alpha);
  }
