#include <AccelStepper.h>
#include <MPU9250_asukiaaa.h>
#include <OneButton.h>

#define SDA_PIN 8
#define SCL_PIN 9
#define MOTOR_PIN_1 0
#define MOTOR_PIN_2 1
#define MOTOR_PIN_3 2
#define MOTOR_PIN_4 3
#define BUTTON_PIN 5

#define MotorInterfaceType 8 // 4 wire motor in half step mode (4096 steps)
AccelStepper motor = AccelStepper(MotorInterfaceType, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4);

MPU9250_asukiaaa mpu;
float aX, aY, aZ;

OneButton button;
bool measureState = false;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  Wire.begin(SDA_PIN, SCL_PIN);
  mpu.setWire(&Wire);

  button.setup(BUTTON_PIN, INPUT_PULLUP, true);
  button.attachClick(singleClick);
  //button.attachDoubleClick(doubleClick);
  
  mpu.beginAccel();
  motor.setMaxSpeed(100);


}

void loop() {
  
  button.tick();
  delay(50);

}

void singleClick() {
  int result;

  motor.setCurrentPosition(0);
  while (motor.currentPosition() <= 4096 && measureState) {
    motor.moveTo(motor.currentPosition() + 8);
    delay(1000);

    result = mpu.accelUpdate();
    if (result == 0) {
      aX = mpu.accelX();
      aY = mpu.accelY();
      aZ = mpu.accelZ();
    } else {
      Serial.println("Cannot read accel values " + String(result));
    }
    Serial.write(int(aX * 1000));
    Serial.print(",");
    Serial.write(int(aY * 1000));
    Serial.print(",");
    Serial.write(int(aZ * 1000));
    Serial.print("\n");
    delay(100);
  }
  Serial.println("0,0,0");
  motor.moveTo(0);
}

