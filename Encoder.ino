int counter1=0,counter3=0; 
int counter2=0,counter4=0;
int as1,as2,as3,as4;
int ls1,ls2,ls3,ls4;  

int clkA=A0,clkB=A2,clkC=A4,clkD=2;    //clk pins of the 4 encoders
int dtA=A1,dtB=A3,dtC=A5,dtD=3;        //dt pins of the 4 encoders

int pwm1=9,pwm2=10;           //PWM pins of the 2 motor drivers
int brk1=6,brk2=7;            //BRK pins of the 2 motor drivers
int dir1=11,dir2=12;          //DIR pins of the 2 motor drivers

int spd=30;                  //pwm value of the motor drivers

void setup() { 
  pinMode (clkD,INPUT);
  pinMode (dtD,INPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(brk1,OUTPUT);
  pinMode(brk2,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(dir2,OUTPUT);
  Serial.begin (9600);
  ls1=digitalRead(clkA);
  ls2=digitalRead(clkB);
  ls3=digitalRead(clkC);
  ls4=digitalRead(clkD);   
} 

void loop() {
  analogWrite(pwm1,spd);
  analogWrite(pwm2,spd);
  
  //Counting the steps rotated by each motor
  
  as1=digitalRead(clkA);
  as2=digitalRead(clkB);
  as3=digitalRead(clkC);
  as4=digitalRead(clkD);
  if(as1!=ls1 || as2!=ls2 || as3!=ls3 || as4!=ls4){
    if(as1!=ls1){
    if (digitalRead(dtA) != as1) { 
       counter1 ++;
     } else {
       counter1 --;
     }
    }
     if(as2!=ls2){
     if (digitalRead(dtB) != as2) { 
      counter2 ++;
     } else {
      counter2 --;
     }
    }
    if(as3!=ls3){
    if (digitalRead(dtC) != as3) { 
       counter3 ++;
     } else {
        counter3 --;
     }
    }
     if(as4!=ls4){
     if (digitalRead(dtD) != as4) { 
        counter4 ++;
     } else {
        counter4 --;
      }
     }
    Serial.print("Counter1= ");
    Serial.print(counter1);
    Serial.print("    Counter2= ");
    Serial.print(counter2);
    Serial.print("    Counter3= ");
    Serial.print(counter3);
    Serial.print("    Counter4= ");
    Serial.println(counter4);
  }
  ls1=as1;  
  ls2=as2;
  ls3=as3;
  ls4=as4;

if(counter1<0)
  counter1=-counter1;
  
//Moving the drive in a square

  if(counter4<50)
    Forward();  
  if(counter4>=50 && counter4<100) 
    Right();
  if(counter4>=100 && counter4<150)
    Back();
  if(counter4>=150 && counter4>200)
    Left();
  if(counter4==200)
    counter4=0;
  //delay(2000);
}

void Forward(){
  //Brake();
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,LOW);
}
void Back(){
  //Brake();
  digitalWrite(dir1,HIGH);
  digitalWrite(dir2,HIGH);
}
void Right(){
  //Brake();
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,HIGH);
}
void Left(){
  //Brake();
  digitalWrite(dir1,HIGH);
  digitalWrite(dir2,LOW);
}
void Brake(){
  digitalWrite(brk1,HIGH);
  digitalWrite(brk2,HIGH);
  delay(100);
  digitalWrite(brk1,LOW);
  digitalWrite(brk2,LOW);
}
