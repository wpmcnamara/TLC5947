
#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-variable"

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#endif

#include <SPI.h>

#pragma pack(push, 1)

typedef struct TLC5947_channel_pair {
    union {
        uint8_t reg[3];
        struct {
            uint16_t low:12,
                     high:12;
        };
    };
} TLC5947_channel_pair_t;

class TLC5947 {
    public:
    TLC5947(uint8_t latch_pin);
    void begin();
    void channel(uint8_t chan, uint16_t value);
    uint16_t channel(uint8_t);
    void update();
    TLC5947_channel_pair_t pair[12];
    private:
    
    uint8_t _latch;
};


