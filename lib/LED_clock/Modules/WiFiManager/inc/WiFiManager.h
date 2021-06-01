/**
 * \file WiFiManager.h
 * \author Florian Laschober
 * \brief Adaption of the code from https://github.com/Hraph/ESP32WiFiManager
 */

#ifndef __WIFI_MANAGER_H_
#define __WIFI_MANAGER_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include "ConfigManager.h"
#include "DisplayManager.h"

#define WEBSERVER_PORT 	80
#define DNS_PORT		53
#define AP_SSID			"LED-Pixel clock fallback AP"
#define AP_PW			"0123456789"
#define CONNECTION_TIMEOUT	30000

class WiFiManager
{
private:
	AsyncWebServer* server;
	DNSServer* dnsServer;
	ConfigManager* config;
	DisplayManager* ShelfDisplays;

	bool connect;
	String WIFI_SSID;
	String WIFI_PW;
	wifi_event_id_t reconnectEvent;

	static WiFiManager* currentInstance;
	WiFiManager();

	void handleRoot(AsyncWebServerRequest *request);
	void handleNotFound(AsyncWebServerRequest *request);
	String saveWiFiSettings(ConfigManager::ConfigType type, JsonObject* json);
	void handleWifiSubmit(AsyncWebServerRequest *request, JsonVariant &json);
	void handleSaveUnavailable(AsyncWebServerRequest *request, JsonVariant &json);
	void startWebInterface();
	void stopAnimation();
	void setDisplay(DisplayManager* display);
	uint8_t waitForConnectResult();
	int connectWifi(String ssid, String pass);
	bool startConfigPortal();
	void setupConfigPortal();
	bool captivePortal(AsyncWebServerRequest *request);
	String saveSettings(ConfigManager::ConfigType type, JsonObject* json);
	void tryToReconnect(WiFiEvent_t event, WiFiEventInfo_t info);
public:
	static WiFiManager* getInstance();
	~WiFiManager();
	bool autoConnect();
	bool autoConnect(DisplayManager* display);
	void startWebUI();
};



#endif