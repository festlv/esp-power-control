#pragma once
#include <stdint.h>
#include <stdbool.h>

#define POWER_OUT_PIN   14
#define RESET_OUT_PIN   16

#define POWER_IN_PIN    4
#define ACT_IN_PIN      5


class PowerManager
{
public:
    PowerManager(uint8_t _power_out_pin, uint8_t _reset_out_pin,
            uint8_t _power_in_pin, uint8_t _act_in_pin);

    //should be called at 100Hz, does the housekeeping
    void update(void);
    
    void power_on(void);

    void power_off(void);

    void reset(void);

    bool get_power_state(void)
    {
        return power_high;
    }

    //system activity in percent
    uint8_t get_activity(void)
    {
        return prev_act_high_events / 2;
    }

private:
    uint8_t power_out_pin;
    uint8_t reset_out_pin;

    uint8_t power_in_pin;
    uint8_t act_in_pin;

    uint64_t cycle_counter;

    uint64_t clear_power_output;
    uint64_t clear_reset_output;

    uint16_t  act_high_events;
    uint16_t  prev_act_high_events;
    bool     power_high;
};
