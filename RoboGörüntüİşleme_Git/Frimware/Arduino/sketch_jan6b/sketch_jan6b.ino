#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define FREQUENCY 50
#define DEADBAND 1   // <<< TİTREME KESİCİ

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// PCA9685 kanallar
#define HAND      11
#define WRIST     12
#define ELBOW     13
#define SHOULDER  14
#define BASE      15

// Limitler
#define BASE_MIN 0
#define BASE_MAX 180
#define SHOULDER_MIN 0
#define SHOULDER_MAX 180
#define ELBOW_MIN 50
#define ELBOW_MAX 180
#define WRIST_MIN 20
#define WRIST_MAX 140
#define HAND_MIN 0
#define HAND_MAX 180

// [BASE, SHOULDER, ELBOW, WRIST, HAND]
int currentAngle[5] = {90, 0, 180, 90, 90};

bool robotBusy = false;

// PWM 
int angleToPulse(int angle) {
  return map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH)
         * FREQUENCY * 4096 / 1000000;
}

void moveServo(uint8_t ch, int ang) {
  pwm.setPWM(ch, 0, angleToPulse(ang));
}

void smoothMoveAll(
  int baseT, int shoulderT, int elbowT, int wristT, int handT
) {
  int target[5] = {
    constrain(baseT, BASE_MIN, BASE_MAX),
    constrain(shoulderT, SHOULDER_MIN, SHOULDER_MAX),
    constrain(elbowT, ELBOW_MIN, ELBOW_MAX),
    constrain(wristT, WRIST_MIN, WRIST_MAX),
    constrain(handT, HAND_MIN, HAND_MAX)
  };

  int maxDiff = 0;
  for (int i = 0; i < 5; i++) {
    int diff = abs(target[i] - currentAngle[i]);
    if (diff > maxDiff) maxDiff = diff;
  }

  for (int step = 0; step < maxDiff; step++) {
    for (int i = 0; i < 5; i++) {
      int diff = target[i] - currentAngle[i];

      if (abs(diff) > DEADBAND) {
        currentAngle[i] += (diff > 0) ? 1 : -1;
      }
    }

    moveServo(BASE,     currentAngle[0]);
    moveServo(SHOULDER, currentAngle[1]);
    moveServo(ELBOW,    currentAngle[2]);
    moveServo(WRIST,    currentAngle[3]);
    moveServo(HAND,     currentAngle[4]);

    delay(2); 
  }
}


void alma_birakma() {
//sağa git
  smoothMoveAll(30, 175, 90, 75, 45);
  delay(800);
  smoothMoveAll(30, 175, 90, 75, 0);
  delay(800);
//merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

// sola git
  smoothMoveAll(140, 175, 90, 75, 0);
  delay(800);
  smoothMoveAll(140, 175, 90, 75, 45);
  delay(800);
  //çok az yükarı kaldır
  smoothMoveAll(140, 160, 85, 75, 0);
  delay(800);
  //merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

  //sağa git
  smoothMoveAll(10, 175, 90, 75, 45);
  delay(800);
  smoothMoveAll(10, 175, 90, 75, 0);
  delay(800);
//merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);
// sola git

  smoothMoveAll(140, 160, 90, 75, 0);
  delay(800);
  smoothMoveAll(140, 160, 90, 75, 45);
  delay(800);
  //çok az yükarı kaldır
  smoothMoveAll(140, 145, 85, 75, 0);
  delay(800);
  //merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

  /*smoothMoveAll(140, 100, 90, 125, 45);
  delay(800);
  smoothMoveAll(140, 100, 90, 50, 45);
  delay(800);
  smoothMoveAll(170, 100, 90, 50, 45);
  delay(800);
  smoothMoveAll(20, 100, 90, 50, 45);
  delay(800);
  smoothMoveAll(20, 100, 90, 125, 45);
  delay(800);

  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);*/
}

