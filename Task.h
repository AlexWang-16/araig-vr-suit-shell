//
//  Task.h
//  ARAIG
//
//  Created by Alex Wang on 2016-11-25.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#ifndef Task_H
#define Task_H

#include "Stimulation.h"
namespace ARAIG{
  class Task{
    static int global_task_num;
    std::list<Stimulation*>task_list_;
    std::string name_ = "Task";
    int task_num_ = 0;
  public:
    Task();
    Task (std::string name);
    Task (const Task& src);
    Task (Task&& src);
    virtual ~Task();
    Task& operator=(const Task& src);
    Task& operator=(Task&& src);
    void copy(std::string name, std::list<Stimulation*>task_list);
    void operator+=(Stimulation* ptr);
    Stimulation* operator[] (unsigned int i)const;
    long getSize()const;
    std::string getName()const;
    void setName(std::string name);
    void removeStim(std::string name);
    void clear();
    // Print the list of tasks in there
    std::ostream& dump(std::ostream& os)const;
    //Print the simulations inside a task
    std::ostream& execute(std::ostream& os)const;
  };
}
#endif /* Task_H */
