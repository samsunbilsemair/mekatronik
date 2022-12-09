/* http://www.temrinler.com/?p=4148   den alınmıştır  */

#include <QTRSensors.h> //Qtr v4.0 

#define AIN1 4 //A sağ motor.
#define AIN2 3
#define ENA 5

#define ENB 6 //B sol motor.
#define BIN1 7
#define BIN2 8
#define STBY 9

#define sensorSayisi 8
#define sensorOrnekSayisi 4
#define emiterPini 11
#define LED 13

int maxHiz = 70; // Motor pwm ayarı 0 - 255.

int hata = 0, turev = 0;
float KP = 0.03, KD = 0.5; // Oran (KP) ve türev (KD) sabitleri. (Her araca göre ayar yapılmalıdır.)

unsigned int pozisyon = 3500;

int fark = 0; // Motorlara uygulanan fark.
int sonHata; // Orantılı son değer. (Hatanın türevini hesaplamak için kullanılır.)
int hedef = 3500; // Sensörden gelen 0 - 7000 arası değerin orta noktası.

QTRSensors qtr; // qtr isimli nesne oluşturuldu.
unsigned int sensor[sensorSayisi];

void setup() {
  qtr.setTypeAnalog();  //QTR-8A ayarla. (QTR-8RC için qtr.setTypeRC() fonksiyonu kullanılır.)
  qtr.setSensorPins((const uint8_t[]) {
    A0, A1, A2, A3, A4, A5, A6, A7
  }, 8);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(STBY, OUTPUT);

  delay(1000); //Araca enerji verince 1sn bekle
  kalibrasyon(1); // 0 elle, 1 otomatik kafa sallama.
}

void loop() {
  sensorOku();
  pd();
}

void sensorOku() {
  pozisyon = qtr.readLineWhite(sensor); // Beyaz çizginin pozisyonunu oku. (0 - 7000)
  hata = pozisyon - hedef; // Pozisyondan 3500 (hedef) çıkar. Hatayı bul.
  qtr.read(sensor); // Sekiz sensörün ham değelerini oku.
}

void pd() {
  turev = hata - sonHata; // Hatadan bir önceki hatayı çıkar.
  sonHata = hata; // Şimdiki hatayı kaydet.

  fark = ( hata * KP) + ( turev * KD ); // Motorlara uygulanacak farkı hesapla.

  constrain(fark, -maxHiz, maxHiz); // fark en fazla maxHiz olsun.

  if ( fark < 0 ) // fark negatif ise
    motor(maxHiz, maxHiz + fark); // Sağ motorun hızını düşür.
  else // fark negatif değilse
    motor(maxHiz - fark, maxHiz); // Sol motorun hızını düşür.
}

void motor(int solMotorPWM, int sagMotorPWM) {
  digitalWrite(STBY, HIGH);

  if ( solMotorPWM >= 0 )  { // İleri.
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  else  { // Negatifse geri döndür.
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    solMotorPWM *= -1;
  }
  analogWrite(ENB, solMotorPWM);

  if ( sagMotorPWM >= 0 )  { // İleri.
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }
  else  { // Negatifse geri döndür.
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    sagMotorPWM *= -1;
  }
  analogWrite(ENA, sagMotorPWM);
}

void kalibrasyon(bool secim) { // 1 otomatik, 0 elle.
  if (secim) { // secim 1 ise otomatik kalibrasyon yap.
    byte hiz = 40; // Aracın kafasını sallama hızı.
    for (byte i = 0; i < 3; i++) {  // Sağa sola üç kez kafa salla.
      while (sensor[7] < 300) {
        motor(hiz, -hiz);
        qtr.calibrate();
        sensorOku();
      }
      while (sensor[7] > 700) {
        motor(hiz, -hiz);
        qtr.calibrate();
        sensorOku();
      }
      while (sensor[0] < 300) {
        motor(-hiz, hiz);
        qtr.calibrate();
        sensorOku();
      }
      while (sensor[0] > 700) {
        motor(-hiz, hiz);
        qtr.calibrate();
        sensorOku();
      }
      while (sensor[3] > 500)  { // Ortada dur.
        motor(hiz, -hiz);
        qtr.calibrate();
        sensorOku();
      }
    }
  } else { // secim 0 ise elle kalibrasyon yap.
    for ( byte i = 0; i < 70; i++)  { // Dahili LED yanıp söndüğü sürece (3 sn) elle kalibrasyon yap.
      digitalWrite(LED, HIGH); delay(20);
      qtr.calibrate();
      digitalWrite(LED, LOW); delay(20);
      qtr.calibrate();
    }
  }
  motor(0, 0);
  delay(2000); // Kalbirasyondan sonra 3 sn bekle.
}