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
#include "Profile.h"
using namespace ARAIG;
extern const int max_duration, max_intensity;

int main(int argc, const char * argv[]) {
  
  try{
    if (argc != 5 ){
      throw Exceptions ("Error: Incorrect number of arguments.\nFormat: Stimulation config filename, Task config filename, Profile config filename, Output filename\n", 1);
    }
  } catch (Exceptions& e) {
    std::cerr << e.what() << '\n';
    std::cerr.flush();
    exit (e.code_);
  }
  
  //StimulationConfig.csv
  std::ofstream of (argv[4], std::ios::trunc);
  //TODO: Some form of file open check for ofstream
  try{
    if(!argv[4]){
      throw Exceptions ("Error: Invalid output filename. Check your parameters.\n", 2);
    }else if (!of){
      throw Exceptions ("Error: Cannot open or create " + std::string(argv[4]) + ". Check permissions for executable file and directory to ensure writing is possible.\n", 5);
    }
  }catch (Exceptions& e){
    std::cerr << e.what() << '\n';
    std::cerr.flush();
    exit (e.code_);
  }
  
  ARAIG_sensors alpha (argv[1], argv[2]);
  Profile p1 (argv[3], of, alpha);
  
  p1.run();
}
