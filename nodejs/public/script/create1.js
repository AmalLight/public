function domanda()
{
    var return_dict =
    {
        "url"      : "empty",
        "Domanda"  : "La Domanda",

        "Risposta1" : "Risposta",
        "Risposta2" : "Risposta",
        "Risposta3" : "Risposta",
        "Risposta4" : "Risposta",
        "Risposta5" : "Risposta"
    };

    return return_dict;
}

function create_json_init()
{
    var domande = [];

    for( var i = 0; i < 10; i++ ) domande.push( domanda() );

    return_dict =
    {
        "titolo"      : "Titolo del gioco",
        "descrizione" : "La Descrizone del gioco",

        "scuola" : "elementari",
        "gruppo" : "singolo",

        "nome"    : "nome del creatore",
        "cognome" : "cognome del creatore",
        "numero"  : 1,

        "gioco" : domande
    };

    return return_dict;
}

function init_rige() {

    var domanda_pos = function_json.posdj();
    var topjson = function_json.readj();
    var domande = function_json.readj()[ 'gioco' ];
    var domanda = domande[ domanda_pos ];

    $( '#domanda' ).text( domanda_pos+1 );

    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------

    if ( $( "#riga3 input[ name=titolo ]" ).val() == '' )
         $( "#riga3 input[ name=titolo ]" ).val( topjson.titolo );

    if ( $( "#riga3 textarea[ name=descrizione ]" ).val() == '' )
         $( "#riga3 textarea[ name=descrizione ]" ).val( topjson.descrizione );

    if ( $( "#riga3 input[ name=nome ]" ).val() == '' )
         $( "#riga3 input[ name=nome ]" ).val( topjson.nome );

    if ( $( "#riga3 input[ name=cognome ]" ).val() == '' )
         $( "#riga3 input[ name=cognome ]" ).val( topjson.cognome );

    if ( $( "#riga3 input[ name=numero ]" ).val() == '' )
         $( "#riga3 input[ name=numero ]" ).val( topjson.numero );

    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------

    $( "#riga4 input[ name=url ]" ).val( domanda.url );

    $( "#riga4 textarea[ name=domanda ]" ).val( domanda.Domanda );

    $( "#riga4 input[ name=r1 ]" ).val( domanda.Risposta1 );
    $( "#riga4 input[ name=r2 ]" ).val( domanda.Risposta2 );
    $( "#riga4 input[ name=r3 ]" ).val( domanda.Risposta3 );
    $( "#riga4 input[ name=r4 ]" ).val( domanda.Risposta4 );
    $( "#riga4 input[ name=r5 ]" ).val( domanda.Risposta5 );

    init_up_dw( domanda_pos, domande.length );
}
