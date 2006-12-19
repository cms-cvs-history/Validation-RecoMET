
void DrawBox(TBox *bColor, TBox *bLine, Float_t x, Float_t y, Float_t dx, Float_t dy, Int_t FillColor)
{  
  bColor = new TBox(x-dx/2.0,y-dy/2.0, x+dx/2.0, y+dy/2.0 );
  bLine = new TBox(x-dx/2.0,y-dy/2.0, x+dx/2.0, y+dy/2.0 );
  bColor->SetFillStyle(1001);
  bColor->SetFillColor( FillColor );
  bLine->SetLineColor(kBlack);
  bLine->SetLineWidth(0.5);	  
  bLine->SetLineStyle(1);	  
  bLine->SetFillStyle(0);

  //-----Draw the Box---------//
  bColor->Draw("SAME");
  bLine->Draw("SAME");
}

Int_t GetColor(Float_t Min, Float_t Max, Float_t CurrentValue)
{
  Float_t delta = Max - Min;
  Int_t ncolors  = gStyle->GetNumberOfColors() ;
  Float_t color = Float_t(CurrentValue - Min);
  Int_t theColorBin = Int_t((color)*Float_t(ncolors)/Float_t(delta) );
  if (theColorBin > ncolors-1) theColorBin = ncolors-1;
  Int_t theColor = Int_t(gStyle->GetColorPalette( theColorBin ) );
  //if (CurrentValue <=0.0) theColor = 0;
  return theColor;
}

void DrawMuons(TPad *pad)
{
  double pi = TMath::Pi();
  TFile fEventObjects("DumpEvent_data.root"); 
  //----Loop over electrons
  TLatex *mLabel[100];
  TString *mString[100];
  hMuon_phi->GetName();
  for (int m=1; m<=hMuon_eta->GetEntries(); m++)
    if (hMuon_pt->GetBinContent(m)>0.0)
      {
	mString[m-1] = new TString("#mu_{"); *mString[m-1]+=m; *mString[m-1]+="}";      
	Float_t eta = hMuon_eta->GetBinContent(m);
	Float_t phi = hMuon_phi->GetBinContent(m);
	Float_t theta = 2*atan(exp(-1*eta));
	Float_t r=fabs(317.0*tan(theta)); 
	
	pad->cd();
	mLabel[m-1] = new TLatex(eta, phi*(180.0/pi), mString[m-1]->Data());
	mLabel[m-1]->SetTextSize(0.01);
	mLabel[m-1]->SetTextColor(1);
	mLabel[m-1]->Draw("SAME");
      }
}

void DrawElectrons(TPad *pad)
{
  double pi = TMath::Pi();
  TFile fEventObjects("DumpEvent_data.root"); 
  //----Loop over electrons
  TLatex *eLabel[100];
  TString *eString[100];
  for (int e=1; e<=hElectron_eta->GetEntries(); e++)
    {
      eString[e-1] = new TString("e_{"); *eString[e-1]+=e; *eString[e-1]+="}";      
      Float_t eta = hElectron_eta->GetBinContent(e);
      Float_t phi = (hElectron_phi->GetBinContent(e));
      Float_t theta = 2*atan(exp(-1*eta));
      Float_t r= fabs(317.0*tan(theta));
      
      pad->cd();
      eLabel[e-1] = new TLatex(eta, phi*(180.0/pi), eString[e-1]->Data());
      eLabel[e-1]->SetTextSize(0.01);
      eLabel[e-1]->SetTextColor(1);
      eLabel[e-1]->Draw("SAME");
    }
}

void DrawPhotons(TPad *pad)
{
  double pi = TMath::Pi();
  TFile fEventObjects("DumpEvent_data.root"); 
  //----Loop over photons
  TLatex *gLabel[100];
  TString *gString[100];
  for (int g=1; g<=hPhoton_eta->GetEntries(); g++)
    {
      gString[g-1] = new TString("#gamma_{"); *gString[g-1]+=g; *gString[g-1]+="}";      
      //----EndCaps
      Float_t eta = hPhoton_eta->GetBinContent(g);
      Float_t phi = (hPhoton_phi->GetBinContent(g));
      Float_t theta = 2*atan(exp(-1*eta));
      Float_t r = fabs( 317.0*tan(theta) );
      
      pad->cd();
      gLabel[g-1] = new TLatex(eta, phi*(180.0/pi), gString[g-1]->Data());
      gLabel[g-1]->SetTextSize(0.01);
      gLabel[g-1]->SetTextColor(1);
      gLabel[g-1]->Draw("SAME");
    }
}

void DrawJets(TPad *pad)
{
  double pi = TMath::Pi();
  TFile fEventObjects("DumpEvent_data.root"); 
  //---Loop over jets
  TLatex *jLabel[100];
  TString *jString[100];
  TEllipse *jEllipse[100];
  TGraph *jGraph[100];
  for (int j=1; j<=hJet_eta->GetEntries(); j++)
    {
      jString[j-1] = new TString("j_{"); *jString[j-1]+=j; *jString[j-1]+="}";
          //----EndCaps
      Float_t eta = hJet_eta->GetBinContent(j);
      Float_t phi = (hJet_phi->GetBinContent(j));
      Float_t theta = 2*atan(exp(-1*eta));
      Float_t r= fabs( 317.0*tan(theta) );
  
      pad->cd();
      jEllipse[j-1] = new TEllipse( eta, phi*(180.0/pi) , 0.5, 0.5*(180.0/pi) );
      jEllipse[j-1]->Draw("SAME");
      jLabel[j-1] = new TLatex(eta, phi*(180.0/pi), jString[j-1]->Data());
      jLabel[j-1]->SetTextSize(0.025);
      jLabel[j-1]->Draw("SAME");
    }
}

void DrawMET(TPad *pad)
{
  double pi = TMath::Pi();
  TFile fEventObjects("DumpEvent_data.root"); 
  
  Float_t phi = (hRecoMET_phi->GetBinContent(1));
  cout << "METphi = " << phi << endl;
  TLine RecoMET(-5.191, phi*(180.0/pi), 5.191, phi*(180.0/pi));
  RecoMET.SetLineColor(kRed);
  RecoMET.SetLineWidth(2);
  RecoMET.SetLineStyle(2);
  TLatex RecoMET_Label(-5.191, phi+10, "MET_{Reco}");
  RecoMET_Label.SetTextColor(kRed);
  RecoMET_Label.SetTextSize(0.25);
  pad->cd();
  RecoMET.Draw("SAME");
  RecoMET_Label.Draw("SAME");
}
