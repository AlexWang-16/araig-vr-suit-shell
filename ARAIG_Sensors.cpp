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

#include "ARAIG_Sensors.h"
#include "Exoskeleton.h"
#include "Stims.h"
#include "Task.h"
#include "Stimulation.h"

namespace ARAIG {

  ARAIG_sensors::ARAIG_sensors(const char* stims_filename, const char* tasks_filename){
    
    std::ifstream f (stims_filename);
    try {
      if (!stims_filename){
        throw Exceptions("Error: Invalid stimulation configuration filename. Check your parameters.\n", 2);
      }else if (!tasks_filename){
        throw Exceptions("Error: Invalid Task configuration filename. Check your parameters.", 2);
      }else if(!f){
        throw Exceptions ("Error: Cannot open ", stims_filename, 3);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() <<'\n';
      new_line(user_interface_system_message_skip_line / 2);
      std::cerr.flush();
      exit(e.code_);
    }
    
    //Variables
    std::string data, type, name, location, header, key, err_msg;
    int intensity, frequency, duration;
    std::vector<std::string> result, errors;
    std::shared_ptr<Stimulation> stim;
    std::shared_ptr<Task> temp_task;
  
    while (!f.fail()){
      //Reading stimulation configuration
      skip_blank_lines(f, result);
      type = result[0];
      if (type == "stim") {
        name = result[1];
        location = result[2];
        intensity = stoi(result[3]);
        frequency = stoi(result[4]);
        duration = stoi(result[5]);
        //Stim shared pointer
        stim.reset();
        stim = std::make_shared<Stims>(name, location, intensity, frequency, duration);
        stim_list_.insert(std::pair<std::string, std::shared_ptr<Stimulation>>(name, stim));
        //stim_list_[name] = new Stims(name, location, intensity, frequency, duration);
        
      } else if (type == "exoskeleton") {
        name = result[1];
        intensity = stoi(result[2]);
        duration = stoi(result[3]);
        stim.reset();
        stim = std::make_shared<Exoskeleton>(name, intensity, duration);
        stim_list_.insert(std::pair<std::string, std::shared_ptr<Stimulation>>(name, stim));
        //stim_list_[name] = new Exoskeleton(name, intensity, duration);
      }
    }
    f.close();
    
    f.open (tasks_filename);
    try {
      if(!f.is_open()){
        throw Exceptions ("Error: Cannot open ", tasks_filename, 3);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() <<'\n';
      std::cerr.flush();
      new_line(user_interface_system_message_skip_line / 2);
      exit(e.code_);
    }
    
    result.clear();
    //Reading Task Configurations
    while (!f.fail()){
      
      skip_blank_lines(f, result);
      header = result[0].substr(0,3);
      
      if (header == "TAS"){
        //Detects an incomming TASK
        
        if (temp_task && temp_task->getSize() > 0){
          //A task has completed, push it into the list!
          task_list_[temp_task->getName()] = std::move(temp_task);
          temp_task = nullptr;
        }
        
        //Start a fresh task and give it a name
        temp_task.reset(new Task);
        temp_task->setName(result[1]);
        
      } else {
        //Detect Stimulation name and grab it from the map
        key = result[0];
        
        if (key != " "){
          if (temp_task){
            if (stim_list_.find(key) != stim_list_.end()){
              *temp_task += stim_list_[key];
            }else{
              errors.push_back (std::string("Error: Stimulation: " + key + " not found.\n"));
            }
          }else{
              errors.push_back (std::string("Error: No task instantiated to accept the Stimulation.\n"));
          }
        }
      }
    }
  //Final push and house cleaning
    if (temp_task){task_list_.insert (std::pair <std::string, std::shared_ptr<Task>> (temp_task->getName(), std::move(temp_task)));}
  
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
  
  long ARAIG_sensors::getTaskSize(){
    return task_list_.size();
  }
  
  Task& ARAIG_sensors::getTask(std::string key){
    
    std::map<std::string, std::shared_ptr<Task>>::iterator it = task_list_.find(key);
    if (taskExists(key)){
      return *it->second;
    }
    return dummy;
  }
  
  bool ARAIG_sensors::taskExists(std::string key){
    //return true if tasks exists
    std::map<std::string, std::shared_ptr<Task>>::iterator i = task_list_.find(key);
    return (i != task_list_.end());
  }
  
  std::ostream& ARAIG_sensors::dump (std::ostream& os) {
    //Iterate through the entire list and run dump and execute()

    std::for_each(task_list_.begin(), task_list_.end(), [&](std::pair<const std::string, std::shared_ptr<Task>> i){
      if (i.second){
        i.second -> dump(os);
        os << '\n';
        i.second ->execute(os);
          os << '\n';
      }
    });
    return os;
  }
}
