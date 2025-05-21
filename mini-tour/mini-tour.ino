#include <AccelStepper.h>
#include <MPU9250_asukiaaa.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define motorPin1 8
#define motorPin2 9
#define motorPin3 10
#define motorPin4 11

#define MotorInterfaceType 8 // 4 wire motor in half step mode (4096 steps)
AccelStepper motor = AccelStepper(MotorInterfaceType, motorPin1, motorPin2, motorPin3, motorPin4);

MPU9250_asukiaaa mpu;
float aX, aY, aZ;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  Wire.begin(SDA_PIN, SCL_PIN);
  mpu.setWire(&Wire);

  mpu.beginAccel();

}

void loop() {
  int result;


}
