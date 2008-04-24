#include <iostream>
#include <sstream>

#include "TSystem.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "TText.h"
#include "TPaveLabel.h"
#include "TLine.h"
#include "TLegend.h"

#include "include/PlotCompareUtility.h"
#include "include/HistoData.h"
using namespace std;

const bool KS_TEST = true;
const bool CHI2_TEST = false;

int main(int argc, char *argv[]) {

  // make sure command line arguments were supplied
  if (argc != 3) { cerr << "Usage: " << argv[0] << " [reference.root] [new-comparison.root]\n"; return 1; }

  // create the comparison class
  PlotCompareUtility *pc = new PlotCompareUtility(argv[1],argv[2],"DQMData/RecoMETV/METtask/MET/met/","METTask_");
  HistoData *hd;

  if (pc->GetStatus() != 0) { cout << "Final Result: no_data" << endl; return 0; }

  // add histogram information
  hd = pc->AddHistoData("CaloEmEtFraction");
  hd = pc->AddHistoData("CaloEmEtInEB");
  hd = pc->AddHistoData("CaloEmEtInEE");
  hd = pc->AddHistoData("CaloEmEtInHF");
  hd = pc->AddHistoData("CaloEtFractionHadronic");
  hd = pc->AddHistoData("CaloHadEtInHB");
  hd = pc->AddHistoData("CaloHadEtInHE");
  hd = pc->AddHistoData("CaloHadEtInHF");
  hd = pc->AddHistoData("CaloHadEtInHO");
  hd = pc->AddHistoData("CaloMET");
  hd = pc->AddHistoData("CaloMETPhi");
  hd = pc->AddHistoData("CaloMETSig");
  hd = pc->AddHistoData("CaloMEx");
  hd = pc->AddHistoData("CaloMEy");
  hd = pc->AddHistoData("CaloMaxEtInEmTowers");
  hd = pc->AddHistoData("CaloMaxEtInHadTowers");
  hd = pc->AddHistoData("CaloSumET");
  hd = pc->AddHistoData("GenMET");
  hd = pc->AddHistoData("GenMETPhi");
  hd = pc->AddHistoData("GenMETSig");
  hd = pc->AddHistoData("GenMEx");
  hd = pc->AddHistoData("GenMEy");
  hd = pc->AddHistoData("GenSumET");
  hd = pc->AddHistoData("Nevents");
  
  if (pc->GetStatus() != 0) { cerr << "error encountered, exiting.\n"; return pc->GetStatus(); }

  int num_histos = pc->GetNumHistos()-1;
  bool combinedFailed = false;
  float threshold = KS_TEST ?  pc->GetKSThreshold() : pc->GetChi2Threshold(); 

    // get the reference and comparison histograms
  int Nevents_ref = ((TH1F *)pc->GetRefHisto("Nevents"))->GetEntries();
  int Nevents_new = ((TH1F *)pc->GetNewHisto("Nevents"))->GetEntries();
  int Nevents = -1;
  if (Nevents_ref>Nevents_new) Nevents = Nevents_ref;
  else Nevents = Nevents_new;

  // create summary histograms
  TH1F h1dResults_passed("h1dResults_passed","",num_histos, 1, num_histos + 1);
  TH1F h1dResults_failed("h1dResults_failed","",num_histos, 1, num_histos + 1);

  // loop over the supplied list of histograms for comparison
  for (int index = 0; index < pc->GetNumHistos()-1; index++) {

    int number = index + 1;
    hd = pc->GetHistoData(number);
    //int type = hd->GetType();
    //types[index] = type;
    string name = hd->GetName();
    //string value = hd->GetValueX();
    cout << name << endl;

    // get the reference and comparison histograms
    TH1F *href = (TH1F *)pc->GetRefHisto(name);
    TH1F *hnew = (TH1F *)pc->GetNewHisto(name);


    // ignore if histogram is empty
    if (hnew->GetEntries() <= 1 || href->GetEntries() <= 1) {
      cerr << name << " error: no entries"; combinedFailed = true; continue;
    }

    // calculate and set range and number of bins
    double h1RMS =  hnew->GetRMS();
    double h2RMS =  href->GetRMS();
    double RMS = TMath::Max(h1RMS, h2RMS);
    double h1Mean =  hnew->GetMean();
    double h2Mean =  href->GetMean();
    double Mean = 0.5 * (h1Mean + h2Mean);
    double Nbins = href->GetNbinsX();
    double min = href->GetXaxis()->GetXmin();
    double max = href->GetXaxis()->GetXmax();
    double dX = max - min;
    double dNdX = 1;
    double NewMin = 0;
    double NewMax = 1;
    if (RMS>0) 
      {
	dNdX = 100. / ( 10 * RMS);
	NewMin = Mean - 5 * RMS;
	NewMax = Mean + 5 * RMS;
      }
    
    int rebinning = 1;
    if ((dX * dNdX)>0) 
      rebinning = (int)(double(Nbins) / (dX * dNdX));
    
    //    if (rebinning > 1) {
    //  href->Rebin(rebinning);
    //  hnew->Rebin(rebinning);
    // }

    
    href->GetXaxis()->SetRangeUser(NewMin, NewMax);
    hnew->GetXaxis()->SetRangeUser(NewMin, NewMax);

  if (rebinning > 1) {
      href->Rebin(rebinning);
      hnew->Rebin(rebinning);
    }
    
  // href->SetMinimum(0);
  //hnew->SetMinimum(0);

    // perform statistical tests
    double ks_score = hnew->KolmogorovTest(href,"D");
    double chi2_score = hnew->Chi2Test(href, "p");
    //double result = KS_TEST ? ks_score : chi2_score;
    double result = (ks_score>chi2_score) ? ks_score : chi2_score;
    
    href->SetNormFactor(hnew->GetEntries());
    //hnew->SetNormFactor(1);

    // ensure that the peaks of both histograms will be shown by making a dummy histogram
    float Nentries_ref = href->GetEntries();
    float Nentries_new = hnew->GetEntries();
    float XaxisMin_ref = 0, XaxisMax_ref = 0, YaxisMin_ref = 0, YaxisMax_ref = 0;
    float XaxisMin_new = 0, XaxisMax_new = 0, YaxisMin_new = 0, YaxisMax_new = 0;
    if (Nentries_ref>0) YaxisMax_ref = (href->GetMaximum()+sqrt(href->GetMaximum()))*(Nentries_new/Nentries_ref);
    if (Nentries_new>0) YaxisMax_new = (hnew->GetMaximum()+sqrt(hnew->GetMaximum()));

    XaxisMin_ref = href->GetXaxis()->GetXmin()>NewMin  ? href->GetXaxis()->GetXmin() : NewMin;
    XaxisMax_ref = href->GetXaxis()->GetXmax()<=NewMax ? href->GetXaxis()->GetXmax() : NewMax;
    YaxisMax_ref = (YaxisMax_ref>=YaxisMax_new) ? YaxisMax_ref : YaxisMax_new;

    if (fabs(XaxisMin_ref - XaxisMax_ref)<1E-6)
      {
	XaxisMin_ref = 0;
	XaxisMax_ref = 1;
      }
    
    TH1F *hdumb = new TH1F("hdumb","", rebinning, XaxisMin_ref, XaxisMax_ref);
    hdumb->SetMinimum(1E-1); //--For Rick
    hdumb->SetMaximum(1.05*YaxisMax_ref);
    //    if (href->GetMaximum() < hnew->GetMaximum())
    //  href->SetAxisRange(0, 1.1 * hnew->GetMaximum(), "Y");
        
    // set drawing options on the reference histogram
    href->SetStats(0);
    href->SetLineWidth(2);
    href->SetLineColor(14);
    href->SetMarkerColor(14);
    href->SetFillColor(17);
    //href->SetFillStyle(3004);
    href->GetXaxis()->SetTitle(name.c_str());
    href->GetYaxis()->SetTitle("Entries");
    href->GetYaxis()->SetTitleOffset(1.5);

    // set drawing options on the new histogram
    hnew->SetStats(0);
    hnew->SetLineWidth(2);
    hnew->SetFillStyle(3001);
    // set drawing options on the dummy histogram
    hdumb->SetStats(0);
    hdumb->GetXaxis()->SetTitle(name.c_str());
    hdumb->GetXaxis()->SetLabelSize(0.5 * hdumb->GetXaxis()->GetTitleSize());
    hdumb->GetYaxis()->SetTitle("Entries");
    hdumb->GetYaxis()->SetTitleOffset(1.5);
    hdumb->GetYaxis()->SetLabelSize(0.5 * hdumb->GetXaxis()->GetTitleSize());
    
    stringstream ss_title;
    ss_title.precision(5);
    if (ks_score>chi2_score)
      ss_title << "KS Score = " << ks_score;
    else
      ss_title << "Chi^2 Score = " << chi2_score;
    TText canvas_title(0.1,0.97,ss_title.str().c_str());


    // determine if test is a "pass" or a "fail"
    if (result <= threshold) {

      canvas_title.SetTextColor(kRed);

      // make this histogram red to denote failure
      hnew->SetFillColor(kRed);
      hnew->SetLineColor(206);
      hnew->SetMarkerColor(206);

      // mark the entire sample as being 'not-compatible'
      combinedFailed = true;

      // set the summary bin to failed (only need to set titles for passed h1dResults)
      h1dResults_passed.GetXaxis()->SetBinLabel(number, name.c_str());
      h1dResults_failed.SetBinContent(number, result);

    } else {

      canvas_title.SetTextColor(kGreen);

      // make this histogram green to denote passing score
      hnew->SetFillColor(kGreen);
      hnew->SetLineColor(103);  
      hnew->SetMarkerColor(103);

      // set the summary bin to passed
      h1dResults_passed.GetXaxis()->SetBinLabel(number, name.c_str());
      h1dResults_passed.SetBinContent(number, result);

    }

    // setup canvas for displaying the compared histograms
    TCanvas histo_c("histo_c","histo_c",785,800);
    histo_c.Draw();

    TPad histo_p("histo_p","histo_p",0,0,1,0.99);
    histo_p.Draw();

    histo_c.cd();
    canvas_title.SetTextSize(0.025);
    canvas_title.Draw();

    histo_p.cd();

    histo_p.SetLogy(1); //--This is just for Dr. Rick
    hdumb->Draw();
    href->Draw("SAME");
    hnew->Draw("SAME");
    hnew->Draw("E1SAME");

    TLegend l1(0.15,0.01,0.3, 0.08);
    l1.AddEntry(hnew,"New","lF");
    l1.AddEntry(href,"Reference","lF");
    l1.SetFillColor(kNone);      
    l1.Draw("SAME");

    // print the result to gif
    gSystem->mkdir(name.c_str());
    string histo_name = name + "/results.gif";
    histo_c.Print(histo_name.c_str(),"gif");
    cout << "Result of comparison for " << name << ": ks score = " << ks_score << " : chi2 score = " << chi2_score << endl << endl;

  }

  // create summary canvas
  int summary_height = int(780 * float(num_histos) / 22); // 780;
  TCanvas main_c("main_c","main_c",799,summary_height);
  main_c.Draw();

  TPad main_p("main_p","main_p",0.01,0.01,0.99,0.94);
  main_p.SetLeftMargin(0.30);
  main_p.SetBottomMargin(0.15);
  main_p.SetLogx(1);
  main_p.SetGrid();
  main_p.SetFrameFillColor(10);
  main_p.Draw();

  main_c.cd();
  TText summary_title(.01, .95, "");
  summary_title.Draw("SAME");

  main_p.cd();

  // setup the passing test bars
  h1dResults_passed.SetStats(0);
  h1dResults_passed.GetXaxis()->SetLabelSize(0.04);
  h1dResults_passed.GetYaxis()->SetTitle("Compatibility");
  h1dResults_passed.SetBarWidth(0.7);
  h1dResults_passed.SetBarOffset(0.1);
  h1dResults_passed.SetFillColor(kGreen);
  h1dResults_passed.SetLineColor(1);
  h1dResults_passed.GetYaxis()->SetRangeUser(1E-7,2);
  h1dResults_passed.Draw("hbar0");

  // setup the failing test bars
  h1dResults_failed.SetStats(0);
  h1dResults_failed.GetXaxis()->SetLabelSize(0.04);
  h1dResults_failed.GetYaxis()->SetTitle("Compatibility");
  h1dResults_failed.SetBarWidth(0.7);
  h1dResults_failed.SetBarOffset(0.1);
  h1dResults_failed.SetFillColor(kRed);
  h1dResults_failed.SetLineColor(1);
  h1dResults_failed.GetYaxis()->SetRangeUser(1E-7,2);
  h1dResults_failed.Draw("hbar0SAME");

  // draw the pass/fail threshold line
  TLine l(threshold, 1, threshold, num_histos+1);
  l.SetLineColor(kRed);
  l.SetLineWidth(2);
  l.SetLineStyle(2);
  l.Draw("SAME"); 

  // print the results
  main_c.Update();
  main_c.Print("AllResults-1dHistoCheck.gif","gif");

  if (combinedFailed) cout << "Final Result: fail" << endl;
  else cout << "Final Result: pass" << endl;

  //delete pc;
  return 0;

}
