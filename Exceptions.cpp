//
//  Exceptions.cpp
//  ARAIG
//
//  Created by Alex Wang on 2016-11-24.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include "Exceptions.h"
namespace ARAIG {
  const char* Exceptions::what() const throw (){return (msg_ + filename_).c_str();}
  
  Exceptions::Exceptions(std::string msg):msg_(msg){};
  
  Exceptions::Exceptions(std::string msg, std::string filename):msg_(msg), filename_(filename){}
}
