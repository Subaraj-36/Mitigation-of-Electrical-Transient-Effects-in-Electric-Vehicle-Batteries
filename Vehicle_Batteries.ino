#include <Servo.h>
Servo esc;
const int currentPin = A0; 
mosfetPin  = 10;
const int escPin     = 9; 
const int rpmPin     = 2; 

volatile int count = 0;
int rpm = 0;
float sensitivity = 0.185; 

zeroCurrent = 0.0;
float current = 0.0;
float thresholdCurrent = 0.3; 

bool pulseGiven = false
void setup() {  
Serial.begin(9600);  
esc.attach(escPin);  
esc.writeMicroseconds(1000); 
pinMode(rpmPin, INPUT);  attachInterrupt(digitalPinToInterrupt(rpmPin), pulse, RISING); pinMode(mosfetPin, OUTPUT);  
digitalWrite(mosfetPin, LOW);  
long sum = 0;  
for (int i = 0; i < 500; i++) {    
sum += analogRead(currentPin);    
delay(2);  
} 
zeroCurrent = (sum / 500.0) * 5.0 / 1023.0;  Serial.println("System Ready...");
}
void loop() { 
 
esc.writeMicroseconds(1400);  
count = 0;  delay(1000);  
rpm = count * 60;  

int sensorValue = analogRead(currentPin);  
float voltage = sensorValue * (5.0 / 1023.0);  
current = (voltage - zeroCurrent) / sensitivity;

if (current >= thresholdCurrent && !pulseGiven) {   

Serial.println("Threshold Reached! MOSFET Pulse Triggered");    
digitalWrite(mosfetPin, HIGH);    
delay(50);                    
digitalWrite(mosfetPin, LOW);   
pulseGiven = true; 

}
if (current < thresholdCurrent) { 
   
pulseGiven = false;  

} 

Serial.print("RPM: ");  
Serial.print(rpm);  
Serial.print(" | Current: ");  
Serial.print(current, 3); 
Serial.println(" A");  
delay(200);

}

void pulse() {  

count++;
}
