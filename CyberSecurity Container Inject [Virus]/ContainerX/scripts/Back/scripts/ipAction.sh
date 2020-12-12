#!/bin/bash
#
# tabella / buffer / array
# business add-in => https://docs.microsoft.com/en-us/dynamics365/business-central/dev-itpro/developer/devenv-dotnet-controladdins
#                    https://docs.microsoft.com/en-us/dynamics365/business-central/dev-itpro/developer/devenv-get-started-call-dotnet-from-al
#
#
ipActionf () {

    if (( ${#@} > 0  )) && (( ${#1} > 1  )); then fush=$1 ; fi
    if (( ${#@} > 1  )) && (( ${#2} > 1  )); then view=$2 ; fi
    if (( ${#@} > 2  )) && (( ${#3} > 1  )); then mask=$3 ; fi

    if (( ${#@} > 3  )) && (( ${#4} > 1  )); then table=$4 ; fi
    if (( ${#@} > 4  )) && (( ${#5} > 1  )); then chain=$5 ; fi

    if (( ${#@} > 5  )) && (( ${#6} > 1  )); then src=$6 ; fi
    if (( ${#@} > 6  )) && (( ${#7} > 1  )); then dst=$7 ; fi

    if (( ${#@} > 7  )) && (( ${#8} > 1  )); then sport=$8 ; fi
    if (( ${#@} > 8  )) && (( ${#9} > 1  )); then dport=$9 ; fi

    if (( ${#@} >  9 )) && (( ${#10} > 1 )); then to_dst=${10} ; fi
    if (( ${#@} > 10 )) && (( ${#11} > 1 )); then to_src=${11} ; fi
    if (( ${#@} > 11 )) && (( ${#12} > 1 )); then to_prt=${12} ; fi
    if (( ${#@} > 12 )) && (( ${#13} > 1 )); then to_jmp=${13} ; fi

    # echo "argv : $@"

 #--------------------------------------------------------------------

    if (( ${#fush} != 0 ));
    then
        command="iptables -t $fush -Z"
        echo "$command"
        sudo  $command

        command="iptables -t $fush -F"
        echo "$command"
        sudo  $command

        command="iptables -t $fush -X"
        echo "$command"
        sudo  $command

 #-------------------------------------------

    elif (( ${#view} != 0 )); then

        command="iptables -L -vn -t $view"
        echo "$command"
        sudo  $command

 #-------------------------------------------

    elif (( ${#mask} != 0 )); then

        command="iptables -t nat -A POSTROUTING -o $mask -j MASQUERADE"
        echo "$command"
        sudo  $command

 #-------------------------------------------

    else
        cmd1='sudo iptables' ; cmd2=''

        if (( ${#src} != 0 )) || (( ${#dst} != 0 ));
        then
            if (( ${#table} == 0 )) && (( ${#chain} == 0 ));
            then
                if (( ${#src} != 0 )); then cmd1+=" -A INPUT -s $src"  ; fi ;
                if (( ${#dst} != 0 )); then cmd1+=" -A OUTPUT -d $dst" ; fi ;
            else
                if (( ${#src} != 0 )); then cmd1+=" -t $table -A $chain -s $src" ; fi ;
                if (( ${#dst} != 0 )); then cmd1+=" -t $table -A $chain -d $dst" ; fi ;
            fi;

        elif (( ${#table} != 0 )) && (( ${#chain} != 0 )); then

            cmd1+=" -t $table -A $chain"
        fi;

        #-----------------------------------------------------------------------------------------

        if (( ${#sport}  != 0 )) || (( ${#dport}  != 0 )) ||
           (( ${#to_dst} != 0 )) || (( ${#to_src} != 0 )) || (( ${#to_prt} != 0 ));
        then
            cmd2=$cmd1' -p udp' ; cmd1+=' -p tcp'
        fi;

        #-----------------------------------------------------------------------------------------

        if (( ${#sport} != 0 ));
        then
            cmd1+=" --sport $sport"
            if (( ${#cmd2} != 0 )); then cmd2+=" --sport $sport" ; fi ;

        elif (( ${#dport}  != 0 )); then

            cmd1+=" --dport $dport"
            if (( ${#cmd2} != 0 )); then cmd2+=" --dport $dport" ; fi ;
        fi ;

        #-----------------------------------------------------------------------------------------

        if (( ${#to_jmp} != 0 ));
        then
            cmd1+=" -j $to_jmp"
            if (( ${#cmd2} != 0 )); then cmd2+=" -j $to_jmp" ; fi ;

        elif (( ${#to_dst} != 0 )); then

            cmd1+=" -j DNAT --to-destination $to_dst"
            if (( ${#cmd2} != 0 )); then cmd2+=" -j DNAT --to-destination $to_dst" ; fi ;

        elif (( ${#to_src} != 0 )); then

            cmd1+=" -j SNAt --to-source $to_src"
            if (( ${#cmd2} != 0 )); then cmd2+=" -j SNAt --to-source $to_src" ; fi ;

        elif (( ${#to_prt} != 0 )); then

            cmd1+=" -j REDIRECT --to-port $to_prt"
            if (( ${#cmd2} != 0 )); then cmd2+=" -j REDIRECT --to-port $to_prt" ; fi ;
        fi;

        #-----------------------------------------------------------------------------------------

        echo $cmd1 ; sudo  $cmd1
        if (( ${#cmd2} != 0 )); then echo $cmd2 ; sudo  $cmd2 ; fi ;

        #-----------------------------------------------------------------------------------------

        if  (( ${#table} == 0 )) && (( ${#chain}  == 0 )) &&
            (( ${#src}   != 0 )) && (( ${#to_jmp} != 0 ));
        then
            dst=$src ; sport=$dport

            if (( ${#dport} != 0 ));
            then
                ipAction f v m t c s $dst $sport u 1 2 3 $to_jmp
            else
                ipAction f v m t c s $dst i u 1 2 3 $to_jmp
            fi;

        elif [[ $table == 'filter' ]] && [[ $chain == 'INPUT' ]] && (( ${#to_jmp} != 0 )); then

            sport=$dport ; chain='OUTPUT'

            if (( ${#dport} != 0 ));
            then
                ipAction f v m $table $chain s d $sport u 1 2 3 $to_jmp
            else
                ipAction f v m $table $chain s d i u 1 2 3 $to_jmp
            fi;
        fi;
    fi;
}

#----------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------

if (( ${#@} > 0 ));
then	
    ipActionf $@
else
    echo '|____________________________________________________________________'
    echo '|\__________________________________________________________________\\'
    echo '|\ flush<=1 , for -t option , default is filter                     /|'
    echo '|\ view<=2  , for -t option , default is filter                      |'
    echo '|\ mask<=3  , for -o option , only for POSTROUTING                   |'
    echo '|\___________________________________________________________________|'
    echo '|\ table<=4 , for -t option , default is filter                      |'
    echo '|\ chain<=5 , for -A option , default is INPUT/OUTPUT                |'
    echo '|\___________________________________________________________________|'
    echo '|\ src<=6  ,  for -s option  , useful for  INPUT                     |'
    echo '|\ dest<=7 ,  for -d option  , useful for OUTPUT                     |'
    echo '|\___________________________________________________________________|'
    echo '|\ sport<=8 , for -sport option , useful for OUTPUT                  |'
    echo '|\ dport<=9 , for -dport option , useful for  INPUT                  |'
    echo '|\                                                                   |'
    echo '|\ to_dest<=10 , in PREROUTING  for -j DNAT --to-destination option  |'
    echo '|\ to_src<=11  , in POSTROUTING for -j SNAT      --to-source option  |'
    echo '|\ to_port<=12 , in PREROUTING  for -j REDIRECT    --to-port option  |'
    echo '|\                                                                   |'
    echo '|\ jump<=13 , for -j option : ACCEPT/DROP/LOG/REJECT/RETURN/ULOG/..  |'
    echo '|_\_________________________________________________________________\|'
    echo '|'
    echo ''
fi

