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

namespace ARAIG {
  typedef unsigned short ushort;
  class Stimulation {
  protected:
    std::string stimName_;
    std::string stimType_;
    ushort intensity_ = 0;
    size_t duration_ = 0;
  public:
    virtual std::ostream& display(std::ostream&)const = 0;
    Stimulation (std::string, ushort, size_t);
    Stimulation()=delete;
  };
}

#endif /* Stimulation_h */
