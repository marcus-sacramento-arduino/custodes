/**
Custodes Library
Name: Biblioteca de vigilância
Purpose: Definir funções para checagem de ambiente e horas de atuação

@author Marcus Sacramento
@version 1.0.0
*/
#include "Custodes.h"

/**
Checa a hora e luminosidade na Garagem

@param lightValue Valor atual de luminosidade
@param hour Hora atual
@param min Minuto atual
@param minLight Luminosidade mínima para atuar
@return result booleano
*/
bool Custodes::garagemCheck(float lightValue, int hour, int min, float minLight){
  bool result = false;
  if(hour>=19 && hour<=23){
    //Serial.print("|N tem 19>=<23 falso|Verdadeiro|");
    result = true;
    if((min>=0 && min<=15)){
      //Serial.print("|N tem 19>=<23 0>=<15 verdadeiro|Falso|");
      result = false;
    }
    if((min>=30 && min<=40)){
      // Serial.print("|N tem 23>=<19 30>=<40 verdadeiro|Falso|");
      result = false;
    }
    if(lightValue>minLight && hour<19){
      // Serial.print("|Tem Luz|Falso|");
      result = false;
    }
  }else{
    result = false;
  }
  return result;
}

/**
Checa a hora e luminosidade na Sala

@param lightValue Valor atual de luminosidade
@param hour Hora atual
@param min Minuto atual
@param minLight Luminosidade mínima para atuar
@return result booleano
*/
bool Custodes::salaCheck(float lightValue, int hour, int min, float minLight){
  bool result = false;
  if(hour>=18 && hour<=23){
    //Serial.print("|N tem 19>=<23 falso|Verdadeiro|");
    result = true;
    if((min>=15 && min<=30)){
      //Serial.print("|N tem 19>=<23 0>=<15 verdadeiro|Falso|");
      result = false;
    }
    if((min>=40 && min<=59)){
      // Serial.print("|N tem 23>=<19 30>=<40 verdadeiro|Falso|");
      result = false;
    }
    if(lightValue>minLight && hour<18){
      // Serial.print("|Tem Luz|Falso|");
      result = false;
    }
  }else{
    result = false;
  }
  return result;
}
