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
#include "LinkedList.h"
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
    DynamicList<changedEventCallback*> eventCallbacks;
    static char UNDEFINED[];
	DynamicJsonDocument* BaseConfig;
	DynamicJsonDocument* ColorConfig;
	DynamicJsonDocument* HWConfig;

	ConfigManager();
    DynamicJsonDocument* deserializeDynamically(fs::File &input, uint64_t initialDocSize);
	bool deserializeDynamically(fs::File &input, DynamicJsonDocument* initialDocument);

	template<typename T>
	T getProperty(DynamicJsonDocument* root, char* key);

	bool loadConfigFromMemory(const char* filename, DynamicJsonDocument* doc);
public:

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



	template<typename T>
	T getBaseProperty(char* key);

	template<typename T>
	T getColorProperty(char* key);

	template<typename T>
	T getHWProperty(char* key);

	template<typename T>
	bool setBaseProperty(char* key, T value);

	bool setBaseProperty(JsonPair& keyValuePair);

};


#endif
