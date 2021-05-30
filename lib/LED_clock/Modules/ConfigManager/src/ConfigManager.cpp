/**
 * \file ConfigManager.cpp
 * \author Florian Laschober
 * \brief Implementation of the ConfigManager class member functions
 */


#include "ConfigManager.h"

ConfigManager* ConfigManager::instance = nullptr;

//Template types that can be used

template bool ConfigManager::getProperty<bool>(ConfigType config, const char* key);
template int ConfigManager::getProperty<int>(ConfigType config, const char* key);
template const char* ConfigManager::getProperty<const char*>(ConfigType config, const char* key);

ConfigManager::ConfigManager()
{
    if(!SPIFFS.begin(true))
	{
		Serial.println("Filesystem mount failed aborting...");
		abort();
	}

	Serial.printf("Filesystem mount successful; %d out of %d bytes used\n\r", SPIFFS.usedBytes(), SPIFFS.totalBytes());

	BaseConfig 	= new DynamicJsonDocument(JSON_BUFFER_BASE_CONFIG);
	ColorConfig = new DynamicJsonDocument(JSON_BUFFER_COLOR_CONFIG);
	HWConfig 	= new DynamicJsonDocument(JSON_BUFFER_HW_CONFIG);
	EventIDs 	= new DynamicJsonDocument(JSON_BUFFER_EVENT_IDS);

	bool loadSuccessful = true;
    loadSuccessful &= loadConfigFromMemory(BASE_CONFIG_FILE_NAME, BaseConfig);
	loadSuccessful &= loadConfigFromMemory(COLOR_CONFIG_FILE_NAME, ColorConfig);
	loadSuccessful &= loadConfigFromMemory(HW_CONFIG_FILE_NAME, HWConfig);
	loadSuccessful &= loadConfigFromMemory(EVENT_IDS_FILE_NAME, EventIDs);
	if(loadSuccessful == false)
	{
		Serial.println("[E]: Loading of json config from filesystem unsuccessful");
	}
	for (uint8_t i = 0; i < _CONFIG_CLASS_ID_LENGTH; i++)
	{
		configClassWasUpdated[i] = false;
	}
	for (uint8_t i = 0; i < _CONFIG_TYPE_LENGTH; i++)
	{
		configNeedsSaving[i] = false;
	}
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
		Serial.println("[D]: ConfigManager instance created");
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

bool ConfigManager::deserializeDynamically(fs::File &input, DynamicJsonDocument* doc)
{
	if(doc == nullptr)
	{
		return false;
	}
	bool successful = false;
	bool firstTry = true;
	size_t DocumentSize = (*doc).size();

	do
	{
		if(firstTry == true)
		{
			firstTry = false;
		}
		else
		{
			doc = new DynamicJsonDocument(DocumentSize);
		}

		DeserializationError error = deserializeJson(*doc, input);
		if (error)
		{
			if (error.code() == DeserializationError::NoMemory)
			{
				delete doc;
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

    return successful;
}

bool ConfigManager::loadConfigFromMemory(const char* filename, DynamicJsonDocument* doc)
{
    #define ERROR_HANDLING(x, key) if(x == false) { Serial.printf("E: Key %s is mandatory", key); delete doc; return false;}
	bool loadOK = false;
	if(SPIFFS.exists(filename))
	{
		File jsonFile = SPIFFS.open(filename, "r");
		if (!jsonFile)
		{
			Serial.println("E: Open config  file failed");
		}
		else
		{
            if(deserializeDynamically(jsonFile, doc) == true)
            {
				loadOK = true;
            }
			jsonFile.close();
		}
	}
	else
	{
        Serial.printf("E: Config file %s does not exist on the filesystem yet. Please create it first\n\r", filename);
		loadOK = false;
	}
	return loadOK;
}


template<typename T>
T ConfigManager::getProperty(DynamicJsonDocument* root, const char* key)
{
	JsonVariant jvalue = (*root)[key];
	if (!jvalue.isNull())
	{
		if(!jvalue.is<T>())
		{
			Serial.printf("[E]: BaseConfig key \"%s\" is not the correct type\n\r", key);
		}
		else
		{
			return jvalue.as<T>();
		}
	}
	return  T();
}

template<typename T>
T ConfigManager::getProperty(ConfigType config, const char* key)
{
	return getProperty<T>(getDocument(config), key);
}

template<typename T>
bool ConfigManager::setProperty(ConfigType config, char* key, T value)
{
	DynamicJsonDocument* doc = getDocument(config);
	if(doc->containsKey(key))
	{
		return (*doc)[key].set(key);
	}
	Serial.printf("[E]: Config does not contain key %s\n\r", key);
	return false;
}

DynamicJsonDocument* ConfigManager::getDocument(ConfigType config)
{
	switch (config)
	{
	case BASE_CONFIG:
		return BaseConfig;
	case COLOR_CONFIG:
		return ColorConfig;
	case HW_CONFIG:
		return HWConfig;
	default:
		return nullptr;
	}
}

const char* ConfigManager::getFileName(ConfigType config)
{
	switch (config)
	{
	case BASE_CONFIG:
		return BASE_CONFIG_FILE_NAME;
	case COLOR_CONFIG:
		return COLOR_CONFIG_FILE_NAME;
	case HW_CONFIG:
		return HW_CONFIG_FILE_NAME;
	default:
		return nullptr;
	}
}

bool ConfigManager::setProperty(JsonPair& keyValuePair, ConfigType config)
{
	if(config >= _CONFIG_TYPE_LENGTH)
	{
		Serial.printf("[E]: Config id %d is higher than maximum allowed of %d\n\r", config, _CONFIG_TYPE_LENGTH);
		return false;
	}
	DynamicJsonDocument* doc = getDocument(config);
	if(doc == nullptr)
	{
		Serial.printf("[E]: Config with config id %d was invalid\n\r", config);
		return false;
	}
	if(doc->containsKey(keyValuePair.key()))
	{
		if((*doc)[keyValuePair.key()] != keyValuePair.value())
		{
			//TODO: find a better solution for this
			uint8_t eventID = (*EventIDs)[keyValuePair.key()];
			configClassWasUpdated[eventID] = true;
			configNeedsSaving[config] = true;
			return (*doc)[keyValuePair.key()].set(keyValuePair.value());
		}
		else
		{
			return true;
		}
	}
	Serial.printf("[E]: Config does not contain key %s\n\r", keyValuePair.key().c_str());
	return false;
}

void ConfigManager::saveConfigPersistent(ConfigType config)
{
	if(config >= _CONFIG_TYPE_LENGTH)
	{
		return;
	}
	if(configNeedsSaving[config])
	{
		File configFile = SPIFFS.open(getFileName(config), FILE_WRITE);
		serializeJson(*getDocument(config), configFile);
		configFile.close();
		configNeedsSaving[config] = false;
	}
	else
	{
		Serial.printf("[I]: Skipped saving of %s to memory as there was no change.\n\r", getFileName(config));
	}
}

void ConfigManager::applyChanges()
{
	uint8_t updatedConfigClasses = 0x00;
	for (uint8_t i = 0; i < _CONFIG_CLASS_ID_LENGTH; i++)
	{
		if(configClassWasUpdated[i] == true)
		{
			updatedConfigClasses |= 1 << i;
			configClassWasUpdated[i] = false;
		}
	}
	checkCallbacks(updatedConfigClasses);
}

void ConfigManager::checkCallbacks(uint8_t ConfigEvent)
{
	bool needsRestart = false;
    for (int i = 0; i < eventCallbacks.size(); i++)
    {
		if((eventCallbacks.get(i)->configEvent & ConfigEvent) != 0x00)
		{
			needsRestart |= eventCallbacks.get(i)->callback(this);
		}
    }
	if(needsRestart == true)
	{
		ESP.restart();
	}
}

void ConfigManager::registerOnChangedCallback(uint8_t ConfigEvent, propertyChangedCallback Callback)
{
    changedEventCallback* newCallback = new changedEventCallback{.callback = Callback, .configEvent = ConfigEvent};
    eventCallbacks.add(newCallback);
}

void ConfigManager::unregisterOnChangedCallback(propertyChangedCallback Callback)
{
    for (int i = 0; i < eventCallbacks.size(); i++)
    {
        if(eventCallbacks.get(i)->callback == Callback)
        {
            eventCallbacks.remove(i);
        }
    }
}