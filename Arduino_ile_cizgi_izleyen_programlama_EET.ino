//https://www.youtube.com/watch?v=NVqttJxtbMU&ab_channel=ElektrikElektronikTeminler 


#include <QTRSensors.h>
//motor sürücünün bağlantılarını tanımla
#define AIN1 4//A motor sağ
#define AIN2 3 
#define PWMA 5

#define BIN1 7//B motor sol
#define BIN2 8 
#define PWMB 6
#define STBY 9
// qtr sensor tanımlamaları
#define sensorSayisi 8
#define sensorOrnekSayisi 4
#define emiterPini 11
#define LedR 0
#define LedG 1
#define LedB 2

int hiz=70; // en az motor hızı

// zemin değeri
boolean zemin=1;// 1 siyah zemin, 0 beyaz zemin

// PID değişkenlerini tanımlayalım
int hata=0;
int turev=0;

float KP=0.01;//bu değerler deneyseldir
float KD=0.1;// kp nin 10 yada 20 katı alınabilir.

int pozisyon;// qtrnin konumunu tanımladık

int fark=0;//Motora uygulanacak farkı tanımladık

int sonHata; //Orantılı Son değer Hatanın türevini hesaplamak için kullanılır

int hedef=3500; //ayar noktası (8 sensör kullandığımız için pozisyon 0 ile 7000 arasında olmalıdır bu yüzden ideal 3500 )

// 8 sensor için 8li dizi oluştralım
int sensor[sensorSayisi];

QTRSensorsAnalog qtra((unsigned char[]){A0,A1,A2,A3,A4,A5,A6,A7},sensorSayisi)



void setup() {
pinMode(AIN1,OUTPUT);
pinMode(AIN2,OUTPUT);
pinMode(BIN1,OUTPUT);
pinMode(BIN2,OUTPUT);
pinMode(PWMA,OUTPUT);
pinMode(PWMB,OUTPUT);
pinMode(LedR,OUTPUT);
pinMode(LedG,OUTPUT);
pinMode(LedB,OUTPUT);
pinMode(STBY,OUTPUT);
//kalibrasyon için magenta yanım sönerken yap
for(int i=0;i<70;i+){
  digitalWrite(LedR,HIGH);
  digitalWrite(LedB,HIGH);delay(20);
  qtra.calibrate();
  digitalWrite(LedR,LOW);
  digitalWrite(LedB,LOW);delay(20);
  }
  while(digitalRead(MZ80)==1) fren(1,1);
}

void loop() {

pozisyon=qtra.readLine(sensors,true,zemin);
hata=pozisyon-hedef;
turev=hata-sonHata;
sonHata=hata;
fark=(hata*KP)+(turev*KD);//hata/100 veya turev/10 şeklinde de yazılabilir

if(fark<0){
  motor(hiz,hiz+fark);//motor değişkeni motor(sol motor, sağ motor); şeklinde tanımlayacağız
  else motor(hiz-fark,hiz);
  }
}
