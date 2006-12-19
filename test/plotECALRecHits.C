void SetUp()
{
  gROOT->Reset();
  gStyle->SetPalette(1,0);
  gROOT->ProcessLine(".L ECALPlotUtilities.C");  
}
void plotECALRecHits(){
  SetUp();
  double pi = TMath::Pi(); 
  
  //----Open the CaloTower geometry to get out the CaloTower grid
  TFile fCaloTowerGeom("CaloTower_geometry.root");
  TH2F *hTowerGeom_eta = hCT_ieta_iphi_etaMap;
  TH2F *hTowerGeom_phi = hCT_ieta_iphi_phiMap;
  TH1F *hTowerGeom_deta = hCT_ieta_detaMap;
  TH1F *hTowerGeom_dphi = hCT_ieta_dphiMap;
  // Load the geometry Histograms
  TFile fECALTowerGeom("ECAL_geometry.root");
  TH2F *hEBGeom_eta = hEB_ieta_iphi_etaMap;
  TH2F *hEBGeom_phi = hEB_ieta_iphi_phiMap;
  TH1F *hEBGeom_dphi = hEB_ieta_dphiMap;
  TH1F *hEBGeom_deta = hEB_ieta_detaMap;
  TH2F *hEEpZGeom_x = hEEpZ_ix_iy_xMap;
  TH2F *hEEpZGeom_y = hEEpZ_ix_iy_yMap;
  TH2F *hEEmZGeom_x = hEEmZ_ix_iy_xMap;
  TH2F *hEEmZGeom_y = hEEmZ_ix_iy_yMap;
  // Load ECALRecHit Histograms
  TFile fECALTowerData("ECALRecHitAnalyzer_data.root");
  TH2F *hEBEnergy = hEB_energy_ieta_iphi;
  TH2F *hEEpZEnergy = hEEpZ_energy_ix_iy;
  TH2F *hEEmZEnergy = hEEmZ_energy_ix_iy;
  TH2F *hEBOcc = hEB_Occ_ieta_iphi;
  TH2F *hEEpZOcc = hEEpZ_Occ_ix_iy;
  TH2F *hEEmZOcc = hEEmZ_Occ_ix_iy;
  


  //---------------------Make Canvas-------------------------------------//
  TCanvas *c1 = new TCanvas("c1","c1",1130,1075); 
  TPad *c1_11  = new TPad("c1_11","c1_11", 0.01,0.63,0.30,0.95);      c1_11->Draw(); 
  TPad *c1_12  = new TPad("c1_12","c1_12",0.31,0.63,0.6,0.95);        c1_12->Draw(); 
  TPad *c1_13  = new TPad("c1_13","c1_13",0.61,0.63,0.9,0.95);        c1_13->Draw(); 
  TPad *c1_21  = new TPad("c1_21","c1_21",0.01,0.18,0.26,0.46);       c1_21->Draw(); 
  TPad *c1_22  = new TPad("c1_22","c1_22",0.27,0.01,0.64,0.62);       c1_22->Draw(); 
  TPad *c1_23  = new TPad("c1_23","c1_23",0.65,0.18,0.9,0.46);        c1_23->Draw(); 
  TPad *c1_spec  = new TPad("c1_spec","c1_spec",0.91,0.01,0.99,0.95); c1_spec->Draw(); 
 
  //-----------Define axis for eta,phi plot-------------------//
  TGaxis xbottom(-1.6,-180,1.6,-180,-1.6,1.6,5,"");
  xbottom.SetTitle("#eta"); xbottom.SetTitleOffset(1);
  TGaxis yleft(-1.6,-180,-1.6,180,-180,180,15,"");
  yleft.SetTitle("#phi (Degrees)"); yleft.SetTitleOffset(1.5);
  TGaxis xtop(-1.6,180,1.6,180,-1.6,1.6,0,"");
  TGaxis yright(1.6,-180,1.6,180,-180,180,0,"");
  
  TGaxis xEEbottom(-160,-160,160,-160,-160,160,10,"");
  xEEbottom.SetTitle("x (cm)"); xEEbottom.SetTitleOffset(1.1);
  TGaxis yEEleft(-160,-160,-160,160,-160,160,10,"");
  yEEleft.SetTitle("y (cm)"); yEEleft.SetTitleOffset(1.3);
  TGaxis xEEtop(-160,160,160,160,-160,160,0,"");
  TGaxis yEEright(160,-160,160,160,-160,160,0,"");
  //----------------------------------------------------------//
  
  //---------------Make ECAL Energy Plots------------//
  //---------------ECAL Barrel
  {
    int useLogZ = true;
    // For a common z-scale, get the maximum energy
    Float_t Energy_Max = TMath::Max( hEBEnergy->GetMaximum(), TMath::Max(hEEpZEnergy->GetMaximum(), hEEmZEnergy->GetMaximum()) );
    Float_t Energy_Min = TMath::Min( hEBEnergy->GetMinimum(), TMath::Max(hEEpZEnergy->GetMinimum(), hEEmZEnergy->GetMinimum()) );
    // if using LogZ option, we need to correctly set the minimum of the palette 
    if (useLogZ)
      {
	Energy_Min = TMath::Min( hEBEnergy->GetMinimum(0.0), TMath::Max(hEEpZEnergy->GetMinimum(0.0), hEEmZEnergy->GetMinimum(0.0)) );
	if (Energy_Min == 0.0) Energy_Min = 1E-1;
      }
    // Format the Histograms
    hEBEnergy->SetMinimum(Energy_Min); hEBEnergy->SetMaximum(Energy_Max);
    hEEpZEnergy->SetMinimum(Energy_Min); hEEpZEnergy->SetMaximum(Energy_Max);
    hEEmZEnergy->SetMinimum(Energy_Min); hEEmZEnergy->SetMaximum(Energy_Max);
    hEBEnergy->SetStats(0); hEBEnergy->SetContour(50);
    hEEpZEnergy->SetStats(0); hEEpZEnergy->SetContour(50);
    hEEmZEnergy->SetStats(0); hEEmZEnergy->SetContour(50);
    hEBEnergy->GetXaxis()->SetTitle("ieta");
    hEBEnergy->GetYaxis()->SetTitle("iphi");
    hEBEnergy->GetYaxis()->SetTitleOffset(1.2);
    hEEpZEnergy->GetXaxis()->SetTitle("ix");
    hEEpZEnergy->GetYaxis()->SetTitle("iy");
    hEEpZEnergy->GetYaxis()->SetTitleOffset(1.2);
    hEEmZEnergy->GetXaxis()->SetTitle("ix");
    hEEmZEnergy->GetYaxis()->SetTitle("iy");
    hEEmZEnergy->GetYaxis()->SetTitleOffset(1.2);

    c1->cd(); c1->SetFillColor(18);
    TText CanvasTitle(.01, .965, "ECAL Energy"); CanvasTitle.SetTextSize(0.035); CanvasTitle.Draw();
    TLine topLine(.01, .955, .99, .955); topLine.SetLineWidth(1); topLine.SetLineColor(kBlack); topLine.SetLineStyle(1); topLine.Draw();
    c1_11->cd();  c1_11->SetLogz(useLogZ);   c1_11->SetFrameFillColor(10);
    c1_12->cd();  c1_12->SetLogz(useLogZ);   c1_12->SetFrameFillColor(10);
    c1_13->cd();  c1_13->SetLogz(useLogZ);   c1_13->SetFrameFillColor(10);

    c1_13->cd(); hEEpZEnergy->Draw("COL"); 
    TLatex c13Title(0.05,0.94,"+Endcap"); c13Title.SetTextSize(0.05); c13Title.SetNDC(); c13Title.Draw();

    c1_11->cd(); hEEmZEnergy->Draw("COL");
    TLatex c11Title(0.05,0.94,"-Endcap"); c11Title.SetTextSize(0.05); c11Title.SetNDC(); c11Title.Draw();

   
    c1_12->cd();
    hEBEnergy->Draw("COLZ");
    c1->Update();
    TPaletteAxis *palette = (TPaletteAxis*)hEBEnergy->GetListOfFunctions()->FindObject("palette");
    hEBEnergy->Draw("COL");
    TLatex c12Title(0.05,0.94,"Barrel"); c12Title.SetTextSize(0.05); c12Title.SetNDC(); c12Title.Draw();

    c1_spec->cd(); c1_spec->SetLogz(useLogZ);
    TText PaletteLabel(0.15,0.8,"Energy (GeV)");
    PaletteLabel.SetTextSize(0.15);
    PaletteLabel.SetTextAngle(90);
    PaletteLabel.Draw();
    palette->SetX1NDC(0.25); 
    palette->SetX2NDC(0.55); 
    palette->SetLabelOffset(0.03); 
    palette->SetLabelSize(0.2);
    palette->DrawClone();
    c1->Update();

    c1_22->cd();  
    c12Title.Draw();
    c1_22->Range(-2.5,-220,2.5,220);
    TBox b22(-1.6, -180, 1.6, 180);
    b22.SetFillStyle(1001); b22.SetFillColor(10); b22.Draw();

    double Nietabins = hEBGeom_eta->GetNbinsX();
    double Niphibins = hEBGeom_eta->GetNbinsY();
    TBox *boxColor[172][402], *boxLine[172][402];
    for (int ieta=1; ieta<=Nietabins; ieta++)
      if (ieta!=42) // ieta = 0 
	{
	  for (int iphi=1; iphi<=Niphibins; iphi++)
	    if (hEBGeom_phi->GetBinContent(ieta, iphi)>-999)
	      {
		Float_t eta =  hEBGeom_eta->GetBinContent(ieta, iphi);
		Float_t deta = hEBGeom_deta->GetBinContent(ieta);
		Float_t phi = hEBGeom_phi->GetBinContent(ieta,iphi);
		Float_t dphi = hEBGeom_dphi->GetBinContent(ieta);

	        deta = 0.0174;
		dphi = 0.0174*(180.0/pi);

		//-----Draw the box----//
		Float_t CurrentValue = hEBEnergy->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hEBEnergy->GetBinContent(ieta, iphi);
		Float_t Min = hEBEnergy->GetMinimum(0.0);
		Float_t Max = hEBEnergy->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		if (CurrentValue == 0.0) theColor = 0;
		if (fabs(eta)<=1.566 && CurrentValue>0.0)
		  {
		    DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
		  }
	      }
	}
    
    //-------Draw the CaloTower grid lines------//
    double NCTietabins = hTowerGeom_eta->GetNbinsX();
    double NCTiphibins = hTowerGeom_eta->GetNbinsY();
    TBox *CTboxLine[90][90];
    for (int ieta=1; ieta<=NCTietabins; ieta++)
      if (ieta!=42) // ieta = 0 
	{
	  for (int iphi=1; iphi<=NCTiphibins; iphi++)
	    if (hTowerGeom_phi->GetBinContent(ieta, iphi)>-999)
	      {
		Float_t eta =  hTowerGeom_eta->GetBinContent(ieta, iphi);
		Float_t deta = hTowerGeom_deta->GetBinContent(ieta);
		Float_t phi = hTowerGeom_phi->GetBinContent(ieta,iphi);
		Float_t dphi = hTowerGeom_dphi->GetBinContent(ieta);
		if (fabs(eta)<1.6)
		  {
		    CTboxLine[ieta][iphi] = new TBox(eta-deta/2.0,phi-dphi/2.0, eta+deta/2.0, phi+dphi/2.0 );
		    CTboxLine[ieta][iphi]->SetLineColor(kBlack);
		    CTboxLine[ieta][iphi]->SetLineWidth(0.5);	  
		    CTboxLine[ieta][iphi]->SetLineStyle(1);	  
		    CTboxLine[ieta][iphi]->SetFillStyle(0);
		    CTboxLine[ieta][iphi]->Draw("SAME");
		  }
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    
    //-------------Energy +Endcap
    c1_23->cd(); 
    c13Title.Draw();
    c1_23->Range(-225,-225,225,225);
    TBox b23(-160, -160, 160, 160);
    b23.SetFillStyle(1001); b23.SetFillColor(17); b23.Draw();
    double Nixbins = hEEpZGeom_x->GetNbinsX();
    double Niybins = hEEpZGeom_x->GetNbinsY();
    TBox *boxColor[102][102], *boxLine[102][102];
    for (int ix=1; ix<=Nixbins; ix++)
      for (int iy=1; iy<=Niybins; iy++)
	if (hEEpZGeom_x->GetBinContent(ix, iy)>-999)
	  {
	    Float_t x =  hEEpZGeom_x->GetBinContent(ix, iy);
	    Float_t y =  hEEpZGeom_y->GetBinContent(ix, iy);
	    Float_t dx = 2.462;
	    Float_t dy = 2.462;
	    //-----Get the Fill Color----//
	    Float_t CurrentValue = hEEpZEnergy->GetBinContent(ix, iy);
	    Float_t Min = hEEpZEnergy->GetMinimum(0.0);
	    Float_t Max = hEEpZEnergy->GetMaximum();
	    if (useLogZ)
	      {
		if (CurrentValue >= Energy_Min) CurrentValue = TMath::Log10(CurrentValue);
		if (Min >= Energy_Min) Min = TMath::Log10(Min);
		if (Max >= Energy_Min) Max = TMath::Log10(Max);
	      }
	    Int_t theColor  = GetColor(Min, Max, CurrentValue);
	    if (CurrentValue == 0.0) theColor = 0.0;
	    // Make the box
	    DrawBox(boxColor[ix][iy], boxLine[ix][iy], x, y, dx, dy, theColor);
	  }
    xEEbottom.Draw(); yEEleft.Draw(); xEEtop.Draw(); yEEright.Draw();
    
   //-------------Energy -Endcap
    c1_21->cd(); 
    c11Title.Draw();
    c1_21->Range(-225,-225,225,225);
    TBox b21(-160, -160, 160, 160);
    b21.SetFillStyle(1001); b21.SetFillColor(17); b21.Draw();
     double Nixbins = hEEmZGeom_x->GetNbinsX();
    double Niybins = hEEmZGeom_x->GetNbinsY();
    TBox *boxColor[102][102], *boxLine[102][102];
    for (int ix=1; ix<=Nixbins; ix++)
      for (int iy=1; iy<=Niybins; iy++)
	if (hEEmZGeom_x->GetBinContent(ix, iy)>-999)
	  {
	    Float_t x =  hEEmZGeom_x->GetBinContent(ix, iy);
	    Float_t y =  hEEmZGeom_y->GetBinContent(ix, iy);
	    Float_t dx = 2.462;
	    Float_t dy = 2.462;
	    //-----Get the Fill Color----//
	    Float_t CurrentValue = hEEmZEnergy->GetBinContent(ix, iy);
	    
	    Float_t Min = hEEmZEnergy->GetMinimum(0.0);
	    Float_t Max = hEEmZEnergy->GetMaximum();
	    if (useLogZ)
	      {
		if (CurrentValue >= Energy_Min) CurrentValue = TMath::Log10(CurrentValue);
		if (Min >= Energy_Min) Min = TMath::Log10(Min);
		if (Max >= Energy_Min) Max = TMath::Log10(Max);
	      }
	    Int_t theColor  = GetColor(Min, Max, CurrentValue);
	    if (CurrentValue == 0.0) theColor = 0.0;
	    // Make the box
	    DrawBox(boxColor[ix][iy], boxLine[ix][iy], x, y, dx, dy, theColor);
	  }
    xEEbottom.Draw(); yEEleft.Draw(); xEEtop.Draw(); yEEright.Draw();
    
    DrawElectrons(c1_23, c1_21, c1_22);
    DrawPhotons(c1_23, c1_21, c1_22);
    DrawJets(c1_23, c1_21, c1_22);
    DrawMET(c1_23, c1_21, c1_22);
    DrawMuons(c1_23, c1_21, c1_22);
    
    c1->Print("ECALRecHits_Energy.eps");
    c1_11->Clear(); c1_12->Clear(); c1_13->Clear();
    c1_21->Clear(); c1_22->Clear(); c1_23->Clear();
    c1_spec->Clear();
 
    
  }    
  
  //---------------ECAL Crystal->SuperCluster Map------------//
  //---------------ECAL Barrel
  {
    // Load Physics Objects
    TFile fEventObjects("DumpEvent_data.root");
    TH2F *hEBSC = hEB_SC_ieta_iphi;
    TH2F *hEEpZSC = hEEpZ_SC_ix_iy;
    TH2F *hEEmZSC = hEEmZ_SC_ix_iy;

    int useLogZ = false;
    // For a common z-scale, get the maximum energy
    Float_t SC_Max = TMath::Max( hEBSC->GetMaximum(), TMath::Max(hEEpZSC->GetMaximum(), hEEmZSC->GetMaximum()) );
    Float_t SC_Min = TMath::Min( hEBSC->GetMinimum(), TMath::Max(hEEpZSC->GetMinimum(), hEEmZSC->GetMinimum()) );
    // if using LogZ option, we need to correctly set the minimum of the palette 
    if (useLogZ)
      {
	SC_Min = TMath::Min( hEBSC->GetMinimum(0.0), TMath::Max(hEEpZSC->GetMinimum(0.0), hEEmZSC->GetMinimum(0.0)) );
	if (SC_Min == 0.0) SC_Min = 1E-1;
      }
    //---Kludge to get the supercluster plot on the same z-axis as the energy plot
    SC_Min = Energy_Min;
    SC_Max = Energy_Max;
    //----------------------
    // Format the Histograms
    hEBSC->SetMinimum(SC_Min); hEBSC->SetMaximum(SC_Max);
    hEEpZSC->SetMinimum(SC_Min); hEEpZSC->SetMaximum(SC_Max);
    hEEmZSC->SetMinimum(SC_Min); hEEmZSC->SetMaximum(SC_Max);
    hEBSC->SetStats(0); hEBSC->SetContour(50);
    hEEpZSC->SetStats(0); hEEpZSC->SetContour(50);
    hEEmZSC->SetStats(0); hEEmZSC->SetContour(50);
    hEBSC->GetXaxis()->SetTitle("ieta");
    hEBSC->GetYaxis()->SetTitle("iphi");
    hEBSC->GetYaxis()->SetTitleOffset(1.2);
    hEEpZSC->GetXaxis()->SetTitle("ix");
    hEEpZSC->GetYaxis()->SetTitle("iy");
    hEEpZSC->GetYaxis()->SetTitleOffset(1.2);
    hEEmZSC->GetXaxis()->SetTitle("ix");
    hEEmZSC->GetYaxis()->SetTitle("iy");
    hEEmZSC->GetYaxis()->SetTitleOffset(1.2);

    c1->cd(); c1->SetFillColor(18);
    TText CanvasTitle(.01, .965, "ECAL SC"); CanvasTitle.SetTextSize(0.035); CanvasTitle.Draw();
    TLine topLine(.01, .955, .99, .955); topLine.SetLineWidth(1); topLine.SetLineColor(kBlack); topLine.SetLineStyle(1); topLine.Draw();
    c1_11->cd();  c1_11->SetLogz(useLogZ);   c1_11->SetFrameFillColor(10);
    c1_12->cd();  c1_12->SetLogz(useLogZ);   c1_12->SetFrameFillColor(10);
    c1_13->cd();  c1_13->SetLogz(useLogZ);   c1_13->SetFrameFillColor(10);

    c1_13->cd(); hEEpZSC->Draw("COL"); 
    TLatex c13Title(0.05,0.94,"+Endcap"); c13Title.SetTextSize(0.05); c13Title.SetNDC(); c13Title.Draw();

    c1_11->cd(); hEEmZSC->Draw("COL");
    TLatex c11Title(0.05,0.94,"-Endcap"); c11Title.SetTextSize(0.05); c11Title.SetNDC(); c11Title.Draw();

   
    c1_12->cd();
    hEBSC->Draw("COLZ");
    c1->Update();
    TPaletteAxis *palette = (TPaletteAxis*)hEBSC->GetListOfFunctions()->FindObject("palette");
    hEBSC->Draw("COL");
    TLatex c12Title(0.05,0.94,"Barrel"); c12Title.SetTextSize(0.05); c12Title.SetNDC(); c12Title.Draw();


    c1_22->cd();  
    c12Title.Draw();
    c1_22->Range(-2.5,-220,2.5,220);
    TBox b22(-1.6, -180, 1.6, 180);
    b22.SetFillStyle(1001); b22.SetFillColor(10); b22.Draw();

    double Nietabins = hEBGeom_eta->GetNbinsX();
    double Niphibins = hEBGeom_eta->GetNbinsY();
    TBox *boxColor[172][402], *boxLine[172][402];
    for (int ieta=1; ieta<=Nietabins; ieta++)
      if (ieta!=42) // ieta = 0 
	{
	  for (int iphi=1; iphi<=Niphibins; iphi++)
	    if (hEBGeom_phi->GetBinContent(ieta, iphi)>-999)
	      {
		Float_t eta =  hEBGeom_eta->GetBinContent(ieta, iphi);
		Float_t deta = hEBGeom_deta->GetBinContent(ieta);
		Float_t phi = hEBGeom_phi->GetBinContent(ieta,iphi);
		Float_t dphi = hEBGeom_dphi->GetBinContent(ieta);

	        deta = 0.0175;
		dphi = 0.0175*(180.0/pi);

		//-----Draw the box----//
		Float_t CurrentValue = hEBSC->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hEBSC->GetBinContent(ieta, iphi);
		Float_t Min = hEBSC->GetMinimum(0.0);
		Float_t Max = hEBSC->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= SC_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= SC_Min) Min = TMath::Log10(Min);
		    if (Max >= SC_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = CurrentValue+1;
		if (theColor>=10) theColor+=2;
		Int_t theLineColor = 10;
		if (CurrentValue == 0.0) theColor = 0;
		if (fabs(eta)<=1.566 && CurrentValue>0.0)
		  {
		    DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
		  }
	      }
	}

    //-------Draw the CaloTower grid lines------//
    double NCTietabins = hTowerGeom_eta->GetNbinsX();
    double NCTiphibins = hTowerGeom_eta->GetNbinsY();
    TBox *CTboxLine[90][90];
    for (int ieta=1; ieta<=NCTietabins; ieta++)
      if (ieta!=42) // ieta = 0 
	{
	  for (int iphi=1; iphi<=NCTiphibins; iphi++)
	    if (hTowerGeom_phi->GetBinContent(ieta, iphi)>-999)
	      {
		Float_t eta =  hTowerGeom_eta->GetBinContent(ieta, iphi);
		Float_t deta = hTowerGeom_deta->GetBinContent(ieta);
		Float_t phi = hTowerGeom_phi->GetBinContent(ieta,iphi);
		Float_t dphi = hTowerGeom_dphi->GetBinContent(ieta);
		if (fabs(eta)<1.6)
		  {
		    CTboxLine[ieta][iphi] = new TBox(eta-deta/2.0,phi-dphi/2.0, eta+deta/2.0, phi+dphi/2.0 );
		    CTboxLine[ieta][iphi]->SetLineColor(kBlack);
		    CTboxLine[ieta][iphi]->SetLineWidth(0.5);	  
		    CTboxLine[ieta][iphi]->SetLineStyle(1);	  
		    CTboxLine[ieta][iphi]->SetFillStyle(0);
		    CTboxLine[ieta][iphi]->Draw("SAME");
		  }
	      }
	}
   
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
 

    //-------------SC +Endcap
    c1_23->cd(); 
    c13Title.Draw();
    c1_23->Range(-225,-225,225,225);
    TBox b23(-160, -160, 160, 160);
    b23.SetFillStyle(1001); b23.SetFillColor(17); b23.Draw();
    double Nixbins = hEEpZGeom_x->GetNbinsX();
    double Niybins = hEEpZGeom_x->GetNbinsY();
    TBox *boxColor[102][102], *boxLine[102][102];
    for (int ix=1; ix<=Nixbins; ix++)
      for (int iy=1; iy<=Niybins; iy++)
	if (hEEpZGeom_x->GetBinContent(ix, iy)>-999)
	  {
	    Float_t x =  hEEpZGeom_x->GetBinContent(ix, iy);
	    Float_t y =  hEEpZGeom_y->GetBinContent(ix, iy);
	    Float_t dx = 2.47;
	    Float_t dy = 2.47;
	    //-----Get the Fill Color----//
	    Float_t CurrentValue = hEEpZSC->GetBinContent(ix, iy);
	    Float_t Min = hEEpZSC->GetMinimum(0.0);
	    Float_t Max = hEEpZSC->GetMaximum();
	    if (useLogZ)
	      {
		if (CurrentValue >= SC_Min) CurrentValue = TMath::Log10(CurrentValue);
		if (Min >= SC_Min) Min = TMath::Log10(Min);
		if (Max >= SC_Min) Max = TMath::Log10(Max);
	      }
	    Int_t theColor = CurrentValue+1;
	    Int_t theLineColor=10;
	    if (theColor>=10) theColor+=2;
	    if (CurrentValue == 0.0) theColor = 0.0;
	    // Make the box
	    DrawBox(boxColor[ix][iy], boxLine[ix][iy], x, y, dx, dy, theColor);
	  }
    xEEbottom.Draw(); yEEleft.Draw(); xEEtop.Draw(); yEEright.Draw();
    
   //-------------SC -Endcap
    c1_21->cd(); 
    c11Title.Draw();
    c1_21->Range(-225,-225,225,225);
    TBox b21(-160, -160, 160, 160);
    b21.SetFillStyle(1001); b21.SetFillColor(17); b21.Draw();
     double Nixbins = hEEmZGeom_x->GetNbinsX();
    double Niybins = hEEmZGeom_x->GetNbinsY();
    TBox *boxColor[102][102], *boxLine[102][102];
    for (int ix=1; ix<=Nixbins; ix++)
      for (int iy=1; iy<=Niybins; iy++)
	if (hEEmZGeom_x->GetBinContent(ix, iy)>-999)
	  {
	    Float_t x =  hEEmZGeom_x->GetBinContent(ix, iy);
	    Float_t y =  hEEmZGeom_y->GetBinContent(ix, iy);
	    Float_t dx = 2.47;
	    Float_t dy = 2.47;
	    //-----Get the Fill Color----//
	    Float_t CurrentValue = hEEmZSC->GetBinContent(ix, iy);
	    
	    Float_t Min = hEEmZSC->GetMinimum(0.0);
	    Float_t Max = hEEmZSC->GetMaximum();
	    if (useLogZ)
	      {
		if (CurrentValue >= SC_Min) CurrentValue = TMath::Log10(CurrentValue);
		if (Min >= SC_Min) Min = TMath::Log10(Min);
		if (Max >= SC_Min) Max = TMath::Log10(Max);
	      }
	    Int_t theColor = CurrentValue+1;
	    if (theColor>=10) theColor+=2;
	    Int_t theLineColor=10;
	    if (CurrentValue == 0.0) theColor = 0.0;
	    // Make the box
	    DrawBox(boxColor[ix][iy], boxLine[ix][iy], x, y, dx, dy, theColor);
	  }
    xEEbottom.Draw(); yEEleft.Draw(); xEEtop.Draw(); yEEright.Draw();
    c1->Print("ECALRecHits_SuperClusters.eps");
    c1_11->Clear(); c1_12->Clear(); c1_13->Clear();
    c1_21->Clear(); c1_22->Clear(); c1_23->Clear();
    c1_spec->Clear();
    
  }
  
  //---------------Make ECALRecHits Occupancy Plots------------//
  //---------------ECAL Barrel
  {
    int useLogZ = true;
    // For a common z-scale, get the maximum energy
    Float_t Occ_Max = TMath::Max( hEBOcc->GetMaximum(), TMath::Max(hEEpZOcc->GetMaximum(), hEEmZOcc->GetMaximum()) );
    Float_t Occ_Min = TMath::Min( hEBOcc->GetMinimum(), TMath::Max(hEEpZOcc->GetMinimum(), hEEmZOcc->GetMinimum()) );
    if (useLogZ)
      {
	Occ_Min = TMath::Min( hEBOcc->GetMinimum(0.0), TMath::Max(hEEpZOcc->GetMinimum(0.0), hEEmZOcc->GetMinimum(0.0)) );
	if (Energy_Min == 0.0) Occ_Min = 1E-1;
      }
    // Format the Histograms
    hEBOcc->SetMinimum(Occ_Min); hEBOcc->SetMaximum(Occ_Max);
    hEEpZOcc->SetMinimum(Occ_Min); hEEpZOcc->SetMaximum(Occ_Max);
    hEEmZOcc->SetMinimum(Occ_Min); hEEmZOcc->SetMaximum(Occ_Max);
    hEBOcc->SetStats(0); hEBOcc->SetContour(50);
    hEEpZOcc->SetStats(0); hEEpZOcc->SetContour(50);
    hEEmZOcc->SetStats(0); hEEmZOcc->SetContour(50);
    hEBOcc->GetXaxis()->SetTitle("ieta");
    hEBOcc->GetYaxis()->SetTitle("iphi");
    hEBOcc->GetYaxis()->SetTitleOffset(1.2);
    hEEpZOcc->GetXaxis()->SetTitle("ix");
    hEEpZOcc->GetYaxis()->SetTitle("iy");
    hEEpZOcc->GetYaxis()->SetTitleOffset(1.2);
    hEEmZOcc->GetXaxis()->SetTitle("ix");
      hEEmZOcc->GetYaxis()->SetTitle("iy");
      hEEmZOcc->GetYaxis()->SetTitleOffset(1.2);
      
      c1->cd(); c1->SetFillColor(18);
      TText CanvasTitle(.01, .965, "ECAL Occpancy"); CanvasTitle.SetTextSize(0.035); CanvasTitle.Draw();
      TLine topLine(.01, .955, .99, .955); topLine.SetLineWidth(1); topLine.SetLineColor(kBlack); topLine.SetLineStyle(1); topLine.Draw();
      c1_11->cd();  c1_11->SetLogz(useLogZ);   c1_11->SetFrameFillColor(10);
      c1_12->cd();  c1_12->SetLogz(useLogZ);   c1_12->SetFrameFillColor(10);
      c1_13->cd();  c1_13->SetLogz(useLogZ);   c1_13->SetFrameFillColor(10);
      
      c1_13->cd(); hEEpZOcc->Draw("COL"); 
      TLatex c13Title(0.05,0.94,"+Endcap"); c13Title.SetTextSize(0.05); c13Title.SetNDC(); c13Title.Draw();
      
      c1_11->cd(); hEEmZOcc->Draw("COL");
      TLatex c11Title(0.05,0.94,"-Endcap"); c11Title.SetTextSize(0.05); c11Title.SetNDC(); c11Title.Draw();
      
      
      c1_12->cd();
      hEBOcc->Draw("COLZ");
      c1->Update();
      TPaletteAxis *palette = (TPaletteAxis*)hEBOcc->GetListOfFunctions()->FindObject("palette");
      hEBOcc->Draw("COL");
      TLatex c12Title(0.05,0.94,"Barrel"); c12Title.SetTextSize(0.05); c12Title.SetNDC(); c12Title.Draw();
      
      c1_spec->cd(); c1_spec->SetLogz(useLogZ);
      TText PaletteLabel(0.15,0.8,"Occupancy (%)");
      PaletteLabel.SetTextSize(0.15);
      PaletteLabel.SetTextAngle(90);
      PaletteLabel.Draw();
      palette->SetX1NDC(0.25); 
      palette->SetX2NDC(0.55); 
      palette->SetLabelOffset(0.03); 
      palette->SetLabelSize(0.2);
      palette->DrawClone();
      c1->Update();    
      
      c1_22->cd();  
      c12Title.Draw();
      c1_22->Range(-2.5,-220,2.5,220);
      TBox b22(-1.6, -180, 1.6, 180);
      b22.SetFillStyle(1001); b22.SetFillColor(10); b22.Draw();

    double Nietabins = hEBGeom_eta->GetNbinsX();
    double Niphibins = hEBGeom_eta->GetNbinsY();
    TBox *boxColor[172][402], *boxLine[172][402];
    for (int ieta=1; ieta<=Nietabins; ieta++)
      {
	for (int iphi=1; iphi<=Niphibins; iphi++)
	  if (hEBGeom_phi->GetBinContent(ieta, iphi)>-999)
	    {
	      Float_t eta =  hEBGeom_eta->GetBinContent(ieta, iphi);
	      //  float deta = hEBGeom_deta->GetBinContent(ieta);
	      Float_t phi = hEBGeom_phi->GetBinContent(ieta,iphi);
	      // float dphi = hEBGeom_dphi->GetBinContent(ieta);	 
	      Float_t deta = 0.0174;
	      Float_t dphi = 0.0174*(180.0/pi); 
	      
	      //-----Get the Fill Color----//
	      Float_t CurrentValue = hEBOcc->GetBinContent(ieta, iphi);
	      Float_t CurrentValueL10 = hEBOcc->GetBinContent(ieta, iphi);
	      Float_t Min = hEBOcc->GetMinimum(0.0);
	      Float_t Max = hEBOcc->GetMaximum();
	      if (useLogZ)
		  {
		    if (CurrentValue >= Occ_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Occ_Min) Min = TMath::Log10(Min);
		    if (Max >= Occ_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		Int_t theLineColor = 10;
		if (CurrentValue == 0.0) theColor = 0;
		if (fabs(eta)<=1.566 && CurrentValue>0.0)
		  {
		    DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
		  }
	    }
      }
      //-------Draw the CaloTower grid lines------//
    double NCTietabins = hTowerGeom_eta->GetNbinsX();
    double NCTiphibins = hTowerGeom_eta->GetNbinsY();
    TBox *CTboxLine[90][90];
    for (int ieta=1; ieta<=NCTietabins; ieta++)
      if (ieta!=42) // ieta = 0 
	{
	  for (int iphi=1; iphi<=NCTiphibins; iphi++)
	    if (hTowerGeom_phi->GetBinContent(ieta, iphi)>-999)
	      {
		Float_t eta =  hTowerGeom_eta->GetBinContent(ieta, iphi);
		Float_t deta = hTowerGeom_deta->GetBinContent(ieta);
		Float_t phi = hTowerGeom_phi->GetBinContent(ieta,iphi);
		Float_t dphi = hTowerGeom_dphi->GetBinContent(ieta);
		if (fabs(eta)<1.6)
		  {
		    CTboxLine[ieta][iphi] = new TBox(eta-deta/2.0,phi-dphi/2.0, eta+deta/2.0, phi+dphi/2.0 );
		    CTboxLine[ieta][iphi]->SetLineColor(kBlack);
		    CTboxLine[ieta][iphi]->SetLineWidth(0.5);	  
		    CTboxLine[ieta][iphi]->SetLineStyle(1);	  
		    CTboxLine[ieta][iphi]->SetFillStyle(0);
		    CTboxLine[ieta][iphi]->Draw("SAME");
		  }
	      }
	}

  
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
 
    //-------------Occ +Endcap
    c1_23->cd(); 
    c13Title.Draw();
    c1_23->Range(-225,-225,225,225);
    TBox b23(-160, -160, 160, 160);
    b23.SetFillStyle(1001); b23.SetFillColor(17); b23.Draw();
    double Nixbins = hEEpZGeom_x->GetNbinsX();
    double Niybins = hEEpZGeom_x->GetNbinsY();
    TBox *boxColor[102][102], *boxLine[102][102];
    for (int ix=1; ix<=Nixbins; ix++)
      for (int iy=1; iy<=Niybins; iy++)
	if (hEEpZGeom_x->GetBinContent(ix, iy)>-999)
	  {
	    Float_t x =  hEEpZGeom_x->GetBinContent(ix, iy);
	    Float_t y =  hEEpZGeom_y->GetBinContent(ix, iy);
	    Float_t dx = 2.462;
	    Float_t dy = 2.462;
	    //-----Get the Fill Color----//
	    Float_t CurrentValue = hEEpZOcc->GetBinContent(ix, iy);
	    Float_t Min = hEEpZOcc->GetMinimum(0.0);
	    Float_t Max = hEEpZOcc->GetMaximum();
	    if (useLogZ)
	      {
		if (CurrentValue >= Occ_Min) CurrentValue = TMath::Log10(CurrentValue);
		if (Min >= Occ_Min) Min = TMath::Log10(Min);
		if (Max >= Occ_Min) Max = TMath::Log10(Max);
	      }
	    Int_t theColor  = GetColor(Min, Max, CurrentValue);
	    if (CurrentValue == 0.0) theColor = 0.0;
	    // Make the box
	    DrawBox(boxColor[ix][iy], boxLine[ix][iy], x, y, dx, dy, theColor);
	  }
    xEEbottom.Draw(); yEEleft.Draw(); xEEtop.Draw(); yEEright.Draw();
    
    //-------------Occ -Endcap
    c1_21->cd(); 
    c11Title.Draw();
    c1_21->Range(-225,-225,225,225);
    TBox b21(-160, -160, 160, 160);
    b21.SetFillStyle(1001); b21.SetFillColor(17); b21.Draw();
     double Nixbins = hEEmZGeom_x->GetNbinsX();
    double Niybins = hEEmZGeom_x->GetNbinsY();
    TBox *boxColor[102][102], *boxLine[102][102];
    for (int ix=1; ix<=Nixbins; ix++)
      for (int iy=1; iy<=Niybins; iy++)
	if (hEEmZGeom_x->GetBinContent(ix, iy)>-999)
	  {
	    Float_t x =  hEEmZGeom_x->GetBinContent(ix, iy);
	    Float_t y =  hEEmZGeom_y->GetBinContent(ix, iy);
	    Float_t dx = 2.462;
	    Float_t dy = 2.462;
	    //-----Get the Fill Color----//
	    Float_t CurrentValue = hEEmZOcc->GetBinContent(ix, iy);
	    
	    Float_t Min = hEEmZOcc->GetMinimum(0.0);
	    Float_t Max = hEEmZOcc->GetMaximum();
	    if (useLogZ)
	      {
		if (CurrentValue >= Occ_Min) CurrentValue = TMath::Log10(CurrentValue);
		if (Min >= Occ_Min) Min = TMath::Log10(Min);
		if (Max >= Occ_Min) Max = TMath::Log10(Max);
	      }
	    Int_t theColor  = GetColor(Min, Max, CurrentValue);
	    if (CurrentValue == 0.0) theColor = 0.0;
	    // Make the box
	    DrawBox(boxColor[ix][iy], boxLine[ix][iy], x, y, dx, dy, theColor); 
	  }
    xEEbottom.Draw(); yEEleft.Draw(); xEEtop.Draw(); yEEright.Draw();
    c1->Print("ECALRecHitOcc.eps");   
  }
  
  // Make Eta-Ring Occupancy plots
  {
    //---------------------Make Canvas-------------------------------------//
    TCanvas *c2 = new TCanvas("c2","c2",1000,500); 
    TPad *c2_1  = new TPad("c2_1","c2_1",0.01,0.01,0.99,0.94); 
    c2_1->SetFrameFillColor(10); c2_1->SetGridy(1); c2_1->SetLogy(useLogZ); c2_1->Draw(); 
    c2->cd();
    TLatex CanvasTitle_(.01, .95, "ECAL Crystal #eta-Ring Occupancy");
    CanvasTitle_.Draw();  
    
    TH1F *hOcc_ietaEBRing = new TH1F("hOcc_ietaEBRing", "Occupancy vs i#eta", 171, -85, 86);
    hOcc_ietaEBRing->GetXaxis()->SetTitle("#eta");
    hOcc_ietaEBRing->GetYaxis()->SetTitleOffset(1.3);
    hOcc_ietaEBRing->GetYaxis()->SetTitle("Occupancy (%)");
    Float_t EBEtaBins[172]; EBEtaBins[85] = -0.0031411; // sets the lower edge of the bin 0
    Float_t EBdphi[171];

    double Nietabins = hEBGeom_eta->GetNbinsX();
    double Niphibins = hEBGeom_eta->GetNbinsY();
    for (int ieta=1; ieta<=Nietabins; ieta++)
      {
	TH1F *hTemp = new TH1F("hTemp","",20000,0,200);
	for (int iphi=1; iphi<=Niphibins; iphi++)
	  {
	    if (hEBGeom_phi->GetBinContent(ieta, iphi)>-999)
	      {
		Float_t eta =  hEBGeom_eta->GetBinContent(ieta, iphi);
		Float_t phi = hEBGeom_phi->GetBinContent(ieta,iphi);
		Float_t deta = 0.0174;
		Float_t dphi = 0.0174*(180.0/pi);
		EBdphi[ieta-1] = 0.0174*0.0174;
		EBEtaBins[ieta-1] = eta-deta/2.0;
		if (ieta==Nietabins) EBEtaBins[ieta] = eta+deta/2.0;
		Float_t CurrentValue = hEBOcc->GetBinContent(ieta, iphi);
		hTemp->Fill(CurrentValue);
	      }
	  } // end iphi loop
	
	hOcc_ietaEBRing->SetBinContent(ieta, hTemp->GetMean());
	hOcc_ietaEBRing->SetBinError(ieta, hTemp->GetRMS());
	delete hTemp;
      }

    TH1F *hOcc_etaEBRing = new TH1F("hOcc_etaEBRing", "Occupancy vs #eta", 171, EBEtaBins);
    hOcc_etaEBRing->GetXaxis()->SetTitle("#eta");
    hOcc_etaEBRing->GetYaxis()->SetTitleOffset(1.3);
    hOcc_etaEBRing->GetYaxis()->SetTitle("Occupancy (%)");
    hOcc_etaEBRing->SetAxisRange(-3.1,3.1,"X");
       
    for (int i=1; i<=hOcc_etaEBRing->GetNbinsX()+1; i++)
      {	
	if (i!=86)
	  {
	    hOcc_etaEBRing->SetBinContent(i, hOcc_ietaEBRing->GetBinContent(i));
	    hOcc_etaEBRing->SetBinError(i, hOcc_ietaEBRing->GetBinError(i));
	  }
      }
    
    //-------------Occ +Endcap
    TH1F *hOcc_ietaEEpZRing = new TH1F("hOcc_ietaEEpZRing", "Occupancy vs i#eta", 39,1,39);
    Float_t EEpZEtaBins[40];
    Float_t EEpZdphi[39];
    double Nixbins = hEEpZGeom_x->GetNbinsX();
    double Niybins = hEEpZGeom_x->GetNbinsY();
    for (int iy_=1; iy_<=39; iy_++)
      {
	Float_t x_ =  hEEpZGeom_x->GetBinContent(50, iy_);
	Float_t y_ =  hEEpZGeom_y->GetBinContent(50, iy_);
	Float_t z_ =  317.0;
	Float_t dx_ = 2.462;
	Float_t dy_ = 2.462;
	TVector3 v_(x_,y_,z_), vLow_(x_,y_-dy_/2.0,z_), vHigh_(x_,y_+dy_/2.0,z_), vSide1_(x_+dx_/2.0,y_,z_), vSide2_(x_-dx_/2.0,y_,z_);
	EEpZdphi[iy_-1] = fabs( vSide1_.Phi() - vSide2_.Phi() )*fabs( vHigh_.Eta() - vLow_.Eta()) ;
	EEpZEtaBins[iy_-1] = vLow_.Eta();
	// cout << "iy=" << iy_ << " x=" << x_ << ", y=" << y_ << "dPhi=" << EEpZdphi[iy_-1] << endl;
	if (iy_ == 39) EEpZEtaBins[iy_] = vHigh_.Eta();

	TH1F *hTemp = new TH1F("hTemp","",20000,0,200);
	for (int ix=1; ix<=Nixbins; ix++)
	    for (int iy=1; iy<=Niybins; iy++)
	      if (hEEpZGeom_x->GetBinContent(ix, iy)>-999)
		{
		  Float_t x =  hEEpZGeom_x->GetBinContent(ix, iy);
		  Float_t y =  hEEpZGeom_y->GetBinContent(ix, iy);
		  Float_t z =  317.0;
		  Float_t dx = 2.462;
		  Float_t dy = 2.462;
		  TVector3 v(x,y,z);
		  if (vHigh_.Eta()>v.Eta() && vLow_.Eta()<=v.Eta())
		    {
		      Float_t CurrentValue = hEEpZOcc->GetBinContent(ix, iy);
		      hTemp->Fill(CurrentValue);
		    }
		}
	hOcc_ietaEEpZRing->SetBinContent(iy_, hTemp->GetMean());
	hOcc_ietaEEpZRing->SetBinError(iy_, hTemp->GetRMS());
	delete hTemp;
	// cout << iy_ << 	" " << EEpZEtaBins[iy_-1] << " " <<  hTemp->GetMean() << endl;
      } // loop over iy_
    
    TH1F *hOcc_etaEEpZRing = new TH1F("hOcc_etaEEpZRing", "Occupancy vs #eta", 39, EEpZEtaBins);
    hOcc_etaEEpZRing->GetXaxis()->SetTitle("#eta");
    hOcc_etaEEpZRing->GetYaxis()->SetTitleOffset(1.3);
    hOcc_etaEEpZRing->GetYaxis()->SetTitle("Occupancy (%)");
           
    for (int i=1; i<=hOcc_etaEEpZRing->GetNbinsX()+1; i++)
      {	
	hOcc_etaEEpZRing->SetBinContent(i, hOcc_ietaEEpZRing->GetBinContent(i));
	hOcc_etaEEpZRing->SetBinError(i, hOcc_ietaEEpZRing->GetBinError(i));
      }

  //-------------Occ -Endcap
    TH1F *hOcc_ietaEEmZRing = new TH1F("hOcc_ietaEEmZRing", "Occupancy vs i#eta", 39,1,39);
    Float_t EEmZEtaBins[40];
    Float_t EEmZdphi[39];
    double Nixbins = hEEmZGeom_x->GetNbinsX();
    double Niybins = hEEmZGeom_x->GetNbinsY();
    Int_t iy_ = 0;
    for (int jy_=Niybins-38; jy_<=Niybins; jy_++)
      {
	iy_++;
	Float_t x_ =  hEEmZGeom_x->GetBinContent(50, jy_);
	Float_t y_ =  hEEmZGeom_y->GetBinContent(50, jy_);
	Float_t z_ =  -317.0;
	Float_t dx_ = 2.462;
	Float_t dy_ = 2.462;
	TVector3 v_(x_,y_,z_), vLow_(x_,y_-dy_/2.0,z_), vHigh_(x_,y_+dy_/2.0,z_), vSide1_(x_+dx_/2.0,y_,z_), vSide2_(x_-dx_/2.0,y_,z_);
	EEmZdphi[iy_-1] = fabs( vSide1_.Phi() - vSide2_.Phi() )*fabs( vHigh_.Eta() - vLow_.Eta());
	EEmZEtaBins[iy_-1] = vLow_.Eta();
	if (iy_ == 39) EEmZEtaBins[iy_] = vHigh_.Eta();

	TH1F *hTemp = new TH1F("hTemp","",20000,0,200);
	for (int ix=1; ix<=Nixbins; ix++)
	    for (int iy=1; iy<=Niybins; iy++)
	      if (hEEmZGeom_x->GetBinContent(ix, iy)>-999)
		{
		  Float_t x =  hEEmZGeom_x->GetBinContent(ix, iy);
		  Float_t y =  hEEmZGeom_y->GetBinContent(ix, iy);
		  Float_t z =  -317.0;
		  Float_t dx = 2.462;
		  Float_t dy = 2.462;
		  TVector3 v(x,y,z);
		  if (vHigh_.Eta()>v.Eta() && vLow_.Eta()<=v.Eta())
		    {
		      Float_t CurrentValue = hEEmZOcc->GetBinContent(ix, iy);
		      hTemp->Fill(CurrentValue);
		    }
		}
	hOcc_ietaEEmZRing->SetBinContent(iy_, hTemp->GetMean());
	hOcc_ietaEEmZRing->SetBinError(iy_, hTemp->GetRMS());
	delete hTemp;
	//cout << iy_ << 	" " << EEmZEtaBins[iy_-1] << " " <<  hTemp->GetMean() << endl;
      } // loop over iy_
    
    TH1F *hOcc_etaEEmZRing = new TH1F("hOcc_etaEEmZRing", "Occupancy vs #eta", 39, EEmZEtaBins);
    hOcc_etaEEmZRing->GetXaxis()->SetTitle("#eta");
    hOcc_etaEEmZRing->GetYaxis()->SetTitleOffset(1.3);
    hOcc_etaEEmZRing->GetYaxis()->SetTitle("Occupancy (%)");
           
    for (int i=1; i<=hOcc_etaEEmZRing->GetNbinsX()+1; i++)
      {	
	hOcc_etaEEmZRing->SetBinContent(i, hOcc_ietaEEmZRing->GetBinContent(i));
	hOcc_etaEEmZRing->SetBinError(i, hOcc_ietaEEmZRing->GetBinError(i));
      }

    //----Combine histos    
    Float_t EtaBins[252];
    for (int i=0;i<=39;i++)   EtaBins[i] = EEmZEtaBins[i];
    for (int i=0;i<=171;i++)  EtaBins[40+i] = EBEtaBins[i];
    for (int i=0;i<=39;i++)   EtaBins[40+172+i] = EEpZEtaBins[i];

    TH1F *hOcc_etaRing = new TH1F("hOcc_etaRing", "Occupancy vs #eta", 251, EtaBins);
    hOcc_etaRing->SetStats(0);
    hOcc_etaRing->GetXaxis()->SetTitle("#eta");
    hOcc_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hOcc_etaRing->GetYaxis()->SetTitle("Occupancy (%)");
    TH1F *hdOccdphi_etaRing = new TH1F("hdOccdphi_etaRing", "Occupancy vs #eta", 251, EtaBins);
    hdOccdphi_etaRing->SetStats(0);
    hdOccdphi_etaRing->GetXaxis()->SetTitle("#eta");
    hdOccdphi_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hdOccdphi_etaRing->GetYaxis()->SetTitle("Occupancy (%)");

    for (int i=1; i<=39; i++)
      {
	hOcc_etaRing->SetBinContent(i, hOcc_ietaEEmZRing->GetBinContent(i));
	hOcc_etaRing->SetBinError(i, hOcc_ietaEEmZRing->GetBinError(i));
	if (EEmZdphi[i-1]>0)
	  {
	    //cout << "EEmZdphi[" << (i-1) <<"] = " << EEmZdphi[i-1] << endl;
	    hdOccdphi_etaRing->SetBinContent(i, hOcc_ietaEEmZRing->GetBinContent(i)/EEmZdphi[i-1]);
	    hdOccdphi_etaRing->SetBinError(i, hOcc_ietaEEmZRing->GetBinError(i)/EEmZdphi[i-1]);
	  }
      }
    for (int i=1; i<=171; i++)
      {
	//cout << "EBdphi[" << (i-1) <<"] = " << EBdphi[i-1] << endl;
	hOcc_etaRing->SetBinContent(1+39+i, hOcc_ietaEBRing->GetBinContent(i));
	hOcc_etaRing->SetBinError(1+39+i, hOcc_ietaEBRing->GetBinError(i));
	if (EBdphi[i-1]>0)
	  {
	    hdOccdphi_etaRing->SetBinContent(1+39+i, hOcc_ietaEBRing->GetBinContent(i)/EBdphi[i-1]);
	    hdOccdphi_etaRing->SetBinError(1+39+i, hOcc_ietaEBRing->GetBinError(i)/EBdphi[i-1]);
	  }
      }
    for (int i=1; i<=39; i++)
      {
	//cout << "EEpZdphi[" << (i-1) <<"] = " << EEpZdphi[i-1] << endl;
	hOcc_etaRing->SetBinContent(2+39+171+i, hOcc_ietaEEpZRing->GetBinContent(i));
	hOcc_etaRing->SetBinError(2+39+171+i, hOcc_ietaEEpZRing->GetBinError(i));
      	if (EEpZdphi[i-1]>0)
	  {
	    hdOccdphi_etaRing->SetBinContent(2+39+171+i, hOcc_ietaEEpZRing->GetBinContent(i)/EEpZdphi[i-1]);
	    hdOccdphi_etaRing->SetBinError(2+39+171+i, hOcc_ietaEEpZRing->GetBinError(i)/EEpZdphi[i-1]);
	  }
      }
    
    TFile fOut("ECALRecHitPlots.root","RECREATE");

    c2_1->cd();
    hOcc_etaRing->Draw();
    c2->Print("ECALRecHits_EtaRingOccupancy.eps");   
    c2_1->Clear();
    hdOccdphi_etaRing->Draw();
    c2->Print("ECALRecHits_dOccdetadphi.eps");   

    hdOccdphi_etaRing->Write();
    fOut.Close();
  }
}
