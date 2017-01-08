//
//  Global.h
//  ARAIG
//
//  This file holds Configs, Constants, Global var and functions
//
//  Created by Alex Wang on 2016-12-09.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#ifndef Global_H
#define Global_H
#include <iostream>
#include <limits>
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <iterator>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>

namespace ARAIG {
//Version tracking (Profile.cpp)
const float version = 0.97;

//Stimulation Configurations (Stimulations.h)
const int duration_max = 300;
const int intensity_max = 100, frequency_max = 10000;
//User interface configurations (Profile.cpp)
const int user_interface_skip_screen = 40;
const int user_interface_system_message_skip_line = 4;

//Global Functions
std::vector<std::string> split(std::string str, char delim = ' ');
void skip_blank_lines(std::ifstream& file, std::vector<std::string>& result);
void print_dash(int numOfDashes = 30);
void new_line (int numOfNewLines = 1);
}
#endif /* Global_H */
