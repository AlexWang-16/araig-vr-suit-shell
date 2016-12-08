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
  
  Exceptions::Exceptions(std::string msg, int code):msg_(msg), code_(code){};
  
  Exceptions::Exceptions(std::string msg, const char* filename, int code):msg_(msg), code_(code){
    if (filename){
      filename_ = filename;
    }
  }
}
