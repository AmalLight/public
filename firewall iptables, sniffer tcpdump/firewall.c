#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;
string pass = "";
string new_pass = "";
string devi = "";

const char* go( string add )
{
    new_pass = "sshpass -p "+ pass +" ssh -t kaumi@51.75.141.107 '";
    new_pass = new_pass +" echo "+ pass +" | sudo -S "+ add    +"'";
    return new_pass.c_str();
}

int count_nl( string x )
{
    int c = 0;
    for ( int i=0; i<x.length(); i++ )
        if ( x[ i ] == '\n' ) c++;
    return c+1;
}

string* split_nl( string x )
{
    int c = count_nl( x );
    string* el = new string[ c ];

    if ( c-1 < 1 ) el[ 0 ] = x;
    else
    {
        for( int i=0; i < c; i++ ) el[ i ] = "";
        for( int i=0, k=0; i < x.length(); i++ )
            if ( x[ i ] == '\n' ) k++;
            else el[ k ] += x[ i ];
    }
    return el;
}

void firewall( string x )
{
    string* f = split_nl( x );
    for( int i=0; i < count_nl( x ); i++ )
    {
        cout << go( f[ i ] ) << endl;
        system( go( f[ i ] ) );
    }
}

int main( int argc, char *argv[] )
{
    pass = argv[ 1 ];
    devi = argv[ 2 ];

    cout << endl;

    string ok = "-j ACCEPT \n" ;
    string no = "-j DROP   \n" ;

    string flush   = "iptables -t raw -F \n iptables -t mangle -F \n iptables -t nat -F \n"
                     "iptables -t filter -F INPUT \n iptables -t filter -F OUTPUT \n" ;

    string view    = "iptables -t nat -S \n iptables -t filter -S" ;

    string redir1  = "--dport 443  -j REDIRECT --to-ports 5000 \n" ;
    string redir2  = "--dport 5000 -j REDIRECT --to-ports 666  \n" ;

    string pre     = "-t nat -A PREROUTING " ;
    string post    = "-t nat -A OUTPUT     " ;

    firewall( flush +

              "iptables "+ pre  +" -i "+ devi +" -p tcp "+ redir1 +
              "iptables "+ pre  +" -i "+ devi +" -p udp "+ redir1 +
              "iptables "+ pre  +" -i "+ devi +" -p tcp "+ redir2 +
              "iptables "+ pre  +" -i "+ devi +" -p udp "+ redir2 +

              "iptables -A INPUT -i "+ devi +" -p tcp --dport 5000 "+ ok +
              "iptables -A INPUT -i "+ devi +" -p udp --dport 5000 "+ ok +
              "iptables -A INPUT -i "+ devi +" -p tcp --dport 80   "+ ok +
              "iptables -A INPUT -i "+ devi +" -p udp --dport 80   "+ ok +

              "iptables -A INPUT  -i "+ devi +" -p tcp --dport 22 -g SSH \n" +
              "iptables -A OUTPUT -o "+ devi +" -p tcp --sport 22 -g SSH \n" +

              "iptables -A OUTPUT -o "+ devi +" -p tcp --sport 5000 "+ ok +
              "iptables -A OUTPUT -o "+ devi +" -p udp --sport 5000 "+ ok +
              "iptables -A OUTPUT -o "+ devi +" -p tcp --sport 80   "+ ok +
              "iptables -A OUTPUT -o "+ devi +" -p udp --sport 80   "+ ok +

              "iptables -A INPUT  "+ no +
              "iptables -A OUTPUT "+ no + view );

    cout << endl;
    return 0;
}
