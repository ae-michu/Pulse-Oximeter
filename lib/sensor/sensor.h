#ifndef sensor_h
#define sensor_h

#include <Arduino.h>
#include <Wire.h>
#include <MAX30105.h>
#include <heartRate.h>

#define BPM_BUFFER      15                   // size of array that stores bpm reading for averaging
#define O2_BUFFER       15                   // size of array that stores o2 sensor readings for averaging
#define ADC_MAX_VALUE   262114               // maximum adc value

class Sensor : public MAX30105 {
    private:
        long lastBeatTime;
        float bpmData[BPM_BUFFER];
        int dataPos = 0;
        bool dataReady = false;
        float o2Data[O2_BUFFER];
        int o2DataPos = 0;
        bool o2DataReady = false;

    public:
        void init();
        float getBPMData();
        float getBPM();
        float getO2Data();
        float getO2();
};

#endif