//
//  Profile.h
//  ARAIG
//
//  Created by Alex Wang on 2016-12-06.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#ifndef Profile_H
#define Profile_H

#include "ARAIG_sensors.h"

namespace ARAIG{
  extern const float version;
class Profile{
  class Student{
    std::string FName_,
                LName_,
                Num_;
    int calMin_ = 0, calMax_ = 0;
  public:
    Student() = delete;
    Student(std::string firstName, std::string lastName, std::string studentNum);
    virtual ~Student();
    void setCalMax (std::string input);
    void setCalMin (std::string input);
    std::string getFName()const;
    std::string getLName()const;
    std::string getName()const;
    std::string getNumber()const;
    void writeData(std::ofstream& of);
    void writeCalibration(std::ofstream& of);
  };
  
  class Instructor{
    std::string FName_,
                LName_,
                Num_;
  public:
    Instructor() = delete;
    Instructor(std::string firstName, std::string lastName, std::string EmployeeNum);
    ~Instructor();
    std::string getFName()const;
    std::string getLName()const;
    std::string getName()const;
    std::string getNumber()const;
    void writeToFile(std::ofstream& of);
  };
  
  std::vector<Task*>ToRun_;
  std::vector<Task*>Completed_;
  std::vector<std::string>menu_;
  //Ownership of ofstream object
  std::ofstream& of_;
public:
  Profile (const char* filename, std::ofstream& os, ARAIG_sensors& as);
  virtual ~Profile();
  void run();
  //Executes specified number of tasks user specifies
  void execute (unsigned long tasks);
  void load_menu();
  long show_menu()const;
  long getInput(std::string prompt, int min, long max, bool menuPrompt = false);
  //Display all tasks to the screen
  std::ostream& display_todo_tasks (std::ostream& os) const;
  //Display completed tasks to the screen
  std::ostream& display_completed_tasks (std::ostream& os)const;
  //Display next task to the screen
  std::ostream& display_next_task (std::ostream& os) const;
  //Display last completed task
  std::ostream& display_last_task(std::ostream& os)const;

};
}

#endif /* Profile_H */
