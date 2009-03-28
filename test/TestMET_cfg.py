import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.load("RecoMET.Configuration.CaloTowersOptForMET_cff")

process.load("RecoMET.Configuration.RecoMET_cff")

process.load("RecoMET.Configuration.RecoHTMET_cff")

process.load("RecoMET.Configuration.RecoGenMET_cff")

process.load("RecoMET.Configuration.GenMETParticles_cff")

process.load("RecoMET.Configuration.RecoPFMET_cff")

process.load("RecoJets.Configuration.CaloTowersRec_cff")

process.load("Validation.RecoMET.CaloMET_cff")

process.load("Validation.RecoMET.GenMET_cff")

process.load("Validation.RecoMET.HTMET_cff")

process.load("Validation.RecoMET.GenMETFromGenJets_cff")

process.load("Validation.RecoMET.caloTowers_cff")

process.load("Validation.RecoMET.RecHits_cff")

process.load("Validation.RecoMET.PFMET_cff")

process.load("Validation.RecoMET.TCMET_cff")

process.load("Configuration.StandardSequences.Geometry_cff")

process.load("Configuration.StandardSequences.MagneticField_cff")

process.DQMStore = cms.Service("DQMStore")

 


    
# load the noise info producer
process.load('RecoMET.METProducers.hcalnoiseinfoproducer_cfi')
process.hcalnoise.dropRefVectors = cms.bool(False)
process.hcalnoise.requirePedestals = cms.bool(False)


process.source = cms.Source("PoolSource",
    debugFlag = cms.untracked.bool(True),
    debugVebosity = cms.untracked.uint32(10),
    fileNames = cms.untracked.vstring(

        '/store/relval/CMSSW_3_1_0_pre4/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_30X_v1/0003/06072974-1916-DE11-80F2-001617DBD224.root'

    )


)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(20) )

process.fileSaver = cms.EDFilter("METFileSaver",
    OutputFile = cms.untracked.string('METTester_data_QCD_80-120.root')
) 
process.p = cms.Path(process.fileSaver*
                     process.calotoweroptmaker*
                     process.towerMakerWithHO*
                     process.calotoweroptmakerWithHO*
                     process.metreco*
                     process.analyzecaloTowers*
                     process.analyzeGenMET*
                     process.analyzeGenMETFromGenJets*
                     process.analyzeHTMET*
                     process.analyzeCaloMET*
                     process.analyzePFMET*
                     process.analyzeTCMET)


process.schedule = cms.Schedule(process.p)


