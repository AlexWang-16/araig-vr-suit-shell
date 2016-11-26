//
//  MS2_tester.cpp
//
//  ARAIG - As Real As It Gets Augmented reality game suit final project
//  For BTP305 C++ course at Seneca
//
//  Created by Alex Wang on 2016-11-14.
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include <iostream>
#include "Stims.h"
#include "Exoskeleton.h"
#include "Task.h"
using namespace ARAIG;
extern const int max_duration;
extern const sint max_intensity;

int main(int argc, const char * argv[]) {
  //Test: Creating an empty Task
  //Expected: Task# should be 1 and name should be should be "Task_1"
  Task alpha;
  alpha.dump(std::cout);
  
  //Test: Instanting a second empty class and attempting to print its data and list of empty stimulations
  //Expected: Task# should be 2, Task name should be "Task_2" and no stimulation should show
  Task beta;
  beta.dump(std::cout);
  
  //Test: Giving task a name "Charlie" and an empty list of stimulations and printing task information
  //Expected: "Task 3 Task Test"
  Task charlie ("Charlie");
  charlie.dump(std::cout);
  
  //Test: Providing an empty name and an empty list of stimulations and printing task information
  //Expected: Task 4 Task_4
  Task delta ("");
  delta.dump(std::cout);
  
  //Test: Creating a generic task and add 3 stimulations to the Task, then print out task information and details of each stimulation
  //Expected: It should print "Task 5 Task_5" followed by the stimulation information
  //TODO
  
  //Test: Copy Task 5 using "=" operator
  //Expected: Information printed should be the same as Task 5 (see above)
  
  
}
