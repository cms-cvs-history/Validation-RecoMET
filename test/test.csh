#!/bin/csh

    eval `scramv1 ru -csh`

    rm *.xml*
    if ( -e METTester.log ) rm METTester.log
    
    cmsRun --parameter-set METTester.cfg >& METTester.log

    root -b -q plotCompare.C >> METTester.log


