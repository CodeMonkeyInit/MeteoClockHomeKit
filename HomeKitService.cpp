//
// Created by Денис Кулиев on 11.04.2021.
//

#include "HomeKitService.h"

#define MHZ_RX D3
#define MHZ_TX D4

int32_t next_report_ms = 0;

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

int random_value(int min, int max) {
    return min + random(max - min);
}

void HomeKitService::init() {
    arduino_homekit_setup(&config);
}

void HomeKitService::generateHomeKitReport(int co2Concentration, float temperature, float humidity) {


    homekitAirQuality.value.int_value = this->getAirQuality(co2Concentration);
    homeKitCO2Level.value.float_value = co2Concentration == - 1 ? 0 : (float) co2Concentration;
    homeKitHumidity.value.float_value = humidity;
    homeKitTemperature.value.float_value = temperature;

    LOG_D("Current temperature: %.1f", temperature);
    LOG_D("Current humidity: %.1f", humidity);
    LOG_D("Current co2 concentration: %.1f", homeKitCO2Level.value.float_value);
    LOG_D("Current air quality: %d", homekitAirQuality.value.int_value);

    homekit_characteristic_notify(&homeKitTemperature, homeKitTemperature.value);
    homekit_characteristic_notify(&homeKitHumidity, homeKitHumidity.value);
    homekit_characteristic_notify(&homekitAirQuality, homekitAirQuality.value);
    homekit_characteristic_notify(&homeKitCO2Level, homeKitCO2Level.value);
}

void HomeKitService::loopOnce(int co2Concentration, float temperature, float humidity) {
    arduino_homekit_loop();

    const uint32_t t = millis();
    if (t > next_report_ms) {
        // report sensor values every 10 seconds
        next_report_ms = t + 10 * 1000;
        this->generateHomeKitReport( co2Concentration,  temperature,  humidity);
    }
}

int HomeKitService::getAirQuality(int co2) {
    if(co2 == -1)
        return 0;

    if (co2 < 400) {
        return 1;
    }

    if (co2 < 1000)
        return 2;

    if (co2 < 2000) {
        return 3;
    }

    if (co2 < 5000) {
        return 3;
    }

    return 5;

}
