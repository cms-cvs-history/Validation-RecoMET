import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.load("RecoMET.Configuration.CaloTowersOptForMET_cff")

process.load("RecoMET.Configuration.RecoMET_cff")

process.load("RecoMET.Configuration.RecoHTMET_cff")

process.load("RecoMET.Configuration.RecoGenMET_cff")

process.load("RecoMET.Configuration.GenMETParticles_cff")

process.load("RecoJets.Configuration.CaloTowersRec_cff")

process.load("Validation.RecoMET.CaloMET_cff")

process.load("Validation.RecoMET.GenMET_cff")

process.load("Validation.RecoMET.HTMET_cff")

process.load("Validation.RecoMET.GenMETFromGenJets_cff")

process.load("Validation.RecoMET.caloTowers_cff")

process.load("Validation.RecoMET.RecHits_cff")

process.DQMStore = cms.Service("DQMStore")

process.source = cms.Source("PoolSource",
    debugFlag = cms.untracked.bool(True),
    debugVebosity = cms.untracked.uint32(10),
    fileNames = cms.untracked.vstring('/store/relval/2008/6/6/RelVal-RelValTTbar-1212531852-IDEAL_V1-2nd-02/0000/081018D5-EC33-DD11-A623-000423D6CA42.root')
)

process.fileSaver = cms.EDFilter("METFileSaver",
    OutputFile = cms.untracked.string('METTester_data_ttbar.root')
)

process.p = cms.Path(process.fileSaver*process.calotoweroptmaker*process.analyzeRecHits*process.analyzecaloTowers*process.analyzeGenMET*process.analyzeGenMETFromGenJets*process.analyzeHTMET*process.analyzeCaloMET)
process.schedule = cms.Schedule(process.p)


