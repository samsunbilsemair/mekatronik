void motor(int sol,int sag){

  solmotor(sol);
  sagmotor(sag);
}


void sagmotor(int deger){
if (deger>0){
  digitalWrite(AIN1,HIGH);
  digitalWrete(AIN2,LOW)
}
else {//TERSE GİDER
  digitalWrite(AIN1,LOW);
  digitalWrete(AIN2,HIGH);
  deger *= -1;

}
analogWrite(PWMA,deger);
}

void solmotor(int deger){
if (deger>0){
  digitalWrite(BIN1,HIGH);
  digitalWrete(BIN2,LOW)
}
else {//TERSE GİDER
  digitalWrite(BIN1,LOW);
  digitalWrete(BIN2,HIGH);
  deger *= -1;

}
analogWrite(PWMB,deger);
}


void fren(boolean sol,boolean sag){ //fren(1,1) fren yapar, fren(0,0) freni bırakır.

  digitalWrite(BIN1,sag);
  digitalWrete(BIN2,sag);
  digitalWrite(AIN1,sol);
  digitalWrete(AIN2,sol);
  }


}