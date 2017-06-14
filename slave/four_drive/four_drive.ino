//#include <MsTimer2.h>
//#include <FlexiTimer2.h> 
//2015.5.25  xiu  gai  fengyang

//motor defin
#include <avr/wdt.h>
#include"PinChangeInt.h"
#define TIMEOUT WDTO_8S 

int al1=2;
int al2=3;
int alc=11;

int ar1=4;
int ar2=5;
int arc=10;

int bl2=7;
int bl1=8;
int blc=9;

int br1=12;
int br2=13;
int brc=6;

double spd=140;
String words1;

String num2;
//int num=0
//State Of The Car
// 0 stop
// 1 running
unsigned int state = 0;

unsigned int al_wheel; //记录U型测速模块的次数
unsigned int ar_wheel;
unsigned int bl_wheel; //记录U型测速模块的次数
unsigned int br_wheel;
double speedAL; 
double speedAR;
double speedBL;
double speedBR;

/**PID定义**/    
//double kp=1.5, ki=0.0, kd=0.5; //single wheel test good
double kp=1.5, ki=0.00, kd=1.2;
double speeds=0; //角度平衡点，PWM差，死区，PWM1，PWM2

String Words;//
            
unsigned long SampleTime2=20;// 采样时间
unsigned long preTime;
int pwm_al,pwm_ar,pwm_bl,pwm_br;
unsigned long pid_pre;
    
double lastErr_AL = 0;
double lastErr_AR = 0;
double lastErr_BL = 0;
double lastErr_BR = 0;

double errSum_AL = 0;
double errSum_AR = 0;
double errSum_BL = 0;
double errSum_BR = 0;

double Setpoint_AL=0;
double Setpoint_AR=0;
double Setpoint_BL=0;
double Setpoint_BR=0;

int Led = 13;


 
int lastTime2;

//void InitPid();
//void go(int d_al,int d_ar,int d_bl,int d_br);
//void testPID();
//void pwm_output(int pwm_al,int pwm_ar,int pwm_bl,int pwm_br);
void aLCount()
{ 
      al_wheel++;   
}
void aRCount()
{
      ar_wheel++;
}
  void bLCount()
{ 
      bl_wheel++;   
}
void bRCount()
{
      br_wheel++;
}
 
void setup ()
{
     Serial.begin(9600);
     // Serial.begin(115200);
       
      attachPinChangeInterrupt(A3,bRCount, FALLING);//pin A3 br
      attachPinChangeInterrupt(A2,bLCount, FALLING);//pin A2 bl
      attachPinChangeInterrupt(A1,aRCount, FALLING);//pin A1 ar
      attachPinChangeInterrupt(A0,aLCount, FALLING);// pin A0 al 
      
      pinMode(al1,OUTPUT);
      pinMode(al2,OUTPUT);
      pinMode(alc,OUTPUT);
      pinMode(ar1,OUTPUT);
      pinMode(ar2,OUTPUT);
      pinMode(arc,OUTPUT);
      pinMode(bl1,OUTPUT);
      pinMode(bl2,OUTPUT);
      pinMode(blc,OUTPUT);
      pinMode(br1,OUTPUT);
      pinMode(br2,OUTPUT);
      pinMode(brc,OUTPUT); 
      pinMode(Led,OUTPUT); 
      digitalWrite(Led,HIGH);    

      InitPid();      
      wdt_enable(TIMEOUT);

      Serial.println("Start Working.");
   
}
 
