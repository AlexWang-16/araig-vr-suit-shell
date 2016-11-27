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
    task_id_ = task_id_ + std::to_string(task_num_);
    name_ = name_ + std::to_string(task_num_);
    global_task_num++;
  }
  
  Task::Task(std::string name){
    task_num_ = global_task_num;
    name_ = name_ + std::to_string(task_num_);
    task_id_ = task_id_ + std::to_string(task_num_);
    if (name.length() > 0){
      name_ = name;
    }
    global_task_num++;
  }
  
  Task::Task (const Task& src){
    copy(src.task_id_, src.name_, src.task_num_, src.task_list_);
  }
  
  Task::Task (Task&& src){
    //Move constructor
    move(src.task_id_, src.name_, src.task_num_, src.task_list_);
  }
  
  Task::~Task() {
    task_id_.clear();
    name_.clear();
    task_list_.clear();
    task_num_ = 0;
  }
  
  Task& Task::operator=(const Task& src){
    if (&src != this){
      copy(src.task_id_, src.name_, src.task_num_, src.task_list_);
    }
    return *this;
  }
  
  Task& Task::operator=(Task&& src){
    if (this != &src){
      move(src.task_id_, src.name_, src.task_num_, src.task_list_);
    }
    return *this;
  }
  
  void Task::copy (std::string task_id, std::string name, int task_num, std::list<Stimulation*>tsk_list){
      task_id_ = task_id;
      name_ = name;
      task_num_ = task_num;
      for (Stimulation* element : tsk_list){
        task_list_.push_back(element);
      }
  }
  
  void Task::move (std::string& task_id, std::string& name, int& task_num, std::list<Stimulation*>& task_list){
    task_id_ = task_id;
    name_ = name;
    task_num_ = task_num;
    task_list_.clear();
    for (auto i = task_list.begin(); i !=task_list.end(); i++){
      task_list_.push_back(*i);
    }
    //House Cleaning
    task_id.clear();
    name.clear();
    task_num = 0;
    task_list.clear();
  }
  
  void Task::operator+=(Stimulation* ptr){
    task_list_.push_back(ptr);
  }
  
  Stimulation* Task::operator[](unsigned int i)const{
    //Go to the specific index and return  Stimulation*
    auto it = task_list_.begin();
    if (i < task_list_.size()){
      std::advance(it, i);
    }
    return *it;
  }
  
  void Task::removeStim(std::string name){
    //Search task_list_ for item and delete
    auto i = task_list_.begin();
    while (i != task_list_.end()){
      if ((*i)->getName() == name){
        task_list_.erase(i);
        break;
      }
      i++;
    }
  }
  
  std::ostream& Task::dump(std::ostream& os)const{
    os << task_id_ << ' ' << name_ << '\n';
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
