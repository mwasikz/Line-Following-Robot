## Line Following Robot Using PID Algorithm

### 🟠 Demo

https://user-images.githubusercontent.com/74035623/172057608-b405b7c9-6d87-4bb6-a85a-57520bc15b1f.mp4

A line following robot created using Arduino Nano. This robot can also sense obstacles and avoid them. Sonar sensor has been used to detect obstacles. This robot has a programmable interface. The type of line can be changed from the interface. It can swicth between black line or white surface or white line on black surface. Motor speed can also be changed through the interface. 
<p align="center">
<img src="https://github.com/mwasikz/Line-Following-Robot/blob/main/reademe_assets/LFR.png" width="400">
</p>

### PID Algorithm
The accuracy of the movement of a line follower mostly depends on the motor movement and sensing system. Many algorithms are used to coordinate the line data read by the sensors to control the motors. But a simple and most precise control is obtained by PID (proportional integral derivative) algorithm.

The PID function formula having a combination of three successive terms [P]+[I]+[D] is as follows:
<img src="https://latex.codecogs.com/gif.latex?f(t) = [K_{p}e(t)]+[K_{i}\int e(t)dt]+[K_{p}\frac{de}{dt}]" />
f(t) = [K_{p}e(t)]+[K_{i}\int e(t)dt]+[K_{p}\frac{de}{dt}]

