#include <SHT21P.h>

SHT21P sht(A4, A3, A2);

void setup() {
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);

  Serial.begin(115200);

  sht.powerUp();

  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
}

int setpoint = 55;
long last = 0;
int state = 0;
void loop() {
  static float temp, rh;
  if (millis() - last >= 1000) {
    last = millis();
    temp = sht.readTemp();
    rh = sht.readRH();
    Serial.print(setpoint);
    Serial.print(", ");
    Serial.print(temp);
    Serial.print(", ");
    Serial.print(rh);
    Serial.print(", ");
    Serial.println(state);
  }

  if(temp <= setpoint -1) {
    if(temp > 10) {
      digitalWrite(6, HIGH);
      state = 1;
    } else {
      digitalWrite(6, LOW);
      state = 0;
    }
  } else if(temp >= setpoint +1) {
    digitalWrite(6, LOW);
    state = 0;
  }

}
