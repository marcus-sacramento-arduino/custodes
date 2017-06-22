#ifndef CUSTODES_H
#define CUSTODES_H


class Custodes {
public:
  bool  sala = false;
  bool  garagem = false;
  Custodes() {}
  void garagemCheck(float lightValue,int hour, int min, float minLight);
  void salaCheck(float lightValue,int hour, int min,float minLight);
  void offControl(int hour);
};

#endif
