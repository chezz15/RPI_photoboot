#------------------------------------------------------------------------------

SOURCE= src/main.c  
EXECUTABLE=build/RPI_Photobooth
INCLUDES=/includes
LIB_PATH=/C/RPI_Photobooth/src/main
LIBRARY=wiringPi
CC=arm-linux-gnueabihf-g++.exe

#------------------------------------------------------------------------------



all: $(EXECUTABLE)


$(EXECUTABLE): $(SOURCE)

	$(CC) -I$(INCLUDES) $(SOURCE) -L$(LIB_PATH) -l$(LIBRARY) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)