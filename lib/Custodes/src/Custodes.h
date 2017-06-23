#ifndef CUSTODES_H
#define CUSTODES_H

class Custodes {
public:
  Custodes() {}
  bool garagemCheck(float lightValue,int hour, int min, float minLight);
  bool salaCheck(float lightValue,int hour, int min,float minLight);
};
#endif
