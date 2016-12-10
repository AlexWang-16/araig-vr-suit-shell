all:
	clang++ -Wall -Werror -std=c++11 -O2 -Wextra -o araig main.cpp Exceptions.cpp Exoskeleton.cpp Stims.cpp Stimulation.cpp Task.cpp ARAIG_sensors.cpp Profile.cpp Global.cpp
