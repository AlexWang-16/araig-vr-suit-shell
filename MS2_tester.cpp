//
//  MS2_tester.cpp
//
//  ARAIG - As Real As It Gets Augmented reality game suit final project
//  For BTP305 C++ course at Seneca
//
//  Created by Alex Wang on 2016-11-14.
//  Copyright © 2016 Alex Wang. All rights reserved.
//

#include "Stims.h"
#include "Exoskeleton.h"
#include "Task.h"
using namespace ARAIG;
extern const int max_duration, max_intensity;

const void print_dash(int x = 30) {
  //Creates underline for titles
  std::cout.width(x);
  std::cout.fill('-');
  std::cout << '-' << '\n';
  std::cout.fill (' ');
}

const void new_line(int x = 1) {
  //Prints i number of newline characters
  for (int i = 0; i < x; i++){
    std::cout << '\n';
  }
}

void data_parameter_positions(std::string input, int num_pos, std::vector<size_t>& list){
  //Takes in number of positions and stores positions for 2nd parameter onwards
  for (int i = 1; i < num_pos - 1; i++){
    list.push_back(input.find(',', list[i-1] + 1));
  }
}

int main(int argc, const char * argv[]) {
  //Test: Creating an empty Task
  //Expected: Task# should be 1 and name should be should be "Task_1"
  Task alpha;
  alpha.dump(std::cout);
  new_line();
  
  //Test: Instanting a second empty class and attempting to print its data and list of empty stimulations
  //Expected: Task# should be 2, Task name should be "Task_2" and no stimulation should show
  Task beta;
  beta.dump(std::cout);
  new_line();
  
  //Test: Giving task a name "Charlie" and an empty list of stimulations and printing task information
  //Expected: "Task 3 Task Test"
  Task charlie ("Charlie");
  charlie.dump(std::cout);
  new_line();
  //Test: Providing an empty name and an empty list of stimulations and printing task information
  //Expected: Task 4 Task_4
  Task delta ("");
  delta.dump(std::cout);
  new_line();
  
  //Test: Creating a generic task and add 3 stimulations to the Task, then print out task information and details of each stimulation
  //Expected: It should print "Task 5 Task_5" followed by the stimulation information
  std::ifstream file ("StimulationConfig.csv");
  try {
    if(!file){
      throw Exceptions ("Error: Cannot open file");
    }
  }catch (Exceptions& e){
    std::cerr << e.what() <<'\n';
    std::cerr.flush();
    exit(2);
  }
  
  std::list<Stimulation*> stim_list;
  std::vector<size_t> comma;
  while (!file.fail()){
    //Create Stim objects and store them into a list :)
    std::string data, type, name, location;
    int intensity, frequency, duration;
    
    getline(file, data);
    
    if (data.find('\r')){
      //Detects \n characters and trim it
      data = data.substr(0,data.length()-1);
    }
    
    comma.push_back (data.find(','));
    type = data.substr(0, comma[0]);
    if (type == "stim") {
      data_parameter_positions(data, 6, comma);
      name = data.substr(comma[0]+1, comma[1] - comma[0]-1);
      location = data.substr(comma[1]+1, comma[2] - comma[1]-1);
      intensity = stoi(data.substr(comma[2]+1, comma[3]-comma[2]-1));
      frequency = stoi(data.substr(comma[3]+1, comma[4]-comma[3]-1));
      duration = stoi(data.substr(comma[4]+1));
      stim_list.push_back(new Stims(name, location, intensity, frequency, duration));
      
    } else if (type == "exoskeleton") {
      data_parameter_positions(data, 4, comma);
      name = data.substr(comma[0]+1, comma[1] - comma[0]-1);
      intensity = stoi(data.substr(comma[1]+1, comma[2]-comma[1]-1));
      
      duration = stoi(data.substr(comma[2]+1));
      
      stim_list.push_back(new Exoskeleton(name, intensity, duration));
    }
    comma.clear();
  }
  
  Task echo;
  for_each (stim_list.begin(), stim_list.end(), [&echo](Stimulation* i){
    echo += i;
  });
  
  std::cout << "Task Echo\n";
  print_dash();
  echo.dump(std::cout);
  echo.execute(std::cout);
  new_line();
  
  //TODO: Reference data into Task Echo
  
  
  //Test: Print the 2nd element from Echo using overloaded [] operator
  //Expected: Stims 2 data
  std::cout << "Element 2 of Task Echo\n";
  print_dash();
  echo[1]->display(std::cout);
  new_line(2);
  
  
  //Test: Copy Task 5 using "=" operator
  //Expected: Information printed should be the same as Task 5 (see above)
  std::cout << "Testing use of copy assignment operator\n";
  print_dash(40);
  Task foxtrot = echo;
  foxtrot.dump(std::cout);
  foxtrot.execute(std::cout);
  new_line(2);
  
  //Test: Calling Copy constructor directly
  //Expected: A copy of Task 5 will be created
  Task golf (echo);
  std::cout << "Direct copy constructor call\n";
  print_dash();
  golf.dump(std::cout);
  golf.execute(std::cout);
  new_line();
  
  //Test: Removing the 3rd Stimulation from Echo (Exoskeleton element)
  //Expected: 2 Stims remain when execute() is executed
  std::cout << "Deleting Sim1 from Task 5 (echo)\n";
  print_dash(33);
  echo.removeStim("Sim1");
  echo.dump(std::cout);
  echo.execute(std::cout);
  new_line(2);
  
  //Test: Using move assignment operator to move foxtrot's data over to Task Hotel
  //Expecting: hotel to contain foxtrot's information and foxtrot's data should be wiped and not print any data.
  Task hotel;
  hotel = std::move(foxtrot);
  std::cout << "Test move assignment operator to move foxtrot's data into hotel.\nMoving data...\n\n";
  std::cout << "Hotel's data\n";
  print_dash(12);
  hotel.dump(std::cout);
  hotel.execute(std::cout);
  new_line(2);
  std::cout << "Updated Foxtrot's data\n";
  print_dash(22);
  foxtrot.dump(std::cout);
  foxtrot.execute(std::cout);
  new_line(2);
  
  //Test: Using move constructor to move golf's data to Task India
  //Expected: Task India should have all of golf's contents while golf will print empty data
  //Need help here. Not sure how to test move constructor.
  std::cout << "Test: Moving tasks in golf data over to india using move constructor. Golf should be empty after.\n";
  print_dash();
  Task india (std::move(golf));
  india.dump(std::cout);
  india.execute(std::cout);
  new_line(2);
  std::cout << "Golf's data\n";
  print_dash();
  golf.dump(std::cout);
  golf.execute(std::cout);
  new_line();
}
