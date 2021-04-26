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

	BaseConfig 	= new DynamicJsonDocument(JSON_BUFFER_BASE_CONFIG);
	ColorConfig = new DynamicJsonDocument(JSON_BUFFER_COLOR_CONFIG);
	HWConfig 	= new DynamicJsonDocument(JSON_BUFFER_HW_CONFIG);

	bool loadSuccessful = true;
    loadSuccessful &= loadConfigFromMemory(BASE_CONFIG_FILE_NAME, BaseConfig);
	loadSuccessful &= loadConfigFromMemory(COLOR_CONFIG_FILE_NAME, ColorConfig);
	loadSuccessful &= loadConfigFromMemory(HW_CONFIG_FILE_NAME, HWConfig);
	if(loadSuccessful == false)
	{
		Serial.println("[E]: Loading of json config from filesystem unsuccessful");
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
T ConfigManager::getProperty(DynamicJsonDocument* root, char* key)
{
	JsonVariant jvalue = (*root)[key];
	if (!jvalue.isNull())
	{
		if(!jvalue.is<T>())
		{
			Serial.printf("[E]: BaseConfig key \"%s\" is not the correct type", key);
		}
		else
		{
			return jvalue.as<T>();
		}
	}
	return nullptr;
}

template<typename T>
T ConfigManager::getBaseProperty(char* key)
{
	return getProperty<T>(BaseConfig, key);
}

template<typename T>
T ConfigManager::getColorProperty(char* key)
{
	return getProperty<T>(ColorConfig, key);
}

template<typename T>
T ConfigManager::getHWProperty(char* key)
{
	return getProperty<T>(HWConfig, key);
}

template<typename T>
bool ConfigManager::setBaseProperty(char* key, T value)
{
	if(BaseConfig->containsKey(key))
	{
		return (*BaseConfig)[key].set(key);
	}
	return false;
}

bool ConfigManager::setBaseProperty(JsonPair& keyValuePair)
{
	if(BaseConfig->containsKey(keyValuePair.key()))
	{
		return (*BaseConfig)[keyValuePair.key()].set(keyValuePair.value());
	}
	return false;
}