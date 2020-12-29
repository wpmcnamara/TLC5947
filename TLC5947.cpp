#include <TLC5947.h>

TLC5947::TLC5947(uint8_t latch_pin) :
    _latch(latch_pin)
{
    for(uint8_t i=0; i<12; i++) {
        pair[i].reg[0]=0;
        pair[i].reg[1]=0;
        pair[i].reg[2]=0;
    }
}

void TLC5947::begin() {
    pinMode(_latch, OUTPUT);
    digitalWrite(_latch, LOW);

}

void TLC5947::channel(uint8_t chan, uint16_t value) {
    uint8_t pair_idx=chan/2;
    uint8_t high_low=chan%2;
    if(high_low) {
        pair[pair_idx].high=value;
    } else {
        pair[pair_idx].low=value;
    }
}

void TLC5947::update() {
    SPISettings settings(2000000, MSBFIRST, SPI_MODE0); 
    SPI.beginTransaction(settings);
    for(int group=11; group>=0; group--) {
        for(int sub_group=2; sub_group>=0; sub_group--) {
            SPI.transfer(pair[group].reg[sub_group]);
        }
    }
    SPI.endTransaction();
    digitalWrite(_latch, HIGH);
    digitalWrite(_latch, LOW);

}