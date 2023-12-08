#include <Wire.h>

// Q - left
// E - right
// W - button release
#define EncoderPinCLK PA1
#define EncoderPinDT PA2
#define EncoderPinSW PA3

int8_t currentState;
int8_t previousStateCLK;
int8_t previousStateSW;
int8_t debounceSW;

void onRequest();
void buffAdd(uint8_t c);

void setup() {
  Wire_beginSlave(0x11);
  // Wire_setClock(400000);
  Wire_onRequest(onRequest);

  // Set encoder pins as inputs
  pinMode(EncoderPinCLK, INPUT);
  pinMode(EncoderPinDT, INPUT);
  pinMode(EncoderPinSW, INPUT_PULLUP);

  // Read the initial state of EncoderPinCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(EncoderPinCLK);
  previousStateSW = digitalRead(EncoderPinSW);

  debounceSW = 3;
}

void loop() {
  currentState = digitalRead(EncoderPinCLK);
  if (currentState != previousStateCLK) {

    if (digitalRead(EncoderPinDT) != currentState) {
      buffAdd('E'); // clockwise
    } else {
      buffAdd('Q'); // counter clockwise
    }
  }
  previousStateCLK = currentState;

  currentState = digitalRead(EncoderPinSW);
  if (currentState == LOW && debounceSW > 0) {
    debounceSW--;
  } else if (currentState == HIGH && debounceSW < 3) {
    debounceSW++;
  }
  currentState = debounceSW < 2? LOW: HIGH;
  if (currentState == HIGH && previousStateSW == LOW) {
    buffAdd('W'); // switch unclicked
  }
  previousStateSW = currentState;
}
