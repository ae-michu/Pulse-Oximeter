#include "sensor.h"

void Sensor :: init() {
    if (!begin(Wire, I2C_SPEED_FAST)) {                            // start communication with the sensor
        if (Serial.available()) {
            Serial.println("ERR: Sensor not found");
        }
        while(true);
    }

    setup();                                                       // start measurments with default values
    setPulseAmplitudeRed(0x0A);                                    // set red led to dimm to indicate that sensor is working
    setPulseAmplitudeGreen(0);                                     // disable green led (our sensor doesn't have it)
}

float Sensor :: getBPMData() {
    long ir = getIR();                                              // get infrared light detector value from the sensor

    if (ir > 50000) {                                               // check if finger is placed
        if (checkForBeat(ir)) {                                     // check for pulse
            long deltaBeats = millis() - lastBeatTime;              // calculate time differance between two hearth beats
            lastBeatTime = millis();

            float newBpm = 60 / (deltaBeats / 1000.0);              // calculate bpm value based on previously calculated time differance

            if (newBpm > 20 && newBpm < 255) {                      // check if bpm value is realistic
                bpmData[dataPos] = newBpm;                          // add bpm value to array

                dataPos++;                                          // increase data position index
                if (dataPos == BPM_BUFFER) {                        // check if data position index is equal to specified data buffer size (if so, reset it back to 0) to avoid array overflow 
                    dataPos = 0;
                }
            }

            return newBpm;
        }
    }

    return 0;
}

float Sensor :: getBPM() {
    float bpm = 0.0;

    if (!dataReady) {                                               // dataReady flag is false, buffer is not filled                              
        if (dataPos == (BPM_BUFFER - 1)) {                          // if index dataPos is equal to buffer size-1 then set dataReady flag to true (buffer is full) 
            dataReady = true;
        } else {
            for (int i = 0; i < dataPos; i++) {                     // because buffer is not filled we will calculate average bpm using available values in buffer
                bpm += bpmData[i];
            }

            bpm = bpm / dataPos;
        }
    }

    if (dataReady) {                                                // dataReady flag is true, buffer is filled
        for (int i = 0; i < BPM_BUFFER; i++) {                      // calculate average bpm using whole buffer
            bpm += bpmData[i];
        }

        bpm = bpm / BPM_BUFFER;
    }

    return bpm;
}

float Sensor :: getO2Data() {
    int data = getRed();                                                            // get red led detector value from sensor

    if (data != 0) {                                                                // do not use values equal to zero
        o2Data[o2DataPos] = ((data / (ADC_MAX_VALUE / 3.3)) / 3.3) * -100;          // calculate % of light reflected back to sensor based on voltage read from sensor (calulated from maximum adc value)
        o2DataPos++;

        if (o2DataPos == O2_BUFFER) {                                               // if position index is equal to buffer size then set it to zero and override the oldest value with the newest one
            o2DataPos = 0;
        }
    }

    return data;
}

float Sensor :: getO2() {
    float o2 = 0.0;

    if (!o2DataReady) {                                                             // o2DataReady flag is false, buffer is not filled
        if (o2DataPos == (O2_BUFFER - 1)) {
            o2DataReady = true;                                                     // if index o2DataPos is equal to buffer size-1 then set o2DataReady flag to true (buffer is full) 
        } else {
            for (int i = 0; i < o2DataPos; i++) {                                   // because buffer is not filled we will calculate average o2 using available values in buffer
                o2 += o2Data[i];
            }

            o2 = o2 / o2DataPos;
        }
    }

    if (o2DataReady) {                                                              // o2DataReady flag is true, buffer is filled
        for (int i = 0; i < O2_BUFFER; i++) {                                       // calculate average o2 using whole buffer
            o2 += o2Data[i];
        }

        o2 = o2 / O2_BUFFER;
    }

    return o2;
}