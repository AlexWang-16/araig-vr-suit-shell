//
//  ARAIG_sensors.h
//  ARAIG
//
//  Created by Alex Wang on 2016-12-02.
//  Student# 118 540 152
//  Email: awang63@myseneca.ca
//
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#ifndef ARAIG_sensors_H
#define ARAIG_sensors_H

#include "Stimulation.h"
#include "Task.h"
namespace ARAIG {
  class ARAIG_sensors{
    std::map<std::string, std::shared_ptr<Stimulation>> stim_list_;
    std::map<std::string, Task*> task_list_;
    Task dummy;
  public:
    ARAIG_sensors (const char* stims_filename, const char* tasks_filename);
    ~ARAIG_sensors();
    long getTaskSize();
    bool taskExists(std::string index);
    Task& getTask(std::string key);
    std::ostream& dump(std::ostream& os);
  };
}
#endif /* ARAIG_sensors_H */
