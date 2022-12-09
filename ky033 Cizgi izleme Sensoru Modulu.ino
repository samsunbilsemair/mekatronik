/*
  Arduino KY-033 Çizgi İzleme Sensörü Modülü
 
  Arduino 37 parça sensör setinin bir parçası olan Çizgi İzleme Sensörü modülünün örnek
  sketch'idir. Üzerinde birbirlerine çok yakın bulunan kızılötesi verici ve alıcı sayesinde
  parlak yüzeylerde bulunan karanlık çizgiler üzerinde hareket eden robotlar yapmakta
  kullanılır.
 
  Setin diğer parçalarının açıklama ve örnek kodlarına
  web sitemizden ulaşabilirsiniz.
 
  Oluşturma: 8 Ekim 2021 / Mete Hoca
 
  https://www.metehoca.com/
*/
 
int led = 13;    // Arduino'nun Dahili LED'i
int sensor = 2;  // (OUT) Sensör çıkış bağlantısı
                 // GND ve VCC pinlerini Arduino üzerinde 5V(VCC) ve GND'ye bağlamalıyız
 
void setup ()
{
  pinMode(led, OUTPUT);                      // LED'i çıkış olarak ayarlıyoruz
  pinMode(sensor, INPUT);                    // Dijital bağlantıyı giriş olarak ayarlıyoruz
  Serial.begin(9600);                        // Seri Port Ekranı'nı doğru ayarlamayı unutmayın
}
 
void loop (){
  if (digitalRead(sensor) == LOW) {          // Sensör çizgi üzerinde ise LOW olur
    Serial.println("Sensör çizgi üzerinde"); // Sensörün çizgi üzerinde olduğunu bildirelim
    digitalWrite(led, HIGH);                 // LED'i de yakalım
  }
  else {
    Serial.println("Sensör çizgi üzerinde değil!"); // Sensör çizgi üzerinde değilse HIGH olur
    digitalWrite(led, LOW);                         // LED'i söndürelim
  }
  delay(100);                                       // Biraz bekleyelim
}