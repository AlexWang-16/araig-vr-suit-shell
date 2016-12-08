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
class Profile{
  std::string studentFName_, studentLName_, studentNum_;
  std::string instructorFname_, instructorLName_, instructorNum_;
  int calMax_, calMin_;
  std::deque<Task*>ToRun_;
  std::deque<Task*>Completed_;
public:
  Profile (std::string filename, std::ostream& os, ARAIG_sensors& as);
  
  void run();
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
