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
    copy(src.name_, src.task_list_);
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
      copy(src.name_, src.task_list_);
    }
    return *this;
  }
  
  Task& Task::operator=(Task&& src){
    if (this != &src){
      move(src.name_, src.task_list_);
    }
    return *this;
  }
  
  void Task::copy (std::string name, std::list<Stimulation*>tsk_list){
      name_ = name;
      for (Stimulation* element : tsk_list){
        task_list_.push_back(element);
      }
  }
  
  void Task::move (std::string& name, std::list<Stimulation*>& task_list){
    name_ = name;
    task_list_.clear();
    for (auto i = task_list.begin(); i !=task_list.end(); i++){
      task_list_.push_back(*i);
    }
    //House Cleaning
    name.clear();
    task_list.clear();
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
