//
//  Profile.cpp
//  ARAIG
//
//  Created by Alex Wang on 2016-12-06.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include "Profile.h"
#include "ARAIG_sensors.h"
#include "Stimulation.h"
namespace ARAIG{
  
  Profile::Profile (const char* filename, std::ofstream& os, ARAIG_sensors& as){
    
    std::ifstream f (filename);
    try{
      if (!filename){
        throw Exceptions ("Error: Invalid Profile configuration filename. Check your parameters.\n", 2);
      }else if (!f){
        throw Exceptions ("Error: Cannot open ", filename, 3);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() <<'\n';
      std::cerr.flush();
      exit(e.code_);
    }
    
    //variables
    int index = 0;
    long max_index = as.getTaskSize();
    std::vector<std::string>result, errors;
    
    //Get student data
    skip_blank_lines(f, result);
    
    try {
      if (result.size() != 3){
        throw Exceptions ("Error: File data corruption. Incorrect instructor or student data format.", 4);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() << '\n';
      std::cerr.flush();
      exit(e.code_);
    }
    studentFName_ = result[0];
    studentLName_ = result[1];
    studentNum_ = result[2];
    //TODO: Write student data to file
    
    //Get instructor data
    ARAIG::skip_blank_lines(f, result);
    try{
      if (result.size() != 3){
        throw Exceptions ("Error: File data corruption. Incorrect instructor or student data format.", 4);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() << '\n';
      std::cerr.flush();
      exit(e.code_);
    }
    
    instructorFname_ = result[0];
    instructorLName_ = result[1];
    instructorNum_ = result[2];
    //TODO: Write instructor data to file
    
    //Get Calibration data
    ARAIG::skip_blank_lines(f, result);
    try{
      if (result.size() != 2){
        throw Exceptions("Error: File data corruption. Missing Student calibration data.", 4);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() << '\n';
      std::cerr.flush();
      exit(e.code_);
    }
    
    calMax_ = std::stoi(result[0]);
    calMin_ = std::stoi(result[1]);
    //TODO:Write calibration data to file
    
    while (!f.fail()){
      ARAIG::skip_blank_lines(f, result);
      
      if (result[0] != " "){
        //I've read in a proper task
        index = std::stoi(result[0].substr(4));
        if (index < 0){
          errors.push_back(std::string("Error: Task" + std::to_string(index) + " does not conform to Task name format. Task name format: Task# (where # > 0)."));
        }else if (index > max_index){
          errors.push_back (std::string("Error: Task requested does not exist. Skipping Task" + std::to_string(index) + "."));
        }else{
          ToRun_.push_back(new Task (as.getTask(index + 1)));
        }
      }
    }
    
    if (errors.size() > 0){
      for_each(errors.begin(), errors.end(), [](std::string msg) {
        std::cerr << msg << '\n';
      });
      errors.clear();
    }
  }
  
  void Profile::run(){
    //Execute the next task in ToRun container
    if (ToRun_.size() > 0){
      ToRun_[0]->execute(std::cout);
      Completed_.push_back(std::move(ToRun_[0]));
      ToRun_.erase(ToRun_.begin());
    }else{
      std::cout << "There are no more tasks to run.\n";
    }
  }
  
  std::ostream& Profile::display_todo_tasks(std::ostream& os)const{
    //Display all tasks in ToRun container
    if(ToRun_.size() > 0){
      std::cout << "Tasks To run\n";
      print_dash();
      for_each(ToRun_.begin(), ToRun_.end(), [&](Task* e){
        if (e != nullptr){
          os << e->getName() <<'\n';
        }
      });
    }else{
      std::cerr << "There are no tasks to be performed in the task list.\n";
      std::cerr.flush();
    }
    return os;
  }
  
  std::ostream& Profile::display_completed_tasks(std::ostream& os) const{
    //Display all completed tasks on screen
    if (Completed_.size()>0){
      for_each(Completed_.begin(), Completed_.end(), [&](Task* e) {
        if (e != nullptr){
          os << e->getName() << '\n';
        }
      });
    }else{
      std::cerr << "There are no completed tasks. No tasks has been executed.\n";
      std::cerr.flush();
    }
    return os;
  }
  
  std::ostream& Profile::display_next_task(std::ostream& os) const{
    //Display next task to the screen
    if (ToRun_.size() > 0){
      os << ToRun_[0]->getName() <<'\n';
    }else{
      os << "There is no task to be executed next.\n";
    }
    return os;
  }
  
  std::ostream& Profile::display_last_task(std::ostream& os)const{
    //Display last completed task to screen
    if (Completed_.size() > 0){
      os << Completed_[Completed_.size() - 1]->getName() << '\n';
    }else{
      os << "No Task has been completed yet.\n";
    }
    return os;
  }
}
