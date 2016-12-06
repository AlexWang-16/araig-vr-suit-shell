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
            break;
        default:
          return false;
          break;
      }
    }), str.end());
    
    if (str.length() == 0){
      //Let the vector return 1 element of an empty string with 1 space to signal an empty space. ARAIG_sensors constructor will handle note that it is not a Stimulation or task and skip it.
      str =" ";
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
  
  void ARAIG_sensors::stims_data_positions(std::string input, int num_pos, std::vector<size_t>& list){
    //Takes in number of positions and stores positions for 2nd parameter onwards
    for (int i = 1; i < num_pos - 1; i++){
      list.push_back(input.find(',', list[i-1] + 1));
    }
  }

  ARAIG_sensors::ARAIG_sensors(std::string stims_filename, std::string tasks_filename){
    
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
    
    std::string data, type, name, location, header, err_msg;
    int intensity, frequency, duration, index = 0;
    std::vector<std::string> result, errors;
    Task temp_task;
  
    while (!f.fail()){
      //Reading stimulation configuration
      getline(f, data);
      result = split(data, ',');
      type = result[0];
      if (type == "stim") {
        name = result[1];
        location = result[2];
        intensity = stoi(result[3]);
        frequency = stoi(result[4]);
        duration = stoi(result[5]);
        stim_list_.push_back(new Stims(name, location, intensity, frequency, duration));
        
      } else if (type == "exoskeleton") {
        name = result[1];
        intensity = stoi(result[2]);
        duration = stoi(result[3]);
        stim_list_.push_back(new Exoskeleton(name, intensity, duration));
      }
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
    
    result.clear();
    //Reading Task Configurations
    while (!f.fail()){
      
      getline(f, data);
      result = split(data, ',');
      header = result[0].substr(0,3);
      
      if (header == "TAS"){
        //Detects an incomming TASK
        
        if (temp_task.getSize() > 0){
          //A task has completed, push it into the list!
          task_list_.push_back(temp_task);
        }
        
        //Start a fresh task and give it a name
        temp_task.clear();
        temp_task.setName(result[1]);
        
      } else if (header == "Sim") {
        
        //Detect Stimulation number and grab it from the vector
        index = stoi(result[0].substr(3));
        
        if (index < 1 ){
          //Check for out of lower bound index
          err_msg = "Error: Cannot add Sim" + std::to_string(index);
          err_msg += ". Sim name format: Sim# (where # > 0).\n";
          errors.push_back(err_msg);
          err_msg.clear();
        }
        else if (index > stim_list_.size()){
          //Check for out of upper bound index
          err_msg = "Error: Cannot add Sim" + std::to_string(index);
          err_msg += " to " + temp_task.getName();
          err_msg += ". Stimulation not found.\n";
          errors.push_back(err_msg);
          err_msg.clear();
        } else if (stim_list_[index-1]->getName() == result[0]){
          //Final comparison check
          temp_task += stim_list_[index-1];
        }
      }
    }
    //Final push and house cleaning
    task_list_.push_back(temp_task);
    temp_task.clear();
    dump(std::cout);
    
    if (errors.size()){
      //If errors existed while adding stimulations, print them out
      std::for_each(errors.begin(), errors.end(), [&errors](std::string msg){
        std::cerr << msg;
      });
      errors.clear();
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
