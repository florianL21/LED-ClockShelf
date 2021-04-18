/**
 * \file ConfigManager.cpp
 * \author Florian Laschober
 * \brief Implementation of the ConfigManager class member functions
 */


#include "ConfigManager.h"

ConfigManager* ConfigManager::instance = nullptr;
char ConfigManager::UNDEFINED[] = "UNDEFINED";

ConfigManager::ConfigManager()
{
    if(!SPIFFS.begin(true))
	{
		Serial.println("Filesystem mount failed aborting...");
		abort();
	}

	Serial.printf("Filesystem mount successful; %d out of %d bytes used\n\r", SPIFFS.usedBytes(), SPIFFS.totalBytes());

    // writing some default values:
    WIFI.enabled = false;
    WIFI.blynk_enabled = false;
    WIFI.ota_enabled = false;
    WIFI.smart_config_enabled = false;
    WIFI.connection_retries = 0;
    WIFI.blynk_token = UNDEFINED;
    WIFI.blynk_server = UNDEFINED;
    WIFI.host_name = UNDEFINED;
    WIFI.ssid = UNDEFINED;
    WIFI.pw = UNDEFINED;

    loadConfigFromMemory();
}

ConfigManager::~ConfigManager()
{
	instance = nullptr;
}

ConfigManager* ConfigManager::getInstance()
{
	if(instance == nullptr)
	{
		instance = new ConfigManager();
	}
	return instance;
}

DynamicJsonDocument* ConfigManager::deserializeDynamically(fs::File &input, uint64_t initialDocSize)
{
	//try  to initialize a json document big enough to fit all the data
	uint64_t DocumentSize = initialDocSize;
	DynamicJsonDocument* doc;
	bool successful = false;

	do
	{
		doc = new DynamicJsonDocument(DocumentSize);
		DeserializationError error = deserializeJson(*doc, input);
		if (error)
		{
			delete doc;
			if (error.code() == DeserializationError::NoMemory)
			{
				DocumentSize += JSON_BUFFER_CHUNK_SIZE;
			}
			else
			{
				Serial.println("E: json:" + String(error.c_str()));
				break;
			}
		}
		else
		{
			successful = true;
			break; //no error detected -> memory size is okay
		}
	} while (DocumentSize < MAX_JSON_BUFFER);

	if(successful == true)
	{
        return doc;
    }
    return nullptr;
}

void ConfigManager::checkCallbacks(void* property, uint8_t ConfigClass)
{
    for (int i = 0; i < eventCallbacks.size(); i++)
    {
        if(eventCallbacks[i]->property != nullptr)
        {
            if(eventCallbacks[i]->property == property)
            {
                eventCallbacks[i]->callback();
            }
        }
        else
        {
            if((eventCallbacks[i]->configClass & ConfigClass) != 0x00)
            {
                eventCallbacks[i]->callback();
            }
        }
    }
}

template <class valueType, class jsonObjectType>
bool ConfigManager::parseValue(jsonObjectType* root, String key, valueType* value)
{
	bool successful = false;
	JsonVariant jvalue = (*root)[key];
	if (!jvalue.isNull())
	{
		if(!jvalue.is<valueType>())
		{
			Serial.println("E: " + key + " is not the right type");
		}
		else
		{
            *value = jvalue.as<valueType>();
			successful = true;
		}
	}
	return successful;
}

template <class valueType, class jsonObjectType>
bool ConfigManager::parseValue(jsonObjectType* root, String key, valueType* value, uint8_t ConfigClass)
{
	bool successful = false;
	JsonVariant jvalue = (*root)[key];
	if (!jvalue.isNull())
	{
		if(!jvalue.is<valueType>())
		{
			Serial.println("E: " + key + " is not the right type");
		}
		else
		{
            valueType newValue = (valueType)jvalue.as<valueType>();
            if(*value != newValue)
            {
                *value = newValue;
                checkCallbacks(value, ConfigClass);
            }
			successful = true;
		}
	}
	return successful;
}

