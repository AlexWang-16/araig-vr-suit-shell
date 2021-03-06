//
//  Exoskeleton.cpp
//  ARAIG
//
//  Created by Alex Wang on 2016-11-14.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include "Exoskeleton.h"
namespace ARAIG {
  Exoskeleton::Exoskeleton(std::string name, int intensity, int duration) : Stimulation(name, intensity, duration){}
  
  std::ostream& Exoskeleton::display(std::ostream& os)const{
    os << stimName_ << '\n';
    os.width(5);
    os << ' ' << "Type = " << stimType_ << '\n';
    os.width(5);
    os << ' ' << "Intensity = " << intensity_ << '\n';
    os.width(5);
    os << ' ' << "Duration = " << duration_;
    os.flush();
    return os;
  }
  
  Exoskeleton::~Exoskeleton(){
    stimType_.clear();
  }
  
  std::ostream& operator<<(std::ostream& os, Exoskeleton& exo_skeleton){
    exo_skeleton.display(os);
    return os;
  }
}