void alma_birakma1() {

 //sağa git
  smoothMoveAll(30, 175, 90, 75, 45);
  delay(800);
  smoothMoveAll(30, 175, 90, 75, 0);
  delay(800);
//merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

// sola git
  smoothMoveAll(150, 175, 90, 75, 0);
  delay(800);
  smoothMoveAll(150, 175, 90, 75, 45);
  delay(800);
  //çok az yükarı kaldır
  smoothMoveAll(150, 160, 85, 75, 45);
  delay(800);
  //merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

  //sağa git
  smoothMoveAll(10, 175, 90, 75, 45);
  delay(800);
  smoothMoveAll(10, 175, 90, 75, 0);
  delay(800);
//merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);
  
// sola git
  smoothMoveAll(120, 175, 90, 75, 0);
  delay(800);
  smoothMoveAll(120, 175, 90, 75, 45);
  delay(800);
    //çok az yükarı kaldır
  smoothMoveAll(120, 160, 85, 75, 45);
  delay(800);
  //merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);


  //sağa git
  smoothMoveAll(0, 175, 90, 75, 45);
  delay(800);
  smoothMoveAll(0, 175, 90, 75, 0);
  delay(800);
//merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);
// sola git
  smoothMoveAll(135, 160, 90, 75, 0);
  delay(800);
  smoothMoveAll(135, 160, 90, 75, 45);
  delay(800);
  //çok az yükarı kaldır
  smoothMoveAll(135, 155, 85, 75, 45);
  delay(800);
  //merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

}

void alma_birakma2() {
//sağa git
  smoothMoveAll(50, 175, 90, 75, 45);
  delay(800);
  smoothMoveAll(50, 175, 90, 75, 0);
  delay(800);
//merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

// sola git
  smoothMoveAll(140, 175, 90, 75, 0);
  delay(800);
  smoothMoveAll(140, 175, 90, 75, 45);
  delay(800);
  //çok az yükarı kaldır
  smoothMoveAll(140, 160, 85, 75, 45);
  delay(800);
  //merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

  //sağa git
  smoothMoveAll(25, 175, 90, 75, 45);
  delay(800);
  smoothMoveAll(25, 175, 90, 75, 0);
  delay(800);
//merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

// sola git
  smoothMoveAll(140, 160, 90, 75, 0);
  delay(800);
  smoothMoveAll(140, 160, 90, 75, 45);
  delay(800);
  //çok az yükarı kaldır
  smoothMoveAll(140, 155, 85, 75, 45);
  delay(800);
  //merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

   //sağa git
  smoothMoveAll(0, 175, 90, 75, 45);
  delay(800);
  smoothMoveAll(0, 175, 90, 75, 0);
  delay(800);
//merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

// sola git
  smoothMoveAll(140, 145, 90, 75, 0);
  delay(800);
  smoothMoveAll(140, 145, 90, 75, 45);
  delay(800);
  //çok az yükarı kaldır
  smoothMoveAll(140, 135, 85, 75, 45);
  delay(800);
  //merkeze git
  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);

 
  /*smoothMoveAll(140, 100, 90, 125, 45);
  delay(800);
  smoothMoveAll(140, 100, 90, 50, 45);
  delay(800);
  smoothMoveAll(170, 100, 90, 50, 45);
  delay(800);
  smoothMoveAll(20, 100, 90, 50, 45);
  delay(800);
  smoothMoveAll(20, 100, 90, 125, 45);
  delay(800);

  smoothMoveAll(90, 0, 175, 90, 0);
  delay(800);*/
}



// GÖREVLER
void ev_yap() {
  robotBusy = true;
  Serial.println("Ev yapiliyor");
  alma_birakma();
  Serial.println("Ev tamamlandi");
  robotBusy = false;
}

void kopru_yap() {
  robotBusy = true;
  Serial.println("Kopru yapiliyor");
  alma_birakma1();
  Serial.println("Kopru tamamlandi");
  robotBusy = false;
}

void kule_yap() {
  robotBusy = true;
  Serial.println("Kule yapiliyor");
  alma_birakma2();
  Serial.println("Kule tamamlandi");
  robotBusy = false;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);

  delay(1000);

  moveServo(BASE, 90);
  moveServo(SHOULDER, 0);
  moveServo(ELBOW, 180);
  moveServo(WRIST, 90);
  moveServo(HAND, 90);

  Serial.println("Hazir: ev / kopru / kule");
}

void loop() {
  if (robotBusy) return;

  if (Serial.available()) {
    char cmd[10];
    int len = Serial.readBytesUntil('\n', cmd, sizeof(cmd) - 1);
    cmd[len] = '\0';

    if (!strcmp(cmd, "ev")) ev_yap();
    else if (!strcmp(cmd, "kopru")) kopru_yap();
    else if (!strcmp(cmd, "kule")) kule_yap();
    else Serial.println("Gecersiz komut");
  }
}
