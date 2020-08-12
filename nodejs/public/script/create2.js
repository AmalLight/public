function init_up_dw( i, len )
{
    if ( i == 0 ) $( '#up' ).css( 'display', 'none'  );
    else          $( '#up' ).css( 'display', 'block' );

    if ( i+1 == len ) $( '#dw' ).css( 'display', 'none'  );
    else              $( '#dw' ).css( 'display', 'block' );
}

function up() {
    var domanda_pos = function_json.posdj();
    if ( domanda_pos > 0 ) function_json.meno();

    init_rige();
}

function dw() {

    var domanda_pos = function_json.posdj();
    var domande = function_json.readj()[ 'gioco' ];

    if ( domanda_pos+1 < domande.length ) function_json.plus();

    init_rige();
}

function plus() {
    var cjson = function_json.readj();
    cjson[ 'gioco' ].push( domanda() );

    function_json.alloc( cjson ); init_rige();
}

function save() {
    var domanda_pos = function_json.posdj();

    var cjson = function_json.readj();

    cjson[ 'gioco' ][ domanda_pos ][ 'url'      ] = $( "#riga4 textarea[ name=url     ]" ).val();
    cjson[ 'gioco' ][ domanda_pos ][ 'Domanda'  ] = $( "#riga4 textarea[ name=domanda ]" ).val();

    cjson[ 'gioco' ][ domanda_pos ][ 'Risposta1' ] = $( "#riga4 input[ name=r1 ]" ).val();
    cjson[ 'gioco' ][ domanda_pos ][ 'Risposta2' ] = $( "#riga4 input[ name=r2 ]" ).val();
    cjson[ 'gioco' ][ domanda_pos ][ 'Risposta3' ] = $( "#riga4 input[ name=r3 ]" ).val();
    cjson[ 'gioco' ][ domanda_pos ][ 'Risposta4' ] = $( "#riga4 input[ name=r4 ]" ).val();
    cjson[ 'gioco' ][ domanda_pos ][ 'Risposta5' ] = $( "#riga4 input[ name=r5 ]" ).val();

    function_json.alloc( cjson );
    alert( 'salvato in domande alla posizione: ' + ( domanda_pos+1 ) );
}

function replaceALL( string, char, new_char ) {
    var new_string = '';

    for( var i = 0; i < string.length; i++ )
        if ( string[ i ] == char ) new_string += new_char;
        else                       new_string += string[ i ];

    return new_string;
}

function submit() {
    var cjson = function_json.readj();

    var titolo = $( "#riga3 input[ name=titolo ]" ).val();
        titolo = replaceALL( titolo, ' ', '_' );
        titolo = replaceALL( titolo, '.', '_' );
        titolo = replaceALL( titolo, '|', '_' );

    cjson[ 'titolo' ] = titolo;
    cjson[ 'descrizione' ] = $( "#riga3 textarea[ name=descrizione ]" ).val();

    cjson[ 'scuola' ] = $( "#riga3 input[ name=scuola ]:checked" ).val();
    cjson[ 'gruppo' ] = $( "#riga3 input[ name=gruppo ]:checked" ).val();

    cjson[ 'nome'    ] = $( "#riga3 input[ name=nome    ]" ).val();
    cjson[ 'cognome' ] = $( "#riga3 input[ name=cognome ]" ).val();
    cjson[ 'numero'  ] = $( "#riga3 input[ name=numero  ]" ).val();

    function_json.alloc( cjson );

    $.post( '/sendjson', { 'dict' : JSON.stringify( cjson ) }, function( data )
    {
        alert( data );
    });
}
