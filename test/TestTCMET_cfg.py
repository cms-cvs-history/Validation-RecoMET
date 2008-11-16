import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.load("RecoMET.Configuration.RecoMET_cff")

process.load("Validation.RecoMET.TCMET_cff")

rocess.load("RecoMET.METProducers.TCMET_cfi")

process.load("Configuration.StandardSequences.Geometry_cff")

process.load("Configuration.StandardSequences.MagneticField_cff")

process.DQMStore = cms.Service("DQMStore")

process.source = cms.Source("PoolSource",
    debugFlag = cms.untracked.bool(True),
    debugVebosity = cms.untracked.uint32(10),
    fileNames = cms.untracked.vstring(

    '/store/relval/CMSSW_2_1_9/RelValTTbar/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v2/0000/B28D6FA4-1E86-DD11-8E98-000423D952C0.root'

    )
)

process.fileSaver = cms.EDFilter("METFileSaver",
    OutputFile = cms.untracked.string('TCMet_ttbar.root')
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) ) 


process.p = cms.Path(process.fileSaver*process.tcMet*process.AnalyzeTCMET)
process.schedule = cms.Schedule(process.p)


