#! /bin/bash

current_area=`pwd`
echo $current_area

dirlist="ZDimu ZprimeDijets QCD_0-15 QCD_15-20 QCD_20-30 QCD_30-50 QCD_50-80 QCD_80-120 QCD_120-170 QCD_170-230 QCD_230-300 QCD_300-380 QCD_380-470 QCD_470-600 QCD_600-800 QCD_800-1000"

RunPath="fileSaver, caloTowers, analyzeRecHits, analyzecaloTowers, analyzeGenMET, analyzeGenMETFromGenJets, analyzeHTMET, analyzeCaloMET"

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

include \"RecoMET/Configuration/data/CaloTowersOptForMET.cff\"
include \"RecoMET/Configuration/data/RecoMET.cff\"
include \"RecoMET/Configuration/data/RecoHTMET.cff\"
include \"RecoMET/Configuration/data/RecoGenMET.cff\"
include \"RecoMET/Configuration/data/GenMETParticles.cff\"
include \"RecoJets/Configuration/data/CaloTowersRec.cff\"

include \"Validation/RecoMET/data/CaloMET.cff\"
include \"Validation/RecoMET/data/GenMET.cff\"
include \"Validation/RecoMET/data/HTMET.cff\"
include \"Validation/RecoMET/data/GenMETFromGenJets.cff\"
include \"Validation/RecoMET/data/caloTowers.cff\"
include \"Validation/RecoMET/data/RecHits.cff\"



  service = DQMStore{ }
  source = PoolSource
  {
      include \"Validation/RecoMET/data/RelVal_data/FilePaths-$i.cfi\"


    untracked uint32 debugVebosity = 10
     untracked bool   debugFlag     = true
  }

 #   include \"Validation/RecoMET/data/RelVal_data/MaxEvents.cfi\"


  module fileSaver = METFileSaver
  {
        untracked string OutputFile = \"METTester_data_$i.root\"
  }


  path p = {$RunPath}
  schedule = { p }
}" > RunAnalyzers-$i.cfg
#============================================#
cd $current_area
done
