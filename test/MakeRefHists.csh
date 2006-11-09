#!/bin/csh

    eval `scramv1 ru -csh`

    rm *.xml*
    if ( -e METReference.log ) rm METReference.log
    if ( -e METReference-run.cfg ) rm METReference-run.cfg

    cd data    
    wget `cat ../../data/download.url`
    set list = `ls *.root`
    cd ..

    foreach i ($list)

      sed "s|_FILE_|$i|" METReference.cfg > METReference-run.cfg
      cmsRun --parameter-set METReference-run.cfg >& METReference-$i.log
      rm METReference-run.cfg

    end

    rm data/*.root

