void SetUp()
{
  gROOT->Reset();
  gStyle->SetPalette(1);
  gStyle->SetNumberContours(45);
  int colPalette[ 45 ];
  for (int i=0; i< 45; i++) {
    int icol = gStyle->GetColorPalette(i+5);   colPalette[ i ] = icol;
  }
  gStyle->SetPalette(45, colPalette);
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

void plotHCALminmaxavgEnergy(){
  SetUp();
  double pi = TMath::Pi();

  int DrawLogical = 0; // 0 = eta,phi , 1 = ieta, iphi
  int DrawMinMaxAvg = 2; // 1 = min , 2 = max, 3 = Avg

  // Load geometry Histograms
  TFile file("METTester_data.root");
  file.cd("DQMData/METTask/HCAL/geometry"); 
  TH2F *hTowerGeom_eta = METTask_HCAL_ieta_iphi_etaMap;
  TH2F *hTowerGeom_phi = METTask_HCAL_ieta_iphi_phiMap;
  TH1F *hTowerGeom_deta = METTask_HCAL_ieta_detaMap;
  TH1F *hTowerGeom_dphi = METTask_HCAL_ieta_dphiMap;
  // Load HCALRecHit Histograms
  file.cd("DQMData/METTask/HCAL/data"); 
  int Nevents = METTask_HCAL_Nevents->GetEntries();

  switch (DrawMinMaxAvg)
    {
    case 1:
      TH2F *hHCAL_D1_energy = METTask_HCAL_D1_Minenergy_ieta_iphi;
      TH2F *hHCAL_D2_energy = METTask_HCAL_D2_Minenergy_ieta_iphi;
      TH2F *hHCAL_D3_energy = METTask_HCAL_D3_Minenergy_ieta_iphi;
      TH2F *hHCAL_D4_energy = METTask_HCAL_D4_Minenergy_ieta_iphi;

      int colPalette[ 45 ];
      for (int i=0; i< 45; i++) {
	int icol = gStyle->GetColorPalette(44-i);   colPalette[ i ] = icol;
      }
      gStyle->SetPalette(45, colPalette);
      break;
    case 2:
      TH2F *hHCAL_D1_energy = METTask_HCAL_D1_Maxenergy_ieta_iphi;
      TH2F *hHCAL_D2_energy = METTask_HCAL_D2_Maxenergy_ieta_iphi;
      TH2F *hHCAL_D3_energy = METTask_HCAL_D3_Maxenergy_ieta_iphi;
      TH2F *hHCAL_D4_energy = METTask_HCAL_D4_Maxenergy_ieta_iphi;
      break;
    case 3:
      TH2F *hHCAL_D1_energy = METTask_HCAL_D1_energy_ieta_iphi; hHCAL_D1_energy->Scale( 1.0/(Double_t) Nevents);
      TH2F *hHCAL_D2_energy = METTask_HCAL_D2_energy_ieta_iphi; hHCAL_D2_energy->Scale( 1.0/(Double_t) Nevents);
      TH2F *hHCAL_D3_energy = METTask_HCAL_D3_energy_ieta_iphi; hHCAL_D3_energy->Scale( 1.0/(Double_t) Nevents);
      TH2F *hHCAL_D4_energy = METTask_HCAL_D4_energy_ieta_iphi; hHCAL_D4_energy->Scale( 1.0/(Double_t) Nevents);
      break;
    }


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
  if (!DrawLogical)
  {
    int useLogZ = false;
    // For a common z-scale, get the maximum energy
    Float_t Energy_Max = TMath::Max( TMath::Max(hHCAL_D1_energy->GetMaximum(),hHCAL_D2_energy->GetMaximum()),
				     TMath::Max(hHCAL_D3_energy->GetMaximum(),hHCAL_D4_energy->GetMaximum()) );
    Float_t Energy_Min = TMath::Min( TMath::Min(hHCAL_D1_energy->GetMinimum(),hHCAL_D2_energy->GetMinimum()),
				     TMath::Min(hHCAL_D3_energy->GetMinimum(),hHCAL_D4_energy->GetMinimum()) );
    // if using LogZ option, we need to correctly set the minimum of the palette 
    if (useLogZ)
      {
	Energy_Min =  TMath::Min( TMath::Min(hHCAL_D1_energy->GetMinimum(0.0),hHCAL_D2_energy->GetMinimum(0.0)),
				  TMath::Min(hHCAL_D3_energy->GetMinimum(0.0),hHCAL_D4_energy->GetMinimum(0.0)) );
	if (Energy_Min == 0.0) Energy_Min = 1E-1;
      }
    hHCAL_D1_energy->SetMinimum(Energy_Min); hHCAL_D1_energy->SetMaximum(Energy_Max);
    hHCAL_D2_energy->SetMinimum(Energy_Min); hHCAL_D2_energy->SetMaximum(Energy_Max);
    hHCAL_D3_energy->SetMinimum(Energy_Min); hHCAL_D3_energy->SetMaximum(Energy_Max);
    hHCAL_D4_energy->SetMinimum(Energy_Min); hHCAL_D4_energy->SetMaximum(Energy_Max);
    hHCAL_D1_energy->SetStats(0);   hHCAL_D1_energy->SetContour(50);
    hHCAL_D2_energy->SetStats(0);   hHCAL_D2_energy->SetContour(50);
    hHCAL_D3_energy->SetStats(0);   hHCAL_D3_energy->SetContour(50);
    hHCAL_D4_energy->SetStats(0);   hHCAL_D4_energy->SetContour(50);
    hHCAL_D1_energy->GetXaxis()->SetTitle("ieta"); hHCAL_D1_energy->GetYaxis()->SetTitle("iphi");
    hHCAL_D2_energy->GetXaxis()->SetTitle("ieta"); hHCAL_D2_energy->GetYaxis()->SetTitle("iphi");
    hHCAL_D3_energy->GetXaxis()->SetTitle("ieta"); hHCAL_D3_energy->GetYaxis()->SetTitle("iphi");
    hHCAL_D4_energy->GetXaxis()->SetTitle("ieta"); hHCAL_D4_energy->GetYaxis()->SetTitle("iphi");

    c1->cd(); c1->SetFillColor(18);
    TText CanvasTitle(.01, .965, "HCALRecHit Energy"); CanvasTitle.SetTextSize(0.035); CanvasTitle.Draw();
    TLine topLine(.01, .955, .99, .955); topLine.SetLineWidth(1); topLine.SetLineColor(kBlack); topLine.SetLineStyle(1); topLine.Draw();

    TCanvas ctemp; ctemp.cd(); ctemp.SetLogz(useLogZ);
    hHCAL_D1_energy->Draw("COLZ");
    ctemp.Update();
    TPaletteAxis *palette = (TPaletteAxis*)hHCAL_D1_energy->GetListOfFunctions()->FindObject("palette");
    //   hHCAL_D1_energy->Draw("COLZ");
    // ctemp.Update();
    c1_spec->cd(); c1_spec->SetLogz(useLogZ);
    TText PaletteLabel(0.15,0.8,"Energy (GeV)");
    PaletteLabel.SetTextSize(0.15);
    PaletteLabel.SetTextAngle(90);
    PaletteLabel.Draw();

    palette->SetX1NDC(0.25); 
    palette->SetX2NDC(0.55); 
    palette->SetLabelOffset(0.03); 
    palette->SetLabelSize(0.2);
    hHCAL_D1_energy->GetListOfFunctions()->FindObject("palette")->Draw();
      //    palette->DrawClone();
   


    c1_11->cd();  
    TLatex c11Title(0.05,0.94,"Depth 1"); c11Title.SetTextSize(0.05); c11Title.SetNDC(); c11Title.Draw();
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
		Float_t CurrentValue = hHCAL_D1_energy->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_D1_energy->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_D1_energy->GetMinimum(0.0);
		Float_t Max = hHCAL_D1_energy->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		//	if (CurrentValue == 0.0) theColor = 0;
	if ( (ieta<=2 || ieta>=82 ) && (iphi == 35)) 
		{
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, -175, deta, 10, theColor);
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, 175, deta, 10, theColor);
		}
		else
		DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
	
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    c1->Update();

    //---Depth 2
    c1_12->cd();  
    TLatex c12Title(0.05,0.94,"Depth 2"); c12Title.SetTextSize(0.05); c12Title.SetNDC(); c12Title.Draw();
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
		Float_t CurrentValue = hHCAL_D2_energy->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_D2_energy->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_D2_energy->GetMinimum(0.0);
		Float_t Max = hHCAL_D2_energy->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		//if (CurrentValue == 0.0) theColor = 0;
	if ( (ieta<=2 || ieta>=82 ) && (iphi == 35)) 
		{
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, -175, deta, 10, theColor);
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, 175, deta, 10, theColor);
		}
		else
		DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);    
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    
    //---Depth 3
    c1_21->cd();  
    TLatex c21Title(0.05,0.94,"Depth 3"); c21Title.SetTextSize(0.05); c21Title.SetNDC(); c21Title.Draw();
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
		Float_t CurrentValue = hHCAL_D3_energy->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_D3_energy->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_D3_energy->GetMinimum(0.0);
		Float_t Max = hHCAL_D3_energy->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		//if (CurrentValue == 0.0) theColor = 0;
		if (fabs(eta)<3 && fabs(eta)>1.305)
		  {
	if ( (ieta<=2 || ieta>=82 ) && (iphi == 35)) 
		{
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, -175, deta, 10, theColor);
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, 175, deta, 10, theColor);
		}
		else
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);
		  }    
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    
    //---Depth 4
    c1_22->cd();  
    TLatex c22Title(0.05,0.94,"Depth 4"); c22Title.SetTextSize(0.05); c22Title.SetNDC(); c22Title.Draw();
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
		Float_t CurrentValue = hHCAL_D4_energy->GetBinContent(ieta, iphi);
		Float_t CurrentValueL10 = hHCAL_D4_energy->GetBinContent(ieta, iphi);
		Float_t Min = hHCAL_D4_energy->GetMinimum(0.0);
		Float_t Max = hHCAL_D4_energy->GetMaximum();
		if (useLogZ)
		  {
		    if (CurrentValue >= Energy_Min) CurrentValueL10 = TMath::Log10(CurrentValueL10);
		    if (Min >= Energy_Min) Min = TMath::Log10(Min);
		    if (Max >= Energy_Min) Max = TMath::Log10(Max);
		  }
		Int_t theColor = GetColor(Min, Max, CurrentValueL10);
		//	if (CurrentValue == 0.0) theColor = 0;
		if (fabs(eta)<1.305)
		  {
	if ( (ieta<=2 || ieta>=82 ) && (iphi == 35)) 
		{
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, -175, deta, 10, theColor);
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, 175, deta, 10, theColor);
		}
		else
		  DrawBox(boxColor[ieta][iphi], boxLine[ieta][iphi], eta, phi, deta, dphi, theColor);
		  }    
	      }
	}
    xbottom.Draw(); yleft.Draw(); xtop.Draw(); yright.Draw();
    c1->Print("HCALRecHits_Energy.gif");
    c1_11->Clear(); c1_12->Clear(); c1_21->Clear(); c1_22->Clear(); c1_spec->Clear();
  }
  else
    {
      c1->Clear(); c1->Divide(2,2);
      c1->cd(1);
      hHCAL_D1_energy->SetStats(0);
      hHCAL_D1_energy->Draw("COLZ");
      c1->cd(2);
      hHCAL_D2_energy->SetStats(0);
      hHCAL_D2_energy->Draw("COLZ");
      c1->cd(3);
      hHCAL_D3_energy->SetStats(0);
      hHCAL_D3_energy->Draw("COLZ");
      c1->cd(4);
      hHCAL_D4_energy->SetStats(0);
      hHCAL_D4_energy->Draw("COLZ");
      c1->Print("HCALRecHits_Energy-logical.gif");
    }
 

}
