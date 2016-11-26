//
//  Stims.h
//  ARAIG
//
//  Created by Alex Wang on 2016-11-14.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//
// Stims determines the contractions of muscles across the body
#ifndef Stims_H
#define Stims_H

#include <iostream>
#include "Stimulation.h"
namespace ARAIG {
  class Stims : public Stimulation {
    enum location {NONE = 0, ABS, FRONT, BACK, TRAPS};
    std::string stimType_ = "stim";
    location stimLocation_;
    sint frequency_ = 0;
    
    //private member functions
    location stringToLocation(std::string);
    const std::string locationToString(location)const;
  public:
    Stims() = delete;
    Stims (std::string, std::string, sint, sint, int);
    //~Stims(); not sure if I need this yet
    virtual Stimulation* clone();
    std::ostream& display(std::ostream& os)const;
    
  };
}

#endif /* Stims_H */
