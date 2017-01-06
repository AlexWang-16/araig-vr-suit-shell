README – ARAIG Control Flight Simulator Manual

Please ensure the following before compiling the program:
* All Files are inside one single directory
* Folder has read and write permissions
* The execution file “araig” is granted read and execute permissions.

Compiling the program:
1) Unzip the folder and its contents
2) In a terminal, execute “make” command inside the directory to begin compiling the program.
3) Execute the command “araig StimulationConfig.csv TaskConfiguration.csv SampleProfileConfiguration.csv output.txt” to begin the program.

This program will generate the output text file “output” using the command above you may change the name from “output” to anything you like. If the file already exists, it will overwrite its data. Backup the output file before running this program more than once.

Error Codes:
Included is a text file named “err_codes.txt”. This file contains references to exit codes that maybe useful to you for additional details on why the error occurred. 

This program is designed to be self-healing and will recover from minor errors to proceed with your desired commands. Exceptions are only thrown when data is corrupted beyond the ability to recover.
