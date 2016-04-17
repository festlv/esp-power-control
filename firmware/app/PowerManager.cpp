#include <SmingCore/SmingCore.h>
#include "AppSettings.h"
#include "PowerManager.h"

PowerManager::PowerManager(uint8_t _power_out_pin, uint8_t _reset_out_pin,
            uint8_t _power_in_pin, uint8_t _act_in_pin) :
    power_out_pin(_power_out_pin),
    reset_out_pin(_reset_out_pin),
    power_in_pin(_power_in_pin),
    act_in_pin(_act_in_pin),
    cycle_counter(0),
    clear_power_output(0),
    clear_reset_output(0),
    act_high_events(0),
    prev_act_high_events(0),
    power_high(false)
{
    pinMode(power_out_pin, OUTPUT);
    digitalWrite(power_out_pin, LOW);

    pinMode(reset_out_pin, OUTPUT);
    digitalWrite(reset_out_pin, LOW);

    pinMode(act_in_pin, INPUT);
    pinMode(power_in_pin, INPUT);

    pinMode(NET_LED_PIN, OUTPUT);
    pinMode(UART_LED_PIN, OUTPUT);

    digitalWrite(NET_LED_PIN, HIGH);
    digitalWrite(UART_LED_PIN, HIGH);

    delay(100);

    digitalWrite(NET_LED_PIN, LOW);
    digitalWrite(UART_LED_PIN, LOW);
}

void PowerManager::update(void)
{
    cycle_counter++;

    if (clear_power_output == cycle_counter)
    {
        digitalWrite(power_out_pin, LOW);
        clear_power_output = 0;
        debugf("PM: clearing power output\n");
    }

    if (clear_reset_output == cycle_counter)
    {
        digitalWrite(reset_out_pin, LOW);
        clear_reset_output = 0;
        debugf("PM: clearing reset output\n");
    }
    
    power_high = digitalRead(power_in_pin) == HIGH ? true : false;
     
    if (digitalRead(act_in_pin) == HIGH)
    {
        act_high_events++;
    }

    //copy the activity level into another variable, reset act_high
    if (cycle_counter % 200 == 0)
    {
        prev_act_high_events = act_high_events;
        act_high_events = 0;
    }

    digitalWrite(NET_LED_PIN, digitalRead(reset_out_pin));
    digitalWrite(UART_LED_PIN, digitalRead(power_out_pin));
}

void PowerManager::power_on(void)
{
    debugf("PM: powering on\n");
    digitalWrite(power_out_pin, HIGH);
    clear_power_output = cycle_counter + 30;
}
void PowerManager::power_off(void)
{
    debugf("PM: powering off\n");
    digitalWrite(power_out_pin, HIGH);
    clear_power_output = cycle_counter + 500;
}

void PowerManager::reset(void)
{
    debugf("PM: restarting\n");
    digitalWrite(reset_out_pin, HIGH);
    clear_reset_output = cycle_counter + 30;
}
