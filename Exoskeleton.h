//
//  Exoskeleton.h
//  ARAIG
//
//  Created by Alex Wang on 2016-11-14.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//
// Exoskelete determines vibrations across the body
#ifndef Exoskeleton_H
#define Exoskeleton_H

#include <iostream>
#include "Stimulation.h"
namespace ARAIG {
  class Exoskeleton : public Stimulation{
    std::string stimType_ = "exoskeleton";
  public:
    Exoskeleton() = delete;
    Exoskeleton(std::string, sint, int);
    //~Exoskeleton(); not sure if I need this yet
    virtual Stimulation* clone();
    std::ostream& display(std::ostream& os)const;
  };
}

#endif /* Exoskeleton_H */
