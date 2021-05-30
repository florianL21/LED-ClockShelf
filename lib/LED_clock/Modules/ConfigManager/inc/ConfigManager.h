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
 * \addtogroup Config_manager_config
 * \brief Configuration for the config manager
 * \{
 */

#define BASE_CONFIG_FILE_NAME 		"/BaseConfig.json"
#define COLOR_CONFIG_FILE_NAME 		"/ColorConfig.json"
#define HW_CONFIG_FILE_NAME 		"/HWConfig.json"
#define EVENT_IDS_FILE_NAME			"/ConfigChangeEventIDs.json"
#define JSON_BUFFER_BASE_CONFIG		1536
#define JSON_BUFFER_COLOR_CONFIG	384
#define JSON_BUFFER_HW_CONFIG		1536
#define JSON_BUFFER_EVENT_IDS		2106

#define JSON_BUFFER_CHUNK_SIZE		256
#define JSON_BUFFER_INITIAL_SIZE	200
#define MAX_JSON_BUFFER				5000

#define BLYNK_ACTIVE_KEY			"ENABLE_BLYNK"
#define BLYNK_TOKEN_KEY				"BLYNK_AUTH_TOKEN"
#define BLYNK_SERVER_KEY			"BLYNK_SERVER"
#define DIGIT_ANIMATION_SPEED_KEY	"DIGIT_ANIMATION_SPEED"

#define WIFI_CONNECTING_COLOR_KEY	"WIFI_CONNECTING"
#define WIFI_CONNECTED_COLOR_KEY	"WIFI_CONNECTION_SUCCESSFUL"
#define WIFI_CONFIG_COLOR_KEY		"WIFI_SMART_CONFIG"
#define ERROR_COLOR_KEY				"ERROR"

#define DEMO_MODE_KEY				"TIME_MANAGER_DEMO_MODE"

/** \} */

// const char* Wifi_config_classes[] = {};

#define SYSTEM_RESTART_REQUIRED			true
#define SYSTEM_NO_RESTART_REQUIRED		false

/**
 * \brief The config manager is responsible to handle the json configuration files.
 *        It stores all config values in variables to be able to use them in the code
 */
class ConfigManager
{
public:
    typedef bool (*propertyChangedCallback)(ConfigManager* config);
	enum ConfigType {BASE_CONFIG, COLOR_CONFIG, HW_CONFIG, _CONFIG_TYPE_LENGTH};
private:
    struct changedEventCallback {
        propertyChangedCallback callback;
        uint8_t configEvent;
    };

	enum ConfigClass_id {
		WIFI_CONFIG_CLASS_ID 	= 0,
		BLYNK_CONFIG_CLASS_ID 	= 1,
		BASE_CONFIG_CLASS_ID	= 2,
		COLOR_CONFIG_CLASS_ID 	= 3,
		HW_CONFIG_CLASS_ID		= 4,
		_CONFIG_CLASS_ID_LENGTH = 5
	};

    static ConfigManager* instance;
    DynamicList<changedEventCallback*> eventCallbacks;
	DynamicJsonDocument* BaseConfig;
	DynamicJsonDocument* ColorConfig;
	DynamicJsonDocument* HWConfig;
	DynamicJsonDocument* EventIDs;

	bool configClassWasUpdated[_CONFIG_CLASS_ID_LENGTH];
	bool configNeedsSaving[_CONFIG_TYPE_LENGTH];

	ConfigManager();
    DynamicJsonDocument* deserializeDynamically(fs::File &input, uint64_t initialDocSize);
	bool deserializeDynamically(fs::File &input, DynamicJsonDocument* initialDocument);

	template<typename T>
	T getProperty(DynamicJsonDocument* root, const char* key);

	bool loadConfigFromMemory(const char* filename, DynamicJsonDocument* doc);
	DynamicJsonDocument* getDocument(ConfigType config);
	const char* getFileName(ConfigType config);

	void checkCallbacks(uint8_t ConfigEvent);
public:

	enum ConfigEvents {
		WIFI_CONFIG_CHANGED 	= 0x01 << WIFI_CONFIG_CLASS_ID,
		BLYNK_CONFIG_CHANGED 	= 0x01 << BLYNK_CONFIG_CLASS_ID,
		BASE_CONFIG_CHANGED		= 0x01 << BASE_CONFIG_CLASS_ID,
		COLOR_CONFIG_CHANGED 	= 0x01 << COLOR_CONFIG_CLASS_ID,
		HW_CONFIG_CHANGED		= 0x01 << HW_CONFIG_CLASS_ID
	};

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
	T getProperty(ConfigType config, const char* key);

	template<typename T>
	bool setProperty(ConfigType config, char* key, T value);

	bool setProperty(JsonPair& keyValuePair, ConfigType config);

	void saveConfigPersistent(ConfigType config);
	void applyChanges();

	void registerOnChangedCallback(uint8_t ConfigEvent, propertyChangedCallback Callback);
	void unregisterOnChangedCallback(propertyChangedCallback Callback);

};

#endif
