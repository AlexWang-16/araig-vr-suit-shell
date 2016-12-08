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
      std::cerr.flush();
      exit(e.code_);
    }
    
    //Variables
    std::string data, type, name, location, header, err_msg;
    int intensity, frequency, duration, index = 0;
    std::vector<std::string> result, errors;
    Task* temp_task = nullptr;
  
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
        throw Exceptions ("Error: Cannot open ", tasks_filename, 3);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() <<'\n';
      std::cerr.flush();
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
          task_list_.push_back(std::move(temp_task));
          temp_task = nullptr;
        }
        
        //Start a fresh task and give it a name
        temp_task = new Task;
        temp_task->setName(result[1]);
        
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
          err_msg += " to " + temp_task->getName();
          err_msg += ". Stimulation not found.\n";
          errors.push_back(err_msg);
          err_msg.clear();
        } else if (stim_list_[index-1]->getName() == result[0]){
          //Final comparison check
          if (temp_task){
            *temp_task += stim_list_[index-1];
          }else{
            errors.push_back (std::string("Error: No task instantiated to accept the Stimulation. Skipping Sim" + std::to_string(index) + ".\n"));
          }
      }
    }
  }
  //Final push and house cleaning
  task_list_.push_back(temp_task);
  temp_task = nullptr;
  
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
  
  Task& ARAIG_sensors::getTask(int index){
    if (index < task_list_.size()){
      std::list<Task*>::iterator it = task_list_.begin();
      std::advance(it, index);
      return *(*it);
    } else {
      return dummy;
    }
  }
  
  std::ostream& ARAIG_sensors::dump (std::ostream& os) {
    //Iterate through the entire list and run dump and execute()

    std::for_each(task_list_.begin(), task_list_.end(), [&](Task* i){
      if (i){
        i->dump(std::cout);
        std::cout << '\n';
        i->execute(std::cout);
          std::cout << '\n';
      }
    });
    return os;
  }
}
