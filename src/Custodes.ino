//Programa: Programa de Vigia para casa
//Descrição: Simula presença através do acionamento de lampadas e aparelhos de TV
//Autor: Marcus Sacramento

#include <Wire.h>
#include <DS1307.h>

int delayTime = 30000;
int minLight = 50;
//Variáveis de tempo para o RTC IC2
DS1307 rtc;
uint8_t sec, min, hour, day, month;
uint16_t year;
//Variáveis para o LDR e Relay
int LDRpin = 0;
float lightValue = 0;
int chIn1 = 7;
int chIn2 = 8;
boolean  in1 = false;
boolean  in2 = false;


void setup()
{
  Serial.begin(9600);
  //Serial.println("Inicializando o RTC...");
  Serial.print("Data,Luminosidade,Canal 1,Canal 2,Luz Sala,Luz Garagem");
  //Ajuste de Data e Hora do RTC IC2
  // rtc.set(0, 19, 21, 20, 06, 2017); //08:00:00 24.12.2014 //sec, min, hour, day, month, year
  rtc.start();
  //Configurando o pino de leitura do LDRpin e dos canais do módulo rele
  pinMode(LDRpin,INPUT);
  pinMode(chIn1,OUTPUT);
  pinMode(chIn2,OUTPUT);
  digitalWrite(chIn1, LOW);
  digitalWrite(chIn2, LOW);
}

void logDateTime(float lightValue){
  Serial.print("\n");
  Serial.print(year, DEC);
  Serial.print("-");
  Serial.print(month, DEC);
  Serial.print("-");
  Serial.print(day, DEC);
  Serial.print("T");
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(min, DEC);
  Serial.print(":");
  Serial.print(sec, DEC);
  Serial.print(",");
  Serial.print(lightValue);
  Serial.print(",");
  Serial.print(in1);
  Serial.print(",");
  Serial.print(in2);
  Serial.print(",");
}

float LDRRead(int pin){

  return map(analogRead(pin), 0, 1023, 0, 255);
}


void garageControl(float lightValue){
  if(lightValue<minLight && hour>=20 && hour<=23){
    //Serial.print("|N tem 19>=<23 falso|Verdadeiro|");
    in2 = true;
    if((min>=0 && min<=15)){
      //Serial.print("|N tem 19>=<23 0>=<15 verdadeiro|Falso|");
      in2 = false;
    }
    if((min>=30 && min<=40)){
      // Serial.print("|N tem 23>=<19 30>=<40 verdadeiro|Falso|");
      in2 = false;
    }
    if(lightValue>minLight && hour<19){
      // Serial.print("|Tem Luz|Falso|");
      in2 = false;
    }
  }
}

void roomControl(float lightValue){
  if(lightValue<minLight && hour>=18 && hour<=23){
    //Serial.print("|N tem 19>=<23 falso|Verdadeiro|");
    in1 = true;
    if((min>=15 && min<=30)){
      //Serial.print("|N tem 19>=<23 0>=<15 verdadeiro|Falso|");
      in1 = false;
    }
    if((min>=40 && min<=59)){
      // Serial.print("|N tem 23>=<19 30>=<40 verdadeiro|Falso|");
      in1 = false;
    }
    if(lightValue>minLight && hour<18){
      // Serial.print("|Tem Luz|Falso|");
      in1 = false;
    }
  }
}

void offControl(){
  if(hour>=0 && hour <=18){
    in1 = false;
    in2 = false;
    digitalWrite(chIn1, LOW);
    digitalWrite(chIn2, LOW);
  }
}
void loop()
{
  //get time from RTC
  rtc.get(&sec, &min, &hour, &day, &month, &year);
  lightValue = LDRRead(LDRpin);
  //roomControl(lightValue);
  logDateTime(lightValue);
  garageControl(lightValue);
  if(in1){
    Serial.print("Acende Sala,");
    digitalWrite(chIn2, HIGH);
  }else{
    Serial.print("Apaga Sala,");
    digitalWrite(chIn2, LOW);
  }
  if(in2){
    Serial.print("Acende Garagem");
    digitalWrite(chIn2, HIGH);
  }else{
    Serial.print("Apaga Garagem");
    digitalWrite(chIn2, LOW);
  }
  offControl();
  delay(delayTime);
}
