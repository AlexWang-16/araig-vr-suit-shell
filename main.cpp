//
//  main.cpp
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

int main(int argc, const char * argv[]) {
  
  //Test: constructing an empty stim object
  //Expected: Compiler should fail because empty constructor has been deleted
  //  Stims emptyStim;
  //  emptyStim.display(std::cout) << '\n';
  
  Stims alphaStim ("Stim1", "back", 87, 35, 10);
  alphaStim.display(std::cout) << '\n';
  
  //Test: Intensity exceeding 100
  //Expected: Intensity to be capped at 100 despite 101 being specified
  Stims itensityOverload_stim ("Stim2", "abs", 101, 35, 20);
  itensityOverload_stim.display(std::cout) << '\n';
  
  
  //TODO: Change intensity and frequency from unsigned to signed. Manually handle negative numbers.
  
  //TODO: Handle negative duration
  
  //TODO: Stim with empty name
  
  //TODO: Stim with empty location
  
  //Test: constructing an empty exoskeleton object
  //Expected: Compilation should fail because empty constructor has been deleted
  //Exoskeleton emptyExoskeleton;
  
  Exoskeleton alphaExo ("Stim7", 66, 5);
  alphaExo.display(std::cout) << '\n';
  
  //TODO: Exoskeleton () should handle empty stim name
  
  //TODO: Exoskeleton () should handle negative Intensity
  
  //TODO: Exoskeleton () should handle negative duration
}
