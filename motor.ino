void inch()
{
  setMotors(100, 100);
  delay(100);
  halt();
}
void turn(char dir, int deg)
{
  int n;
  if (deg == 0) {
    if (dir == 'l' || dir == 'L')setMotors(-tSpd, tSpd); else setMotors(tSpd, -tSpd);
    while (getPattern() == "00000000000");
  } else {
    n = deg / 15;
    if (dir == 'l' || dir == 'L')setMotors(-tSpd, tSpd); else setMotors(tSpd, -tSpd);
    for (int i = 1; i <= n; i++)delay(35 - min(3 * n, 10));
  }
  setMotors(0, 0);
}
void setMotors(int spdL, int spdR)
{
  spdL = min(spdL, 255); spdR = min(spdR, 255);
  spdL = max(spdL, -255); spdR = max(spdR, -255);
  digitalWrite(3, HIGH);
  if (spdL < 0) {
    analogWrite(lmf, 0);
    analogWrite(lmb, -spdL);
  } else {
    analogWrite(lmf, spdL);
    analogWrite(lmb, 0);
  }
  if (spdR < 0) {
    analogWrite(rmf, 0);
    analogWrite(rmb, -spdR);
  } else {
    analogWrite(rmf, spdR);
    analogWrite(rmb, 0);
  }
  //  if(spdL<0){analogWrite(lpwm,-spdL);digitalWrite(lmf,LOW);digitalWrite(lmb,HIGH);}
  //  else{analogWrite(lpwm,spdL);digitalWrite(lmf,HIGH);digitalWrite(lmb,LOW);}
  //  if(spdR<0){analogWrite(rpwm,-spdR);digitalWrite(rmf,LOW);digitalWrite(rmb,HIGH);}
  //  else{analogWrite(rpwm,spdR);digitalWrite(rmf,HIGH);digitalWrite(rmb,LOW);}
}
void halt()
{
  digitalWrite(lmf, LOW); digitalWrite(rmf, LOW);
  digitalWrite(lmb, LOW); digitalWrite(rmb, LOW);
  //  analogWrite(lpwm,0);analogWrite(rpwm,0);
  //  digitalWrite(lmf,HIGH);digitalWrite(rmf,HIGH);
  //  digitalWrite(lmb,HIGH);digitalWrite(rmb,HIGH);
}

void pid(bool reverse) {
  static long P, I = 0, D, err, lasterr = 0, spd;
  err = pos - 250;
  P = err;
  I = (P) ? (I + P) : 0;
  D = err - lasterr;
  lasterr = P;
  spd = KP * P + KI * I + KD * D;
  if (reverse)setMotors(min(max(max_spd + spd, -32), 255), min(max(max_spd - spd, -32), 255));
  else setMotors(min(max(max_spd + spd, 0), 255), min(max(max_spd - spd, 0), 255));
}
