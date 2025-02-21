//https://www.youtube.com/watch?v=phrEH-wW3qg

//digital pin 7

#include <Arduino.h>

#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
#include "Vocab_US_TI99.h"
#include "Vocab_US_Clock.h"
Talkie voice;

void setup() {
       Serial.begin(115200);

}
void loop() {
    // voice.say(spPAUSE2);
    // voice.say(sp2_DANGER);
    // voice.say(sp2_DANGER);
    // voice.say(spPAUSE2);
    // voice.say(sp2_RED);
    // voice.say(sp2_ALERT);
    // voice.say(spPAUSE2);
    // voice.say(sp2_MOTOR);
    // voice.say(sp2_IS);
    // voice.say(sp2_ON);
    // voice.say(sp2_FIRE);

    // US Clock words
    voice.say(spPAUSE2);
    voice.say(spc_GOOD);
    voice.say(spc_EVENING);
    voice.say(spPAUSE1);
    voice.say(spc_THE);
    voice.say(spc_TIME);
    voice.say(spc_IS);
    voice.say(spc_SEVEN);
    voice.say(spc_FOURTY);
    voice.say(spc_FIVE);
    voice.say(spc_P_M_);
    voice.say(spPAUSE1);
  

}