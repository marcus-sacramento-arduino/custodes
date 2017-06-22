//Programa: Programa de Vigia para casa
//Descrição: Simula presença através do acionamento de lampadas e aparelhos de TV
//Autor: Marcus Sacramento

#include <Wire.h>
#include <DS1307.h>
#include "Arduino.h"
#include "Custodes.h"

#ifndef UNIT_TEST  // IMPORTANT LINE!
int delayTime = 30000;
int minLight = 50;
//Variáveis de tempo para o RTC IC2
DS1307 rtc;
uint8_t sec, min, hour, day, month;
uint16_t year;
//Variáveis para o LDR e Relay
int LDRpin = 0;
float lightValue = 0;
int chanel1 = 7;
int chanel2 = 8;

Custodes custodes;

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
  pinMode(chanel1,OUTPUT);
  pinMode(chanel2,OUTPUT);
  digitalWrite(chanel1, LOW);
  digitalWrite(chanel2, LOW);
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
  Serial.print(custodes.sala);
  Serial.print(",");
  Serial.print(custodes.garagem);
  Serial.print(",");
}

float LDRRead(int pin){
  return map(analogRead(pin), 0, 1023, 0, 255);
}

void lampControl(bool sala, bool garagem,int chanel1, int chanel2){
  if(sala){
    Serial.print("Acende Sala,");
    digitalWrite(chanel1, HIGH);
  }else{
    Serial.print("Apaga Sala1,");
    digitalWrite(chanel1, LOW);
  }
  if(garagem){
    Serial.print("Acende Garagem");
    digitalWrite(chanel2, HIGH);
  }else{
    Serial.print("Apaga Garagem");
    digitalWrite(chanel2, LOW);
  }
}

void loop()
{
  //get time from RTC
  rtc.get(&sec, &min, &hour, &day, &month, &year);
  lightValue = LDRRead(LDRpin);
  custodes.salaCheck(lightValue, hour, min, minLight);
  custodes.garagemCheck(lightValue, hour, min, minLight);

  logDateTime(lightValue);
  lampControl(custodes.sala, custodes.garagem, chanel1, chanel2);
  custodes.offControl(hour);

  delay(delayTime);
}

#endif    // IMPORTANT LINE!
