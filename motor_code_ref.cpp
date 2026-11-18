 const int IN1=5; 
const int IN2=4; 
const int ENA=6; 
 
const int IN3=8; 
const int IN4=7; 
const int ENB=9; 
 
void setup() { 
     Serial.begin(9600);
     pinMode(A0, INPUT);
     pinMode(A5, INPUT);
     pinMode(IN1, OUTPUT); 
     pinMode(IN2, OUTPUT); 
     pinMode(ENA, OUTPUT); 
      
     pinMode(IN4, OUTPUT);

     pinMode(IN3, OUTPUT); 
     pinMode(ENB, OUTPUT); 
} 
 
void loop() { 
 updateMotors();
 printEncoderReadings();
}

void printEncoderReadings() {
 static unsigned long lastReading = 0;
 unsigned long now = millis();
 if (now - lastReading < 2) return;
 lastReading = now;

 Serial.print("A0:");
 Serial.print(analogRead(A0));
 Serial.print("\tA5:");
 Serial.println(analogRead(A5));
}

void updateMotors() {
 static byte step = 0;
 static unsigned long stepStarted = 0;
 static unsigned long stepDuration = 0;
 unsigned long now = millis();
 if (now - stepStarted < stepDuration) return;
 stepStarted = now;

 switch (step) {
 case 0:
 case 2:
     Motor1_Brake();
     Motor2_Brake();
     stepDuration = 100;
     break;
 case 1:
     Motor1_Forward(200);
     Motor2_Forward(200);
     stepDuration = 1000;
     break;
 case 3:
     Motor1_Backward(200);
     Motor2_Backward(200);
     stepDuration = 1000;
     break;
 }
 step = (step + 1) % 4;
}
 
void Motor1_Forward(int Speed)  
{ 
     digitalWrite(IN1,HIGH);  
     digitalWrite(IN2,LOW);   
     analogWrite(ENA,Speed); 
} 
   
void Motor1_Backward(int Speed)  
{     
     digitalWrite(IN1,LOW);  
     digitalWrite(IN2,HIGH);   
     analogWrite(ENA,Speed); 
} 
void Motor1_Brake()       
{ 
     digitalWrite(IN1,LOW);  
     digitalWrite(IN2,LOW);  
}      
void Motor2_Forward(int Speed)  
{ 
     digitalWrite(IN3,HIGH);  
     digitalWrite(IN4,LOW);   
     analogWrite(ENB,Speed); 
} 
   
void Motor2_Backward(int Speed)  
{     
     digitalWrite(IN3,LOW);  
     digitalWrite(IN4,HIGH);   
     analogWrite(ENB,Speed); 
} 
void Motor2_Brake() 
{ 
     digitalWrite(IN3,LOW);  
     digitalWrite(IN4,LOW);
}
