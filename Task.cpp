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
    name_ = name_ + std::to_string(global_task_num);
    global_task_num++;
  }
  
  Task::Task(std::string name){
    name_ = name_ + std::to_string(global_task_num);
    if (name.length() > 0){
      name_ = name;
    }
    global_task_num++;
  }
  
  Task::Task (const Task& src){
    *this = (src);
  }
  
  Task::Task (Task&& src){
    //Move constructor
    *this = std::move(src);
  }
  
  Task::~Task() {
    clear();
  }
  
  Task& Task::operator=(const Task& src){
    if (&src != this){
      name_ = src.name_;
      for (Stimulation* element : src.task_list_){
        task_list_.push_back(element);
      }
    }
    return *this;
  }
  
  Task& Task::operator=(Task&& src){
    if (this != &src){
      name_ = src.name_;
      task_list_.clear();
      task_list_ = src.task_list_;
      //House Cleaning
      src.name_.clear();
      src.task_list_.clear();
    }
    return *this;
  }
  
  void Task::operator+=(Stimulation* ptr){
    task_list_.push_back(ptr);
    task_num_++;
  }
  
  Stimulation* Task::operator[](unsigned int i)const{
    //Go to the specific index and return  Stimulation*
    auto it = task_list_.begin();
    if (i < task_list_.size()){
      std::advance(it, i);
    }
    return *it;
  }
  
  long Task::getSize()const{
    return task_list_.size();
  }
  
  std::string Task::getName()const{
    return name_;
  }
  void Task::setName(std::string name){
    if (name.length() > 0)
      name_ = name;
  }
  void Task::removeStim(std::string name){
    //Search task_list_ for item and delete
    auto i = task_list_.begin();
    while (i != task_list_.end()){
      if ((*i)->getName() == name){
        task_list_.erase(i);
        task_num_--;
        break;
      }
      i++;
    }
  }
  
  void Task::clear(){
    //resets task data
    name_.clear();
    task_list_.clear();
    task_num_ = 0;
  }
  
  std::ostream& Task::dump(std::ostream& os)const{
    os << name_ << '\n';
    os << "Number of stimulations in task list: " << getSize() <<'\n';
    os.flush();
    return os;
  }
  
  std::ostream& Task::execute(std::ostream& os)const{
    //Print details of all stimulations inside a task. Will require iterator

    for (Stimulation* element : task_list_){
      element->display(os) << '\n';
    }
    return os;
  }
}
