#include <NewPing.h> 
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define halt_delay 50
#define MAX_SPD 155
#define MIN_SPD 155
#define tSpd 200
#define KP 1.5
#define KI 0.000
#define KD 9
#define NUM_SENSORS 11
#define lpwm 8
#define rpwm 2
#define lmf 6
#define lmb 7
#define rmf 3
#define rmb 5
#define DEBUGGING (analogRead(A14)>200)
#define ad_smin 0
#define ad_smax 13
#define ad_wallDist 26
#define ad_objDist 27
#define ad_rampDist 28

int max_spd=MAX_SPD;
int wallDist=16, objDist=12, rampDist=20;

int smin[NUM_SENSORS]={1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023},smax[NUM_SENSORS]={0,0,0,0,0,0,0,0,0,0,0};
int s[NUM_SENSORS]={A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10}, ds[NUM_SENSORS];
uint8_t bar[16][16];
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
NewPing sonarF(4,4,400), sonarL(7,7,400), sonarR(8,8,400);
String patt,lastPatt="00000100000",patt5,lastPatt5="00100",patt9,lastPatt9="000010000";
long pos,lastPos=0;
char line='B', hand='R', dir='S';

uint8_t arrow_r[16]={0x00,0x00,0x00,0x00,0x40,0x70,0x7c,0x7f,0x7f,0x7c,0x70,0x40,0x00,0x00,0x00,0x00};
uint8_t arrow_l[16]={0x00,0x00,0x00,0x00,0x02,0x0e,0x3e,0xfe,0xfe,0x3e,0x0e,0x02,0x00,0x00,0x00,0x00};

void oled_printLogo();
void oled_print(String,bool=true,int=1,int=WHITE);void oled_println(String,bool=true,int=1,int=WHITE);
void oled_printXY(int,int,String,bool=true,int=1,int=WHITE);
void oled_clear(String="",bool=true);
void oled_printBar(long*,int,int,int,int,int,int);void create_bar(int);void create_bar2(int);
void calibrate_line();void calibrate_wall();void calibrate_ramp();void calibrate_obj();
bool hasWall();char detectWall(char);void followWall(char);void followWallBoth();
bool hasObject(long);void avoidObject(char);
String getPattern(int=0);long getPos(int,int);int dS(int);
void setMotors(int,int);void pid(bool=false);
void wave();void turn(char,int=0);void halt();void inch();
void menu();void settings();

void setup() {
  
  pinMode(lmf,OUTPUT);pinMode(lmb,OUTPUT);pinMode(rmf,OUTPUT);pinMode(rmb,OUTPUT);pinMode(lpwm,OUTPUT);pinMode(rpwm,OUTPUT);
  Serial.begin(9600);
  if(!oled.begin(SSD1306_SWITCHCAPVCC,0x3C)){Serial.println("SSD1306 failed");}oled_printLogo();delay(500);oled.clearDisplay();
  create_bar(16);
  
  menu();

  wallDist=EEPROM[ad_wallDist];
  for(int i=0; i<NUM_SENSORS; i++){smin[i]=map(EEPROM[ad_smin+i],0,255,0,1023);smax[i]=map(EEPROM[ad_smax+i],0,255,0,1023);}
  delay(500);
  
}

void loop() {
  int i=0, gap=0, trig=0, tCount=0, plusCount=0;
  bool acceleration=true;
  long prevMillis=0, stepMillis=0;
  while(1){
    if(DEBUGGING){
      oled.display();
      delay(10);
      oled.clearDisplay();
      oled_printXY(0,0,String(map(analogRead(A14),420,1000,0,100)),false);oled.write(37);
      oled_printXY(110,0,String(analogRead(A13)),false);oled.write(37);
    }
    pos=getPos(2,8);
    patt=getPattern();
    if(DEBUGGING)continue;

    if(patt=="11111111111"){ // black box
      halt();
      oled.clearDisplay();
      oled_printXY(20,0,"TRACK\n ENDED!",true,2);
      while(!DEBUGGING);
      oled.setCursor(0,0);oled.print(" Restarting...  ");
      oled.setCursor(0,1);oled.print("Place the Robot ");
      while(DEBUGGING);
      dir='S';
      oled_clear();
      prevMillis=millis()+1000;
      delay(1000);continue;
    }else if(patt=="10000000001"){ // T
      tCount++;
    }
    
    if(hand=='R'){
      if(ds[5] && ds[0]){
        dir='L';
      }else if(ds[5] && ds[10]){
        halt();delay(halt_delay);
        turn('R',90);turn('R');
        dir='S';
        prevMillis=millis();
        continue;
      }
    }else{ // hand=='L'
      if(ds[5] && ds[10]){
        dir='R';
      }else if(ds[5] && ds[0]){
        halt();delay(halt_delay);
        turn('L',90);turn('L');
        dir='S';
        prevMillis=millis();
        continue;
      }
    }
    
    if(straight_line(patt)){
    if(patt=="00000000000" && 0<pos && pos<500){
      halt();delay(halt_delay);
      if(dir=='S') turn(hand); else turn(dir);
      dir='S';
    }
    pid(true);
    if(0<pos && pos<500){
      max_spd=MAX_SPD;
      pid(true);
    }else{
      max_spd=191;
      pid(true);
    }

    
    else{
      halt();
      oled.clearDisplay();
      oled_printXY(10,20,patt,true,2);
      oled_printXY(10,40,lastPatt,true,2);
      while(!DEBUGGING);
    }
    
    lastPatt=patt; 
  }  endwhile;
}
