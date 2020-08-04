#!/bin/bash

if (( ${#@} > 1 && ${#@} < 6 ));
then
    file=$1

    startminutes=$2
    startseconds=$3
    startcompose=$startminutes':'$startseconds.500

    volstart=$4 ; volend=$5 ; volstart2=$volstart

    rm -f ./out1.mp3 ./out2.mp3

# --------------------------------------------------------------------------

    reduce $file 00 $startcompose mp3 ; mv ./out.mp3 ./out1.mp3

# --------------------------------------------------------------------------

    if (( $volstart > $volend )); then volstart2=$(( volstart - 1 )) ; fi
    if (( $volstart < $volend )); then volstart2=$(( volstart + 1 )) ; fi

# --------------------------------------------------------------------------

    reduce $file $startcompose 22:22:22 mp3 ; 

    mv ./out.mp3 ./out2.mp3

    volume out2.mp3 $volstart2

    mv ./out.mp3 ./out2.mp3

# --------------------------------------------------------------------------

    concat2 out1.mp3   out2.mp3 mp3
    rm -f ./out1.mp3 ./out2.mp3

    startseconds=$(( startseconds + 1 ))

# --------------------------------------------------------------------------

    echo ''
    echo "from: volume1: $volstart  "
    echo "to:   volume2: $volstart2 "
    echo ''

    rm -f ./out3.mp3

    if ((
          ($volstart2 > 1       && $volstart2 <       9) &&
          ($volstart2 > $volend || $volstart2 < $volend) && $startseconds < 59
    ));
    then
        mv ./out.mp3 ./out3.mp3
        volume2 out3.mp3 $startminutes $startseconds $volstart2 $volend
    fi

else
    echo ''
    echo 'forgot arg1: file          ?'
    echo ''
    echo 'forgot arg2: start minutes ?'
    echo 'forgot arg3: start seconds ?'
    echo ''
    echo 'forgot arg4: volume start  ?'
    echo 'forgot arg5: volume end    ?'
    echo ''
fi
