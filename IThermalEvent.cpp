#include <iostream>
#include "IThermalEvent.h"

IThermalEvent::IThermalEvent()
    : fCurrent(0.), fVoltage(0.),
      fTemp(new double[4])
{}

IThermalEvent::~IThermalEvent()
{
  delete[] fTemp;
}

void IThermalEvent::SetTemperature(double T1, double T2, double T3, double T4)
{
  fTemp[0] = T1;
  fTemp[1] = T2;
  fTemp[2] = T3;
  fTemp[3] = T4;
}

double IThermalEvent::GetdT(const int s1, const int s2) const
{
  double dT = fTemp[s1-1] - fTemp[s2-1];
  if (dT<0)
    dT = fTemp[s2-1] - fTemp[s1-1];
  return dT;
}

double IThermalEvent::GetT(const int s1, const int s2) const
{
  double T = (fTemp[s1-1]+fTemp[s2-1]) / 2;
  return T;
}

double IThermalEvent::GetTError(const int s1, const int s2) const
{
  double Te = fTemp[s1-1] - (fTemp[s1-1]+fTemp[s2-1]) / 2;
  if (Te<0)
    Te = (fTemp[s1-1]+fTemp[s2-1]) / 2 - fTemp[s1-1];
  return Te;
}
