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

#include "Global.h"
#include "Profile.h"
#include "ARAIG_sensors.h"
namespace ARAIG{
  Profile::Student::Student(std::string FName, std::string LName,
                            std::string studentNumber):FName_(FName),
                            LName_(LName), Num_(studentNumber){
    if(FName.length() < 1){
      throw Exceptions("Error: Student first name is empty.", 3);
    }else if (LName.length() < 1){
      throw Exceptions("Error: Student last name is empty.", 3);
    }else if (std::stoi(studentNumber) == 0){
      throw Exceptions("Error: Student number is invalid.", 3);
    }else if (std::stoi(studentNumber) < 0) {
      throw Exceptions("Error: Student number cannot be negative.", 3);
    }
  }
  
  Profile::Student::~Student(){
    FName_.clear();
    LName_.clear();
    Num_.clear();
    calMin_ = 0;
    calMax_ = 0;
  }
  
  std::string Profile::Student::getFName()const{
    return FName_;
  }
  
  std::string Profile::Student::getLName()const{
    return LName_;
  }
  
  std::string Profile::Student::getName()const{
    return (FName_ + ' ' + LName_);
  }
  
  std::string Profile::Student::getNumber()const{
    return Num_;
  }
  
  void Profile::Student::writeData(std::ofstream& of){
    of << "Student:     " << getName();
    of << " - " << getNumber() <<'\n';
  }
  
  void Profile::Student::writeCalibration(std::ofstream& of){
    of << "Student Calibration:\n";
    of << "MAX = " << calMax_ << '\n';
    of << "MIN = " << calMin_ << '\n';
  }
  
  void Profile::Student::setCalMax(std::string input){
    int intensity = std::stoi(input);
    
    if (intensity == 0){
      throw Exceptions("Error: Invalid calibration max intensity.", 3);
    }else if (intensity > 100){ calMax_ = 100; }
    else if (intensity < 0 ) { calMax_ = 0;}
    else{ calMax_ = intensity; }
  }
  
  void Profile::Student::setCalMin(std::string input){
    int intensity = std::stoi(input);
    
    if (intensity == 0){
      throw Exceptions("Error: Invalid calibration min intensity.", 3);
    }else if (intensity > 100){ calMin_ = 100; }
    else if (intensity < 0 ) { calMin_ = 0;}
    else{ calMin_ = intensity; }
  }
  
  Profile::Instructor::Instructor(std::string FName, std::string LName,
                                  std::string EmployeeNum): FName_(FName),
                                  LName_(LName), Num_(EmployeeNum){
    if(FName.length() < 1){
      throw Exceptions("Error: Instructor first name is empty.", 3);
    }else if (LName.length() < 1){
      throw Exceptions("Error: Instructor last name is empty.", 3);
    }else if (std::stoi(EmployeeNum) == 0){
      throw Exceptions("Error: Instructor number is invalid.", 3);
    }else if (std::stoi(EmployeeNum) < 0) {
      throw Exceptions("Error: Instructor number cannot be negative.", 3);
    }
  }
  
  Profile::Instructor::~Instructor(){
    FName_.clear();
    LName_.clear();
    Num_.clear();
  }
  
  std::string Profile::Instructor::getFName()const{
    return FName_;
  }
  
  std::string Profile::Instructor::getLName()const{
    return LName_;
  }
  
  std::string Profile::Instructor::getName()const{
    return (FName_ + ' ' + LName_);
  }
  
  std::string Profile::Instructor::getNumber()const{
    return Num_;
  }
  
  void Profile::Instructor::writeToFile(std::ofstream& of){
    of << "Instructor:  " << getName();
    of << " - " << getNumber() <<'\n';
  }
  
