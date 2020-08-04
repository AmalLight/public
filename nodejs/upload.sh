#!/bin/bash

unibop=`get unibop`

sshpass -p $unibop ssh mohammad.fumagalli@filindo.cs.unibo.it -t "cd /home/web/site181981/html/; rm -f *.sh"

# ---------------------------------------------------------------------------------------------------------------------------------------

read -p '  s/n per index.html: ' sino1
if [[ $sino1 == 's' ]] ; then
    sshpass -p $unibop scp -r ./index.html mohammad.fumagalli@filindo.cs.unibo.it:/home/web/site181981/html/
    sshpass -p $unibop ssh mohammad.fumagalli@filindo.cs.unibo.it -t "cd /home/web/site181981/html/; chmod 775 index.html "
fi

# ---------------------------------------------------------------------------------------------------------------------------------------

read -p '  s/n per public: ' sino2
if [[ $sino2 == 's' ]] ; then
    sshpass -p $unibop ssh mohammad.fumagalli@filindo.cs.unibo.it -t "cd /home/web/site181981/html/; chmod 777 -R public "
    sshpass -p $unibop ssh mohammad.fumagalli@filindo.cs.unibo.it -t "cd /home/web/site181981/html/; rm        -r public "

    sshpass -p $unibop scp -r ./public  mohammad.fumagalli@filindo.cs.unibo.it:/home/web/site181981/html/
    sshpass -p $unibop ssh mohammad.fumagalli@filindo.cs.unibo.it -t "cd /home/web/site181981/html/; chmod 775 -R public "
fi

# ---------------------------------------------------------------------------------------------------------------------------------------

read -p '  s/n per indexjs: ' sino3
if [[ $sino3 == 's' ]] ; then
    sshpass -p $unibop scp ./index.js mohammad.fumagalli@filindo.cs.unibo.it:/home/web/site181981/html/ ; ./usegocker.sh ;
fi
