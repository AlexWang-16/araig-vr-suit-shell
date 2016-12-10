//
//  Stimulation.h
//  ARAIG
//
//  Created by Alex Wang on 2016-11-14.
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#ifndef Stimulation_h
#define Stimulation_h
#include "Global.h"
#include "Exceptions.h"
namespace ARAIG {
  
  class Stimulation {
  protected:
    std::string stimName_;
    int intensity_ = 0;
    int duration_ = 0;
  public:
    Stimulation()=delete;
    Stimulation (std::string name, int intensity, int duration);
    virtual ~Stimulation();
    virtual std::string getName()const;
    virtual std::ostream& display(std::ostream& os)const = 0;
  };
}
const int max_duration = ARAIG::duration_max;
const int max_intensity = ARAIG::intensity_max;
const int max_frequency = ARAIG::frequency_max;

#endif /* Stimulation_h */
