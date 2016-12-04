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
#include "Task.h"

namespace ARAIG {
  void ARAIG_sensors::stims_data_positions(std::string input, int num_pos, std::vector<size_t>& list){
    //Takes in number of positions and stores positions for 2nd parameter onwards
    for (int i = 1; i < num_pos - 1; i++){
      list.push_back(input.find(',', list[i-1] + 1));
    }
  }

  ARAIG_sensors::ARAIG_sensors(std::string stims_filename, std::string tasks_filename){
    
    std::vector<std::string>errors;
    std::vector<size_t> comma;
    std::ifstream f (stims_filename);
    try {
      if(!f){
        throw Exceptions ("Error: Cannot open ", stims_filename);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() <<'\n';
      std::cerr.flush();
      exit(2);
    }
    
    std::string data, type, name, location;
    int intensity, frequency, duration;
    
    while (!f.fail()){
      
      getline(f, data);
      
      data.erase(std::remove_if(data.begin(), data.end(), [](char i){
        switch (i){
          case ' ':
            return true;
            break;
          case '\r':
            return true;
            break;
          default:
            return false;
        }
      }), data.end());
      
      comma.push_back (data.find(','));
      type = data.substr(0, comma[0]);
      if (type == "stim") {
        stims_data_positions(data, 6, comma);
        name = data.substr(comma[0]+1, comma[1] - comma[0]-1);
        location = data.substr(comma[1]+1, comma[2] - comma[1]-1);
        intensity = stoi(data.substr(comma[2]+1, comma[3]-comma[2]-1));
        frequency = stoi(data.substr(comma[3]+1, comma[4]-comma[3]-1));
        duration = stoi(data.substr(comma[4]+1));
        stim_list_.push_back(new Stims(name, location, intensity, frequency, duration));
        
      } else if (type == "exoskeleton") {
        stims_data_positions(data, 4, comma);
        name = data.substr(comma[0]+1, comma[1] - comma[0]-1);
        intensity = stoi(data.substr(comma[1]+1, comma[2]-comma[1]-1));
        
        duration = stoi(data.substr(comma[2]+1));
        
        stim_list_.push_back(new Exoskeleton(name, intensity, duration));
      }
      comma.clear();
    }
    f.close();
    f.open (tasks_filename);
    try {
      if(!f.is_open()){
        throw Exceptions ("Error: Cannot open ", tasks_filename);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() <<'\n';
      std::cerr.flush();
      exit(2);
    }
    
    std::string header;
    Task temp;
    int index = 0;
    //Reading Task Configurations
    while (!f.fail()){
      
      getline(f, data);
      header = data.substr(0,3);
      
      if (header == "TAS"){
        //Detects an incomming TASK
        
        //Strip spaces and \r from the incomming data to create uniform formatted data for processing.
        data.erase(std::remove_if(data.begin(), data.end(), [](char i){
          switch (i){
              case ' ':
                return true;
                break;
              case '\r':
                return true;
                break;
            default:
              return false;
          }
        }), data.end());
        
        if (temp.getSize() > 0){
          //A task has completed, push it into the list!
          task_list_.push_back(std::move(temp));
        }
        
        //Start a fresh task and give it a name
        temp.clear();
        temp.setName(data.substr(5, data.length()-5));
        
      } else if (header == "Sim") {
        //Found a Stimulation! Strip spaces and /r to create uniform formatted data for processing
        data.erase(std::remove_if(data.begin(), data.end(), [](char i){
          switch (i){
            case ' ':
              return true;
              break;
            case '\r':
              return true;
              break;
            default:
              return false;
          }
        }));
        
        //Detect Stimulation number and grab it from the vector
        index = stoi(data.substr(3));
        if (index > stim_list_.size()){
          std::string err = "Error: Cannot add Sim" + std::to_string(index) + " to " + temp.getName();
          err += ". Stimulation is not found in Stim list! Skipping Sim" + std::to_string(index) + ".\n";
          errors.push_back(err);
        } else {
          temp += stim_list_[index-1];
        }
      }
    }
    //Final push and house cleaning
    task_list_.push_back(temp);
    temp.clear();
    dump(std::cout);
    
    if (errors.size()){
      //If errors existed while adding stimulations, print them out
      std::for_each(errors.begin(), errors.end(), [&errors](std::string msg){
        std::cerr << msg;
        errors.pop_back();
      });
    }
  }
  
  ARAIG_sensors::~ARAIG_sensors(){
    stim_list_.clear();
    task_list_.clear();
  }
  
  std::ostream& ARAIG_sensors::dump (std::ostream& os) {
    //Iterate through the entire list and run dump and execute()
    
    std::for_each(task_list_.begin(), task_list_.end(), [&](Task i){
      i.dump(std::cout);
      std::cout << '\n';
      i.execute(std::cout);
      std::cout << '\n';});
    return os;
  }
}
