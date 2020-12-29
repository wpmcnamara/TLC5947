#include <TLC5947.h>

#define LATCH_PIN 18

TLC5947 driver(LATCH_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(100);
  driver.begin();
  pinMode(MISO, INPUT_PULLUP);
  SPI.begin();


}

void loop() {
    int start=15;
    int fade=0;
    int value=0;
    int led=15;
    while(1) {
        if(led==start) {
            fade=6;
            value=0xF00;
            start--;
            if(start<15) {
                start=23;
            }
            driver.update();
            delay(100);
        }
        driver.channel(led,value);
        if(fade) {
            fade--;
            value=value>>2;
        }
        led++;
        if(led==24) {
            led=15;
        }
        
    }
}