bool ConfigManager::loadConfigFromMemory()
{
    #define ERROR_HANDLING(x, key) if(x == false) { Serial.printf("E: Key %s is mandatory", key); delete doc; return false;}
	bool loadOK = false;
	if(SPIFFS.exists(BASE_CONFIG_FILE_NAME))
	{
		File jsonFile = SPIFFS.open(BASE_CONFIG_FILE_NAME, "r");
		if (!jsonFile)
		{
			Serial.println("E: Open config  file failed");
		}
		else
		{
            DynamicJsonDocument* doc = deserializeDynamically(jsonFile, JSON_BUFFER_BASE_CONFIG);
            if(doc != nullptr)
            {
                ERROR_HANDLING(parseValue<bool>(doc, "ENABLE_WIFI", &(WIFI.enabled), C_WIFI), "ENABLE_WIFI")

                if(WIFI.enabled == true)
                {
                    JsonObject WIFI_object;
                    ERROR_HANDLING(parseValue<JsonObject>(doc, "WIFI", &WIFI_object), "WIFI")

                    ERROR_HANDLING(parseValue<bool>(&WIFI_object, "ENABLE_BLYNK", &(WIFI.blynk_enabled), C_WIFI), "ENABLE_BLYNK")

                    if(WIFI.blynk_enabled == true)
                    {
                        JsonObject blynk_object;
                        ERROR_HANDLING(parseValue<JsonObject>(&WIFI_object, "BLYNK", &blynk_object), "BLYNK")
                        ERROR_HANDLING(parseValue<char*>(&blynk_object, "AUTH_TOKEN", &(WIFI.blynk_token), C_WIFI), "AUTH_TOKEN")
                        ERROR_HANDLING(parseValue<char*>(&blynk_object, "SERVER", &(WIFI.blynk_server), C_WIFI), "SERVER")
                    }

                    ERROR_HANDLING(parseValue<bool>(&WIFI_object, "OTA_UPLOAD", &(WIFI.ota_enabled), C_WIFI), "OTA_UPLOAD")
                    ERROR_HANDLING(parseValue<uint16_t>(&WIFI_object, "NUM_RETRIES", &(WIFI.connection_retries), C_WIFI), "NUM_RETRIES")
                    ERROR_HANDLING(parseValue<bool>(&WIFI_object, "SMART_CONFIG", &(WIFI.smart_config_enabled), C_WIFI), "SMART_CONFIG")
                    ERROR_HANDLING(parseValue<char*>(&WIFI_object, "HOST_NAME", &(WIFI.host_name), C_WIFI), "HOST_NAME")
                    ERROR_HANDLING(parseValue<char*>(&WIFI_object, "WIFI_SSID", &(WIFI.ssid), C_WIFI), "WIFI_SSID")
                    ERROR_HANDLING(parseValue<char*>(&WIFI_object, "WIFI_PW", &(WIFI.pw), C_WIFI), "WIFI_PW")
                }
                { // Color config
                    JsonObject colors_object;
                    ERROR_HANDLING(parseValue<JsonObject>(doc, "COLORS", &colors_object), "COLORS")
                    ERROR_HANDLING(parseValue<uint32_t>(&colors_object, "DEFAULT_HOUR", &(Colors.default_hour), C_COLORS), "DEFAULT_HOUR")
                    ERROR_HANDLING(parseValue<uint32_t>(&colors_object, "DEFAULT_MINUTE", &(Colors.default_minute), C_COLORS), "DEFAULT_MINUTE")
                    ERROR_HANDLING(parseValue<uint32_t>(&colors_object, "DEFAULT_INTERNAL", &(Colors.default_internal), C_COLORS), "DEFAULT_INTERNAL")
                    ERROR_HANDLING(parseValue<uint32_t>(&colors_object, "DEFAULT_SEPARATION_DOT", &(Colors.default_separation_dot), C_COLORS), "DEFAULT_SEPARATION_DOT")
                    ERROR_HANDLING(parseValue<uint32_t>(&colors_object, "OTA_UPDATE", &(Colors.ota_update), C_COLORS), "OTA_UPDATE")
                    ERROR_HANDLING(parseValue<uint32_t>(&colors_object, "WIFI_CONNECTING", &(Colors.wifi_connecting), C_COLORS), "WIFI_CONNECTING")
                    ERROR_HANDLING(parseValue<uint32_t>(&colors_object, "WIFI_CONNECTION_SUCCESSFUL", &(Colors.wifi_connection_successful), C_COLORS), "WIFI_CONNECTION_SUCCESSFUL")
                    ERROR_HANDLING(parseValue<uint32_t>(&colors_object, "WIFI_SMART_CONFIG", &(Colors.wifi_smart_config), C_COLORS), "WIFI_SMART_CONFIG")
                    ERROR_HANDLING(parseValue<uint32_t>(&colors_object, "ERROR", &(Colors.error), C_COLORS), "ERROR")
                }

                Serial.println("Config parsed successfully");
                delete doc; //delete the dynamically allocated document after all values have been stored in variables
                loadOK = true;
            }
			jsonFile.close();
		}
	}
	else
	{
        Serial.printf("E: Config file %s does not exist on the filesystem yet. Please create it first\n\r", BASE_CONFIG_FILE_NAME);
		loadOK = false;
	}
	return loadOK;
}

void ConfigManager::registerOnChangedCallback(void* Property, propertyChangedCallback Callback)
{
    changedEventCallback* newCallback = new changedEventCallback{.callback = Callback, .property = Property, .configClass = 0};
    eventCallbacks.add(newCallback);
}

void ConfigManager::registerOnChangedCallback(uint8_t ConfigClass, propertyChangedCallback Callback)
{
    changedEventCallback* newCallback = new changedEventCallback{.callback = Callback, .property = nullptr, .configClass = ConfigClass};
    eventCallbacks.add(newCallback);
}

void ConfigManager::unregisterOnChangedCallback(propertyChangedCallback Callback, void* Property)
{
    for (int i = 0; i < eventCallbacks.size(); i++)
    {
        if(eventCallbacks[i]->callback == Callback && (Property == nullptr || eventCallbacks[i]->property == Property))
        {
            eventCallbacks.remove(i);
            return;
        }
    }
}