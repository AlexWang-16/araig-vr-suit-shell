//
//  Exceptions.h
//  ARAIG
//
//  Created by Alex Wang on 2016-11-24.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#ifndef Exceptions_H
#define Exceptions_H

#include <iostream>
#include <exception>
namespace ARAIG{

  struct Exceptions: public std::exception {
    std::string msg_;
    std::string filename_;
    const char* what() const throw();
    Exceptions(std::string msg);
    Exceptions(std::string msg, std::string filename);
  };

}
#endif /* Exceptions_H */
