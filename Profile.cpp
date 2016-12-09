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
  
  Profile::Profile (const char* filename, std::ofstream& os, ARAIG_sensors& as): of_(os){
    
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
    
    //Writing student data to file
    of_ << "Student: " << studentFName_ << ' ';
    of_ << studentLName_ << "  - " << studentNum_ <<'\n';
    
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
    
    //Writing instructor data to file
    of_ << "Instructor: " << instructorFname_;
    of_ << ' ' << instructorLName_ << " - ";
    of_ << instructorNum_ << '\n';
    
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
    
    //Writing calibration data to file
    of_ << "Student Calibration:\n";
    of_ << "MAX = " << calMax_ << '\n';
    of_ << "MIN = " << calMin_ << '\n';
    
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
    
    f.close();
    if (errors.size() > 0){
      for_each(errors.begin(), errors.end(), [](std::string msg) {
        std::cerr << msg << '\n';
      });
      errors.clear();
    }
  }
  
  Profile::~Profile(){
    //TODO: Restructor this when instructor and student struct have been created. They will have their own destructors written to streamline this process
    ToRun_.clear();
    Completed_.clear();
    calMax_ = 0;
    calMin_ = 0;
    studentFName_.clear();
    studentLName_.clear();
    studentNum_.clear();
    instructorFname_.clear();
    instructorLName_.clear();
    instructorNum_.clear();
    menu_.clear();
    of_.close();
  }
  
  void Profile::run(){
    //Execute the next task in ToRun container
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    std::cout << "ARAIG Control Flight Simulator v" << version << "\n\n";
    std::cout.unsetf(std::ios::fixed);
    std::cout << "Status: Flight plan data successfully loaded.\n\n";
    
    load_menu();
    
    long user_input = -1;
    do {
      user_input = getInput("Please enter menu item number: ", 1, menu_.size(), menu_.size(), true);
      switch (user_input){
        case 1:
          //Execute tasks
        {
          if (ToRun_.size() > 0){
            std::cout << "\nYou currently have " << ToRun_.size() << " tasks to execute.\n";
            long numOfTasks = getInput("Please enter number of tasks to execute: ", 0, ToRun_.size());
            execute(numOfTasks);
            if (numOfTasks == 1){
              std::cout << '\n' << numOfTasks << " task executed.\n\n";
            }else if (numOfTasks > 1){
              std::cout << '\n' << numOfTasks << " tasks were executed.\n\n";
            }
          }else{
            std::cout << "\nThere are no more tasks to run.\n\n";
          }
        }
          break;
        case 2:
          //Display next task
          display_next_task(std::cout) << '\n';
          break;
        case 3:
          //Display All todo tasks
          display_todo_tasks(std::cout) << '\n';
          break;
        case 4:
          //Display last task completed
          display_last_task(std::cout) <<
          '\n';
          break;
        case 5:
          //Display All tasks completed
          display_completed_tasks(std::cout) << '\n';
          break;
        case 6:
          //Exit Program
          std::cout.setf(std::ios::fixed);
          std::cout.precision(2);
          std::cout << "\nThanks for using ARAIG Control Flight Simulator v" << version;
          std::cout << ". Goodbye!\n\n";
          std::cout.setf(std::ios::fixed);
          break;
        default:
          std::cout << "\nInput out of range.\n\n";
      }
    }while (user_input != menu_.size());
  }
  
  void Profile::execute(long tasks) {
    if (tasks > 0 && tasks <= ToRun_.size()) {
      for (int i = 0; i < tasks; i++){
        of_ << ToRun_[0]->getName() << '\n';
        ToRun_[0]->execute(of_);
        of_ << '\n';
          Completed_.push_back(std::move(ToRun_[0]));
          ToRun_.erase(ToRun_.begin());
      }
    }else if (tasks == 0){
      std::cout << "\nTask execution cancelled.\n\n";
    }
  }
  
  void Profile::load_menu(){
    //Build the menu. Please keep Exit the last option.
    menu_.push_back ("1 - Execute flight plan\n");
    menu_.push_back("2 - Display next task to be completed\n");
    menu_.push_back("3 - Display all tasks to be completed\n");
    menu_.push_back("4 - Display last completed task\n");
    menu_.push_back("5 - Display all completed tasks\n");
    menu_.push_back("6 - Exit\n");
  }
  
  long Profile::show_menu()const{
    //Display menu and return number of items available for selection (excluding "exit" option)
    long options = 3;
    std::cout << "Menu\n";
    print_dash(4);
    if (Completed_.size() < 1){
      for (int i = 0; i < options; i++){std::cout << menu_[i];}
      std::cout << menu_[menu_.size()-1];
    }else{
      options = menu_.size();
      for (std::string item : menu_){std::cout << item;}
    }
    return options;
  }
  
  long Profile::getInput(std::string prompt, int min, long max, long exitCode, bool menuPrompt){
    //Return sanitized user input for menu
    
    long user_input = 0;
    bool bad = true;
    std::string err = "\nError: Invalid input. Please check input and try again.\n\n";
    
    do {
      if (menuPrompt){ max = show_menu(); }
      std::cout << prompt;
      std::cin >> user_input;

      if (std::cin.fail()){
        std::cerr << err;
        std::cin.clear();
      }else if (user_input == exitCode){
        bad = false;
      }else if (user_input < min || user_input > max){
        std::cerr << err;
      }else{
        bad = false;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while(bad);
    return user_input;
  }
  
  std::ostream& Profile::display_todo_tasks(std::ostream& os)const{
    //Display all tasks in ToRun container
    if(ToRun_.size() > 0){
      std::cout << "\nTasks to be completed\n";
      print_dash(21);
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
      std::cout << "\nCompleted Tasks\n";
      print_dash(15);
      
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
      os << "\nThe next task is ";
      os << ToRun_[0]->getName() << ".\n";
    }else{
      os << "There is no task to be executed next.\n";
    }
    return os;
  }
  
  std::ostream& Profile::display_last_task(std::ostream& os)const{
    //Display last completed task to screen
    if (Completed_.size() > 0){
      os << "\nThe last task completed was ";
      os << Completed_[Completed_.size() - 1]->getName() <<
      ".\n";
    }else{
      os << "No Task has been completed yet.\n";
    }
    return os;
  }
}
