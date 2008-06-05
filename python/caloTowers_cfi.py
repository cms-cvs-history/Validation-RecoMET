import FWCore.ParameterSet.Config as cms

# File: caloTowers.cfi
# Author: B. Scurlock
# Date: 03.04.2008
#
# Fill validation histograms for caloTowers.
towerSchemeBAnalyzer = cms.EDAnalyzer("CaloTowerAnalyzer",
    Debug = cms.bool(False),
    CaloTowersLabel = cms.InputTag("caloTowers"),
    OutputFile = cms.untracked.string('CaloTowerAnalyzer_SchemeB.root'),
    DumpGeometry = cms.bool(False),
    GeometryFile = cms.untracked.string('CaloTowerAnalyzer_geometry.dat')
)

towerOptAnalyzer = cms.EDAnalyzer("CaloTowerAnalyzer",
    Debug = cms.bool(False),
    CaloTowersLabel = cms.InputTag("caloTowersOpt"),
    OutputFile = cms.untracked.string('CaloTowerAnalyzer_Opt.root'),
    DumpGeometry = cms.bool(False),
    GeometryFile = cms.untracked.string('CaloTowerAnalyzer_geometry.dat')
)

