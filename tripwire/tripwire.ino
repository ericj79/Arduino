// with the laser the analog read goes down to ~100. Without it is ~750.
// 250 should be a safe threshold


/** 
 * Using a Adafruit trinket wire up the following:
 * 5V to '+' bar
 * Pin # 1 (DIGITAL 1) to plus of buzzer (piezo buzzer)
 * GND to '-' bar
 * buzzer negative to '-' bar
 * laser red wire to '+' bar
 * laser blue wire to '-' bar
 * One side of photoresister to '-' bar
 * Other side of photoresister to a row on the bread board
 * Pin #2  (ANALOG 1) to same row of bread board
 * 1k ohm resistor to same row of bread board
 * other end of 1k ohm resister to '+' bar
 */

#define THRESHOLD  250  // Threshold to either set or break the trip wire

#define SPEAKER    1    // Speaker connected to this DIGITAL pin #
#define PHOTOCELL  1    // CdS photocell connected to this ANALOG pin #

#define BEEP_BREAK 1000 // pitch of beep for warning
#define BEEP_SET1  500  // pitch when laser is set
#define BEEP_SET2  2000 // pitch when laser is set

boolean isSet = false;

void setup() {
  // Set SPEAKER pin to output to drive the piezo buzzer (important)
  pinMode(SPEAKER, OUTPUT);
}

void loop() {
  // Read PHOTOCELL analog pin for the current CdS divider voltage
  int reading = analogRead(PHOTOCELL);
  if (isSet && reading > THRESHOLD) {
    // the trip wire was broken
    isSet = false;
    soundWarning();
  } else if (!isSet && reading < THRESHOLD) {
    isSet = true;
    beep(SPEAKER, BEEP_SET1, 100);
    beep(SPEAKER, BEEP_SET2, 100);
  }
  delay(100);
}

void soundWarning() {
  int  count;
  for (count = 0; count < 4; count++) {
    beep(SPEAKER, BEEP_BREAK, 500);
    delay(500);
  }
}

// The sound-producing function
void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{ // http://web.media.mit.edu/~leah/LilyPad/07_sound_code.html
  int  x;
  long delayAmount = (long)(1000000 / frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));
  for (x = 0; x < loopTime; x++) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(delayAmount);
  }
}

