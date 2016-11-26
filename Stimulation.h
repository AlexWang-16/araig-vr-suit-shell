//
//  Stimulation.h
//  ARAIG
//
//  Created by Alex Wang on 2016-11-14.
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#ifndef Stimulation_h
#define Stimulation_h
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include "Exceptions.h"
typedef short sint;
namespace ARAIG {
  const int duration_max = 300;
  const sint intensity_max = 100, frequency_max = 10000;
  class Stimulation {
  protected:
    std::string stimName_;
    std::string stimType_;
    sint intensity_ = 0;
    sint duration_ = 0;
  public:
    virtual std::ostream& display(std::ostream&)const = 0;
    virtual Stimulation* clone() = 0;
    Stimulation (std::string, sint, int);
    Stimulation()=delete;
  };
}
const int max_duration = ARAIG::duration_max;
const sint max_intensity = ARAIG::intensity_max;
const sint max_frequency = ARAIG::frequency_max;

#endif /* Stimulation_h */
