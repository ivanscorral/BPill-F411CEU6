#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  while (!SerialUSB)
    ;
  SerialUSB.println("Hello World!");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT_ANALOG);
  digitalWrite(LED_BUILTIN, HIGH);
  analogReadResolution(12);
}
double adcToVoltageMv(uint16_t adc) {
  double voltage = adc * 3300 / 4095.0;
  if (voltage < 200) {
    voltage -= 10;
  }if (voltage < 50) {
    voltage -= 20;
   
  }
   if (voltage < 0) {
      voltage = 0;
    }
  return voltage;
}

double voltageToCurrentMa(double voltage) {
  SerialUSB.print("voltage: ");
  SerialUSB.println(voltage);
  return voltage * 1.99350649351 * 2;
}

double avgAdc(uint8_t pin, uint8_t samples) {
  double avg = 0.0;
  for (uint8_t i = 0; i < samples; i++) {
    avg += adcToVoltageMv(analogRead(pin)) / 1.01;
    delay(5);
  }
  avg = avg / samples;
  return avg;
}

void loop() {
  // put your main code here, to run repeatedly:
  double val = avgAdc(A0, 64);
  SerialUSB.print(val, 4);
  SerialUSB.print(" mV, ");
  SerialUSB.print(voltageToCurrentMa(val), 4);
  SerialUSB.println(" mA");
  delay(1000);
}