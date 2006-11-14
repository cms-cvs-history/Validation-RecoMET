#!/bin/sh

    eval `scramv1 ru -sh`

    cd data    
    #wget `cat ../../data/download.url`
    list=`ls *.root`
    cd ..

    for i in $list; do

      sed "s|_FILE_|$i|" METReference.cfg > METReference-run.cfg
      cmsRun --parameter-set METReference-run.cfg >& METReference-$i.log
      rm METReference-run.cfg

    done 

    #rm data/*.root

