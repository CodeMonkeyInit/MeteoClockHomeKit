//
// Created by Денис Кулиев on 11.04.2021.
//

#ifndef SMARTHOMESENSORS_HOMEKITSERVICE_H
#define SMARTHOMESENSORS_HOMEKITSERVICE_H

#include <arduino_homekit_server.h>


extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t homeKitTemperature;
extern "C" homekit_characteristic_t homeKitHumidity;
extern "C" homekit_characteristic_t homekitAirQuality;
extern "C" homekit_characteristic_t homeKitCO2Level;



class HomeKitService{
public:
    void init();
    void loopOnce(int co2Concentration, float temperature, float humidity);

private:
    void generateHomeKitReport(int co2Concentration, float temperature, float humidity);
    int getAirQuality(int co2);
};



#endif //SMARTHOMESENSORS_HOMEKITSERVICE_H
