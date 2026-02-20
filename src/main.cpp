#include <Arduino.h>

#define BUTTON 9

volatile int16_t counter = 0;
volatile bool pressed = false;

void IRAM_ATTR buttonISR() {
  counter++;
  pressed = true;
}

void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.println("\n========================================");
  Serial.println("   ESP32-S3 Button Bounce");
  Serial.println("========================================");
  Serial.printf("Board: ESP32-S3-WROOM-1\n");
  Serial.printf("CPU Freq: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
  Serial.println("========================================\n");

  // ext button with internal pull-down resistor
  pinMode(BUTTON, INPUT); 
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonISR, RISING);
}

void loop() {
  if (pressed) {
    pressed = false;
    Serial.println("\nButton Pressed! Count: " + String(counter));
  }
}
