void SetUp()
{
  gROOT->Reset();
  gStyle->SetPalette(1,0);
  gROOT->ProcessLine(".L HCALPlotUtilities.C");  
}

void plotHCALRecHits(){
  SetUp();
  double pi = TMath::Pi();
  // Load geometry Histograms
  TFile fCaloTowerGeom("CaloTower_geometry.root");
  TH2F *hTowerGeom_eta = hCT_ieta_iphi_etaMap;
  TH2F *hTowerGeom_phi = hCT_ieta_iphi_phiMap;
  TH1F *hTowerGeom_deta = hCT_ieta_detaMap;
  TH1F *hTowerGeom_dphi = hCT_ieta_dphiMap;
  // Load HCALRecHit Histograms
  TFile fHCALData("HCALRecHitAnalyzer_data.root");
  TH2F *hHCAL_L1_energy = new TH2F(*hHCAL_L1_energy_ieta_iphi);
  TH2F *hHCAL_L2_energy = new TH2F(*hHCAL_L2_energy_ieta_iphi);
  TH2F *hHCAL_L3_energy = new TH2F(*hHCAL_L3_energy_ieta_iphi);
  TH2F *hHCAL_L4_energy = new TH2F(*hHCAL_L4_energy_ieta_iphi);
  TH2F *hHCAL_L1_Occ = new TH2F(*hHCAL_L1_Occ_ieta_iphi);
  TH2F *hHCAL_L2_Occ = new TH2F(*hHCAL_L2_Occ_ieta_iphi);
  TH2F *hHCAL_L3_Occ = new TH2F(*hHCAL_L3_Occ_ieta_iphi);
  TH2F *hHCAL_L4_Occ = new TH2F(*hHCAL_L4_Occ_ieta_iphi);
  
  //---------------------Make Canvas-------------------------------------//
  TCanvas *c1 = new TCanvas("c1","c1",1200,800); 
  TPad *c1_11  = new TPad("c1_11","c1_11",0.01,0.475,0.445,0.94); c1_11->Draw(); 
  TPad *c1_12  = new TPad("c1_12","c1_12",0.455,0.475,0.89,0.94); c1_12->Draw(); 
  TPad *c1_21  = new TPad("c1_21","c1_21",0.01,0.01,0.445,0.465); c1_21->Draw(); 
  TPad *c1_22  = new TPad("c1_22","c1_22",0.455,0.01,0.89,0.465); c1_22->Draw(); 
  TPad *c1_spec  = new TPad("c1_spec","c1_spec",0.91,0.01,0.99,0.94); c1_spec->Draw(); 


  //-----------Define axis for eta,phi plot-------------------//
  TGaxis xbottom(-5.191,-180,5.191,-180,-5.191,5.191,16,"");
  xbottom.SetTitle("#eta");
  TGaxis yleft(-5.191,-180,-5.191,180,-180,180,15,"");
  yleft.SetTitle("#phi (Degrees)");
  TGaxis xtop(-5.191,180,5.191,180,-5.191,5.191,0,"");
  TGaxis yright(5.191,-180,5.191,180,-180,180,0,"");
  xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
  //----------------------------------------------------------//
  

  //---------------Make Tower Energy plots------------//
  {
    int useLogZ = true;
    // For a common z-scale, get the maximum energy
    Float_t Energy_Max = TMath::Max( TMath::Max(hHCAL_L1_energy->GetMaximum(),hHCAL_L2_energy->GetMaximum()),
				     TMath::Max(hHCAL_L3_energy->GetMaximum(),hHCAL_L4_energy->GetMaximum()) );
    Float_t Energy_Min = TMath::Min( TMath::Min(hHCAL_L1_energy->GetMinimum(),hHCAL_L2_energy->GetMinimum()),
				     TMath::Min(hHCAL_L3_energy->GetMinimum(),hHCAL_L4_energy->GetMinimum()) );
    // if using LogZ option, we need to correctly set the minimum of the palette 
    if (useLogZ)
      {
	Energy_Min =  TMath::Min( TMath::Min(hHCAL_L1_energy->GetMinimum(0.0),hHCAL_L2_energy->GetMinimum(0.0)),
				  TMath::Min(hHCAL_L3_energy->GetMinimum(0.0),hHCAL_L4_energy->GetMinimum(0.0)) );
	if (Energy_Min == 0.0) Energy_Min = 1E-1;
      }
    hHCAL_L1_energy->SetMinimum(Energy_Min); hHCAL_L1_energy->SetMaximum(Energy_Max);
    hHCAL_L2_energy->SetMinimum(Energy_Min); hHCAL_L2_energy->SetMaximum(Energy_Max);
    hHCAL_L3_energy->SetMinimum(Energy_Min); hHCAL_L3_energy->SetMaximum(Energy_Max);
    hHCAL_L4_energy->SetMinimum(Energy_Min); hHCAL_L4_energy->SetMaximum(Energy_Max);
    hHCAL_L1_energy->SetStats(0);   hHCAL_L1_energy->SetContour(50);
    hHCAL_L2_energy->SetStats(0);   hHCAL_L2_energy->SetContour(50);
    hHCAL_L3_energy->SetStats(0);   hHCAL_L3_energy->SetContour(50);
    hHCAL_L4_energy->SetStats(0);   hHCAL_L4_energy->SetContour(50);
    hHCAL_L1_energy->GetXaxis()->SetTitle("ieta"); hHCAL_L1_energy->GetYaxis()->SetTitle("iphi");
    hHCAL_L2_energy->GetXaxis()->SetTitle("ieta"); hHCAL_L2_energy->GetYaxis()->SetTitle("iphi");
    hHCAL_L3_energy->GetXaxis()->SetTitle("ieta"); hHCAL_L3_energy->GetYaxis()->SetTitle("iphi");
    hHCAL_L4_energy->GetXaxis()->SetTitle("ieta"); hHCAL_L4_energy->GetYaxis()->SetTitle("iphi");

    c1->cd(); c1->SetFillColor(18);
    TText CanvasTitle(.01, .965, "HCAL Energy"); CanvasTitle.SetTextSize(0.035); CanvasTitle.Draw();
    TLine topLine(.01, .955, .99, .955); topLine.SetLineWidth(1); topLine.SetLineColor(kBlack); topLine.SetLineStyle(1); topLine.Draw();

    TCanvas ctemp; ctemp.cd(); ctemp.SetLogz(useLogZ);
    hHCAL_L1_energy->Draw("COLZ");
    ctemp.Update();
    TPaletteAxis *palette = (TPaletteAxis*)hHCAL_L1_energy->GetListOfFunctions()->FindObject("palette");
    hHCAL_L1_energy->Draw("COL");
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

    c1_11->cd();  
    TLatex c11Title(0.05,0.94,"Layer 1"); c11Title.SetTextSize(0.05); c11Title.SetNDC(); c11Title.Draw();
    c1_11->Range(-6.5,-220,6.5,220);
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
		//-----Draw the box----//
		Float_t CurrentValue = hHCAL_L1_energy->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_L1_energy->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_L1_energy->GetMinimum(0.0);
		Float_t Max = hHCAL_L1_energy->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		if (CurrentValue == 0.0) theColor = 0;
		DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    
    //---Layer 2
    c1_12->cd();  
    TLatex c12Title(0.05,0.94,"Layer 2"); c12Title.SetTextSize(0.05); c12Title.SetNDC(); c12Title.Draw();
    c1_12->Range(-6.5,-220,6.5,220);
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
		//-----Draw the box----//
		Float_t CurrentValue = hHCAL_L2_energy->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_L2_energy->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_L2_energy->GetMinimum(0.0);
		Float_t Max = hHCAL_L2_energy->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		if (CurrentValue == 0.0) theColor = 0;
		DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    
    //---Layer 3
    c1_21->cd();  
    TLatex c21Title(0.05,0.94,"Layer 3"); c21Title.SetTextSize(0.05); c21Title.SetNDC(); c21Title.Draw();
    c1_21->Range(-6.5,-220,6.5,220);
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
		//-----Draw the box----//
		Float_t CurrentValue = hHCAL_L3_energy->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_L3_energy->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_L3_energy->GetMinimum(0.0);
		Float_t Max = hHCAL_L3_energy->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		if (CurrentValue == 0.0) theColor = 0;
		if (fabs(eta)<3 && fabs(eta)>1.305)
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    
    //---Layer 4
    c1_22->cd();  
    TLatex c22Title(0.05,0.94,"Layer 4"); c22Title.SetTextSize(0.05); c22Title.SetNDC(); c22Title.Draw();
    c1_22->Range(-6.5,-220,6.5,220);
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
		//-----Draw the box----//
		Float_t CurrentValue = hHCAL_L4_energy->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_L4_energy->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_L4_energy->GetMinimum(0.0);
		Float_t Max = hHCAL_L4_energy->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		if (CurrentValue == 0.0) theColor = 0;
		if (fabs(eta)<1.305)
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    c1->Print("HCALRecHits_Energy.eps");
    c1_11->Clear(); c1_12->Clear(); c1_21->Clear(); c1_22->Clear(); c1_spec->Clear();
  }
  
  //---------------Make HCAL Occupancy plots------------//
  {
    int useLogZ = true;
    // For a common z-scale, get the maximum energy
    Float_t Energy_Max = TMath::Max( TMath::Max(hHCAL_L1_Occ->GetMaximum(),hHCAL_L2_Occ->GetMaximum()),
				     TMath::Max(hHCAL_L3_Occ->GetMaximum(),hHCAL_L4_Occ->GetMaximum()) );
    Float_t Energy_Min = TMath::Min( TMath::Min(hHCAL_L1_Occ->GetMinimum(),hHCAL_L2_Occ->GetMinimum()),
				     TMath::Min(hHCAL_L3_Occ->GetMinimum(),hHCAL_L4_Occ->GetMinimum()) );
    // if using LogZ option, we need to correctly set the minimum of the palette 
    if (useLogZ)
      {
	Energy_Min =  TMath::Min( TMath::Min(hHCAL_L1_Occ->GetMinimum(0.0),hHCAL_L2_Occ->GetMinimum(0.0)),
				  TMath::Min(hHCAL_L3_Occ->GetMinimum(0.0),hHCAL_L4_Occ->GetMinimum(0.0)) );
	if (Energy_Min == 0.0) Energy_Min = 1E-1;
      }
    hHCAL_L1_Occ->SetMinimum(Energy_Min); hHCAL_L1_Occ->SetMaximum(Energy_Max);
    hHCAL_L2_Occ->SetMinimum(Energy_Min); hHCAL_L2_Occ->SetMaximum(Energy_Max);
    hHCAL_L3_Occ->SetMinimum(Energy_Min); hHCAL_L3_Occ->SetMaximum(Energy_Max);
    hHCAL_L4_Occ->SetMinimum(Energy_Min); hHCAL_L4_Occ->SetMaximum(Energy_Max);
    hHCAL_L1_Occ->SetStats(0);   hHCAL_L1_Occ->SetContour(50);
    hHCAL_L2_Occ->SetStats(0);   hHCAL_L2_Occ->SetContour(50);
    hHCAL_L3_Occ->SetStats(0);   hHCAL_L3_Occ->SetContour(50);
    hHCAL_L4_Occ->SetStats(0);   hHCAL_L4_Occ->SetContour(50);
    hHCAL_L1_Occ->GetXaxis()->SetTitle("ieta"); hHCAL_L1_Occ->GetYaxis()->SetTitle("iphi");
    hHCAL_L2_Occ->GetXaxis()->SetTitle("ieta"); hHCAL_L2_Occ->GetYaxis()->SetTitle("iphi");
    hHCAL_L3_Occ->GetXaxis()->SetTitle("ieta"); hHCAL_L3_Occ->GetYaxis()->SetTitle("iphi");
    hHCAL_L4_Occ->GetXaxis()->SetTitle("ieta"); hHCAL_L4_Occ->GetYaxis()->SetTitle("iphi");


    c1->cd(); c1->SetFillColor(18);
    TText CanvasTitle(.01, .965, "HCAL Energy"); CanvasTitle.SetTextSize(0.035); CanvasTitle.Draw();
    TLine topLine(.01, .955, .99, .955); topLine.SetLineWidth(1); topLine.SetLineColor(kBlack); topLine.SetLineStyle(1); topLine.Draw();

    TCanvas ctemp; ctemp.cd(); ctemp.SetLogz(useLogZ);
    hHCAL_L1_Occ->Draw("COLZ");
    ctemp.Update();
    TPaletteAxis *palette = (TPaletteAxis*)hHCAL_L1_Occ->GetListOfFunctions()->FindObject("palette");
    hHCAL_L1_Occ->Draw("COL");
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

    c1_11->cd();  
    TLatex c11Title(0.05,0.94,"Layer 1"); c11Title.SetTextSize(0.05); c11Title.SetNDC(); c11Title.Draw();
    c1_11->Range(-6.5,-220,6.5,220);
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
		//-----Draw the box----//
		Float_t CurrentValue = hHCAL_L1_Occ->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_L1_Occ->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_L1_Occ->GetMinimum(0.0);
		Float_t Max = hHCAL_L1_Occ->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		if (CurrentValue == 0.0) theColor = 0;
		DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    
    //---Layer 2
    c1_12->cd();  
    TLatex c12Title(0.05,0.94,"Layer 2"); c12Title.SetTextSize(0.05); c12Title.SetNDC(); c12Title.Draw();
    c1_12->Range(-6.5,-220,6.5,220);
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
		//-----Draw the box----//
		Float_t CurrentValue = hHCAL_L2_Occ->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_L2_Occ->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_L2_Occ->GetMinimum(0.0);
		Float_t Max = hHCAL_L2_Occ->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		if (CurrentValue == 0.0) theColor = 0;
		DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    //---Layer 3
    c1_21->cd();  
    TLatex c21Title(0.05,0.94,"Layer 3"); c21Title.SetTextSize(0.05); c21Title.SetNDC(); c21Title.Draw();
    c1_21->Range(-6.5,-220,6.5,220);
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
		//-----Draw the box----//
		Float_t CurrentValue = hHCAL_L3_Occ->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_L3_Occ->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_L3_Occ->GetMinimum(0.0);
		Float_t Max = hHCAL_L3_Occ->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		if (CurrentValue == 0.0) theColor = 0;
		if (fabs(eta)<3 && fabs(eta)>1.305)
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    
    //---Layer 4
    c1_22->cd();  
    TLatex c22Title(0.05,0.94,"Layer 4"); c22Title.SetTextSize(0.05); c22Title.SetNDC(); c22Title.Draw();
    c1_22->Range(-6.5,-220,6.5,220);
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
		//-----Draw the box----//
		Float_t CurrentValue = hHCAL_L4_Occ->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_L4_Occ->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_L4_Occ->GetMinimum(0.0);
		Float_t Max = hHCAL_L4_Occ->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		if (CurrentValue == 0.0) theColor = 0;
		if (fabs(eta)<1.305)
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    c1->Print("HCALRecHits_Occupancy.eps");
  }


  // Make Occupancy over Eta-Rings plots
  {
    Int_t userLogZ = false;
    //---------------------Make Canvas-------------------------------------//
    TCanvas *c2 = new TCanvas("c2","c2",1200,800); 
    TPad *c2_11  = new TPad("c2_11","c2_11",0.01,0.475,0.495,0.94); c2_11->SetGridy(1); c2_11->SetLogy(useLogZ ); c2_11->Draw(); 
    TPad *c2_12  = new TPad("c2_12","c2_12",0.505,0.475,0.99,0.94); c2_12->SetGridy(1); c2_12->SetLogy(useLogZ );c2_12->Draw(); 
    TPad *c2_21  = new TPad("c2_21","c2_21",0.01,0.01,0.495,0.465); c2_21->SetGridy(1); c2_21->SetLogy(useLogZ );c2_21->Draw(); 
    TPad *c2_22  = new TPad("c2_22","c2_22",0.505,0.01,0.99,0.465); c2_22->SetGridy(1); c2_22->SetLogy(useLogZ );c2_22->Draw(); 
    
    c2->cd();
    TLatex CanvasTitle_(.01, .95, "CaloTower #eta-Ring Occupancy");
    CanvasTitle_.Draw();  
    
    TH1F *hACOcc_L1_ietaRing = new TH1F("hACOcc_L1_ietaRing", "Avg. Cell Occupancy vs i#eta", 83,-41,42);
    TH1F *hACOcc_L2_ietaRing = new TH1F("hACOcc_L2_ietaRing", "Avg. Cell Occupancy vs i#eta", 83,-41,42);
    TH1F *hACOcc_L3_ietaRing = new TH1F("hACOcc_L3_ietaRing", "Avg. Cell Occupancy vs i#eta", 83,-41,42);
    TH1F *hACOcc_L4_ietaRing = new TH1F("hACOcc_L4_ietaRing", "Avg. Cell Occupancy vs i#eta", 83,-41,42);

    TH1F *hOcc_L1_ietaRing = new TH1F("hOcc_L1_ietaRing", "#eta-Ring Occupancy vs i#eta", 83,-41,42);
    TH1F *hOcc_L2_ietaRing = new TH1F("hOcc_L2_ietaRing", "#eta-Ring Occupancy vs i#eta", 83,-41,42);
    TH1F *hOcc_L3_ietaRing = new TH1F("hOcc_L3_ietaRing", "#eta-Ring Occupancy vs i#eta", 83,-41,42);
    TH1F *hOcc_L4_ietaRing = new TH1F("hOcc_L4_ietaRing", "#eta-Ring Occupancy vs i#eta", 83,-41,42);

    Float_t EtaBins[83];  EtaBins[82] = 5.191; 
  
    double Nietabins = hTowerGeom_eta->GetNbinsX();
    double Niphibins = hTowerGeom_eta->GetNbinsY();
    TBox *boxColor[90][90], *boxLine[90][90];
    for (int ieta=1; ieta<=Nietabins; ieta++)
      if (ieta!=42) // ieta = 0 
	{
	  TH1F *hTempL1 = new TH1F("hTempL1","",20000,0,200);
	  TH1F *hTempL2 = new TH1F("hTempL2","",20000,0,200);
	  TH1F *hTempL3 = new TH1F("hTempL3","",20000,0,200);
	  TH1F *hTempL4 = new TH1F("hTempL4","",20000,0,200);
	  Float_t TotalOccL1=0.0;
	  Float_t TotalOccL2=0.0;
	  Float_t TotalOccL3=0.0;
	  Float_t TotalOccL4=0.0;
	  for (int iphi=1; iphi<=Niphibins; iphi++)
	    {
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
		Float_t CurrentValueL1 = hHCAL_L1_Occ->GetBinContent(ieta, iphi);
		Float_t CurrentValueL2 = hHCAL_L2_Occ->GetBinContent(ieta, iphi);
		Float_t CurrentValueL3 = hHCAL_L3_Occ->GetBinContent(ieta, iphi);
		Float_t CurrentValueL4 = hHCAL_L4_Occ->GetBinContent(ieta, iphi);
		TotalOccL1+=CurrentValueL1;
		TotalOccL2+=CurrentValueL2;
		TotalOccL3+=CurrentValueL3;
		TotalOccL4+=CurrentValueL4;
		hTempL1->Fill(CurrentValueL1);
		hTempL2->Fill(CurrentValueL2);
		hTempL3->Fill(CurrentValueL3);
		hTempL4->Fill(CurrentValueL4);
	      }
	    } // iphi loop
	  hOcc_L1_ietaRing->SetBinContent(ieta, TotalOccL1);
	  hOcc_L2_ietaRing->SetBinContent(ieta, TotalOccL2);
	  hOcc_L3_ietaRing->SetBinContent(ieta, TotalOccL3);
	  hOcc_L4_ietaRing->SetBinContent(ieta, TotalOccL4);
	  
	  hACOcc_L1_ietaRing->SetBinContent(ieta, hTempL1->GetMean());
	  hACOcc_L1_ietaRing->SetBinError(ieta, hTempL1->GetRMS());
	  hACOcc_L2_ietaRing->SetBinContent(ieta, hTempL2->GetMean());
	  hACOcc_L2_ietaRing->SetBinError(ieta, hTempL2->GetRMS());
	  hACOcc_L3_ietaRing->SetBinContent(ieta, hTempL3->GetMean());
	  hACOcc_L3_ietaRing->SetBinError(ieta, hTempL3->GetRMS());
	  hACOcc_L4_ietaRing->SetBinContent(ieta, hTempL4->GetMean());
	  hACOcc_L4_ietaRing->SetBinError(ieta, hTempL4->GetRMS());
	  delete hTempL1;
	  delete hTempL2;
	  delete hTempL3;
	  delete hTempL4;	
	}
    TH1F *hOcc_L1_etaRing = new TH1F("hOcc_L1_etaRing", "Layer-1: #eta-Ring Occupancy vs #eta", 82, EtaBins);
    hOcc_L1_etaRing->GetXaxis()->SetTitle("#eta");
    hOcc_L1_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hOcc_L1_etaRing->GetYaxis()->SetTitle("Occupancy (%)");
    TH1F *hOcc_L2_etaRing = new TH1F("hOcc_L2_etaRing", "Layer-2: #eta-Ring Occupancy vs #eta", 82, EtaBins);
    hOcc_L2_etaRing->GetXaxis()->SetTitle("#eta");
    hOcc_L2_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hOcc_L2_etaRing->GetYaxis()->SetTitle("Occupancy (%)");
    TH1F *hOcc_L3_etaRing = new TH1F("hOcc_L3_etaRing", "Layer-3:  #eta-Ring Occupancy vs #eta", 82, EtaBins);
    hOcc_L3_etaRing->GetXaxis()->SetTitle("#eta");
    hOcc_L3_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hOcc_L3_etaRing->GetYaxis()->SetTitle("Occupancy (%)");
    TH1F *hOcc_L4_etaRing = new TH1F("hOcc_L4_etaRing", "Layer-4:  #eta-Ring Occupancy vs #eta", 82, EtaBins);
    hOcc_L4_etaRing->GetXaxis()->SetTitle("#eta");
    hOcc_L4_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hOcc_L4_etaRing->GetYaxis()->SetTitle("Occupancy (%)");

    TH1F *hdOccdEta_L1_etaRing = new TH1F("hdOccdEta_L1_etaRing", "Layer-1 #frac{dOcc}{d#eta} vs #eta", 82, EtaBins);
    hdOccdEta_L1_etaRing->GetXaxis()->SetTitle("#eta");
    hdOccdEta_L1_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hdOccdEta_L1_etaRing->GetYaxis()->SetTitle("#frac{dOcc(%)}{d#eta}");
    TH1F *hdOccdEta_L2_etaRing = new TH1F("hdOccdEta_L2_etaRing", "Layer-2 #frac{dOcc}{d#eta} vs #eta", 82, EtaBins);
    hdOccdEta_L2_etaRing->GetXaxis()->SetTitle("#eta");
    hdOccdEta_L2_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hdOccdEta_L2_etaRing->GetYaxis()->SetTitle("#frac{dOcc(%)}{d#eta}");
    TH1F *hdOccdEta_L3_etaRing = new TH1F("hdOccdEta_L3_etaRing", "Layer-3 #frac{dOcc}{d#eta} vs #eta", 82, EtaBins);
    hdOccdEta_L3_etaRing->GetXaxis()->SetTitle("#eta");
    hdOccdEta_L3_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hdOccdEta_L3_etaRing->GetYaxis()->SetTitle("#frac{dOcc(%)}{d#eta}");
    TH1F *hdOccdEta_L4_etaRing = new TH1F("hdOccdEta_L4_etaRing", "Layer-4 #frac{dOcc}{d#eta} vs #eta", 82, EtaBins);
    hdOccdEta_L4_etaRing->GetXaxis()->SetTitle("#eta");
    hdOccdEta_L4_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hdOccdEta_L4_etaRing->GetYaxis()->SetTitle("#frac{dOcc(%)}{d#eta}");

    TH1F *hACOcc_L1_etaRing = new TH1F("hACOcc_L1_etaRing", "Layer-1 Occupancy vs #eta", 82, EtaBins);
    hACOcc_L1_etaRing->GetXaxis()->SetTitle("#eta");
    hACOcc_L1_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hACOcc_L1_etaRing->GetYaxis()->SetTitle("Occupancy (%)");
    TH1F *hACOcc_L2_etaRing = new TH1F("hACOcc_L2_etaRing", "Layer-2 Occupancy vs #eta", 82, EtaBins);
    hACOcc_L2_etaRing->GetXaxis()->SetTitle("#eta");
    hACOcc_L2_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hACOcc_L2_etaRing->GetYaxis()->SetTitle("Occupancy (%)");
    TH1F *hACOcc_L3_etaRing = new TH1F("hACOcc_L3_etaRing", "Layer-3 Occupancy vs #eta", 82, EtaBins);
    hACOcc_L3_etaRing->GetXaxis()->SetTitle("#eta");
    hACOcc_L3_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hACOcc_L3_etaRing->GetYaxis()->SetTitle("Occupancy (%)");
    TH1F *hACOcc_L4_etaRing = new TH1F("hACOcc_L4_etaRing", "Layer-4 Occupancy vs #eta", 82, EtaBins);
    hACOcc_L4_etaRing->GetXaxis()->SetTitle("#eta");
    hACOcc_L4_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hACOcc_L4_etaRing->GetYaxis()->SetTitle("Occupancy (%)");

    TH1F *hdACOccdEta_L1_etaRing = new TH1F("hdACOccdEta_L1_etaRing", "Layer-1: #frac{<#DeltaOcc(%)>}{#Delta#eta#Delta#phi} vs #eta", 82, EtaBins);
    hdACOccdEta_L1_etaRing->GetXaxis()->SetTitle("#eta");
    hdACOccdEta_L1_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hdACOccdEta_L1_etaRing->GetYaxis()->SetTitle("#frac{<#DeltaOcc(%)>}{#Delta#eta#Delta#phi}");
    TH1F *hdACOccdEta_L2_etaRing = new TH1F("hdACOccdEta_L2_etaRing", "Layer-2: #frac{<#DeltaOcc(%)>}{#Delta#eta#Delta#phi} vs #eta", 82, EtaBins);
    hdACOccdEta_L2_etaRing->GetXaxis()->SetTitle("#eta");
    hdACOccdEta_L2_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hdACOccdEta_L2_etaRing->GetYaxis()->SetTitle("#frac{<#DeltaOcc(%)>}{#Delta#eta#Delta#phi}");
    TH1F *hdACOccdEta_L3_etaRing = new TH1F("hdACOccdEta_L3_etaRing", "Layer-3: #frac{<#DeltaOcc(%)>}{#Delta#eta#Delta#phi} vs #eta", 82, EtaBins);
    hdACOccdEta_L3_etaRing->GetXaxis()->SetTitle("#eta");
    hdACOccdEta_L3_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hdACOccdEta_L3_etaRing->GetYaxis()->SetTitle("#frac{<#DeltaOcc(%)>}{#Delta#eta#Delta#phi}");
    TH1F *hdACOccdEta_L4_etaRing = new TH1F("hdACOccdEta_L4_etaRing", "Layer-4: #frac{<#DeltaOcc(%)>}{#Delta#eta#Delta#phi} vs #eta", 82, EtaBins);
    hdACOccdEta_L4_etaRing->GetXaxis()->SetTitle("#eta");
    hdACOccdEta_L4_etaRing->GetYaxis()->SetTitleOffset(1.3);
    hdACOccdEta_L4_etaRing->GetYaxis()->SetTitle("#frac{<#DeltaOcc(%)>}{#Delta#eta#Delta#phi}");

    for (int i=1; i<=hOcc_L1_etaRing->GetNbinsX()+1; i++)
      {
	Int_t bin=0;
	if (i<42) bin = i;
	if (i>42) bin = i-1;
	if (i!=42)
	  {
	    Float_t deta = hTowerGeom_deta->GetBinContent(i);
	    Float_t dphi = (pi/180.0)*hTowerGeom_dphi->GetBinContent(i);
	    Float_t darea = deta*dphi;
	    hOcc_L1_etaRing->SetBinContent(bin, hOcc_L1_ietaRing->GetBinContent(i));
	    hOcc_L1_etaRing->SetBinError(bin, hOcc_L1_ietaRing->GetBinError(i));
	    hOcc_L2_etaRing->SetBinContent(bin, hOcc_L2_ietaRing->GetBinContent(i));
	    hOcc_L2_etaRing->SetBinError(bin, hOcc_L2_ietaRing->GetBinError(i));
	    hOcc_L3_etaRing->SetBinContent(bin, hOcc_L3_ietaRing->GetBinContent(i));
	    hOcc_L3_etaRing->SetBinError(bin, hOcc_L3_ietaRing->GetBinError(i));
	    hOcc_L4_etaRing->SetBinContent(bin, hOcc_L4_ietaRing->GetBinContent(i));
	    hOcc_L4_etaRing->SetBinError(bin, hOcc_L4_ietaRing->GetBinError(i));

	    hACOcc_L1_etaRing->SetBinContent(bin, hACOcc_L1_ietaRing->GetBinContent(i));
	    hACOcc_L1_etaRing->SetBinError(bin, hACOcc_L1_ietaRing->GetBinError(i));
	    hACOcc_L2_etaRing->SetBinContent(bin, hACOcc_L2_ietaRing->GetBinContent(i));
	    hACOcc_L2_etaRing->SetBinError(bin, hACOcc_L2_ietaRing->GetBinError(i));
	    hACOcc_L3_etaRing->SetBinContent(bin, hACOcc_L3_ietaRing->GetBinContent(i));
	    hACOcc_L3_etaRing->SetBinError(bin, hACOcc_L3_ietaRing->GetBinError(i));
	    hACOcc_L4_etaRing->SetBinContent(bin, hACOcc_L4_ietaRing->GetBinContent(i));
	    hACOcc_L4_etaRing->SetBinError(bin, hACOcc_L4_ietaRing->GetBinError(i));

	    if (deta>0)
	      {
		hdOccdEta_L1_etaRing->SetBinContent(bin, hOcc_L1_ietaRing->GetBinContent(i)/darea);
		hdOccdEta_L1_etaRing->SetBinError(bin, hOcc_L1_ietaRing->GetBinError(i)/darea);
		hdOccdEta_L2_etaRing->SetBinContent(bin, hOcc_L2_ietaRing->GetBinContent(i)/darea);
		hdOccdEta_L2_etaRing->SetBinError(bin, hOcc_L2_ietaRing->GetBinError(i)/darea);
		hdOccdEta_L3_etaRing->SetBinContent(bin, hOcc_L3_ietaRing->GetBinContent(i)/darea);
		hdOccdEta_L3_etaRing->SetBinError(bin, hOcc_L3_ietaRing->GetBinError(i)/darea);
		hdOccdEta_L4_etaRing->SetBinContent(bin, hOcc_L4_ietaRing->GetBinContent(i)/darea);
		hdOccdEta_L4_etaRing->SetBinError(bin, hOcc_L4_ietaRing->GetBinError(i)/darea);

		hdACOccdEta_L1_etaRing->SetBinContent(bin, hACOcc_L1_ietaRing->GetBinContent(i)/darea);
		hdACOccdEta_L1_etaRing->SetBinError(bin, hACOcc_L1_ietaRing->GetBinError(i)/darea);
		hdACOccdEta_L2_etaRing->SetBinContent(bin, hACOcc_L2_ietaRing->GetBinContent(i)/darea);
		hdACOccdEta_L2_etaRing->SetBinError(bin, hACOcc_L2_ietaRing->GetBinError(i)/darea);
		hdACOccdEta_L3_etaRing->SetBinContent(bin, hACOcc_L3_ietaRing->GetBinContent(i)/darea);
		hdACOccdEta_L3_etaRing->SetBinError(bin, hACOcc_L3_ietaRing->GetBinError(i)/darea);
		hdACOccdEta_L4_etaRing->SetBinContent(bin, hACOcc_L4_ietaRing->GetBinContent(i)/darea);
		hdACOccdEta_L4_etaRing->SetBinError(bin, hACOcc_L4_ietaRing->GetBinError(i)/darea);
	      }
	  }
      }

    TFile fOut("HCALRecHitPlots.root","RECREATE");
    
    c2_11->cd();
    hOcc_L1_etaRing->SetStats(0); hOcc_L1_etaRing->Draw();
    c2_12->cd();
    hOcc_L2_etaRing->SetStats(0); hOcc_L2_etaRing->Draw();
    c2_21->cd();
    hOcc_L3_etaRing->SetStats(0); hOcc_L3_etaRing->Draw();
    c2_22->cd();
    hOcc_L4_etaRing->SetStats(0); hOcc_L4_etaRing->Draw();
    c2->Print("HCALRecHits_EtaRing_Occupancy.eps");
    c2_11->Clear(); c2_12->Clear(); c2_21->Clear(); c2_22->Clear();

    c2_11->cd();
    hdACOccdEta_L1_etaRing->SetStats(0); hdOccdEta_L1_etaRing->Draw();
    c2_12->cd();
    hdOccdEta_L2_etaRing->SetStats(0); hdOccdEta_L2_etaRing->Draw();
    c2_21->cd();
    hdOccdEta_L3_etaRing->SetStats(0); hdOccdEta_L3_etaRing->Draw();
    c2_22->cd();
    hdOccdEta_L4_etaRing->SetStats(0); hdOccdEta_L4_etaRing->Draw();
    c2->Print("HCALRecHits_EtaRing_dOccdEta.eps");
    c2_11->Clear(); c2_12->Clear(); c2_21->Clear(); c2_22->Clear();

    c2_11->cd();
    hACOcc_L1_etaRing->SetStats(0); hACOcc_L1_etaRing->Draw();
    c2_12->cd();
    hACOcc_L2_etaRing->SetStats(0); hACOcc_L2_etaRing->Draw();
    c2_21->cd();
    hACOcc_L3_etaRing->SetStats(0); hACOcc_L3_etaRing->Draw();
    c2_22->cd();
    hACOcc_L4_etaRing->SetStats(0); hACOcc_L4_etaRing->Draw();
    c2->Print("HCALRecHits_EtaRing_Avg_Cell_Occupancy.eps");
    c2_11->Clear(); c2_12->Clear(); c2_21->Clear(); c2_22->Clear();

    c2_11->cd();
    hdACOccdEta_L1_etaRing->SetStats(0); hdACOccdEta_L1_etaRing->Draw();
    c2_12->cd();
    hdACOccdEta_L2_etaRing->SetStats(0); hdACOccdEta_L2_etaRing->Draw();
    c2_21->cd();
    hdACOccdEta_L3_etaRing->SetStats(0); hdACOccdEta_L3_etaRing->Draw();
    c2_22->cd();
    hdACOccdEta_L4_etaRing->SetStats(0); hdACOccdEta_L4_etaRing->Draw();
    c2->Print("HCALRecHits_EtaRing_Avg_Cell_dOccdEta.eps");
    c2_11->Clear(); c2_12->Clear(); c2_21->Clear(); c2_22->Clear();

    hdACOccdEta_L1_etaRing->Write();
    hdACOccdEta_L2_etaRing->Write();
    hdACOccdEta_L3_etaRing->Write();
    hdACOccdEta_L4_etaRing->Write();
    fOut.Close();
  }

 

}
