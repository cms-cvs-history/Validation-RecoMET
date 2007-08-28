#! /bin/bash

current_area=`pwd`
echo $current_area

dirlist="ZDimu ZprimeDijets QCD_0-15 QCD_15-20 QCD_20-30 QCD_30-50 QCD_50-80 QCD_80-120 QCD_120-170 QCD_170-230 QCD_230-300 QCD_300-380 QCD_380-470 QCD_470-600 QCD_600-800 QCD_800-1000"

RunPath="metAnalyzer, AnalyzeECAL, AnalyzeHCAL, AnalyzeTowers"
#RunPath="genMETParticles, genMet, metAnalyzer"
echo "Run path = {" $RunPath "}"

mkdir RelVal_data
cd RelVal_data
#========Make MaxEvents file===============#
echo "'untracked PSet maxEvents = {untracked int32 input = -1}'" >> MaxEvents.cfi
#==========================================#
cd $current_area

for i in $dirlist; do

cd RelVal_data
#========Make path file====================#
echo "untracked vstring fileNames = {

}" >> FilePaths-$i.cfi
#==========================================#
cd $current_area

#mkdir $i 
#cd $i
#echo `pwd`

#======Make RunAnalyzers.cfg=================#
echo "process TEST =
{
#  include \"Configuration/Examples/data/DIGI.cff\"
#  include \"RecoMET/METProducers/test/CaloCandidatesFromDigis.cfi\"
#  include \"RecoMET/METProducers/test/CaloCandidatesFromRecHits.cfi\"
  include \"RecoMET/METProducers/data/CaloMET.cfi\"
  include \"RecoMET/Configuration/data/GenMETParticles.cff\"
  include \"RecoMET/METProducers/data/genMet.cfi\"


  service = DaqMonitorROOTBackEnd{ }
  source = PoolSource
  {
      include \"Validation/RecoMET/data/RelVal_data/FilePaths-$i.cfi\"


    untracked uint32 debugVebosity = 10
     untracked bool   debugFlag     = true
  }

 #   include \"Validation/RecoMET/data/RelVal_data/MaxEvents.cfi\"

# Geometry - overkill, used for test/completeness  #
# includes Sim, Digi & Reco files as far
 #            as I can tell.

 #   include \"Geometry/CMSCommonData/data/cmsIdealGeometryXML.cfi\"

    include \"Geometry/CaloEventSetup/test/data/testCaloConfiguration.cfi\"

 # Magnetic field full setup

    include \"MagneticField/Engine/data/volumeBasedMagneticField.cfi\"

 # Calo geometry service model
    include \"Geometry/CaloEventSetup/data/CaloGeometry.cfi\"

 # Ecal TT mapping
    include \"Geometry/CaloEventSetup/data/EcalTrigTowerConstituents.cfi\"


  module AnalyzeTowers = CaloTowerAnalyzer{
       untracked string OutputFile = 'CaloTowerAnalyzer_data.root'
       untracked string GeometryFile = 'CaloTowerAnalyzer_geometry.dat'
       string CaloTowersLabel  = 'caloTowers'
       bool DumpGeometry = false
       bool Debug = false
  }

  module AnalyzeECAL = ECALRecHitAnalyzer{
       untracked string OutputFile = 'ECALRecHitAnalyzer_data.root'
       untracked string GeometryFile = 'ECALRecHitAnalyzer_geometry.dat'
       string ECALRecHitsLabel  = 'ecalRecHit'
       string EERecHitsLabel  = 'EcalRecHitsEE'
       string EBRecHitsLabel  = 'EcalRecHitsEB'
       bool DumpGeometry = false
       bool Debug = false
  }

  module AnalyzeHCAL = HCALRecHitAnalyzer{
       untracked string OutputFile = 'HCALRecHitAnalyzer_data.root'
       untracked string GeometryFile = 'HCALRecHitAnalyzer_geometry.dat'
       string HBHERecHitsLabel  = 'hbhereco'
       string HORecHitsLabel  = 'horeco'
       string HFRecHitsLabel  = 'hfreco'
       bool DumpGeometry = false
       bool Debug = false

  }
  module Dumper = DumpEvent{
       untracked string OutputFile = 'HCALRecHitAnalyzer_data.root'
       string CaloJetsLabel = 'iterativeCone5CaloJets'
       string MuonsLabel = 'globalMuons'
       string ElectronsLabel = 'pixelMatchElectrons'
       string PhotonsLabel = 'photons'
       string CaloMETLabel = 'met'
       string GenMETLabel = 'genMet'
       string EndcapSCLabel = 'correctedIslandEndcapSuperClusters'
       string BarrelSCLabel = 'correctedHybridSuperClusters'

       bool Debug = true
       bool DoJets = true
       bool DoElectrons = true
       bool DoPhotons = true
       bool DoMET = true
       bool DoSCs = true
}

  module metAnalyzer = METTester
  {
     string InputGenMETLabel  = 'genMet'
     string InputCaloMETLabel = 'met'
     untracked string OutputFile = 'METTester_data_$i.root'
  }

  path p = {$RunPath}
  schedule = { p }
}" > RunAnalyzers-$i.cfg
#============================================#
cd $current_area
done
