//
//  Task.cpp
//  ARAIG
//
//  Created by Alex Wang on 2016-11-25.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include "Task.h"
namespace ARAIG{
  int Task::global_task_num = 1;
  
  Task::Task(){
    task_num_ = global_task_num;
    name_ = name_ + std::to_string(task_num_);
    global_task_num++;
    
  }
  
  Task::Task(std::string name){
    task_num_ = global_task_num;
    name_ = name_ + std::to_string(task_num_);
    if (name.length() > 0){
      name_ = name;
    }
    global_task_num++;
  }
  
  Task::Task (const Task& src){
    copy(src.name_, src.task_num_, src.task_list_);
  }
  
  Task& Task::operator=(const Task& src){
    if (&src != this){
      copy(src.name_, src.task_num_, src.task_list_);
    }
    return *this;
  }
  
  void Task::copy (std::string name, int task_num, std::list<Stimulation*>tsk_list){
      name_ = name;
      task_num_ = task_num;
      auto i = task_list_.begin();
      for (Stimulation* element : tsk_list){
        task_list_.insert(i, element);
        i++;
      }
  }
  
  void Task::operator+=(const Stimulation* src){
    //TODO: += overloaded operator
    

  }
  
  Stimulation* Task::operator[](unsigned int i)const{
    //Go to the specific element and return (*iterator)
    return 0;
  }
  
  void Task::removeStim(std::string name){
    //TODO: Search task_list_ for item and delete
    //task_list_.erase(i)
  }
  
  std::ostream& Task::dump(std::ostream& os)const{
    os << "Task " << task_num_ << ' ' << name_ << '\n';
    os.flush();
    return os;
  }
  
  std::ostream& Task::execute(std::ostream& os)const{
    //Print details of all stimulations inside a task. Will require iterator

    for (Stimulation* element : task_list_){
      os << element << '\n';
    }
    return os;
  }
}