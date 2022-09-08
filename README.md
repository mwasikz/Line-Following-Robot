## Line Following Robot Using PID Algorithm

### 🟠 Demo



https://user-images.githubusercontent.com/74035623/189166476-beff110f-dc74-4c35-885b-17193e444c45.mp4




A line following robot created using Arduino Nano. This robot can also sense obstacles and avoid them, follow a wall, and skip over line gaps. Sonar sensor has been used to detect obstacles. This robot has a programmable interface. The type of line can be changed from the interface. It can swicth between black line or white surface or white line on black surface. Motor speed can also be changed through the interface. The robot can perform auto calibration. 

<p align="center">
  <img src="https://github.com/mwasikz/Line-Following-Robot/blob/main/reademe_assets/65268342_468142970422499_9171565561509838848_n.jpg" width="600">
  <img src="https://github.com/mwasikz/Line-Following-Robot/blob/main/reademe_assets/LFR.png" width="600">
  <img src="https://github.com/mwasikz/Line-Following-Robot/blob/main/reademe_assets/69096385_2035662713200444_142382825901916160_n.jpg" width="600"> 
</p>


### 🟠 PID Algorithm
The accuracy of the movement of a line follower mostly depends on the motor movement and sensing system. Many algorithms are used to coordinate the line data read by the sensors to control the motors. But a simple and most precise control is obtained by PID (proportional integral derivative) algorithm.

The PID function formula having a combination of three successive terms [P]+[I]+[D] is as follows:

![equation](https://latex.codecogs.com/svg.image?f(t)%20=%20%5BK_%7Bp%7De(t)%5D&plus;%5BK_%7Bi%7D%5Cint%20e(t)dt%5D&plus;%5BK_%7Bp%7D%5Cfrac%7Bde%7D%7Bdt%7D%5D)

- Kp=constant for proportion
- Ki=constant for integral
- Kd=constant for derivative
- P=Kp multiplied by error value
- I=Ki multiplied with previous integral error value
- D=Kd multiplied by derivative value


