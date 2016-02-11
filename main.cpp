#include <iostream>
#include <TApplication.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include "IThermalHandle.h"

int main(int argc, char** argv)
{
  TApplication* app = new TApplication("app", &argc, argv);

  TCanvas* c0 = new TCanvas("c0", "c0", 640, 550);
  c0->SetTicks(1,1);

  gStyle->SetEndErrorSize(0);
  gStyle->SetTitleSize(0.041, "xy");
  gStyle->SetTitleOffset(1.4, "y");
  gStyle->SetLabelSize(0.041, "xy");

  Measurement::IThermalHandle* hand = new Measurement::IThermalHandle();
  hand->SetLength(30e-3);
  hand->SetArea(9.9e-3*10e-3);
  hand->SetSensor(1,2);
  hand->Load("ref.txt");

  /*-----------------
     set margin
    -----------------*/
  const double leftMargin   = 0.12;
  const double rightMargin  = 0.05;
  const double headMargin   = 0.06;
  const double bottomMargin = 0.10;
  const double figHeight    = 0.27;
  const double figVStep     = 0.01;
  //-----------------

  TPad* p1 = new TPad("data", "data", 0., 0., 1., 1.);
  p1->SetMargin(leftMargin, rightMargin, bottomMargin+figHeight+figVStep, headMargin);
  p1->SetTicks(1,1);
  p1->SetGrid();
  p1->SetFillColor(0);
  p1->SetFillStyle(0);
  p1->Draw();
  p1->cd(0);
  hand->Draw();

  TPad* p2 = new TPad("dvd", "dvd", 0., 0., 1., 1.);
  p2->SetMargin(leftMargin, rightMargin, bottomMargin, headMargin+2*figHeight+2*figVStep);
  p2->SetTicks(1,1);
  p2->SetGrid();
  p2->SetFillColor(0);
  p2->SetFillStyle(0);
  p2->Draw();
  p2->cd(0);
  hand->DrawDivide();


  app->Run();
  return 0;
}
