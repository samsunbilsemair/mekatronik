//https://gelecegiyazanlar.turkcell.com.tr/konu/egitim/arduino-301/motor-shield-kullanimi
/*
Öncelikle motor shield'ı Arduino kartının üzerine takınız. Takma işleminden sonra Arduino pinlerine shield yokmuş gibi, 
shield üzerindeki pinlerden ulaşabilirsiniz fakat bu pinlerden bazıları motor sürücüde kullanıldığı için başka işlemler için kullanılamaz.
 Motor sürücüsü Arduino'nun Dijital pinlerinden 3, 8, 9, 11, 12 ve 13; analog pinlerden A0 ve A1'i kullanmaktadır. 
 Bu pinlerinde kullanım amaçları aşağıdaki tabloda gösterilmiştir.

Görev	       A motoru	     B motoru
Yön	         Dijital 12	  Dijital 13
Hız (PWM)  	 Dijital 3   	Dijital 11
Fren	       Dijital 9   	Dijital 8
Akım ölçümü	 Analog 0	    Analog 1


Fark edildiği gibi normal motor sürücülerden farklı olarak tek pinle ileri ve geri yön kontrolü yapılmaktadır.
 Yön pinlerinin 5 volt yada 0 volt olmasına göre motor ileri veya geri yönde dönmektedir. Fren pini ise motorun durmasını sağlamaktadır.

Örneğin motorlardan birini harekete geçirmek için öncelikle motorun döneceği yönü belirlemek için yön pinini 5 volt veya 0 volt düzeyine çekmeliyiz.
 İleri yönde dönmesi için bu pin 5 volt, geri yönde dönmesi için 0 volt düzeyine getirilmelidir. 
 Yön ayarlandıktan sonra motorun dönmesi için fren pini 0 volt düzeyine getirilmelidir.
  Motorun hızının ayarlanması için hız pinine analogWrite fonksiyonuyla 0-255 arasında hız bilgisi gönderilmelidir.

Shield doğrudan Arduino üzerine takıldığı için harici olarak devre kurulmasına gerek kalmamaktadır. 
Motor ve besleme bağlantısını aşağıdaki resimde gösterildiği gibi shield üzerine bağlanmalıdır.

*/

int DonmeHizi = 175;
/* bu değişken ile motorların dönme hızı kontrol edilebilir */

void ileri(int hiz) {
  /* A motoru ileri yönde dönmesi için ayarlanıyor */
  digitalWrite(12, HIGH); /* ileri yön ayarı yapıldı */
  digitalWrite(9, LOW);   /* fren kapatıldı */
  analogWrite(3, hiz);    /* dönme hızı ayarlandı */

  /* B motoru ileri yönde dönmesi için ayarlanıyor */
  digitalWrite(13, HIGH); /* ileri yön ayarı yapıldı */
  digitalWrite(8, LOW);   /* fren kapatıldı */
  analogWrite(11, hiz);   /* dönme hızı ayarlandı */
}

void solaDon(int hiz) {
  /* A motoru geri yönde dönmesi için ayarlanıyor */
  digitalWrite(12, LOW); /* geri yön ayarı yapıldı */
  digitalWrite(9, LOW);  /* fren kapatıldı */
  analogWrite(3, hiz);   /* dönme hızı ayarlandı */

  /* B motoru ileri yönde dönmesi için ayarlanıyor */
  digitalWrite(13, HIGH); /* ileri yön ayarı yapıldı */
  digitalWrite(8, LOW);   /* fren kapatıldı */
  analogWrite(11, hiz);   /* dönme hızı ayarlandı */
}

void sagaDon(int hiz) {
  /* A motoru ileri yönde dönmesi için ayarlanıyor */
  digitalWrite(12, HIGH); /* ileri yön ayarı yapıldı */
  digitalWrite(9, LOW);   /* fren kapatıldı */
  analogWrite(3, hiz);    /* dönme hızı ayarlandı */

  /* B motoru geri yönde dönmesi için ayarlanıyor */
  digitalWrite(13, LOW); /* geri yön ayarı yapıldı */
  digitalWrite(8, LOW);  /* fren kapatıldı */
  analogWrite(11, hiz);  /* dönme hızı ayarlandı */
}

void geri(int hiz) {
  /* A motoru geri yönde dönmesi için ayarlanıyor */
  digitalWrite(12, LOW); /* geri yön ayarı yapıldı */
  digitalWrite(9, LOW);  /* fren kapatıldı */
  analogWrite(3, hiz);   /* dönme hızı ayarlandı */

  /* B motoru geri yönde dönmesi için ayarlanıyor */
  digitalWrite(13, LOW); /* geri yön ayarı yapıldı */
  digitalWrite(8, LOW);  /* fren kapatıldı */
  analogWrite(11, hiz);  /* dönme hızı ayarlandı */
}

void dur() {
  digitalWrite(9, HIGH); /* fren yapıldı */
  digitalWrite(8, HIGH); /* fren yapıldı */
}

void setup() {
  /* A motorunun ayarları */
  pinMode(12, OUTPUT); /* yön pini çıkış olarak ayarlandı */
  pinMode(9, OUTPUT);  /* Fren pini çıkış olarak ayarlandı */

  /* B motorunun ayarları */
  pinMode(13, OUTPUT); /* yön pini çıkış olarak ayarlandı */
  pinMode(8, OUTPUT);  /* Fren pini çıkış olarak ayarlandı */
}

void loop() {
  ileri(DonmeHizi);
  delay(1000);
  dur();
  delay(1000);
  solaDon(DonmeHizi);
  delay(1000);
  dur();
  delay(1000);
  sagaDon(DonmeHizi);
  delay(1000);
  dur();
  delay(1000);
  geri(DonmeHizi);
  delay(1000);
  dur();
  delay(1000);
}