#!/bin/sh

    eval `scramv1 ru -sh`

    cd data    
    wget `cat ../../data/download.url`
    list=`ls *.root`
    cd ..

    for i in $list; do

      sed "s|_FILE_|$i|" METTester.cfg > METTester-run.cfg
      cmsRun --parameter-set METTester-run.cfg >& METTester-$i.log
      rm METTester-run.cfg

      sed "s|_FILE_|$i|" plotCompare.C > plotCompare-run.C
      root -b -q plotCompare-run.C >> METTester-$i.log
      rm plotCompare-run.C

    done 

    #rm data/*.root

