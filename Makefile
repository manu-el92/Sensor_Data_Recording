CXX = g++
CXXFLAGS = -std=c++11 -O2
TARGET = Sensor_Data_Recording.exe
SRC = Main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	@echo Running $(TARGET)
	.\$(TARGET)

clean:
	- del /Q $(TARGET) 2>nul || true

.PHONY: all run clean