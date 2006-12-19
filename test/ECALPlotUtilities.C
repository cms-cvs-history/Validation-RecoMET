
void DrawBox(TBox *bColor, TBox *bLine, Float_t eta, Float_t phi, Float_t deta, Float_t dphi, Int_t FillColor)
{  
  bColor = new TBox(eta-deta/2.0,phi-dphi/2.0, eta+deta/2.0, phi+dphi/2.0 );
  bLine = new TBox(eta-deta/2.0,phi-dphi/2.0, eta+deta/2.0, phi+dphi/2.0 );
  bColor->SetFillStyle(1001);
  bColor->SetFillColor( FillColor );
  bLine->SetLineColor(10);
  bLine->SetLineWidth(0.0);	  
  bLine->SetLineStyle(1);	  
  bLine->SetFillStyle(0);

  //-----Draw the Box---------//
  bColor->Draw("SAME");
  bLine->Draw("SAME");
}

void DrawMuons(TPad *cpZ, TPad *cmZ, TPad *cB)
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
      //----EndCaps
      Float_t eta = hMuon_eta->GetBinContent(m);
      Float_t phi = hMuon_phi->GetBinContent(m);
      Float_t theta = 2*atan(exp(-1*eta));
      Float_t r=fabs(317.0*tan(theta)); 
          
      if (r>0.0 && eta>1.566)
	{
	  cpZ->cd();
	  TVector3 v_;
	  v_.SetPtEtaPhi(r, eta, phi);
	  Float_t x = v_.x();
	  Float_t y = v_.y();
	  mLabel[m-1] = new TLatex(x, y, mString[m-1]->Data());
	  mLabel[m-1]->SetTextSize(0.025);
	  mLabel[m-1]->Draw("SAME");
	}
      if (r>0.0 && eta<-1.566)
	{
	  cmZ->cd();
	  TVector3 v_;
	  v_.SetPtEtaPhi(r, eta, phi);
	  Float_t x = v_.x();
	  Float_t y = v_.y();
	  mLabel[m-1] = new TLatex(x, y, mString[m-1]->Data());
	  mLabel[m-1]->SetTextSize(0.025);
	  mLabel[m-1]->Draw("SAME");
	}
      //---Barrel
     if (abs(eta)<1.566)
	{
	  cB->cd();
	  mLabel[m-1] = new TLatex(eta, phi*(180.0/pi), mString[m-1]->Data());
	  mLabel[m-1]->SetTextSize(0.01);
	  mLabel[m-1]->SetTextColor(1);
	  mLabel[m-1]->Draw("SAME");
	}
    }
}

void DrawElectrons(TPad *cpZ, TPad *cmZ, TPad *cB)
{
  double pi = TMath::Pi();
  TFile fEventObjects("DumpEvent_data.root"); 
  //----Loop over electrons
  TLatex *eLabel[100];
  TString *eString[100];
  for (int e=1; e<=hElectron_eta->GetEntries(); e++)
    {
      eString[e-1] = new TString("e_{"); *eString[e-1]+=e; *eString[e-1]+="}";      
      //----EndCaps
      Float_t eta = hElectron_eta->GetBinContent(e);
      Float_t phi = (hElectron_phi->GetBinContent(e));
      Float_t theta = 2*atan(exp(-1*eta));
      Float_t r= fabs(317.0*tan(theta));
      
      if (r>0.0 && eta>1.566)
	{
	  cpZ->cd();
	  TVector3 v_;
	  v_.SetPtEtaPhi(r, eta, phi);
	  Float_t x = v_.x();
	  Float_t y = v_.y();
	  eLabel[e-1] = new TLatex(x, y, eString[e-1]->Data());
	  eLabel[e-1]->SetTextSize(0.025);
	  eLabel[e-1]->Draw("SAME");
	}
      if (r>0.0 && eta<-1.566)
	{
	  cmZ->cd();
	  TVector3 v_;
	  v_.SetPtEtaPhi(r, eta, phi);
	  Float_t x = v_.x();
	  Float_t y = v_.y();
	  eLabel[e-1] = new TLatex(x, y, eString[e-1]->Data());
	  eLabel[e-1]->SetTextSize(0.025);
	  eLabel[e-1]->Draw("SAME");
	}
      //---Barrel
     if (fabs(eta)<1.566)
	{
	  cB->cd();
	  eLabel[e-1] = new TLatex(eta, phi*(180.0/pi), eString[e-1]->Data());
	  eLabel[e-1]->SetTextSize(0.01);
	  eLabel[e-1]->SetTextColor(1);
	  eLabel[e-1]->Draw("SAME");
	}
    }
}

