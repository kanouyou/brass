#ifndef ITHERMALEVENT_HH
#define ITHERMALEVENT_HH

class IThermalEvent
{
  public:
    IThermalEvent();
    ~IThermalEvent();

    // set data
    void SetCurrent(double curr) { fCurrent = curr; }
    void SetVoltage(double volt) { fVoltage = volt; }
    void SetTemperature(double, double, double, double);
    void Set1stTemp(double temp) { fTemp[0] = temp; }
    void Set2ndTemp(double temp) { fTemp[1] = temp; }
    void Set3rdTemp(double temp) { fTemp[2] = temp; }
    void Set4thTemp(double temp) { fTemp[3] = temp; }

    // get data
    double GetCurrent() const { return fCurrent; }
    double GetVoltage() const { return fVoltage; }
    double GetPower() const { return fVoltage*fCurrent; }
    double Get1stTemp() const { return fTemp[0]; }
    double Get2ndTemp() const { return fTemp[1]; }
    double Get3rdTemp() const { return fTemp[2]; }
    double Get4thTemp() const { return fTemp[3]; }
    double* GetTemperature() { return fTemp; }

    double GetdT(const int, const int) const;
    double GetT (const int, const int) const;
    double GetTError(const int, const int) const;

  private:
    double  fCurrent;
    double  fVoltage;
    double* fTemp;
};

#endif
