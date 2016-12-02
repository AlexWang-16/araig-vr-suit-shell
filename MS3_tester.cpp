//
//  MS3_tester.cpp
//
//  ARAIG - As Real As It Gets Augmented reality game suit final project
//  For BTP305 C++ course at Seneca
//
//  Created by Alex Wang on 2016-11-14.
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include "Stims.h"
#include "Exoskeleton.h"
#include "Task.h"
using namespace ARAIG;
extern const int max_duration, max_intensity;

const void print_dash(int x = 30) {
  //Creates underline for titles
  std::cout.width(x);
  std::cout.fill('-');
  std::cout << '-' << '\n';
  std::cout.fill (' ');
}

const void new_line(int x = 1) {
  //Prints i number of newline characters
  for (int i = 0; i < x; i++){
    std::cout << '\n';
  }
}

void data_parameter_positions(std::string input, int num_pos, std::vector<size_t>& list){
  //Takes in number of positions and stores positions for 2nd parameter onwards
  for (int i = 1; i < num_pos - 1; i++){
    list.push_back(input.find(',', list[i-1] + 1));
  }
}

int main(int argc, const char * argv[]) {

  
  //Test: Creating a stim_list vector that holds a list of stimulations read from a file
  //Expected: A vector called stim_list should be created with 32 stimulations inside
  
  std::ifstream file ("StimulationConfig.csv");
  try {
    if(!file){
      throw Exceptions ("Error: Cannot open file");
    }
  }catch (Exceptions& e){
    std::cerr << e.what() <<'\n';
    std::cerr.flush();
    exit(2);
  }
  
  std::list<Stimulation*> stim_list;
  std::vector<size_t> comma;
  while (!file.fail()){
  
    std::string data, type, name, location;
    int intensity, frequency, duration;
    
    getline(file, data);
    
    if (data.find('\r')){
      //Detects \n characters and trim it
      data = data.substr(0,data.length()-1);
    }
    
    comma.push_back (data.find(','));
    type = data.substr(0, comma[0]);
    if (type == "stim") {
      data_parameter_positions(data, 6, comma);
      name = data.substr(comma[0]+1, comma[1] - comma[0]-1);
      location = data.substr(comma[1]+1, comma[2] - comma[1]-1);
      intensity = stoi(data.substr(comma[2]+1, comma[3]-comma[2]-1));
      frequency = stoi(data.substr(comma[3]+1, comma[4]-comma[3]-1));
      duration = stoi(data.substr(comma[4]+1));
      stim_list.push_back(new Stims(name, location, intensity, frequency, duration));
      
    } else if (type == "exoskeleton") {
      data_parameter_positions(data, 4, comma);
      name = data.substr(comma[0]+1, comma[1] - comma[0]-1);
      intensity = stoi(data.substr(comma[1]+1, comma[2]-comma[1]-1));
      
      duration = stoi(data.substr(comma[2]+1));
      
      stim_list.push_back(new Exoskeleton(name, intensity, duration));
    }
    comma.clear();
  }

  
}
