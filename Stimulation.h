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
#include <vector>
#include <memory>
#include <iterator>
#include <fstream>
#include <string>
#include "Exceptions.h"
namespace ARAIG {
  const int duration_max = 300;
  const int intensity_max = 100, frequency_max = 10000;
  class Stimulation {
  protected:
    std::string stimName_;
    std::string stimType_;
    int intensity_ = 0;
    int duration_ = 0;
  public:
    Stimulation()=delete;
    Stimulation (std::string, int, int);
    virtual std::string getName()const;
    virtual std::ostream& display(std::ostream& os)const = 0;
  };
}
const int max_duration = ARAIG::duration_max;
const int max_intensity = ARAIG::intensity_max;
const int max_frequency = ARAIG::frequency_max;

#endif /* Stimulation_h */
