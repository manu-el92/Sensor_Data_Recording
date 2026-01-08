# Sensor Data Recording

A C++ program that demonstrates sensor data management, filtering, and processing using the Standard Template Library (STL).

## Overview

This program:
- Stores sensor measurements (Altitude, Speed, Fuel Consumption) with timestamps
- Generates 100,000 random test measurements
- Demonstrates STL algorithms:
  - **`count_if`**: Counts Altitude measurements on a specific date
  - **`any_of`**: Checks if any speed exceeds 99.9 km/h
  - **`for_each`**: Multiplies fuel consumption values by a factor

## Project Structure

```
Sensor_Data_Recording/
├── Main.cpp       # Main program with SensorData class and test data
├── Makefile       # Build configuration
└── README.md      # This file
```

## Files

### Main.cpp
Contains:
- **`SensorType`** enum: Defines three sensor types (Altitude, SpeedInKmh, FuelConsumption)
- **`SensorData`** class: Stores a measurement (value, type, timestamp)
- **Helper functions**:
  - `FillData()`: Generates 100,000 random sensor readings
  - `CreateTime()`: Converts date/time components to Unix timestamp

### Makefile
Provides build targets:
- `make` or `make all`: Compiles the program
- `make run`: Compiles and runs the program
- `make clean`: Removes the compiled executable

## Requirements

- C++ compiler (g++ recommended)
- Make build tool
- Windows (uses `del` command in Makefile)

## Building

### On Windows (PowerShell):
```powershell
make
```

### Run the Program
```powershell
make run
```

Or run directly:
```powershell
.\Sensor_Data_Recording.exe
```

## Output

The program outputs:
```
Altitude number 2012-01-02: 5292
Maximum speed reached
SpeedInKmh above > 99.9 2012-01-02: Yes
```

- **Line 1**: Count of Altitude measurements on January 2, 2012
- **Line 2**: Whether maximum speed (>99.9 km/h) was reached
- **Line 3**: Confirmation of the maximum speed check

## Code Example

The main program demonstrates three STL algorithms:

```cpp
// Count measurements matching a condition
auto altitudeCount = count_if(sensorData.begin(), sensorData.end(),
    [startTime, endTime](const SensorData& sd) {
        return sd.GetSensorType() == SensorType::Altitude &&
               sd.GetTime() >= startTime &&
               sd.GetTime() <= endTime;
    }
);

// Check if any measurement matches a condition
bool maxSpeed = any_of(sensorData.begin(), sensorData.end(),
    [](const SensorData& sd) {
        return sd.GetSensorType() == SensorType::SpeedInKmh &&
               sd.GetValue() > 99.9f;
    }
);

// Process all measurements
for_each(sensorData.begin(), sensorData.end(),
    [](SensorData& sd) {
        if (sd.GetSensorType() == SensorType::FuelConsumption)
            sd.SetValue(sd.GetValue() * 1.75f);
    }
);
```

## Notes

- Test data is generated with random values and timestamps from January 1, 2012
- The program uses lambda expressions for algorithm predicates
- All comments in the source code are in English
- Compiled executable: `Sensor_Data_Recording.exe`

## Cleaning Up

Remove the compiled executable:
```powershell
make clean
```
