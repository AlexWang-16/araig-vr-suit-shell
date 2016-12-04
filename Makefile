all:
	clang++ -Wall -Werror -std=c++11 -o araig MS3_tester.cpp Exceptions.cpp Exoskeleton.cpp Stims.cpp Stimulation.cpp Task.cpp ARAIG_sensors.cpp
