function noempty()
{
    $( '.noempty' ).each(  function()
    {
        $( this ).attr( 'placeholder', $( this ).val() );
    });

    $( '.noempty' ).keyup( function()
    {
        if ( $( this ).val().length == 0 )
             $( this ).val( $( this ).attr( 'placeholder' ) );
    });
}

function loadcards()
{
    $( '#rowstories' ).html( '' );

    $.get( '/getjson?get=list', function( data1 )
    {
        var list = data1.split( '|' );

        for( var i = 0; i < list.length; i++ )
        {
            $.get( `/getjson?jsonname=${list[ i ]}`, function( data2 )
            {
                if ( data2 != 'request not ok' )
                {
                    var titolo = data2.titolo;
                    var scuola = data2.scuola;
                    var gruppo = data2.gruppo;

                    function_json.insert( titolo, data2 );

                    $( '#rowstories' ).html
                    (
                        $( '#rowstories' ).html() +

                       `<div class=col-4 >
                           <div class="gameContainer">
                               <i class="fas fa-tree fa-3x"></i>
                               <h4 class="gameTitle">${titolo}</h4>
                               <div class="btn-group">
                                   <button type="button" class="btn btn-md btn-outline-info" onclick="loadGame('${titolo}')" >
                                       ${scuola} | ${gruppo}
                                   </button>
                               </div>
                           </div>
                       </div>`
                    );
                }
            });
        }
    });
}
