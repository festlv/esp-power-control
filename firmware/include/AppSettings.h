#pragma once

#include <user_config.h>
#include <SmingCore/SmingCore.h>


#define APP_SETTINGS_FILE ".settings.conf" // leading point for security reasons :)

#define DEFAULT_OTA_LINK FW_UPDATE_LINK

//empty means autogenerated 
#define DEFAULT_AP_SSID ""

//empty- open network
#define DEFAULT_AP_PASSWORD ""

#define RESTORE_PARAMETERS_PIN 0

#define UART_LED_PIN 13
#define NET_LED_PIN 12

#ifndef DEFAULT_AUTH_PASSWORD
#define DEFAULT_AUTH_PASSWORD "authpasskey"
#endif

class ApplicationSettingsStorage
{

public:

    String auth_password;

	String ssid;
	String password;

    String ap_password;
    String ap_ssid;
    
	bool dhcp = true;

	IPAddress ip;
	IPAddress netmask;
	IPAddress gateway;

    String ota_link;

    void restore();

	void load();
	
	void save();

	bool exist();
};

extern ApplicationSettingsStorage AppSettings;

void app_settings_tick_10hz();
