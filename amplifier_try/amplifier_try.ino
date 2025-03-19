#include <Arduino.h>
#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
#include "Vocab_US_TI99.h"
#include "Vocab_US_Clock.h"

Talkie voice;

void setup() {
  Serial.begin(115200);
  // Initialize the voice system (optional, but makes sure the system is ready to speak)
  voice.say(spPAUSE1);
}

void loop() {
  // Speak the phrases in sequence
  voice.say(spPAUSE2);   // Pause between phrases
  voice.say(spc_GOOD);   // "Good"
  voice.say(spc_EVENING); // "Evening"
  voice.say(spPAUSE1);   // Short pause

  voice.say(spc_THE);    // "The"
  voice.say(spc_TIME);   // "Time"
  voice.say(spc_IS);     // "Is"
  voice.say(spc_SEVEN);  // "Seven"
  voice.say(spc_FOURTY); // "Forty"
  voice.say(spc_FIVE);   // "Five"
  voice.say(spc_P_M_);   // "PM"
  voice.say(spPAUSE1);   // Short pause

  // Add a delay to avoid repeating too quickly (you can adjust this delay to your preference)
  delay(5000);
}
