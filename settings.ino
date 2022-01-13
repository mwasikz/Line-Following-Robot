void menu()
{
  int s_delay=100;
  while(DEBUGGING){oled_printXY(0,20,"  Press\n Button",true,2);delay(250);oled.clearDisplay();oled.display();delay(250);}
  while(1){
    int i=0;
    oled.clearDisplay();oled_printXY(0,25," Settings",true,2);
    for(i=0; i<s_delay; i++){if(DEBUGGING){
      for(int j=0;j<=15;j++){oled_drawBitmap(j*8,0,arrow_r,8,16,WHITE);delay(20);}while(DEBUGGING);settings();break;}delay(10);}
    oled.clearDisplay();oled_printXY(0,25,"    Run   ",true,2);
    for(i=0; i<s_delay; i++){if(DEBUGGING){
      for(int j=0;j<=15;j++){oled_drawBitmap(j*8,0,arrow_r,8,16,WHITE);delay(20);}break;}delay(10);}
      if(i<100){oled_clear();delay(200);return;}
  }
}
void settings()
{
  int s_delay=100, anim_delay=10;
  while(1){
    int i=0;
    oled.clearDisplay();oled_printXY(0,25," Set Speed ",true,2);
    for(i=0; i<s_delay; i++){
      if(DEBUGGING){// hand
        for(int j=0;j<=15;j++){oled_drawBitmap(j*8,0,arrow_r,8,16,WHITE);delay(anim_delay);}
        oled.clearDisplay();oled_printXY(20,5,"   Set Speed   ");
        while(1){
          int k=0, n=3, op_count;
          int op[]={255,205,155};
          for(op_count=0;op_count<n;op_count++){
            oled_printXY(0,20," Spd = "+String(op[op_count])+" ",true,2);
            for(k=0; k<100; k++){if(DEBUGGING){max_spd=op[op_count];break;}delay(10);}
            if(k<100){oled_printXY(20,5,"  ** SAVED **  ");delay(1000);break;}
          }if(op_count<n)break;
        }while(DEBUGGING);continue;
      }delay(10);
    }
    
    oled.clearDisplay();oled_printXY(0,25," Set Hand ",true,2);
    for(i=0; i<s_delay; i++){
      if(DEBUGGING){// hand
        for(int j=0;j<=15;j++){oled_drawBitmap(j*8,0,arrow_r,8,16,WHITE);delay(anim_delay);}
        oled.clearDisplay();oled_printXY(20,5,"   Set Hand    ");
        while(1){
          int k=0,n=2, op_count;
          char op[]={'R','L'};
          for(op_count=0;op_count<n;op_count++){
            oled_printXY(0,20," Hand = "+String(op[op_count])+" ",true,2);
            for(k=0; k<100; k++){if(DEBUGGING){hand=op[op_count];break;}delay(10);}
            if(k<100){oled_printXY(20,5,"  ** SAVED **  ");delay(1000);break;}
          }if(op_count<n)break;
        }while(DEBUGGING);continue;
      }delay(10);
    }
    
    oled.clearDisplay();oled_printXY(0,25," Set Line ",true,2);
    for(i=0; i<s_delay; i++){
      if(DEBUGGING){// line
        for(int j=0;j<=15;j++){oled_drawBitmap(j*8,0,arrow_r,8,16,WHITE);delay(anim_delay);}
        oled.clearDisplay();oled_printXY(20,5,"   Set Line    ");
        while(1){
          int k=0,n=2, op_count;
          char op[]={'B','W'};
          for(op_count=0;op_count<n;op_count++){
            oled_printXY(0,20," Line = "+String(op[op_count])+" ",true,2);
            for(k=0; k<100; k++){if(DEBUGGING){line=op[op_count];break;}delay(10);}
            if(k<100){oled_printXY(20,5,"  ** SAVED **  ");delay(1000);break;}
          }if(op_count<n)break;
        }while(DEBUGGING);continue;
      }delay(10);
    }
  
    oled.clearDisplay();oled_printXY(0,25," Calibrate\n   Line ",true,2);
    for(i=0; i<s_delay; i++){if(DEBUGGING){
      for(int j=0;j<=15;j++){oled_drawBitmap(j*8,0,arrow_r,8,16,WHITE);delay(anim_delay);}
      calibrate_line();
      while(DEBUGGING);continue;}delay(10);}
  
    oled.clearDisplay();oled_printXY(0,25," Calibrate\n   Wall ",true,2);
    for(i=0; i<s_delay; i++){if(DEBUGGING){
      for(int j=0;j<=15;j++){oled_drawBitmap(j*8,0,arrow_r,8,16,WHITE);delay(anim_delay);}
      calibrate_wall();
      while(DEBUGGING);continue;}delay(10);}
  
    oled.clearDisplay();oled_printXY(0,25,"   Back ",true,2);
    for(i=0; i<s_delay; i++){if(DEBUGGING){
      for(int j=15;j>=0;j--){oled_drawBitmap(j*8,0,arrow_l,8,16,WHITE);delay(anim_delay);}
      while(DEBUGGING);return;}delay(10);}
  }
}
