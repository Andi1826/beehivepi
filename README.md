### beehivepi

##### Build

To build you need to install sqlite3:  
_sudo apt-get install sqlite3_  
and install sqlite3 headers:  
_sudo apt-get install libsqlite3-dev_

Then build it with:  
_gcc -o main main.c -l sqlite3 -lm_

And run it with:  
_./main_
