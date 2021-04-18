/**
 * \file ConfigManager.h
 * \author Florian Laschober
 * \brief Config manager class definition
 */

#ifndef __CONFIG_MANAGER_H_
#define __CONFIG_MANAGER_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <LinkedList.h>
#include "Configuration.h"

/**
 * \brief The config manager is responsible to handle the json configuration files.
 *        It stores all config values in variables to be able to use them in the code
 */
class ConfigManager
{
public:
    typedef void (*propertyChangedCallback)(void);
private:
    struct changedEventCallback {
        propertyChangedCallback callback;
        void* property;
        uint8_t configClass;
    };
    static ConfigManager* instance;
    LinkedList<changedEventCallback*> eventCallbacks;
    static char UNDEFINED[];

	ConfigManager();
    DynamicJsonDocument* deserializeDynamically(fs::File &input, uint64_t initialDocSize);

    template <class valueType, class jsonObjectType>
    bool parseValue(jsonObjectType* root, String key, valueType* value, uint8_t ConfigClass);

    template <class valueType, class jsonObjectType>
    bool parseValue(jsonObjectType* root, String key, valueType* value);
    void checkCallbacks(void* Property, uint8_t ConfigClass);
public:
    struct WIFI_config {
        bool enabled;
        bool blynk_enabled;
        bool ota_enabled;
        bool smart_config_enabled;
        uint16_t connection_retries;
        char* blynk_token;
        char* blynk_server;
        char* host_name;
        char* ssid;
        char* pw;
    };

    struct Color_config {
        uint32_t default_hour;
        uint32_t default_minute;
        uint32_t default_internal;
        uint32_t default_separation_dot;
        uint32_t ota_update;
        uint32_t wifi_connecting;
        uint32_t wifi_connection_successful;
        uint32_t wifi_smart_config;
        uint32_t error;
    };


    enum ConfigChanges {C_WIFI = 0x01, C_COLORS = 0x02, C_LED = 0x04, C_LIGHT_SENSOR = 0x08, C_TIME = 0x10, C_OTHER = 0x20};
    WIFI_config WIFI;
    Color_config Colors;

    /**
     * \brief Destroys the Config Manager object and cause #ConfigManager::getInstance to create a new object the next time it is called
     */
	~ConfigManager();

    /**
     * \brief Get the instance of the ConfigManager object or create it if it was not yet instantiated.
     *
     * \return ConfigManager* returns the address to the ConfigManager object
     */
	static ConfigManager* getInstance();

    bool loadConfigFromMemory();
    void registerOnChangedCallback(void* Property, propertyChangedCallback Callback);
    void registerOnChangedCallback(uint8_t ConfigClass, propertyChangedCallback Callback);
    void unregisterOnChangedCallback(propertyChangedCallback Callback, void* Property = nullptr);
};


#endif
