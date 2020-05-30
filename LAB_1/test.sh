#!/bin/bash

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac
echo "The script is run on "${machine}" machine"

if [ "${machine}" == 'Mac' ]; then
    MD5_SHELL="md5 -r "
else
    MD5_SHELL="md5sum "
fi

setUp()
{
    rm results.*
}

testLab1()
{
    # execute student's solution
	bash lab1.sh
    # calculate md5 hash of results file
    md5_results=($($MD5_SHELL results.*))
    # remove trailing filename and leave MD5 hashsum only:
    actual=$(echo $md5_results)
    # declare a list of valid md5 hashes
    declare -a expected=(49713444858274e0dcd3b4f51bb9513d 711dd6705a7f353e72afef285602ff26 72246e71e555278bbb8f59f906311489 586eb7421087bbd321d6637522afc0f2 2123fffa1d2cda5fdee16e1e1606ae44 177cf6611b35df84b7dbc90a6fc22336 0f554502d9d039e1e1ed247f55f7e320 9fb2f0671e68ddbdf1ee0f7f884f9583 b846aba317f08a6d10be9860b0fd522f e957402ea82b4626a67c02e9482e6924 aa502da2f56bbc3822e5e11f7546e4c0 9e96dfe3d4c2393c9632a6bc78ac30a6)
    for i in {0..11}
    do
echo $actual
echo $expected[$i]
        nvar=$(($i+1))
        if [ $actual == ${expected[$i]} ]; then
            echo "Solution for task "$nvar" was found and it seems to be correct."
            assertTrue ${SHUNIT_TRUE}
            return
        fi
      done
    # report failure
    fail "No correct solutions were found."
}

# load shunit2
. shunit2-2.1.6/src/shunit2
