/*------- VR = 350 ohm & threshold = 60 for 2.5cm line  --------*/
/*------- VR ~ 500 ohm & threshold = 70 for 3cm line  --------*/
int dS(int i)
{
  if(line=='B') return constrain(map(analogRead(s[i]),smin[i],smax[i],0,100), 0,100) < 70?0:1;
  else return constrain(map(analogRead(s[i]),smin[i],smax[i],0,100), 0,100) > 40?0:1;
}
String getPattern(int mode)
{
  String pattern="";
  for(int i=0; i<NUM_SENSORS; i++){
    if(line=='B') ds[i]=constrain(map(analogRead(s[i]),smin[i],smax[i],0,100), 0,100) < 70?0:1;
    else ds[i]=constrain(map(analogRead(s[i]),smin[i],smax[i],0,100), 0,100) > 40?0:1;
  }

  patt5=pattern+ds[0]+ds[3]+ds[5]+ds[7]+ds[10];
  patt9=pattern+ds[1]+ds[2]+ds[3]+ds[4]+ds[5]+ds[6]+ds[7]+ds[8]+ds[9];

  for(int i=0; i<NUM_SENSORS; i++){
    pattern=pattern+ds[i];
  }
  
  if(DEBUGGING) oled_printXY(90,50,pattern,false);
  return pattern;
}
long getPos(int left_most,int right_most)
{
  long pos, ar[NUM_SENSORS],sum=0,w_sum=0, weight=100, d;
  d=right_most-left_most; // sensor used
  for(int i=left_most; i<=right_most; i++){
    if(line=='B') ar[i]=constrain(map(analogRead(s[i]),smin[i],smax[i],-30,100), 0,100);
    else ar[i]=10-constrain(map(analogRead(s[i]),smin[i],smax[i],0,13), 0,10);
  }
  if(DEBUGGING) oled_printBar(ar,left_most,right_most,0,40,16, 100);
  for(int i=left_most,j=0; i<=right_most; i++,j=j+weight){
    sum+=ar[i];
//    w_sum=w_sum+(ar[i]*j);
  }
  w_sum=ar[2]*0+ar[3]*250+ar[4]*400+ar[5]*500+ar[6]*600+ar[7]*750+ar[8]*1000;
//  w_sum=ar[1]*0+ar[2]*200+ar[3]*350+ar[4]*450+ar[5]*500+ar[6]*550+ar[7]*650+ar[8]*800+ar[9]*1000;
  pos=w_sum/sum;
  pos = constrain(map(pos,0,1000,0,500),0,500);
  if(sum==0)pos=lastPos;
  if(DEBUGGING) oled_printXY(90,40,String(pos),false);
  lastPos=pos;
  return pos;
}

bool straight_line(String p)
{
  if(p=="10000"||p=="11000"||p=="01000"||p=="01100"||p=="00100"||p=="00110"||p=="00010"||p=="00011"||p=="00001"){
    return true;
  }else return false;
}
