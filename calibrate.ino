void calibrate_line()
{
  bool flag=false;
  delay(200);
  oled.clearDisplay();
  oled_printXY(10,30,"Calibrating Line");
  int a[NUM_SENSORS], calSpd = 60, calPeriod = 160;
  for (int count = 0; count < calPeriod; count+=1) {
//    if (count < calPeriod / 4 || count >= calPeriod * 3 / 4) {
//      setMotors(calSpd, -calSpd);
//    } else {
//      setMotors(-calSpd, calSpd);
//    }
    setMotors(50, -50);
    for (int i = 0; i < NUM_SENSORS; i++) {
      a[i] = analogRead(s[i]);
      if(a[i] < smin[i]) smin[i] = a[i];
      if(a[i] > smax[i]) smax[i] = a[i];
    }
    if(count%10==0)oled_drawBitmap((count/10)*8,0,bar[15],8,16,WHITE);
    delay(10);
  }
  setMotors(0, 0);
  while(!DEBUGGING);while(DEBUGGING){oled.clearDisplay();getPos(0,10);oled.display();}
  while(1){
    int k=0;
    oled_printXY(0,20,"  Ignore?  ",true,2);
    for(k=0; k<100; k++){if(DEBUGGING){flag=false;break;}delay(10);}if(k<100)break;
    oled_printXY(0,20,"  Update?  ",true,2);
    for(k=0; k<100; k++){if(DEBUGGING){flag=true;break;}delay(10);}if(k<100)break;
  }
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print("min["); Serial.print(i); Serial.print("]="); Serial.print(smin[i]);
    Serial.print(", ");
    Serial.print("max["); Serial.print(i); Serial.print("]="); Serial.println(smax[i]);
    if(flag){
      EEPROM.update(ad_smin+i, map(smin[i],0,1023,0,255));
      EEPROM.update(ad_smax+i, map(smax[i],0,1023,0,255));
    }
  }
  oled_printXY(0,0," * Done! * ",true,2);
  delay(1000);
}

void calibrate_wall()
{
  bool flag=false;
  delay(200);
  oled.clearDisplay();
  oled_printXY(10,30,"Calibrating Wall");
  if(detectWall(hand)=='R'){
    for(int i=0; i<16;i++){
      wallDist=sonarR.ping_cm();
      oled_drawBitmap(i*8,0,bar[15],8,16,WHITE);
      delay(100);
    }
  }else{
    wallDist=sonarL.ping_cm();
    for(int i=0; i<16;i++){
      oled_drawBitmap(i*8,0,bar[15],8,16,WHITE);
      delay(100);
    }
  }
  while(!DEBUGGING);while(DEBUGGING){oled.clearDisplay();oled_printXY(30,50,String(wallDist)+"cm",false,2);oled.display();}
  while(1){
    int k=0;
    oled_printXY(0,20,"  Ignore?  ",true,2);
    for(k=0; k<100; k++){if(DEBUGGING){flag=false;break;}delay(10);}if(k<100)break;
    oled_printXY(0,20,"  Update?  ",true,2);
    for(k=0; k<100; k++){if(DEBUGGING){flag=true;break;}delay(10);}if(k<100)break;
  }
  if(flag)EEPROM.update(ad_wallDist,wallDist*10);
  oled.clearDisplay();oled_printXY(0,0," * Saved * ",true,2);
  delay(1000);
}
