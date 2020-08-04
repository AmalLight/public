const express     = require('express');
const bodyParser  = require('body-parser');
const querystring = require('querystring');
const fs          = require('fs');
const path        = require('path');

const app         = express();

const html_folder = 'index.html';
const json_folder = 'public/json';

//static in src for html, only for public folder
app.use( '/static', express.static( __dirname + '/public' ) );

// parse application/x-www-form-urlencoded
app.use( bodyParser.urlencoded( { extended: false } ) );
 
// parse application/json
app.use( bodyParser.json() );


app.get( '/', ( req, res ) =>
{
    res.sendFile( path.join( __dirname, html_folder ) );
});

function filejsonexist( name )
{
    return fs.existsSync( path.join( __dirname, `${json_folder}/${name}.json` ) );
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

app.get( '/getjson', ( req, res ) =>
{
    if ( req.originalUrl.includes( '?jsonname=' ) && filejsonexist( req.query.jsonname ) )
    {
        var name = req.query.jsonname;
        res.sendFile( path.join( __dirname, `${json_folder}/${name}.json` ) );
    }

    else if ( req.originalUrl.includes( '?get=list' ) )
    {
        var listfiles = '';

        fs.readdirSync( path.join( __dirname, json_folder ) ).forEach( file =>
        {
            listfiles += file.replace( '.json', '|' );
        });

        res.send( listfiles );
    }

    else res.send( 'request not ok' );
});

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

app.post( '/sendjson', ( req, res ) =>
{
    var dict = JSON.parse( req.body.dict );
    var name = dict.titolo;
    var data = JSON.stringify( dict );

    try { fs.writeFileSync( path.join( __dirname, `${json_folder}/${name}.json` ), data ); }
    catch ( e ) { res.send( JSON.stringify( e ) ); }

    if ( filejsonexist( name ) ) res.send( 'gioco salvato e caricato come json' );
    else res.send( 'gioco non salvato o caricato come json' );
});


app.listen( 8000, function() {;} );
