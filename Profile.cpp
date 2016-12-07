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
  
  Profile::Profile (std::string filename, std::ostream& os, ARAIG_sensors& as){
    //Constructor
    
    /*TODO:
     1) Open file - OK
     2) Check for errors and throw exception - OK
     3) Begin reading - WORKING ON
     4) Begin storing the data
     */
    std::ifstream f (filename);
    try{
      if (!f){
        throw Exceptions ("Error: Cannot open ", filename);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() <<'\n';
      std::cerr.flush();
      exit(2);
    }
    
    //variables
    int index = 0;
    long max_index = as.getTaskSize();
    std::vector<std::string>result, errors;
    
    //Get student data
    skip_blank_lines(f, result);
    
    try {
      if (result.size() != 3){
        throw Exceptions ("Error: File data corruption. Incorrect instructor or student data format.");
      }
    }catch (Exceptions& e){
      std::cerr << e.what() << '\n';
      std::cerr.flush();
      exit(3);
    }
    studentFName_ = result[0];
    studentLName_ = result[1];
    studentNum_ = result[2];
    
    //Get instructor data
    ARAIG::skip_blank_lines(f, result);
    try{
      if (result.size() != 3){
        throw Exceptions ("Error: File data corruption. Incorrect instructor or student data format.");
      }
    }catch (Exceptions& e){
      std::cerr << e.what() << '\n';
      std::cerr.flush();
      exit(3);
    }
    
    instructorFname_ = result[0];
    instructorLName_ = result[1];
    instructorNum_ = result[2];
    
    //Get Calibration data
    ARAIG::skip_blank_lines(f, result);
    try{
      if (result.size() != 2){
        throw Exceptions("Error: File data corruption. Missing Student calibration data.");
      }
    }catch (Exceptions& e){
      std::cerr << e.what() << '\n';
      std::cerr.flush();
      exit(3);
    }
    
    calMax_ = std::stoi(result[0]);
    calMin_ = std::stoi(result[1]);
    
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
          ToRun_.push_back(Task (as.getTask(index + 1)));
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
  }
  
  std::ostream& Profile::display_todo_task(std::ostream& os)const{
    //Display all tasks in ToRun container
    return os;
  }
  
  std::ostream& Profile::display_completed_task(std::ostream& os) const{
    //Display all completed tasks on screen
    return os;
  }
  
  std::ostream& Profile::display_next_task(std::ostream& os) const{
    //Display next task to the screen
    return os;
  }
  
  std::ostream& Profile::display_last_task(std::ostream& os)const{
    //Display last completed task to screen
    return os;
  }
}
