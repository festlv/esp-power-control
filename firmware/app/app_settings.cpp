#include <SmingCore/SmingCore.h>
#include "user_config.h"

#include "AppSettings.h"

ApplicationSettingsStorage AppSettings;

void app_settings_tick_10hz() {

    //counts number of ticks when button was pressed, initiates parameter
    //restore. Blinks both three times, and then reboots after pin is released
    
    static unsigned int ticks_pressed = 0;
    static bool wait_release = false;

    if (digitalRead(RESTORE_PARAMETERS_PIN) == LOW) {
        ticks_pressed++;
        if (ticks_pressed >= 30 && !wait_release) {
            AppSettings.restore();
            AppSettings.save();
            digitalWrite(UART_LED_PIN, HIGH);
            delay(100);
            digitalWrite(NET_LED_PIN, HIGH);
            delay(100);
            digitalWrite(NET_LED_PIN, LOW);
            delay(100);
            digitalWrite(UART_LED_PIN, LOW);
            wait_release = true;
        }
    } else {
        ticks_pressed = 0;
        if (wait_release) {
            delay(1000);
            System.restart();
        }
    }

}

void ApplicationSettingsStorage::restore() {
        auth_password = DEFAULT_AUTH_PASSWORD;
        ota_link = DEFAULT_OTA_LINK;
        ap_password = DEFAULT_AP_PASSWORD;
        ap_ssid = DEFAULT_AP_SSID;
        ssid = "";
        password ="";
        dhcp = true;
}

void ApplicationSettingsStorage::load()
{
    DynamicJsonBuffer jsonBuffer;
    ap_password = DEFAULT_AP_PASSWORD;
    ap_ssid = DEFAULT_AP_SSID;
    auth_password = DEFAULT_AUTH_PASSWORD;

    if (exist())
    {
        int size = fileGetSize(APP_SETTINGS_FILE);
        char* jsonString = new char[size + 1];
        fileGetContent(APP_SETTINGS_FILE, jsonString, size + 1);
        JsonObject& root = jsonBuffer.parseObject(jsonString);

        JsonObject& network = root["network"];
        ssid = network["ssid"].asString();
        password = network["password"].asString();

        dhcp = network["dhcp"];
        
        ip = network["ip"].asString();
        netmask = network["netmask"].asString();
        gateway = network["gateway"].asString();

        ap_password = network["ap_password"].asString();
        ap_ssid = network["ap_ssid"].asString();

        auth_password = root["auth_password"].asString();

        delete[] jsonString;
    }
}

void ApplicationSettingsStorage::save()
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    JsonObject& network = jsonBuffer.createObject();

    root["network"] = network;

    root["auth_password"] = auth_password.c_str();

    network["ssid"] = ssid.c_str();
    network["password"] = password.c_str();

    network["dhcp"] = dhcp;

    // Make copy by value for temporary string objects
    network["ip"] = ip.toString();
    network["netmask"] = netmask.toString();
    network["gateway"] = gateway.toString();

    network["ap_ssid"] = ap_ssid.c_str();
    network["ap_password"] = ap_password.c_str();

    //TODO: add direct file stream writing
    String rootString;
    root.printTo(rootString);
    fileSetContent(APP_SETTINGS_FILE, rootString);
}

bool ApplicationSettingsStorage::exist()
{
    return fileExist(APP_SETTINGS_FILE); 
}
