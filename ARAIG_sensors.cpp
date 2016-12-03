//
//  ARAIG_sensors.cpp
//  ARAIG
//
//  Created by Alex Wang on 2016-12-02.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include "ARAIG_sensors.h"
#include "Exoskeleton.h"
#include "Stims.h"
namespace ARAIG {
  void ARAIG_sensors::stims_data_positions(std::string input, int num_pos, std::vector<size_t>& list){
    //Takes in number of positions and stores positions for 2nd parameter onwards
    for (int i = 1; i < num_pos - 1; i++){
      list.push_back(input.find(',', list[i-1] + 1));
    }
  }

  ARAIG_sensors::ARAIG_sensors(std::string stims_filename, std::string tasks_filename){
    
    std::list<Stimulation*> stim_list;
    std::vector<size_t> comma;
    std::ifstream stims_file (stims_filename);
    try {
      if(!stims_file){
        throw Exceptions ("Error: Cannot open ", stims_filename);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() <<'\n';
      std::cerr.flush();
      exit(2);
    }
    while (!stims_file.fail()){
      
      std::string data, type, name, location;
      int intensity, frequency, duration;
      
      getline(stims_file, data);
      
      if (data.find('\r')){
        //Detects \n characters and trim it
        data = data.substr(0,data.length()-1);
      }
      
      comma.push_back (data.find(','));
      type = data.substr(0, comma[0]);
      if (type == "stim") {
        stims_data_positions(data, 6, comma);
        name = data.substr(comma[0]+1, comma[1] - comma[0]-1);
        location = data.substr(comma[1]+1, comma[2] - comma[1]-1);
        intensity = stoi(data.substr(comma[2]+1, comma[3]-comma[2]-1));
        frequency = stoi(data.substr(comma[3]+1, comma[4]-comma[3]-1));
        duration = stoi(data.substr(comma[4]+1));
        stim_list.push_back(new Stims(name, location, intensity, frequency, duration));
        
      } else if (type == "exoskeleton") {
        stims_data_positions(data, 4, comma);
        name = data.substr(comma[0]+1, comma[1] - comma[0]-1);
        intensity = stoi(data.substr(comma[1]+1, comma[2]-comma[1]-1));
        
        duration = stoi(data.substr(comma[2]+1));
        
        stim_list.push_back(new Exoskeleton(name, intensity, duration));
      }
      comma.clear();
    }
  }
  
  ARAIG_sensors::~ARAIG_sensors(){
    
  }
  
  std::ostream& dump (std::ostream& os) {
    return os;
  }
  
}
