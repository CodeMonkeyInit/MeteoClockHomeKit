//
// Created by Денис Кулиев on 11.04.2021.
//

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

// Called to identify this accessory. See HAP section 6.7.6 Identify Routine
// Generally this is called when paired successfully or click the "Identify Accessory" button in Home APP.
void my_accessory_identify(homekit_value_t _value) {
    printf("accessory identify\n");
}

// For TEMPERATURE_SENSOR,
// the required characteristics are: CURRENT_TEMPERATURE
// the optional characteristics are: NAME, STATUS_ACTIVE, STATUS_FAULT, STATUS_TAMPERED, STATUS_LOW_BATTERY
// See HAP section 8.41 and characteristics.h

// (required) format: float; HAP section 9.35; min 0, max 100, step 0.1, unit celsius
homekit_characteristic_t homeKitTemperature = HOMEKIT_CHARACTERISTIC_(CURRENT_TEMPERATURE, 0);


// (optional) format: string; HAP section 9.62; max length 64
homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "Temperature Sensor");


// (optional) format: bool; HAP section 9.96
// homekit_characteristic_t cha_status_active = HOMEKIT_CHARACTERISTIC_(STATUS_ACTIVE, true);

// (optional) format: uint8; HAP section 9.97; 0 "No Fault", 1 "General Fault"
// homekit_characteristic_t cha_status_fault = HOMEKIT_CHARACTERISTIC_(STATUS_FAULT, 0);

// (optional) format: uint8; HAP section 9.100; 0 "Accessory is not tampered", 1 "Accessory is tampered with"
// homekit_characteristic_t cha_status_tampered = HOMEKIT_CHARACTERISTIC_(STATUS_TAMPERED, 0);

// (optional) format: uint8; HAP section 9.99; 0 "Battery level is normal", 1 "Battery level is low"
// homekit_characteristic_t cha_status_low_battery = HOMEKIT_CHARACTERISTIC_(STATUS_LOW_BATTERY, 0);

// example for humidity
homekit_characteristic_t homeKitHumidity = HOMEKIT_CHARACTERISTIC_(CURRENT_RELATIVE_HUMIDITY, 0);

homekit_characteristic_t homekitAirQuality = HOMEKIT_CHARACTERISTIC_(AIR_QUALITY, 1);
homekit_characteristic_t homeKitCO2Level = HOMEKIT_CHARACTERISTIC_(CARBON_DIOXIDE_LEVEL, 1000);

homekit_accessory_t *accessories[] = {
        HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_sensor, .services=(homekit_service_t*[]) {
                HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
                HOMEKIT_CHARACTERISTIC(NAME, "Home sensors"),
                HOMEKIT_CHARACTERISTIC(MANUFACTURER, "DKN"),
                HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "1337"),
                HOMEKIT_CHARACTERISTIC(MODEL, "Code Monkey"),
                HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "0.1"),
                HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
                NULL
        }),
                          HOMEKIT_SERVICE(
                                  TEMPERATURE_SENSOR,.primary = true, .characteristics=(homekit_characteristic_t*[]) {
                                  &homeKitTemperature,
                                  &cha_name,//optional
                                  //&cha_status_active,//optional
                                  //&cha_status_fault,//optional
                                  //&cha_status_tampered,//optional
                                  //&cha_status_low_battery,//optional
                                  NULL
                          }),
        // Add this HOMEKIT_SERVICE if you has a HUMIDITY_SENSOR together

                          HOMEKIT_SERVICE(HUMIDITY_SENSOR,.characteristics = (homekit_characteristic_t *[]) {
                                  HOMEKIT_CHARACTERISTIC(NAME, "Humidity Sensor"),
                                  &homeKitHumidity,
                                  NULL
                          }),

                          HOMEKIT_SERVICE(AIR_QUALITY_SENSOR, .characteristics = (homekit_characteristic_t *[]) {
                                  HOMEKIT_CHARACTERISTIC(NAME, "Carbon Dioxide Sensor"),
                                  &homekitAirQuality,
                                  &homeKitCO2Level,
                                  NULL
                          }),
                          NULL
                          }),
        NULL
};

homekit_server_config_t config = {
        .accessories = accessories,
        .password = "111-11-111",
        .setupId = "ABCD"
};