void DrawPhotons(TPad *cpZ, TPad *cmZ, TPad *cB)
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
   
      if (r>0.0 && eta>1.566)
	{
	  cpZ->cd();  
	  TVector3 v_;
	  
	  v_.SetPtEtaPhi(r, eta, phi);
	  Float_t x = v_.x();
	  Float_t y = v_.y();
	  gLabel[g-1] = new TLatex(x, y, gString[g-1]->Data() );
	  gLabel[g-1]->SetTextSize(0.025);
	  gLabel[g-1]->Draw("SAME");
	}
      if (r>0.0 && eta<-1.566)
	{
	  cmZ->cd();
	  TVector3 v_;
	  v_.SetPtEtaPhi(r, eta, phi);
	  Float_t x = v_.x();
	  Float_t y = v_.y();
	  gLabel[g-1] = new TLatex(x, y, gString[g-1]->Data() );
	  gLabel[g-1]->SetTextSize(0.025);
	  
	  gLabel[g-1]->Draw("SAME");
	}
      //---Barrel
     if (fabs(eta)<1.566)
	{
	  cB->cd();
	  gLabel[g-1] = new TLatex(eta, phi*(180.0/pi), gString[g-1]->Data());
	  gLabel[g-1]->SetTextSize(0.01);
	  gLabel[g-1]->SetTextColor(1);
	  gLabel[g-1]->Draw("SAME");
	}
    }
}

void DrawJets(TPad *cpZ, TPad *cmZ, TPad *cB)
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
      if (r>0.0 && eta>1.566)
	{
	  cpZ->cd();
	  TVector3 v_;
	  v_.SetPtEtaPhi(r, eta, phi);
	  Float_t x = v_.x();
	  Float_t y = v_.y();
	  jLabel[j-1] = new TLatex(x, y, jString[j-1]->Data());
	  jLabel[j-1]->SetTextSize(0.025);
	  jLabel[j-1]->Draw("SAME");
	  jGraph[j-1] = new TGraph(101);
	  for (int p=0; p<101; p++)
	    {
	      Float_t alpha = (2*pi/100.0)*(p);
	      TVector3 dv_;
	      dv_.SetMagThetaPhi(0.5, pi/2.0, alpha);
	      Float_t phi_ = phi + dv_.y();
	      Float_t eta_ = eta + dv_.x();
	      Float_t theta_ = 2*atan(exp(-1*eta_));
	      Float_t r_=fabs( 317.0*tan(theta_) );
	      TVector3 vxy_;
	      vxy_.SetPtEtaPhi(r_, eta_, phi_);
	      Float_t x_ = vxy_.x();
	      Float_t y_ = vxy_.y();
	      jGraph[j-1]->SetPoint(p, x_, y_);
	    }
	  jGraph[j-1]->Draw("LSAME");
	}
      if (r>0.0 && eta<-1.566)
	{
	  cmZ->cd();	  	  
	  TVector3 v_;
	  v_.SetPtEtaPhi(r, eta, phi);
	  Float_t x = v_.x();
	  Float_t y = v_.y();
	  jLabel[j-1] = new TLatex(x, y, jString[j-1]->Data());
	  jLabel[j-1]->SetTextSize(0.025);
	  jLabel[j-1]->Draw("SAME");
	  jGraph[j-1] = new TGraph(101);
	  for (int p=0; p<101; p++)
	    {
	      Float_t alpha = (2*pi/100.0)*(p);
	      TVector3 dv_;
	      dv_.SetMagThetaPhi(0.5, pi/2.0, alpha);
	      Float_t phi_ = phi + dv_.y();
	      Float_t eta_ = eta + dv_.x();
	      Float_t theta_ = 2*atan(exp(-1*eta_));
	      Float_t r_=fabs( 317.0*tan(theta_) );
	      TVector3 vxy_;
	      vxy_.SetPtEtaPhi(r_, eta_, phi_);
	      Float_t x_ = vxy_.x();
	      Float_t y_ = vxy_.y();
	      jGraph[j-1]->SetPoint(p, x_, y_);
	    }
	  jGraph[j-1]->Draw("LSAME");
	}
      //---Barrel
     if (fabs(eta)<1.566)
	{
	  cB->cd();
	  jEllipse[j-1] = new TEllipse( eta, phi*(180.0/pi) , 0.5, 0.5*(180.0/pi) );
	  jEllipse[j-1]->Draw("SAME");
	  jLabel[j-1] = new TLatex(eta, phi*(180.0/pi), jString[j-1]->Data());
	  jLabel[j-1]->SetTextSize(0.025);
	  jLabel[j-1]->Draw("SAME");
	}
    }
}

void DrawMET(TPad *cpZ, TPad *cmZ, TPad *cB)
{
  double pi = TMath::Pi();
  TFile fEventObjects("DumpEvent_data.root"); 
  
  Float_t phi = (hRecoMET_phi->GetBinContent(1));
  TLine RecoMET(-1.566, phi*(180.0/pi), 1.566, phi*(180.0/pi));
  RecoMET.SetLineColor(kRed);
  RecoMET.SetLineWidth(2);
  RecoMET.SetLineStyle(2);
  TLatex RecoMET_Label(-1.566, phi+10, "MET_{Reco}");
  RecoMET_Label.SetTextColor(kRed);
  RecoMET_Label.SetTextSize(0.25);
  cB->cd();
  RecoMET.Draw("SAME");
  RecoMET_Label.Draw("SAME");
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
