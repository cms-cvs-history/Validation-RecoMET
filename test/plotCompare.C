{

string label[34];
label[1]  = "DQMData/METTask/METTask_CaloEmEtFraction";
label[2]  = "DQMData/METTask/METTask_CaloEmEtFraction";	  
label[3]  = "DQMData/METTask/METTask_CaloEmEtInEB";		  
label[4]  = "DQMData/METTask/METTask_CaloEmEtInEE";		  
label[5]  = "DQMData/METTask/METTask_CaloEmEtInHF";		  
label[6]  = "DQMData/METTask/METTask_CaloEtFractionHadronic";  
label[7]  = "DQMData/METTask/METTask_CaloEz";		  
label[8]  = "DQMData/METTask/METTask_CaloHadEtInHB";		  
label[9]  = "DQMData/METTask/METTask_CaloHadEtInHE";		  
label[10] = "DQMData/METTask/METTask_CaloHadEtInHF";		  
label[11] = "DQMData/METTask/METTask_CaloHadEtInHO";		  
label[12] = "DQMData/METTask/METTask_CaloMET";		  
label[13] = "DQMData/METTask/METTask_CaloMETPhi";		  
label[14] = "DQMData/METTask/METTask_CaloMETSig";		  
label[15] = "DQMData/METTask/METTask_CaloMEx";		  
label[16] = "DQMData/METTask/METTask_CaloMEy";		  
label[17] = "DQMData/METTask/METTask_CaloMaxEtInEmTowers";	  
label[18] = "DQMData/METTask/METTask_CaloMaxEtInHadTowers";	  
label[19] = "DQMData/METTask/METTask_CaloSumET";		  
label[20] = "DQMData/METTask/METTask_GenAuxiliaryEnergy";	  
label[21] = "DQMData/METTask/METTask_GenEmEnergy";		  
label[22] = "DQMData/METTask/METTask_GenEz";			  
label[23] = "DQMData/METTask/METTask_GenHadEnergy";		  
label[24] = "DQMData/METTask/METTask_GenInvisibleEnergy";	  
label[25] = "DQMData/METTask/METTask_GenMET";		  
label[26] = "DQMData/METTask/METTask_GenMETPhi";		  
label[27] = "DQMData/METTask/METTask_GenMETSig";		  
label[28] = "DQMData/METTask/METTask_GenMEx";		  
label[29] = "DQMData/METTask/METTask_GenMEy";		  
label[30] = "DQMData/METTask/METTask_GenSumET";		  
label[31] = "DQMData/METTask/METTask_METSigmaVsGenSumET";	  //profile histo
label[32] = "DQMData/METTask/METTask_meCaloMETvsCaloSumET";	  //2d histo
label[33] = "DQMData/METTask/METTask_meCaloMExvsCaloSumET";       //2d histo

TFile *file     = new TFile(            "RecoMET-ValHist-_FILE_");
TFile *file_ref = new TFile("../data/ref-RecoMET-ValHist-_FILE_");

TH1F *histogram;
TH1F *histogram_ref;

//file->cd("DQMData/METTask");
//file->ls(); 

for(int i = 1; i <= 30; i++)
{ 
  histogram     = (TH1F*)     file->Get( label[i].c_str() );
  histogram_ref = (TH1F*) file_ref->Get( label[i].c_str() );
  cout << "Result of comparison for " << histogram->GetName() << ": " << histogram->Compare(histogram_ref) << endl; 
}

}
