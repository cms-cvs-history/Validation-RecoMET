{
/*
TFile**         RecoMETValidation.root
 TFile*         RecoMETValidation.root
  TDirectory*           DQMData DQMData
   TDirectory*          METTask METTask
    OBJ: TH1F   METTask_CaloEmEtFraction          METTask_CaloEmEtFraction 	  
    KEY: TH1F   METTask_CaloEmEtFraction;1        METTask_CaloEmEtFraction	  
    KEY: TH1F   METTask_CaloEmEtInEB;1            METTask_CaloEmEtInEB		  
    KEY: TH1F   METTask_CaloEmEtInEE;1            METTask_CaloEmEtInEE		  
    KEY: TH1F   METTask_CaloEmEtInHF;1            METTask_CaloEmEtInHF		  
    KEY: TH1F   METTask_CaloEtFractionHadronic;1  METTask_CaloEtFractionHadronic  
    KEY: TH1F   METTask_CaloEz;1                  METTask_CaloEz		  
    KEY: TH1F   METTask_CaloHadEtInHB;1           METTask_CaloHadEtInHB		  
    KEY: TH1F   METTask_CaloHadEtInHE;1           METTask_CaloHadEtInHE		  
    KEY: TH1F   METTask_CaloHadEtInHF;1           METTask_CaloHadEtInHF		  
    KEY: TH1F   METTask_CaloHadEtInHO;1           METTask_CaloHadEtInHO		  
    KEY: TH1F   METTask_CaloMET;1                 METTask_CaloMET		  
    KEY: TH1F   METTask_CaloMETPhi;1              METTask_CaloMETPhi		  
    KEY: TH1F   METTask_CaloMETSig;1              METTask_CaloMETSig		  
    KEY: TH1F   METTask_CaloMEx;1                 METTask_CaloMEx		  
    KEY: TH1F   METTask_CaloMEy;1                 METTask_CaloMEy		  
    KEY: TH1F   METTask_CaloMaxEtInEmTowers;1     METTask_CaloMaxEtInEmTowers	  
    KEY: TH1F   METTask_CaloMaxEtInHadTowers;1    METTask_CaloMaxEtInHadTowers	  
    KEY: TH1F   METTask_CaloSumET;1               METTask_CaloSumET		  
    KEY: TH1F   METTask_GenAuxiliaryEnergy;1      METTask_GenAuxiliaryEnergy	  
    KEY: TH1F   METTask_GenEmEnergy;1             METTask_GenEmEnergy		  
    KEY: TH1F   METTask_GenEz;1                   METTask_GenEz			  
    KEY: TH1F   METTask_GenHadEnergy;1            METTask_GenHadEnergy		  
    KEY: TH1F   METTask_GenInvisibleEnergy;1      METTask_GenInvisibleEnergy	  
    KEY: TH1F   METTask_GenMET;1                  METTask_GenMET		  
    KEY: TH1F   METTask_GenMETPhi;1               METTask_GenMETPhi		  
    KEY: TH1F   METTask_GenMETSig;1               METTask_GenMETSig		  
    KEY: TH1F   METTask_GenMEx;1                  METTask_GenMEx		  
    KEY: TH1F   METTask_GenMEy;1                  METTask_GenMEy		  
    KEY: TH1F   METTask_GenSumET;1                METTask_GenSumET		  
    KEY: TProfile   METTask_METSigmaVsGenSumET;1  METTask_METSigmaVsGenSumET	  
    KEY: TH2F   METTask_meCaloMETvsCaloSumET;1    METTask_meCaloMETvsCaloSumET	  
    KEY: TH2F   METTask_meCaloMExvsCaloSumET;1    METTask_meCaloMExvsCaloSumET    
   KEY: TDirectory      METTask;1       METTask
  KEY: TDirectory       DQMData;1       DQMData
*/

string label[34];
label[1] = "DQMData/METTask/METTask_CaloEmEtFraction";
label[2] = "DQMData/METTask/METTask_CaloEmEtFraction";	  
label[3] = "DQMData/METTask/METTask_CaloEmEtInEB";		  
label[4] = "DQMData/METTask/METTask_CaloEmEtInEE";		  
label[5] = "DQMData/METTask/METTask_CaloEmEtInHF";		  
label[6] = "DQMData/METTask/METTask_CaloEtFractionHadronic";  
label[7] = "DQMData/METTask/METTask_CaloEz";		  
label[8] = "DQMData/METTask/METTask_CaloHadEtInHB";		  
label[9] = "DQMData/METTask/METTask_CaloHadEtInHE";		  
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

TFile *file = new TFile("RecoMETValidation.root");
TFile *file_ref = new TFile("../data/RecoMETValidation-QCD_0_15-ref.root");

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