  Profile::Profile (const char* filename, std::ofstream& os, ARAIG_sensors& as):
  of_(os){
    
    std::ifstream f (filename);
    try{
      if (!filename){
        throw Exceptions ("Error: Invalid Profile configuration filename. Check your parameters.\n", 2);
      }else if (!f){
        throw Exceptions ("Error: Cannot open ", filename, 3);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() <<'\n';
      new_line(user_interface_system_message_skip_line / 2);
      std::cerr.flush();
      exit(e.code_);
    }
    
    //variables
    std::string key;
    std::vector<std::string>result, errors;
    Student* tempStudent;
    Instructor* tempInstructor;
    //Get student data
    skip_blank_lines(f, result);
    
    try {
      if (result.size() != 3){
        throw Exceptions ("Error: File data corruption. Incorrect instructor or student data format.", 4);
      }
      tempStudent = new Student (result[0], result[1], result[2]);
    }catch (Exceptions& e){
      std::cerr << e.what() << '\n';
      new_line(user_interface_system_message_skip_line / 2);
      std::cerr.flush();
      exit(e.code_);
    }
    
    //Writing student data to file
    tempStudent->writeData(of_);
    
    //Get instructor data
    ARAIG::skip_blank_lines(f, result);
    try{
      if (result.size() != 3){
        throw Exceptions ("Error: File data corruption. Incorrect instructor or student data format.", 4);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() << '\n';
      std::cerr.flush();
      new_line(user_interface_system_message_skip_line / 2);
      exit(e.code_);
    }
    
    try{
      tempInstructor = new Instructor (result[0], result[1], result[2]);
    }catch (Exceptions& e){
      std::cerr << e.what();
      new_line(user_interface_system_message_skip_line / 2);
      std::cerr.flush();
      exit(e.code_);
    }
    
    //Writing instructor data to file
    tempInstructor->writeToFile(of_);
    
    //Get Calibration data
    ARAIG::skip_blank_lines(f, result);
    try{
      if (result.size() != 2){
        throw Exceptions("Error: File data corruption. Missing Student calibration data.", 4);
      }
    }catch (Exceptions& e){
      std::cerr << e.what() << '\n';
      new_line(user_interface_system_message_skip_line / 2);
      std::cerr.flush();
      exit(e.code_);
    }
    
    try{
      tempStudent->setCalMax(result[0]);
      tempStudent->setCalMin(result[1]);
    }catch (Exceptions& e){
      std::cerr << e.what();
      new_line(user_interface_skip_screen);
      std::cerr.flush();
      exit(e.code_);
    }
    
    //Writing calibration data to file
    tempStudent->writeCalibration(of_);
    
    while (!f.fail()){
      ARAIG::skip_blank_lines(f, result);
      
      if (result[0] != " "){
        //I've read in a proper task
        key = result[0];
        if (as.taskExists(key)){
          ToRun_.push_back(new Task (as.getTask(key)));
        }
      }
    }
    
    delete tempStudent;
    tempStudent = nullptr;
    delete tempInstructor;
    tempInstructor = nullptr;
    
    f.close();
    if (errors.size() > 0){
      for_each(errors.begin(), errors.end(), [](std::string msg) {
        std::cerr << msg << '\n';
      });
      errors.clear();
    }
    
  }
  
  Profile::~Profile(){
    ToRun_.clear();
    Completed_.clear();
    menu_.clear();
    of_.close();
  }
  
  void Profile::run(){
    //Execute the next task in ToRun container
    new_line(user_interface_skip_screen);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    std::cout << "ARAIG Control Flight Simulator v" << version << "\n\n";
    std::cout.unsetf(std::ios::fixed);
    std::cout << "Flight plan data successfully loaded.\n\n";
    
    load_menu();
    
    unsigned long user_input = 0;
    do {
      user_input = getInput("Please enter menu item number: ", 1, menu_.size(), true);
      switch (user_input){
        case 1:
          //Execute tasks
        {
          if (ToRun_.size() > 0){
            new_line(user_interface_skip_screen);
            std::cout << "\nYou currently have " << ToRun_.size() << " tasks to execute.\n";
            long numOfTasks = getInput("Please enter number of tasks to execute: ", 0, ToRun_.size());
            execute(numOfTasks);
            if (numOfTasks == 1){
              new_line(user_interface_skip_screen);
              std::cout << '\n' << numOfTasks << " task executed. Executed task was logged in output file.";
              new_line(user_interface_system_message_skip_line);
            }else if (numOfTasks > 1){
              new_line(40);
              std::cout << '\n' << numOfTasks << " tasks were executed. Executed tasks were logged in output file.";
              new_line(user_interface_system_message_skip_line);
            }
          }else{
            new_line(40);
            std::cout << "\nThere are no more tasks to run.";
            new_line(user_interface_system_message_skip_line);
          }
        }
          break;
        case 2:
          //Display next task
          new_line(user_interface_skip_screen);
          display_next_task(std::cout);
          break;
        case 3:
          //Display All todo tasks
          new_line(user_interface_skip_screen);
          display_todo_tasks(std::cout);
          break;
        case 4:
          //Display last task completed
          new_line(user_interface_skip_screen);
          display_last_task(std::cout);
          break;
        case 5:
          //Display All tasks completed
          new_line(user_interface_skip_screen);
          display_completed_tasks(std::cout);
          break;
        case 6:
          //Exit Program
          new_line(40);
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
  
  void Profile::execute(unsigned long tasks) {
    if (tasks > 0 && tasks <= ToRun_.size()) {
      for (unsigned long i = 0; i < tasks; i++){
        of_ << ToRun_[0]->getName() << '\n';
        ToRun_[0]->execute(of_);
        of_ << '\n';
          Completed_.push_back(new Task(std::move(*ToRun_[0])));
          ToRun_.erase(ToRun_.begin());
      }
    }else if (tasks == 0){
      new_line(user_interface_skip_screen);
      std::cout << "Task execution cancelled.";
      new_line(user_interface_system_message_skip_line);
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
    print_dash(user_interface_system_message_skip_line);
    if (Completed_.size() < 1){
      for (int i = 0; i < options; i++){std::cout << menu_[i];}
      std::cout << menu_[menu_.size()-1];
    }else{
      options = menu_.size();
      for (std::string item : menu_){std::cout << item;}
    }
    return options;
  }
  
  long Profile::getInput(std::string prompt, int min, long max, bool menuPrompt){
    //Return sanitized user input for menu
    
    unsigned long user_input = 0, exitCode = 0;
    bool bad = true;
    std::string err = "Error: Invalid input. Please check input and try again.";
    
    do {
      if (menuPrompt){
        max = show_menu();
        exitCode = menu_.size();
      }
      std::cout << prompt;
      std::cin >> user_input;

      if (std::cin.fail()){
        new_line(user_interface_skip_screen);
        std::cerr << err;
        new_line(user_interface_system_message_skip_line);
        std::cin.clear();
      }else if (user_input == exitCode){
        bad = false;
      }else if (static_cast<int>(user_input) < min || static_cast<int>(user_input) > max){
        new_line(user_interface_skip_screen);
        std::cerr << err;
        new_line(user_interface_system_message_skip_line);
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
      new_line(user_interface_skip_screen);
      std::cout << "\nTasks to be completed\n";
      print_dash(29);
      for_each(ToRun_.begin(), ToRun_.end(), [&](Task* e){
        if (e != nullptr){
          os << e->getName() <<'\n';
        }
      });
      new_line(user_interface_system_message_skip_line - 1);
    }else{
      std::cerr << "There are no tasks to be performed in the task list.";
      std::cerr.flush();
      new_line(user_interface_system_message_skip_line);
    }
    return os;
  }
  
  std::ostream& Profile::display_completed_tasks(std::ostream& os) const{
    //Display all completed tasks on screen
    if (Completed_.size()>0){
      new_line(user_interface_skip_screen);
      std::cout << "Completed Tasks\n";
      print_dash(23);
      
      for_each(Completed_.begin(), Completed_.end(), [&](Task* e) {
        if (e != nullptr){
          os << e->getName() << '\n';
        }
      });
      new_line(user_interface_system_message_skip_line - 1);
    }else{
      std::cerr << "There are no completed tasks. No tasks has been executed.";
      new_line(user_interface_system_message_skip_line);
      std::cerr.flush();
    }
    return os;
  }
  
  std::ostream& Profile::display_next_task(std::ostream& os) const{
    //Display next task to the screen
    if (ToRun_.size() > 0){
      os << "\nThe next task is ";
      os << ToRun_[0]->getName() << '.';
      new_line(user_interface_system_message_skip_line);
    }else{
      new_line(user_interface_skip_screen);
      os << "There is no task to be executed next.";
      new_line(user_interface_system_message_skip_line);
    }
    return os;
  }
  
  std::ostream& Profile::display_last_task(std::ostream& os)const{
    //Display last completed task to screen
    if (Completed_.size() > 0){
      os << "\nThe last task completed was ";
      os << Completed_[Completed_.size() - 1]->getName() <<
      ".";
      new_line(user_interface_system_message_skip_line);
    }else{
      os << "No Task has been completed yet.";
      new_line(user_interface_system_message_skip_line);
    }
    return os;
  }
}
