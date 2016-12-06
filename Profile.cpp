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
namespace ARAIG{
  
  Profile::Profile (std::string filename, std::ostream& os, ARAIG_sensors& as){
    //Constructor
    
    /*TODO:
     1) Open file
     2) Check for errors and throw exception
     3) Begin reading
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
