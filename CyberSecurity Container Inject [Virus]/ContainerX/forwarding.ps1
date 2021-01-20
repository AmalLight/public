param( $addordel , $ipsrc,$portsrc , $ipdest,$portdest )

if ( ( $addordel.length -gt 0 ) -and
     ( $ipsrc.length    -gt 0 ) -and
     ( $portsrc.length  -gt 0 ) -and

     ( ( $addordel        -eq 1 ) -and
       ( $ipdest.length   -gt 0 ) -and
       ( $portdest.length -gt 0 ) ) -or
		
     ( ( $addordel -eq 2 ) ) )
{
    if ( $addordel -eq 1 )
    {
        netsh interface portproxy add v4tov4 listenaddress=$ipsrc listenport=$portsrc connectaddress=$ipdest connectport=$portdest
        echo `netsh interface portproxy add v4tov4 listenaddress=$ipsrc listenport=$portsrc connectaddress=$ipdest connectport=$portdest`
    }
    elseif ( $addordel -eq 2 )
    {
        netsh interface portproxy delete v4tov4 listenaddress=$ipsrc listenport=$portsrc
        echo `netsh interface portproxy delete v4tov4 listenaddress=$ipsrc listenport=$portsrc`
    }
}
else
{
    echo 'arg1: addordel, must be 1 or 2'
    echo 'arg2: ipsrc    '
    echo 'arg3: portsrc  '
    echo 'arg4: ipdest   '
    echo 'arg5: portdest '
}
