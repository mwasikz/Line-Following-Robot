bool hasObject(long dis)
{
  int front = 0;
  front=sonarF.ping_cm();
  if(front>2 && front<=dis)return true;
  else return false;
}
bool hasWall()
{
  int left = 0, right = 0;
  right=sonarR.ping_cm();
  left=sonarL.ping_cm();
  if(right>2 && right<30)return true;
  if(left>2 && left<30)return true;
  return false;
}
char detectWall(char hand)
{
  int left = 0, right = 0;
  right=sonarR.ping_cm();
  left=sonarL.ping_cm();
  if(hand=='R'){
    if(right>2 && right<30)return 'R';
    if(left>2 && left<30)return 'L';
  }else{
    if(left>2 && left<30)return 'L';
    if(right>2 && right<30)return 'R';
  }
}

void avoidObject(char hand)
{
  int minDist=100, maxDist=200, minSpd=80, maxSpd=200;
//  int minDist=100, maxDist=200, minSpd=100, maxSpd=200; // long dist
  int distance, err, lasterr = 0, P, D, spd;
  while (getPattern(5)=="00000") {
    if(hand=='R')distance = round(sonarL.ping() * 0.343 / 2);
    else distance = round(sonarR.ping() * 0.343 / 2);
    if (distance < minDist && distance != 0)distance = minDist;
    if (distance > maxDist || distance == 0)distance = maxDist;
    distance = constrain(map(distance, minDist, maxDist, 0, 100), 0, 100);
    err = distance - 50;
    P = err;
    D = err - lasterr;
    lasterr=err;
    spd = 5 * P + 4 * D;
    if(hand=='R')setMotors(min(max(maxSpd-spd, minSpd), maxSpd), min(max(maxSpd+spd, minSpd), maxSpd));
    else setMotors(min(max(maxSpd+spd, minSpd), maxSpd), min(max(maxSpd-spd, minSpd), maxSpd));
    delay(10);
  }
  delay(100);
  setMotors(0,0);
}

void followWall(char hand)
{
  int minDist=wallDist-5, maxDist=wallDist+5, minSpd=60, maxSpd=205;
  int front, left, right, distance, err, lasterr = 0, P, D, spd;
  while (getPattern(5)=="11111") {
    front=sonarF.ping_cm();
    if(front>2 && front<=18){
      halt();delay(100);
      if(hand=='R'){
        right=sonarR.ping_cm();
        if(right>2 && right<=30){turn('L',90);}else{turn('R',90);}
      }else{
        left=sonarL.ping_cm();
        if(left>2 && left<=30){turn('R',100);}else{turn('L',100);}
      }
    }
    if(hand=='R')distance = round(sonarR.ping() * 0.343 / 2);
    else distance = round(sonarL.ping() * 0.343 / 2);
    if (distance < minDist && distance != 0)distance = minDist;
    if (distance > maxDist || distance == 0)distance = maxDist;
    distance = constrain(map(distance, minDist, maxDist, 0, 100), 0, 100);
    err = distance - 50;
    P = err;
    D = err - lasterr;
    lasterr=err;
    spd = 5 * P + 4 * D;
    if(hand=='R')setMotors(min(max(maxSpd+spd, minSpd), maxSpd), min(max(maxSpd-spd, minSpd), maxSpd));
    else setMotors(min(max(maxSpd-spd, minSpd), maxSpd), min(max(maxSpd+spd, minSpd), maxSpd));
    delay(1);
  }
  delay(100);
  setMotors(0,0);
}

void followWallBoth()
{
  int minDist=50, maxDist=250, minSpd=120, maxSpd=200;
  int front, left, right, distanceR, distanceL, err, lasterr = 0, P, D, spd;
  while (getPattern(5)=="00000") {
    distanceR = round(sonarR.ping() * 0.343 / 2);
    distanceL = round(sonarL.ping() * 0.343 / 2);
    if (distanceR < minDist && distanceR != 0)distanceR = minDist;
    if (distanceR > maxDist || distanceR == 0)distanceR = maxDist;
    if (distanceL < minDist && distanceL != 0)distanceL = minDist;
    if (distanceL > maxDist || distanceL == 0)distanceL = maxDist;
    distanceR = constrain(map(distanceR, minDist, maxDist, 0, 100), 0, 100);
    distanceL = constrain(map(distanceL, minDist, maxDist, 0, 100), 0, 100);
    err = distanceR - distanceL;
    P = err;
    D = err - lasterr;
    lasterr=err;
    spd = 5 * P + 4 * D;
    setMotors(min(max(maxSpd+spd, minSpd), maxSpd), min(max(maxSpd-spd, minSpd), maxSpd));
//    setMotors(min(max(maxSpd-spd, minSpd), maxSpd), min(max(maxSpd+spd, minSpd), maxSpd));
    delay(10);
  }
  delay(200);
  setMotors(0,0);
}
