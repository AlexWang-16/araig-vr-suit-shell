//
//  Global.cpp - Global functions, constants and variables
//  ARAIG
//
//  Created by Alex Wang on 2016-12-09.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include "Global.h"
namespace ARAIG {
  std::vector<std::string> split(std::string str, char delim){
    std::vector<std::string> temp;
    std::string value;
    size_t comma = 0;
    //Stripping the entire string of white spaces and \r
    str.erase(std::remove_if(str.begin(), str.end(), [](char i){
      switch(i){
        case ' ':
          return true;
          break;
        case '\r':
          return true;
          break;
        case '\n':
          return true;
        default:
          return false;
      }
    }), str.end());
    
    if (str.length() == 0){
      //Let the vector return 1 element of an empty string with 1 space to signal an empty space. ARAIG_sensors constructor will note that it is not a Stimulation or task and skip it.
      str =" ";
      temp.push_back(str);
    }
    
    while (str.length() > 0){
      //There's some data
      comma = str.find(delim);
      if (comma < std::string::npos){
        //I've found a comma
        value = str.substr(0, comma);
        temp.push_back(value);
        str = str.substr(comma + 1);
      }else{
        //I'm at the last item
        temp.push_back(str);
        str.clear();
      }
    }
    value.clear();
    return temp;
  }
  
  void skip_blank_lines(std::ifstream& file, std::vector<std::string>& result){
    do {
      //Skip all the blank lines until there's some data
      std::string data;
      std::getline(file, data);
      result.clear();
      result = split(data, ',');
    }while (!file.fail() && result[0] == " ");
  }
  
  void print_dash(int numOfDashes) {
    //Creates underline for titles
    std::cout.width(numOfDashes);
    std::cout.fill('-');
    std::cout << '-' << '\n';
    std::cout.fill (' ');
  }
  
   void new_line(int numOfNewLines){
    //Prints i number of newline characters
    for (int i = 0; i < numOfNewLines; i++){
      std::cout << '\n';
    }
  }
}
