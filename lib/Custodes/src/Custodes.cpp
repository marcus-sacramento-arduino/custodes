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
  @return result
  TODO Adicionar o retorno em boolean
*/
void Custodes::garagemCheck(float lightValue, int hour, int min, float minLight){
  if(hour>=20 && hour<=23){
    //Serial.print("|N tem 19>=<23 falso|Verdadeiro|");
    garagem = true;
    if((min>=0 && min<=15)){
      //Serial.print("|N tem 19>=<23 0>=<15 verdadeiro|Falso|");
      garagem = false;
    }
    if((min>=30 && min<=40)){
      // Serial.print("|N tem 23>=<19 30>=<40 verdadeiro|Falso|");
      garagem = false;
    }
    if(lightValue>minLight && hour<19){
      // Serial.print("|Tem Luz|Falso|");
      garagem = false;
    }
  }
}

/**
  Checa a hora e luminosidade na Sala

  @param lightValue Valor atual de luminosidade
  @param hour Hora atual
  @param min Minuto atual
  @param minLight Luminosidade mínima para atuar
  @return result
  TODO Adicionar o retorno em boolean
*/
void Custodes::salaCheck(float lightValue, int hour, int min, float minLight){
  if(hour>=18 && hour<=23){
    //Serial.print("|N tem 19>=<23 falso|Verdadeiro|");
    sala = true;
    if((min>=15 && min<=30)){
      //Serial.print("|N tem 19>=<23 0>=<15 verdadeiro|Falso|");
      sala = false;
    }
    if((min>=40 && min<=59)){
      // Serial.print("|N tem 23>=<19 30>=<40 verdadeiro|Falso|");
      sala = false;
    }
    if(lightValue>minLight && hour<18){
      // Serial.print("|Tem Luz|Falso|");
      sala = false;
    }
  }
}

/**
  Realiza Shutdown dos componentes

  @param hour Hora atual
  @return result
  TODO Adicionar o retorno em boolean
*/
void Custodes::offControl(int hour){
  if(hour>=0 && hour <=18){
    sala = false;
    garagem = false;
  }
}
