#!/bin/csh

    eval `scramv1 ru -csh`

    rm *.xml*
    if ( -e METAnalyzer.log ) rm METAnalyzer.log
    if ( -e METAnalyzer-run.cfg ) rm METAnalyzer-run.cfg

    cd data    
    wget `cat ../../data/download.url`
    set list = `ls *.root`
    cd ..

    foreach i ($list)

      sed "s|_FILE_|$i|" METAnalyzer.cfg > METAnalyzer-run.cfg
      cmsRun --parameter-set METAnalyzer-run.cfg >& METAnalyzer-$i.log
      rm METAnalyzer-run.cfg

      sed "s|_FILE_|$i|" plotCompare.C > plotCompare-run.C
      root -b -q plotCompare-run.C >> METAnalyzer-$i.log
      rm plotCompare-run.C

    end

    rm data/*.root

