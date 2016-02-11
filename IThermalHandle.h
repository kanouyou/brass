#ifndef ITHERMALHANDLE_HH
#define ITHERMALHANDLE_HH

#include <string>
#include <vector>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include "IThermalEvent.h"

namespace Measurement
{ class IThermalHandle; }

class Measurement::IThermalHandle
{
  public:
    IThermalHandle();
    ~IThermalHandle();

    // set thermosensor
    void SetSensor(int s1, int s2);

    // set sample's cross section
    void SetArea(double A) { fArea = A; }

    // set measured length
    void SetLength(double l) { fLength = l; }

    // load measurement data
    void Load(std::string filename);

    // get c2600
    double GetC2600Curve(double T);

    // get c2600 curve from NIST
    TGraphErrors* GetC2600();

    // get data plot from measurement
    TGraphErrors* GetData();

    // draw the data with NIST reference
    void Draw();

    // draw measurement / NIST
    void DrawDivide();

  private:
    double fArea;
    double fLength;
    double fT0;
    double fTf;
    int    fSensor1;
    int    fSensor2;
    std::vector<IThermalEvent*> fEvent;
    TMultiGraph* fMg;

};

#endif
