//
//  MS1_tester.cpp
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
using namespace ARAIG;
extern const int max_duration;
extern const sint max_intensity;

int main(int argc, const char * argv[]) {
  
  //Test: constructing an empty stim object
  //Expected: Compiler should fail because empty constructor has been deleted
  //  Stims emptyStim;
  //  emptyStim.display(std::cout) << '\n';
  
  Stims alphaStim ("Stim1", "back", 87, 35, 10);
  alphaStim.display(std::cout) << '\n';
  
  //Test: Intensity negative values
  //Expected: Intensity, Frequency, Duration all set to 0
  Stims negativeStim ("Stim2", "abs", -1, -1, -1);
  negativeStim.display(std::cout) << '\n';
  
  //Test: Intensity overflow
  //Expected: Set to max intensity
  Stims intensityOverload_stims ("Stim3", "traps", max_intensity + 1, 100, 200);
  
  intensityOverload_stims.display(std::cout) << '\n';
  
  //TODO: Frequency overflow
  //Expected: Set to max frequency
  Stims freqOverflow_stims ("Stim4", "traps", 20, max_frequency + 1, 200);
  freqOverflow_stims.display(std::cout) << '\n';
  
  //Test: Duration Exceeding int_max
  //Expected: Duration should be set to max_duration
  Stims durationOverflow_Stim ("Stim5", "back", 10, 10, max_duration + 1);
  durationOverflow_Stim.display(std::cout) << '\n';
  
  //Test: Stim with empty name
  //Expected:: Exception thrown. Any stim without a piece of information that will render output errors will be stopped.
  //Stims emptyStim ("", "front", 1, 50, 20);
  //emptyStim.display(std::cout) << '\n';
  
  //Test: Stim with empty location
  //Expected: Location will be declared as none
  Stims noLocation_stims ("Stim7", "", 50, 50, 50);
  noLocation_stims.display(std::cout) << '\n';
  
  //Test: constructing an empty exoskeleton object
  //Expected: Compilation should fail because empty constructor has been deleted
  //Exoskeleton emptyExo;

  
  Exoskeleton alphaExo ("Exo1", 66, 5);
  alphaExo.display(std::cout) << '\n';
  
  //Test: Empty Exoskeleton name
  //Expected: An exception is thrown. Any stim without a piece of information that will render output errors will be stopped
  //Exoskeleton emptyNameExo ("", 0, 0);;
  //emptyNameExo.display(std::cout) << '\n';
  
  //Test: Exoskeleton with negative intensity and duration
  //Expected: Intensity and duration both set to 0
  Exoskeleton negativeExo ("Exo3", -1, -1);
  negativeExo.display(std::cout) << '\n';
  
  //Test: Exoskeleton exceeding max intensity
  //Expected: Intesnity should be set to 100 (max intensity)
  Exoskeleton intesityOverload_exo ("Exo4", max_intensity + 1, 50);
  intesityOverload_exo.display(std::cout) << '\n';
  
  //Test: Exoskeleton exceeding max duration
  //Expected: Intesnity should be set to max_duration
  Exoskeleton durationOverload_exo ("Exo5", 50, duration_max + 1);
  durationOverload_exo.display(std::cout) << '\n';
}
