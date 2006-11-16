#!/bin/sh

    eval `scramv1 ru -sh`

    cd data    
    wget `cat ../../data/download.url`
    list=`ls *.root`
    cd ..

    for i in $list; do

      sed "s|_FILE_|$i|" METAnalyzer.cfg > METAnalyzer-run.cfg
      cmsRun --parameter-set METAnalyzer-run.cfg >& METAnalyzer-$i.log
      rm METAnalyzer-run.cfg

      sed "s|_FILE_|$i|" plotCompare.C > plotCompare-run.C
      root -b -q plotCompare-run.C >> METAnalyzer-$i.log
      rm plotCompare-run.C

    done 

    #rm data/*.root

