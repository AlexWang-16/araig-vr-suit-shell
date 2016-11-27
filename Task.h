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
    std::string name_ = "Task_";
    int task_num_ = 0;
  public:
    Task();
    Task (std::string);
    Task (const Task&);
    Task (Task&&);
    Task& operator=(const Task&);
    void copy(std::string, int, std::list<Stimulation*>);
    void operator+=(Stimulation*);
    Stimulation* operator[] (unsigned int)const;
    void removeStim(std::string);
    // Print the list of tasks in there
    std::ostream& dump(std::ostream&)const;
    //Print the simulations inside a task
    std::ostream& execute(std::ostream&)const;
  };
}
#endif /* Task_H */