void loop()
{  
          if(Serial.available()>0)
          {   
                 words1+=(char)Serial.read();
                 delay(2);
                 words1+=(char)Serial.read();
                 delay(2);
                 num2=words1;
                 words1="";                
              while(Serial.available()>0)
              {
	         char ch = (char)(Serial.read());
		 if(ch == ';') 
                {
                  words1 = "";
                   break;
                }
                 Words+=ch;
                 delay(2);
              }
              speeds=Words.toInt();
              if(num2=="on")
              {
                digitalWrite(Led,LOW);
              }
                 if(num2=="off")
              {
                digitalWrite(Led,HIGH);
              }
              if(num2=="go"){
                Setpoint_AL = speeds;
                Setpoint_AR = speeds;
                Setpoint_BL = speeds;
                Setpoint_BR = speeds;
              }
              if(num2=="ga"){
                Setpoint_AL = speeds;
              }
              if(num2=="gb"){
                Setpoint_AR = speeds;
              }
              if(num2=="gc"){
                Setpoint_BL = speeds;
              }
              if(num2=="gd"){
                Setpoint_BR = speeds;
              }
              else if(num2=="sp")
              {
                kp = double(speeds/100.0);
                 num2="";
                 Serial.println("kp==");
                 Serial.print(kp);
              }
              else if(num2=="si")
              {
                ki =  double(speeds/100.0);
                 num2="";
                 Serial.println("ki==");
                 Serial.print(ki);
              }
              else if(num2=="sd")
              {
                kd =  double(speeds/100.0);
                num2="";
                Serial.println("kd==");
                Serial.print(kd);
              }
              
              Words="";
              Serial.println("Your input:");
              Serial.print(num2);
              Serial.println(speeds);
              lastErr_AL=0;
              lastErr_AR=0;
              lastErr_BL=0;
              lastErr_BR=0;
          }
          
        if(num2=="aa"){
          state = 1;//running
          go(1,1,1,1); 
        }
        else if(num2=="bb"){ 
          state = 1;    
          go(-1,-1,-1,-1);
        }
        else if(num2=="tr"){
           state = 1;
          go(1,-1,1,-1);
        }
        else if(num2=="gr"){
           state = 1;
          go(1,0,0,1);
        }
        else if(num2=="br"){ 
           state = 1;
          go(0,-1,-1,0);
        }
        else if(num2=="tl"){
           state = 1;   
           go(-1,1,-1,1);
        }
        else if(num2=="gl"){
           state = 1;
           go(0,1,1,0);
        }
        else if(num2=="bl"){
          state = 1; 
          go(-1,0,0,-1); // al ar bl br 
        }
        else if(num2=="rr"){
           state = 1;
           go(1,-1,-1,1);
        }
        else if(num2=="ll"){
           state = 1;
           go(-1,1,1,-1);
        }
        else if(num2=="ss"){
          go(0,0,0,0);
          state = 0;//stopping
        }
        
        if(state == 1){
          testPID();
        }
        wdt_reset();

}

    void InitPid()
    {

            al_wheel=0;
            ar_wheel=0;
            bl_wheel=0;
            br_wheel=0;
            
            pid_pre = millis();
    }
   
    //===============PID=====================
    void testPID()
    {          
          unsigned long pid_now =millis();
          int pid_time =(pid_now-pid_pre);
          if(pid_time>=SampleTime2)  
          { //compute all the working error variables
             pid_pre = pid_now;                         
//             Serial.print("pid_time=========================");
//             Serial.println(pid_time);
             double al_count = (double)al_wheel;
             double ar_count = (double)ar_wheel;
             double bl_count = (double)bl_wheel;
             double br_count = (double)br_wheel;
            //   long pre_time = millis();
             // double dt = (now - preTime) ;// 微分时间(s)
             speedAL =  al_count/pid_time*40.8854;
             speedAR =  ar_count/pid_time*40.8854;
             speedBL =  bl_count/pid_time*40.8854;
             speedBR =  br_count/pid_time*40.8854;
             
//          Serial.print("speedAL==========================");
//          Serial.println(speedAL);
//          Serial.print("speedAR==========================");
//          Serial.println(speedAR);
//          Serial.print("speedBL==========================");
//          Serial.println(speedBL);
//          Serial.print("speedBR==========================");
//          Serial.println(speedBR);
             
         //    preTime = millis(); 
          al_wheel = 0;
          ar_wheel = 0;
          bl_wheel = 0;
          br_wheel = 0;
            
            double Input_AL = speedAL;
            double Input_AR = speedAR;
            double Input_BL = speedBL;
            double Input_BR = speedBR;
            
            double error_AL = Setpoint_AL - Input_AL;
            double error_AR = Setpoint_AR - Input_AR;
            double error_BL = Setpoint_BL - Input_BL;
            double error_BR = Setpoint_BR - Input_BR;
            
               
            errSum_AL += error_AL;
            errSum_AR += error_AR;
            errSum_BL += error_BL;
            errSum_BR += error_BR;
            
            double dErr_AL=(error_AL -lastErr_AL);
            double dErr_AR=(error_AR -lastErr_AR);
            double dErr_BL=(error_BL -lastErr_BL);
            double dErr_BR=(error_BR -lastErr_BR);
            
//            double Output_AL =kp*(error_AL + ki *errSum_AL +kd *dErr_AL);
//            double Output_AR =kp*(error_AR + ki *errSum_AR +kd *dErr_AR);
//            double Output_BL =kp*(error_BL + ki *errSum_BL +kd *dErr_BL);
//            double Output_BR =kp*(error_BR + ki *errSum_BR +kd *dErr_BR);

            double Output_AL =kp*error_AL + ki *errSum_AL +kd *dErr_AL;
            double Output_AR =kp*error_AR + ki *errSum_AR +kd *dErr_AR;
            double Output_BL =kp*error_BL + ki *errSum_BL +kd *dErr_BL;
            double Output_BR =kp*error_BR + ki *errSum_BR +kd *dErr_BR;
            
//             Serial.print("Output_AL==");
//             Serial.println(Output_AL);
//             Serial.print("Output_AR==");
//             Serial.println(Output_AR);
//             Serial.print("Output_BL==");
//             Serial.println(Output_BL);
//             Serial.print("Output_BR==");
//             Serial.println(Output_BR);
            
            if(Output_AL> 255) Output_AL = 255;
            if(Output_AR> 255) Output_AR = 255;
            if(Output_BL> 255) Output_BL = 255;
            if(Output_BR> 255) Output_BR = 255;
            if(Output_AL< -255) Output_AL = -255;
            if(Output_AR< -255) Output_AR = -255;
            if(Output_BL< -255) Output_BL = -255;
            if(Output_BR< -255) Output_BR = -255;            
            /*计算1.33的speeds次方*/

            pwm_al =  pwm_al  + (int)Output_AL;
            pwm_ar =  pwm_ar  + (int)Output_AR;
            pwm_bl =  pwm_bl  + (int)Output_BL;
            pwm_br =  pwm_br  + (int)Output_BR;
            
            if(pwm_al> 255) pwm_al = 255;
            if(pwm_ar> 255) pwm_ar = 255;
            if(pwm_bl> 255) pwm_bl = 255;
            if(pwm_br> 255) pwm_br = 255;
            if(pwm_al< 0) pwm_al = 0;
            if(pwm_ar< 0) pwm_ar = 0;
            if(pwm_bl< 0) pwm_bl = 0;
            if(pwm_br< 0) pwm_br = 0;
               
//              Serial.print("pwm_al=");
//              Serial.println(pwm_al);
//                             
//              Serial.print("pwm_ar=");              
//              Serial.println(pwm_ar);
//              
//              Serial.print("pwm_bl=");              
//              Serial.println(pwm_bl);
//              
//              Serial.print("pwm_br=");
//              Serial.println(pwm_br);
            
            lastErr_AL = error_AL;
            lastErr_AR = error_AR;
            lastErr_BL = error_BL;
            lastErr_BR = error_BR;
            
            //Output The PWM Signal to L298N 
            pwm_output(pwm_al,pwm_ar,pwm_bl,pwm_br);
         }               
    }
