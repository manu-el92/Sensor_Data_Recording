#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>


using namespace std; 

// Type of sensor data that can be stored
enum class SensorType
{
	Altitude,
	SpeedInKmh,
	FuelConsumption
};

// Simple class that holds a measurement: value, type, and timestamp
class SensorData
{
    float value;            
    SensorType sensorType;  
    time_t time;            
public:
	// Accessor methods
	SensorType GetSensorType()const { return sensorType; }
	float GetValue()const { return value; }
	void SetValue(float v) { value = v; }
	time_t GetTime()const { return time; }

	// Constructor - initializes all fields
	SensorData(SensorType sensorType, float value, time_t time)
	{
		this->value = value;
		this->sensorType = sensorType;
		this->time = time;
	}
};


// Helper declarations
void FillData(vector<SensorData> &v); // fills the vector with random data
time_t CreateTime(int year, int month, int day, int hour, int minute, int second);

int main()
{
    // Main data container
    vector<SensorData> sensorData;

	// Example: count how many Altitude measurements exist on a given day
	time_t startTime = CreateTime(2012, 1, 2, 0, 0, 0);
	time_t endTime = CreateTime(2012, 1, 2, 23, 59, 59);

	auto altitudeCount = count_if(sensorData.begin(), sensorData.end(),
	 [startTime, endTime](const SensorData& sd) {
		 return sd.GetSensorType() == SensorType::Altitude &&
			sd.GetTime() >= startTime &&
			sd.GetTime() <= endTime;
		}
	);

	std::cout << "Altitude number 2012-01-02: " << altitudeCount << std::endl;

	// Check if any speed measurement exceeds 99.9 km/h
	bool maxSpeed = any_of(sensorData.begin(), sensorData.end(),
		[](const SensorData& sd) {
			return sd.GetSensorType() == SensorType::SpeedInKmh &&
				sd.GetValue() > 99.9f; 
		}
	);

	if (maxSpeed)
		std::cout<< "Maximum speed reached" << endl;
	else
		std::cout<< "No maximum speed reached" << endl;

	cout << "SpeedInKmh above > 99.9 2012-01-02: " << (maxSpeed ? "Yes" : "No") << std::endl;

	// Multiply fuel consumption by a factor (example of processing)
	for_each(sensorData.begin(), sensorData.end(),
		[](SensorData& sd) {
			if (sd.GetSensorType() == SensorType::FuelConsumption)
				sd.SetValue(sd.GetValue() * 1.75f);
		}
	);

	return 0;
}

// Fills a vector with random sensor values (test data)
void FillData(vector<SensorData>& v){
	srand(time(NULL));

	time_t tid = CreateTime(2012, 1, 1, 1, 1, 1 );
	for (int i = 0; i < 100000; i++)
	{
		SensorType type = static_cast<SensorType>(rand() % 3);
		float value = 0.0f;
		if (type == SensorType::Altitude)
			value = rand() % 1000; // altitude in meters
		else if (type == SensorType::FuelConsumption)
			value = rand() / (float)RAND_MAX * 3.0f; // liters per hour
		else if (type == SensorType::SpeedInKmh)
			value = rand() % 110; // speed
		else
		{
			value = 99;
		}
		v.push_back(SensorData(type,value,tid));
		tid = tid + rand() % 10 + 1; // increase the timestamp randomly
	}
}

// Creates a time_t from separate date/time components
time_t CreateTime(int year, int month, int day, int hour, int minute, int second)
{
	struct tm tid = { 0 };
	tid.tm_year = year-1900;
	tid.tm_mon = month - 1;
	tid.tm_mday = day;
	tid.tm_hour = hour;
	tid.tm_min = minute;
	tid.tm_sec = second;
	return mktime(&tid);

}