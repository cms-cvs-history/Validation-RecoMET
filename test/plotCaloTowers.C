void SetUp()
{
  gROOT->Reset();
  gStyle->SetPalette(1,0);
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

DrawBox(TBox *bColor, TBox *bLine, float eta, float phi, float deta, float dphi, Int_t FillColor)
{  
  bColor = new TBox(eta-deta/2.0,phi-dphi/2.0, eta+deta/2.0, phi+dphi/2.0 );
  bLine = new TBox(eta-deta/2.0,phi-dphi/2.0, eta+deta/2.0, phi+dphi/2.0 );
  bColor->SetFillStyle(1001);
  // bColor->SetFillColor(gStyle->GetColorPalette( FillColor ) );
  bColor->SetFillColor( FillColor );
  bLine->SetLineColor(kBlack);
  bLine->SetLineWidth(0.5);	  
  bLine->SetLineStyle(1);	  
  bLine->SetFillStyle(0);

  //-----Draw the Box---------//
  bColor->Draw("SAME");
  bLine->Draw("SAME");
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


void plotCaloTowers(){
    SetUp();
  double pi = TMath::Pi();
  TFile fCaloTowerGeom("CaloTower_geometry.root");
  TH2F *hTowerGeom_eta = hCT_ieta_iphi_etaMap;
  TH2F *hTowerGeom_phi = hCT_ieta_iphi_phiMap;
  TH1F *hTowerGeom_deta = hCT_ieta_detaMap;
  TH1F *hTowerGeom_dphi = hCT_ieta_dphiMap;
  
  TFile fCaloTowerData("CaloTowerMETAnalyzer_data.root");
  TH2F *hTowerEt = new TH2F(*hCT_et_ieta_iphi);
  TH2F *hTowerEnergy = new TH2F(*hCT_energy_ieta_iphi);
  TH2F *hTowerHadEnergy = new TH2F(*hCT_hadEnergy_ieta_iphi);
  TH2F *hTowerEMEnergy = new TH2F(*hCT_emEnergy_ieta_iphi);
  TH2F *hTowerOcc = new TH2F(*hCT_Occ_ieta_iphi);
  
  TFile fEventObjects("DumpEvent_data.root");
  TH2F *hTower2Jets = new TH2F(*hCaloTowerToJetMap_ieta_iphi);

  //---------------------Make Canvas-------------------------------------//
  TCanvas *c1 = new TCanvas("c1","c1",1500,500); 
  TPad *c1_1  = new TPad("c1_1","c1_1",0.01,0.01,0.40,0.94); c1_1->Draw(); 
  TPad *c1_2  = new TPad("c1_2","c1_2",0.42,0.01,0.89,0.94); c1_2->Draw(); 
  TPad *c1_3  = new TPad("c1_3","c1_3",0.91,0.01,0.99,0.94); c1_3->Draw(); 
  c1_2->Range(-6.5,-220,6.5,220);

  TCanvas *cGeneric = new TCanvas("cGeneric","Hadronic Energy",900,900);
  cGeneric->Divide(1,2);
  cGeneric->GetPad(2)->Range(-8,-200,8,200);
  cGeneric->cd(1);
  cGeneric->GetPad(1)->SetGridx(1);
  cGeneric->GetPad(1)->SetGridy(1);
  cGeneric->cd(2);
  //-----------Define axis for eta,phi plot-------------------//
  TGaxis xbottom(-5.191,-180,5.191,-180,-5.191,5.191,16,"");
  xbottom.SetTitle("#eta");
  TGaxis yleft(-5.191,-180,-5.191,180,-180,180,15,"");
  yleft.SetTitle("#phi (Degrees)");
  TGaxis xtop(-5.191,180,5.191,180,-5.191,5.191,0,"");
  TGaxis yright(5.191,-180,5.191,180,-180,180,0,"");
  xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
  //----------------------------------------------------------//
  

  //---------------Tower Energy plots------------//
  {
    c1->cd();
    TText CanvasTitle(.01, .95, "CaloTower Energy");
    CanvasTitle.Draw();
    c1_1->cd();  c1_1->SetLogz(1);   c1_1->SetFrameFillColor(10);
    hTowerEnergy->SetStats(0);
    hTowerEnergy->SetContour(50);    
    hTowerEnergy->Draw("COLZ");
    c1->Update();
    TPaletteAxis *palette = (TPaletteAxis*)hTowerEnergy->GetListOfFunctions()->FindObject("palette");
    hTowerEnergy->GetXaxis()->SetTitle("ieta");
    hTowerEnergy->GetYaxis()->SetTitle("iphi");
    hTowerEnergy->Draw("COL");

    c1_3->cd(); c1_3->SetLogz(1);
    TText PaletteLabel(0.2,0.65,"Energy (GeV)");
    PaletteLabel.SetTextSize(0.15);
    PaletteLabel.SetTextAngle(90);
    PaletteLabel.Draw();
    palette->SetX1NDC(0.25); 
    palette->SetX2NDC(0.55); 
    palette->SetLabelOffset(0.03); 
    palette->SetLabelSize(0.2);
    //palette->SetName("Occupancy");
    palette->DrawClone();
    c1->Update();

    c1_2->cd();
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
  
    double Nietabins = hTowerGeom_eta->GetNbinsX();
    double Niphibins = hTowerGeom_eta->GetNbinsY();
    TBox *boxColor[90][90], *boxLine[90][90];
    for (int ieta=1; ieta<=Nietabins; ieta++)
      if (ieta!=42) // ieta = 0 
	{
	  for (int iphi=1; iphi<=Niphibins; iphi++)
	    if (hTowerGeom_phi->GetBinContent(ieta, iphi)>-999)
	      {
		float eta =  hTowerGeom_eta->GetBinContent(ieta, iphi);
		float deta = hTowerGeom_deta->GetBinContent(ieta);
		float phi = hTowerGeom_phi->GetBinContent(ieta,iphi);
		float dphi = hTowerGeom_dphi->GetBinContent(ieta);
		//-----Get the Fill Color----//
		float CurrentValue = hTowerEnergy->GetBinContent(ieta, iphi);
	
		float Min = 0; //hTowerEnergy->GetMinimum(0.0);
		float Max = hTowerEnergy->GetMaximum();
		if (CurrentValue > 1E-6)
		  CurrentValue = TMath::Log10(CurrentValue);
		if (Min > 1E-6)
		  Min = TMath::Log10(Min);
		Max = TMath::Log10(Max);
		Float_t delta = Max - Min;
		Int_t ncolors  = gStyle->GetNumberOfColors() ;
		Float_t color = Float_t(CurrentValue - Min);
		Int_t theColorBin = Int_t((color)*Float_t(ncolors)/Float_t(delta) );
		if (theColorBin > ncolors-1) theColorBin = ncolors-1;
		Int_t theColor = Int_t(gStyle->GetColorPalette( theColorBin ) );
		if (CurrentValue <=0.0) theColor = 0;
		// Make the box
		DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);
		//	if (CurrentValue>0)
		//  cout << ieta << " " << iphi << " " << eta  << " " 
		//       << deta << " " << phi  << " " << dphi << " " << CurrentValue << " " << theColor << " " << ( (ncolors/delta)*(CurrentValue-Min)  ) << endl;
      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    DrawMET(c1_2);
    DrawMuons(c1_2);
    DrawJets(c1_2);
    DrawPhotons(c1_2);
    DrawElectrons(c1_2);
    c1->Print("CaloTowerEnergy.eps");
    c1_1->Clear(); c1_2->Clear(); c1_3->Clear();
  }
  //-----------------------------------------------------------------
 
 //---------------Tower EM Energy plots------------//
  {
    c1->cd();
    TText CanvasTitle(.01, .95, "CaloTower Electomagnetic Energy");
    CanvasTitle.Draw();
    c1_1->cd();  c1_1->SetLogz(1);   c1_1->SetFrameFillColor(10);
    hTowerEMEnergy->SetStats(0);
    hTowerEMEnergy->SetContour(50);    
    hTowerEMEnergy->Draw("COLZ");
    c1->Update();
    TPaletteAxis *palette = (TPaletteAxis*)hTowerEMEnergy->GetListOfFunctions()->FindObject("palette");
    hTowerEMEnergy->GetXaxis()->SetTitle("ieta");
    hTowerEMEnergy->GetYaxis()->SetTitle("iphi");
    hTowerEMEnergy->Draw("COL");

    c1_3->cd(); c1_3->SetLogz(1);
    TText PaletteLabel(0.2,0.65,"Energy (GeV)");
    PaletteLabel.SetTextSize(0.15);
    PaletteLabel.SetTextAngle(90);
    PaletteLabel.Draw();
    palette->SetX1NDC(0.25); 
    palette->SetX2NDC(0.55); 
    palette->SetLabelOffset(0.03); 
    palette->SetLabelSize(0.2);
    //palette->SetName("Occupancy");
    palette->DrawClone();
    c1->Update();

    c1_2->cd();
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
  
    double Nietabins = hTowerGeom_eta->GetNbinsX();
    double Niphibins = hTowerGeom_eta->GetNbinsY();
    TBox *boxColor[90][90], *boxLine[90][90];
    for (int ieta=1; ieta<=Nietabins; ieta++)
      if (ieta!=42) // ieta = 0 
	{
	  for (int iphi=1; iphi<=Niphibins; iphi++)
	    if (hTowerGeom_phi->GetBinContent(ieta, iphi)>-999)
	      {
		float eta =  hTowerGeom_eta->GetBinContent(ieta, iphi);
		float deta = hTowerGeom_deta->GetBinContent(ieta);
		float phi = hTowerGeom_phi->GetBinContent(ieta,iphi);
		float dphi = hTowerGeom_dphi->GetBinContent(ieta);
		//-----Get the Fill Color----//
		float CurrentValue = hTowerEMEnergy->GetBinContent(ieta, iphi);
	
		float Min = 0; //hTowerEMEnergy->GetMinimum(0.0);
		float Max = hTowerEMEnergy->GetMaximum();
		if (CurrentValue > 1E-6)
		  CurrentValue = TMath::Log10(CurrentValue);
		if (Min > 1E-6)
		  Min = TMath::Log10(Min);
		Max = TMath::Log10(Max);
		Float_t delta = Max - Min;
		Int_t ncolors  = gStyle->GetNumberOfColors() ;
		Float_t color = Float_t(CurrentValue - Min);
		Int_t theColorBin = Int_t((color)*Float_t(ncolors)/Float_t(delta) );
		if (theColorBin > ncolors-1) theColorBin = ncolors-1;
		Int_t theColor = Int_t(gStyle->GetColorPalette( theColorBin ) );
		if (CurrentValue <=0.0) theColor = 0;
		// Make the box
		DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);
		//	if (CurrentValue>0)
		//  cout << ieta << " " << iphi << " " << eta  << " " 
		//       << deta << " " << phi  << " " << dphi << " " << CurrentValue << " " << theColor << " " << ( (ncolors/delta)*(CurrentValue-Min)  ) << endl;
      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
 
    c1->Print("CaloTowerEMEnergy.eps");
    c1_1->Clear(); c1_2->Clear(); c1_3->Clear();
  }
  //-----------------------------------------------------------------
   

 

 
  //---------------Occupancy plots------------//
  {
  int useLogZ = true;
    // For a common z-scale, get the maximum energy
    Float_t Occ_Max = hTowerOcc->GetMaximum(); 
    Float_t Occ_Min = hTowerOcc->GetMinimum(); 
				     
    // if using LogZ option, we need to correctly set the minimum of the palette 
    if (useLogZ)
      {
	Occ_Min =  hTowerOcc->GetMinimum(0.0); 
	if (Occ_Min == 0.0) Occ_Min = 1E-1;
      }
    hTowerOcc->SetMinimum(Occ_Min); hTowerOcc->SetMaximum(Occ_Max);
    hTowerOcc->SetStats(0);   hTowerOcc->SetContour(50);
    hTowerOcc->GetXaxis()->SetTitle("ieta"); hTowerOcc->GetYaxis()->SetTitle("iphi");
 
    c1->cd();
    TText CanvasTitle(.01, .95, "CaloTower Occupancy");
    CanvasTitle.Draw();

    c1_1->cd();   c1_1->SetFrameFillColor(10); c1_1->SetLogz(useLogZ);
    hTowerOcc->SetStats(0);
    hTowerOcc->SetContour(50);
    hTowerOcc->Draw("COLZ");
    c1->Update();
    TPaletteAxis *palette = (TPaletteAxis*)hTowerOcc->GetListOfFunctions()->FindObject("palette");
    hTowerOcc->GetXaxis()->SetTitle("ieta");
    hTowerOcc->GetYaxis()->SetTitle("iphi");
    hTowerOcc->Draw("COL");

    c1_3->cd(); c1_3->SetLogz(useLogZ);
    TText PaletteLabel(0.2,0.625,"Occupancy (%)");
    PaletteLabel.SetTextSize(0.15);
    PaletteLabel.SetTextAngle(90);
    PaletteLabel.Draw();
    palette->SetX1NDC(0.25); 
    palette->SetX2NDC(0.55); 
    palette->SetLabelOffset(0.03); 
    palette->SetLabelSize(0.2);
    //palette->SetName("Occupancy");
    palette->DrawClone();
    cout << palette << endl;
    c1->Update();

    c1_2->cd(); c1_2->SetLogz(useLogZ);
    xbottom.Draw();
    yleft.Draw();
    xtop.Draw();
    yright.Draw();
    double Nietabins = hTowerGeom_eta->GetNbinsX();
    double Niphibins = hTowerGeom_eta->GetNbinsY();
    TBox *boxColor[90][90], *boxLine[90][90];
    for (int ieta=1; ieta<=Nietabins; ieta++)
      if (ieta!=42) // ieta = 0 
	{
	  for (int iphi=1; iphi<=Niphibins; iphi++)
	    {
	      //     cout << ieta << " " << iphi << " " <<  hCT_ieta_iphi_phiMap->GetBinContent(ieta, iphi) << endl;
	    if (hTowerGeom_phi->GetBinContent(ieta, iphi)>-999)
	      {
		float eta =  hTowerGeom_eta->GetBinContent(ieta, iphi);
		float deta = hTowerGeom_deta->GetBinContent(ieta);
		float phi = hTowerGeom_phi->GetBinContent(ieta,iphi);
		float dphi = hTowerGeom_dphi->GetBinContent(ieta);
		//-----Get the Fill Color----//
		Float_t CurrentValue = hTowerOcc->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hTowerOcc->GetBinContent(ieta, iphi);
		Float_t Min = hTowerOcc->GetMinimum(0.0);
		Float_t Max = hTowerOcc->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Occ_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Occ_Min) Min = TMath::Log10(Min);
		    if (Max >= Occ_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		if (CurrentValue == 0.0) theColor = 0;
		DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor); 	
		
		// Make the box
		//if (ieta == 1)
		//  {
		//    cout << ieta << " " << iphi <<" " << hTowerOcc->GetBinContent(ieta, iphi) << endl;
		//    cout << eta << " " << phi << " " << CurrentValue << " " << theColor << endl;
		//    cout << endl;
		//  }
		DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);
		
	      }
	    }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    c1->Print("CaloTowerOccupancy.eps");
  }

  // Eta Ring plots
  {
    //---------------------Make Canvas-------------------------------------//
    int useLogZ = true;
    TCanvas *c2 = new TCanvas("c2","c2",1000,500); 
    TPad *c2_1  = new TPad("c2_1","c2_1",0.01,0.01,0.99,0.94); 
    c2_1->SetFrameFillColor(10); c2_1->SetGridy(1);  c2_1->SetLogy(useLogZ); c2_1->Draw(); 
    c2->cd();
    TLatex CanvasTitle_(.01, .95, "CaloTower #eta-Ring Occupancy");
    CanvasTitle_.Draw();  
    
    TH1F *hOcc_ietaRing = new TH1F("hOcc_ietaRing", "Occupancy vs i#eta", 83,-41,42);
    TH1F *hACOcc_ietaRing = new TH1F("hACOcc_ietaRing", "Avg. Cell Occupancy vs i#eta", 83,-41,42);
    hOcc_ietaRing->GetXaxis()->SetTitle("i#eta");
    hOcc_ietaRing->GetYaxis()->SetTitleOffset(1.3);
    hOcc_ietaRing->GetYaxis()->SetTitle("Occupancy (%)");
    Float_t EtaBins[83];  EtaBins[82] = 5.191; 
  
    double Nietabins = hTowerGeom_eta->GetNbinsX();
    double Niphibins = hTowerGeom_eta->GetNbinsY();
    TBox *boxColor[90][90], *boxLine[90][90];
    for (int ieta=1; ieta<=Nietabins; ieta++)
      if (ieta!=42) // ieta = 0 
	{
	  Float_t TotalOcc = 0.0;
	  TH1F *hTemp = new TH1F("hTemp","",200000,0,200);
	  for (int iphi=1; iphi<=Niphibins; iphi++)
	    {
	      //     cout << ieta << " " << iphi << " " <<  hCT_ieta_iphi_phiMap->GetBinContent(ieta, iphi) << endl;
	      if (hTowerGeom_phi->GetBinContent(ieta, iphi)>-999)
	      {
		float eta =  hTowerGeom_eta->GetBinContent(ieta, iphi);
		float deta = hTowerGeom_deta->GetBinContent(ieta);
		float phi = hTowerGeom_phi->GetBinContent(ieta,iphi);
		float dphi = hTowerGeom_dphi->GetBinContent(ieta);
		if (ieta<42)
		  EtaBins[ieta-1] = eta - deta/2.0;
		if (ieta>42)
		  EtaBins[ieta-2] = eta - deta/2.0;
		Float_t CurrentValue = hTowerOcc->GetBinContent(ieta, iphi);
		TotalOcc+=CurrentValue;
		hTemp->Fill(CurrentValue);
	      }
	    } // iphi loop
	  hOcc_ietaRing->SetBinContent(ieta, TotalOcc);
	  hACOcc_ietaRing->SetBinContent(ieta, hTemp->GetMean());
	  hACOcc_ietaRing->SetBinError(ieta, hTemp->GetRMS());
	}
    //for (int i=0; i<83; i++) cout << i << " " <<  EtaBins[i] << endl;
    TH1F *hOcc_etaRing = new TH1F("hOcc_etaRing", "Occupancy vs #eta", 82, EtaBins);
    TH1F *hdOccdEta_etaRing = new TH1F("hdOccdEta_etaRing", "#frac{dOcc(%)}{d#eta} vs #eta", 82, EtaBins);
    hOcc_etaRing->GetXaxis()->SetTitle("#eta");
    hOcc_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hOcc_etaRing->GetYaxis()->SetTitle("Occupancy (%)");
    hdOccdEta_etaRing->GetXaxis()->SetTitle("#eta");
    hdOccdEta_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hdOccdEta_etaRing->GetYaxis()->SetTitle("#frac{dOcc(%)}{d#eta}");

    TH1F *hACOcc_etaRing = new TH1F("hACOcc_etaRing", "Occupancy vs #eta", 82, EtaBins);
    TH1F *hdACOccdEta_etaRing = new TH1F("hdACOccdEta_etaRing", "#frac{<#DeltaOcc(%)>}{#Delta#eta#Delta#phi} vs #eta", 82, EtaBins);
    hACOcc_etaRing->GetXaxis()->SetTitle("#eta");
    hACOcc_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hACOcc_etaRing->GetYaxis()->SetTitle("<Occ(%)>");
    hdACOccdEta_etaRing->GetXaxis()->SetTitle("#eta");
    hdACOccdEta_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hdACOccdEta_etaRing->GetYaxis()->SetTitle("#frac{<#DeltaOcc(%)>}{#Delta#eta#Delta#phi}");

    for (int i=1; i<=hOcc_etaRing->GetNbinsX()+1; i++)
      {
	Int_t bin=0;
	if (i<42) bin = i;
	if (i>42) bin = i-1;
	if (i!=42)
	  {
	    Float_t deta = hTowerGeom_deta->GetBinContent(i);
	    Float_t dphi = (pi/180.0)*hTowerGeom_dphi->GetBinContent(i);
	    Float_t darea = deta*dphi;
	    hOcc_etaRing->SetBinContent(bin, hOcc_ietaRing->GetBinContent(i));
	    hOcc_etaRing->SetBinError(bin, hOcc_ietaRing->GetBinError(i));
	    hACOcc_etaRing->SetBinContent(bin, hACOcc_ietaRing->GetBinContent(i));
	    hACOcc_etaRing->SetBinError(bin, hACOcc_ietaRing->GetBinError(i));
	    if (darea>0)
	      {
		hdOccdEta_etaRing->SetBinContent(bin, hOcc_ietaRing->GetBinContent(i)/darea);
		hdOccdEta_etaRing->SetBinError(bin, hOcc_ietaRing->GetBinError(i)/darea);
		hdACOccdEta_etaRing->SetBinContent(bin, hACOcc_ietaRing->GetBinContent(i)/darea);
		hdACOccdEta_etaRing->SetBinError(bin, hACOcc_ietaRing->GetBinError(i)/darea);
	      }
	  }
      }
    
    TFile fOut("CaloTowerPlots.root","RECREATE");

    c2_1->cd();
    hOcc_etaRing->SetStats(0);
    hOcc_etaRing->Draw();
    c2->Print("CaloTowerEtaRingOccupancy.eps");
    c2_1->Clear();
    hdOccdEta_etaRing->SetStats(0);
    hdOccdEta_etaRing->Draw();
    c2->Print("CaloTowerEtaRingdOccdEta.eps");
    c2_1->Clear();
    c2_1->cd();
    hACOcc_etaRing->SetStats(0);
    hACOcc_etaRing->Draw();
    c2->Print("CaloTowerEtaRing_Avg_Cell_Occupancy.eps");
    c2_1->Clear();
    hdACOccdEta_etaRing->SetStats(0);
    hdACOccdEta_etaRing->Draw();
    c2->Print("CaloTowerEtaRing_Avg_Cell_dOccdEta.eps");

    hdACOccdEta_etaRing->Write();
    fOut.Close();
  }
 
  //---------------CaloTower->Jet Mapping------------//
  {
    TCanvas *c3 = new TCanvas("c3","c3",500,325); 
    TPad *c3_1  = new TPad("c3_1","c3_1",0.01,0.01,0.99,0.94); c3_1->Draw(); 
    c3_1->Range(-6.5,-220,6.5,220);

    hTower2Jets->SetMinimum(Occ_Min); hTower2Jets->SetMaximum(Occ_Max);
    hTower2Jets->SetStats(0);   hTower2Jets->SetContour(50);
    hTower2Jets->GetXaxis()->SetTitle("ieta"); hTower2Jets->GetYaxis()->SetTitle("iphi");
 
    c3->cd();
    TText CanvasTitle(.01, .95, "CaloTower to Jets Map");
    CanvasTitle.Draw();

    c3_1->cd(); 
    xbottom.Draw();
    yleft.Draw();
    xtop.Draw();
    yright.Draw();
    double Nietabins = hTowerGeom_eta->GetNbinsX();
    double Niphibins = hTowerGeom_eta->GetNbinsY();
    TBox *boxColor[90][90], *boxLine[90][90];
    for (int ieta=1; ieta<=Nietabins; ieta++)
      if (ieta!=42) // ieta = 0 
	{
	  for (int iphi=1; iphi<=Niphibins; iphi++)
	    {
	      if (hTowerGeom_phi->GetBinContent(ieta, iphi)>-999)
		{
		  float eta =  hTowerGeom_eta->GetBinContent(ieta, iphi);
		  float deta = hTowerGeom_deta->GetBinContent(ieta);
		  float phi = hTowerGeom_phi->GetBinContent(ieta,iphi);
		  float dphi = hTowerGeom_dphi->GetBinContent(ieta);
		  //-----Get the Fill Color----//
		  Float_t CurrentValue = hTower2Jets->GetBinContent(ieta, iphi);
		  Float_t CurrentValueL10 = hTower2Jets->GetBinContent(ieta, iphi);
		  Float_t Min = hTower2Jets->GetMinimum(0.0);
		  Float_t Max = hTower2Jets->GetMaximum();
		  Int_t theColor = CurrentValue+1;
		  if (theColor>=10) theColor+=2;
		  if (CurrentValue == 0.0) theColor = 0;
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor); 	
		}
	    }
	}
    DrawJets(c3_1);
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    c3->Print("CaloTowerToJets.eps");
  }
  
}