void pwm_output(int pwm_al,int pwm_ar,int pwm_bl,int pwm_br)
{
  analogWrite(alc,pwm_al);
  analogWrite(arc,pwm_ar);
  analogWrite(blc,pwm_bl);
  analogWrite(brc,pwm_br);
}
void go(int d_al,int d_ar,int d_bl,int d_br)
{  
  if(d_al>0)
  {
    digitalWrite(al2,HIGH);
    digitalWrite(al1,LOW);
  }
  else if(d_al==0)
  {
    analogWrite(alc,150);
    digitalWrite(al2,HIGH);
    digitalWrite(al1,HIGH);     
  }  else 
  {
    digitalWrite(al2,LOW);
    digitalWrite(al1,HIGH);
  }
  if(d_ar>0)
  {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
    digitalWrite(ar1,HIGH);
    digitalWrite(ar2,LOW);
  }
  else if(d_ar==0)
  {
    analogWrite(arc,150);
    digitalWrite(ar2,HIGH);
    digitalWrite(ar1,HIGH);     
  }
  else
  {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
    digitalWrite(ar1,LOW);
    digitalWrite(ar2,HIGH);
  }
  if(d_bl>0)
  {
    digitalWrite(bl2,LOW);
    digitalWrite(bl1,HIGH);
  }
    else if(d_bl==0){
    analogWrite(blc,150);
    digitalWrite(bl2,HIGH);
    digitalWrite(bl1,HIGH);     
  }  
  else
  {
    digitalWrite(bl2,HIGH);
    digitalWrite(bl1,LOW);
  }
  if(d_br>0)
  {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
    digitalWrite(br2,LOW);
    digitalWrite(br1,HIGH);
  }
    else if(d_br==0){
    analogWrite(brc,150);
    digitalWrite(br2,HIGH);
    digitalWrite(br1,HIGH);     
  } 
  else
  {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    digitalWrite(br2,HIGH);
    digitalWrite(br1,LOW);
  }
}



