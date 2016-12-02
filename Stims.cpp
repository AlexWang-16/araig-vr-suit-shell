//
//  Stims.cpp
//  ARAIG
//
//  Created by Alex Wang on 2016-11-14.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include "Stims.h"
namespace ARAIG {
  Stims::location Stims::stringToLocation(std::string destination){
    location target = NONE;
    if (destination == "abs"){
      target = ABS;
    }
    else if (destination == "front"){
      target = FRONT;
    }
    else if (destination == "back") {
      target = BACK;
    }
    else if (destination == "traps") {
      target = TRAPS;
    }
    return target;
  }
  
  const std::string Stims::locationToString(location stimLocation)const{
    std::string location;
    
    switch (stimLocation){
      case location::ABS:
        location = "abs";
        break;
      case location::FRONT:
        location = "front";
        break;
      case location::BACK:
        location = "back";
        break;
      case location::TRAPS:
        location = "traps";
        break;
      default:
        location = "none";
    }
    
    return location;
  }
  
  Stims::Stims(std::string name, std::string location, int intensity, int frequency, int duration): Stimulation(name, intensity, duration){
      stimLocation_ = stringToLocation(location);
    
    if (frequency >= 0 && frequency <= max_frequency){
      frequency_ = frequency;
    }else if (frequency > max_frequency){
      frequency_= max_frequency;
    }
  }
  
  std::ostream& Stims::display(std::ostream& os)const{
    os << stimName_ << '\n';
    os.width(5);
    os << ' '  << "Type = " << stimType_ << '\n';
    os.width(5);
    os << ' '  << "Location = " << locationToString(stimLocation_) << '\n';
    os.width(5);
    os << ' ' << "Intensity = " << intensity_ << '\n';
    os.width(5);
    os << ' ' << "Frequency = " << frequency_ << '\n';
    os.width(5);
    os << ' ' << "Duration = " << duration_;
    os.flush();
    return os;
  }
}
