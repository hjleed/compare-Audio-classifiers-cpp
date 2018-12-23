# makefile
# auther: Hitham @ 2017

# headers and libraries
HEADERS = -I/usr/local/include -I/opt/boost/include
LIB_DIR = -L/usr/local/lib
LIBS = -lgrt

# Declaration of variables
CC = g++ -std=c++11
CFLAGS = -g -Wall $(LIB_DIR)
QMAKE_LFLAGS += -no-pie

# File names

EXEC = BAG
CPP_CRCS = $(wildcard *.cpp)
OBJECTS = $(CPP_CRCS:.cpp=.o) 


#Build 
make:       
	@echo "----------------- Building BAG -----------------"
    	#Compile the code to create the object files
	$(CC) -c $(CPP_CRCS) $(HEADERS) $(CFLAGS)
    	#Compile the actual output examples and link against the library
	$(CC) $(OBJECTS) -o $(EXEC) $(HEADERS) $(CFLAGS) $(LIBS)

.PHONY : clean
clean: 
	rm -f *.o *.out




