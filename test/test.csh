#!/bin/csh

    eval `scramv1 ru -csh`

    rm *.xml*
    if ( -e METTester.log ) rm METTester.log
    if ( -e METTester-run.cfg ) rm METTester-run.cfg

    cd data    
    wget `cat ../../data/download.url`
    set list = `ls *.root`
    cd ..

    foreach i ($list)

      sed "s|_FILE_|$i|" METTester.cfg > METTester-run.cfg
      cmsRun --parameter-set METTester-run.cfg >& METTester-$i.log
      rm METTester-run.cfg

      sed "s|_FILE_|$i|" plotCompare.C > plotCompare-run.C
      root -b -q plotCompare-run.C >> METTester-$i.log
      rm plotCompare-run.C

    end

    rm data/*.root

