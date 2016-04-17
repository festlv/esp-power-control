#include <user_config.h>
#include <SmingCore/SmingCore.h>

#include "web_config.h"
#include "AppSettings.h"

Timer ten_hz_timer;

void init()
{
    //disable debug output while we're mounting spiffs
    //this has to be done because we can't access settings before mounting
//    system_set_os_print(0);
//
    Serial.begin(115200);
    Serial.systemDebugOutput(true);
    system_set_os_print(1);

	int slot = rboot_get_current_rom();

	if (slot == 0) {
		spiffs_mount_manual(RBOOT_SPIFFS_0 + 0x40200000, SPIFF_SIZE);
	} else {
		spiffs_mount_manual(RBOOT_SPIFFS_1 + 0x40200000, SPIFF_SIZE);
	}

	AppSettings.load();

    webserver_init();

    pinMode(RESTORE_PARAMETERS_PIN, INPUT_PULLUP);

    ten_hz_timer.initializeMs(100, app_settings_tick_10hz).start();
}
