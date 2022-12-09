/*https://xelcode.blogspot.com/2017/09/pid-algoritmal-cizgi-izleyen-robot-pid.html den alınıştır*/

#include <QTRSensors.h>
#define Kp 0 // Kendi deneyimlerinizle bulmanız gerekli küçük bir değer ile başlayıp, büyütebilirsiniz en kararlı Kp değerini bulana kadar..
#define Kd 0 // Bunu da küçük bir değerden başlatın ve deneyimleyerek büyütün. ( Not: Kp < Kd)
#define rightMaxSpeed 200
#define leftMaxSpeed 200
#define rightBaseSpeed 150 // robot için kp ve kd değerlerini tutturduysanız şayet motorların dönmesi gereken hız budur
#define leftBaseSpeed 150 // yukarıdaki değer ile aynıdır
#define NUM_SENSORS 6 // kullanılan sensör numarası siz 8ini de kullanabilirsiniz.
#define TIMEOUT 2500 // Sensörlerden başlangıçta kusursuz değerler almak için 2.5 sn. bekle
#define EMITTER_PIN 2
#define rightMotor1 3
#define rightMotor2 4
#define rightMotorPWM 5
#define leftMotor1 12
#define leftMotor2 13
#define leftMotorPWM 11
#define motorPower 8
QTRSensorsRC qtrrc((unsigned char[]) {14, 15, 16, 17, 18, 19/*,20,21*/} ,NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
void setup()
{
pinMode(rightMotor1, OUTPUT);
pinMode(rightMotor2, OUTPUT);
pinMode(rightMotorPWM, OUTPUT);
pinMode(leftMotor1, OUTPUT);
pinMode(leftMotor2, OUTPUT);
pinMode(leftMotorPWM, OUTPUT);
pinMode(motorPower, OUTPUT);
int i;
for (int i = 0; i < 100; i++) // tercihe bağlı alandır ya robotunuzu hatta yürüterek kalibre edin veya bunu otomatik yapın.
 /* otomatik kalibrasyon için burasının yorumunu kaldırın
  if ( i  < 25 || i >= 75 ) // sensörleri, karşılaşılabilecek en aydınlık ve en karanlık okumalara maruz bırakmak için sola ve sağa çevirin.
     turn_right();  
   else
     turn_left(); */ 
qtrrc.calibrate();
delay(20);
wait();
delay(1000); // Ana döngüye girmeden önce botu konumlandırmak için 1 saniye bekleyin
}
int lastError = 0;
void loop()
{
unsigned int sensors[6];
int position = qtrrc.readLine(sensors);
int error = position - 2500;
int motorSpeed = Kp * error + Kd * (error - lastError);
lastError = error;
int rightMotorSpeed = rightBaseSpeed + motorSpeed;
int leftMotorSpeed = leftBaseSpeed - motorSpeed;
if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed;
if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed;
if (rightMotorSpeed < 0) rightMotorSpeed = 0;
if (leftMotorSpeed < 0) leftMotorSpeed = 0;
{
digitalWrite(motorPower, HIGH); 
digitalWrite(rightMotor1, HIGH);
digitalWrite(rightMotor2, LOW);
analogWrite(rightMotorPWM, rightMotorSpeed);
digitalWrite(motorPower, HIGH);
digitalWrite(leftMotor1, HIGH);
digitalWrite(leftMotor2, LOW);
analogWrite(leftMotorPWM, leftMotorSpeed);
}
}
void wait(){
digitalWrite(motorPower, LOW);
}