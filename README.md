# Gesture-Controlled-IoT-based-Robot-
A gesture-controlled IoT-based robot is a robotic system that can be controlled through hand gestures and movements, offering a seamless and user-friendly interaction experience. Our project showcases the potential of integrating gesture control with IoT to create smart, responsive systems. 

The application of gesture-controlled IoT-based robots in healthcare spans various critical domains, enhancing patient care, therapy sessions, and hospital operations. These robots serve as versatile tools for remote patient monitoring, allowing healthcare providers to navigate hospital wards, monitor vital signs, and provide timely assistance.

A prototype of the gesture-controlled IoT-based robot has been developed, following the direction given by commonly known patterns. It follows five different gestures made by hand to perform its directional movement. 

1.	Stop/Steady: when it gets a hand gesture that is parallel with horizontal.
2.	Front/Forward: when it gets a hand gesture that creates the highest -90 degree in the Y axis.
3.	Rear: when it gets a hand gesture that creates the highest +90 degree in the Y axis.
4.	Left: when it gets a hand gesture that creates the highest -90 degree in the X axis.
5.	Right: when it gets a hand gesture that creates the highest +90 degree in the X axis.

**Hardware Requirements:**
![Screenshot 2024-08-03 121913](https://github.com/user-attachments/assets/3b40ce0e-28d1-4b65-8fc4-38bfddefdde0)

**Working:**

The gesture control IoT-based robot operates through a transmitter and receiver system. The transmitter, consisting of an Arduino Nano, NRF24L01+ module, MPU6050 sensor, and a DC battery, captures and interprets user gestures. The MPU6050 detects hand or body motions, and the Arduino Nano processes this data to recognize specific gestures. These commands are then sent wirelessly via the NRF24L01+ transceiver to the receiver module.

The receiver, also with an Arduino Nano, NRF24L01+ module, L298N driver module, and a DC battery, decodes the commands and controls the robot's motors accordingly using the L298N driver. This setup allows the robot to move and perform actions based on the user's gestures, providing intuitive and hands-free control.

**Circuit Diagram:**


1.1 Transmitter Diagram: 
![image](https://github.com/user-attachments/assets/62eadafc-4d5d-4ba9-b93d-4b99ee45a4c3)

1.2 Receiver Diagram: 
![image](https://github.com/user-attachments/assets/5a1a42d2-3ae1-4d31-9af0-7b3ced743e76)




In summary, creating a gesture-controlled IoT-based robot marks a big step forward in robotics and how we interact with machines. The project successfully demonstrates the implementation of a gesture-control IoT-based robot.




