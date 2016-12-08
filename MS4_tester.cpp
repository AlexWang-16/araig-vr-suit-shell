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

const void new_line(int x = 1) {
  //Prints i number of newline characters
  for (int i = 0; i < x; i++){
    std::cout << '\n';
  }
}


int main(int argc, const char * argv[]) {
  
  //TODO: Main needs to take in 4 command line arguments!
  
  //TODO: Main nneeds to open ostream using output file provided!
  
  ARAIG_sensors alpha ("StimulationConfig.csv", "TaskConfiguration.csv");
  
  Profile p1 ("SampleProfileConfiguration.csv", std::cout, alpha);
  p1.display_todo_tasks(std::cout);
  print_dash();
  std::cout << "Next Task is ";
  p1.display_next_task(std::cout);
  print_dash();
  p1.run();
  print_dash();
  std::cout << "1 cycle complete!\n";
  std::cout << "Next task is ";
  p1.display_next_task(std::cout);
  print_dash();
  p1.run();
  print_dash();
  std::cout << "Last task was ";
  p1.display_last_task(std::cout);
  print_dash();
  std::cout << "Completed tasks so far...\n";
  print_dash();
  p1.display_completed_tasks(std::cout);
}
