#include <iostream>
#include <cmath>
#include <fstream>
#include <TMultiGraph.h>
#include <TAxis.h>
#include "IThermalHandle.h"

using std::string;
using std::vector;

Measurement::IThermalHandle::IThermalHandle()
    : fArea(100e-6), fLength(30e-3),
      fT0(4.2), fTf(15.),
      fSensor1(1), fSensor2(2),
      fMg(new TMultiGraph())
{}

Measurement::IThermalHandle::~IThermalHandle()
{
  fEvent.clear();
}

void Measurement::IThermalHandle::SetSensor(int s1, int s2)
{
  fSensor1 = s1;
  fSensor2 = s2;
}

void Measurement::IThermalHandle::Load(string filename)
{
  std::ifstream inputfile(filename.c_str());
  string buff;
  double dbuff[7];

  if (!inputfile)
    throw "Cannot open this file!!!";
  else {
    getline(inputfile, buff);
    while (true) {
      inputfile >> dbuff[0] >> dbuff[1] >> dbuff[2] >> dbuff[3]
                >> dbuff[4] >> dbuff[5] >> dbuff[6];
      if (!inputfile) break;
      //if (event) {
      //  delete event;
      //  event = NULL;
      //}
      IThermalEvent* event = new IThermalEvent();
      event->SetCurrent(dbuff[5]);
      event->SetVoltage(dbuff[6]);
      event->Set1stTemp(dbuff[0]);
      event->Set2ndTemp(dbuff[1]);
      event->Set3rdTemp(dbuff[2]);
      event->Set4thTemp(dbuff[3]);
      fEvent.push_back(event);
    }
  }
  //delete event;
}

double Measurement::IThermalHandle::GetC2600Curve(double T)
{
   // fitting parameters
  double par[9] = {0.021035, -1.01835,  4.54083,
                   -5.03374,  3.20536, -1.12933,
                   0.174057, -0.0038151, 0.};

  double ax = 0.;
  for (int j=0; j<9; j++)
    ax += par[j] * pow(log10(T),j);
  double k = pow(10,ax);
  return k;
}

TGraphErrors* Measurement::IThermalHandle::GetC2600()
{
  // fitting parameters
  double par[9] = {0.021035, -1.01835,  4.54083,
                   -5.03374,  3.20536, -1.12933,
                   0.174057, -0.0038151, 0.};

  TGraphErrors* gr = new TGraphErrors();
  int    nT = 100;
  double dT = (fTf-fT0)/nT;
  double T, k;
  double ax = 0.;

  for (int i=0; i<nT; i++) {
    T  = fT0 + dT*i;
    ax = 0.;
    for (int j=0; j<9; j++)
      ax += par[j] * pow(log10(T),j);
    k = pow(10,ax);
    gr->SetPoint(i, T, k);
    gr->SetPointError(i, 0.0, k*0.02);
  }

  gr->SetFillColor(kSpring-9);
  gr->SetLineColor(kYellow);
  gr->SetLineWidth(2);
  return gr;
}

TGraphErrors* Measurement::IThermalHandle::GetData()
{
  if (fEvent.size()==0)
    throw "Data is not read!!";

  TGraphErrors* gr = new TGraphErrors();
  double T, k, dT, dTe;
  for (vector<int>::size_type i=1; i<fEvent.size(); i++) {
    T  = fEvent[i]->GetT(fSensor1, fSensor2);
    dT = fEvent[i]->GetdT(fSensor1, fSensor2);
    k  = fLength * fEvent[i]->GetPower() / fArea / dT;
    dTe= 0.01 / dT;
    //std::cout << T << " " << fEvent[i]->GetPower() << " " << dT << std::endl;
    gr->SetPoint(i-1, T, k);
    gr->SetPointError(i-1, fEvent[i]->GetTError(fSensor1,fSensor2), dTe*k);
  }

  gr->SetLineWidth(2);
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(1.1);
  return gr;
}

void Measurement::IThermalHandle::Draw()
{
  fMg->Add(GetC2600(), "lfe3");
  fMg->Add(GetData(), "pe");
  fMg->SetTitle("; ; Thermal Conductivity [W/m/K]");
  fMg->Draw("a");
  fMg->GetXaxis()->SetLimits(fT0, fTf);
  fMg->GetXaxis()->SetLabelSize(0);
  fMg->GetXaxis()->SetTickLength(0.02);
}

void Measurement::IThermalHandle::DrawDivide()
{
  double fit;
  TGraphErrors* gr = new TGraphErrors();
  double* T = GetData()->GetX();
  double* k = GetData()->GetY();

  for (int i=0; i<GetData()->GetN(); i++) {
    fit = GetC2600Curve(T[i]);
    gr->SetPoint(i, T[i], k[i]/fit);
    gr->SetPointError(i, GetData()->GetErrorX(i), 0.02*k[i]/fit);
  }

  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(1.1);
  gr->SetMarkerColor(kRed);
  gr->SetLineWidth(2);
  gr->SetLineColor(kRed);
  gr->SetTitle("; Temperature [K]; Measurement / Data");
  gr->Draw("ape");
  gr->GetXaxis()->SetLimits(fT0, fTf);
  gr->GetXaxis()->SetTickLength(0.02);
}
