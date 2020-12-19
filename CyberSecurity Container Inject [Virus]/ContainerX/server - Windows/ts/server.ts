import express, {Express} from 'express'
import path from 'path';

const app : Express = express();

app.use( '/static', express.static( path.join( __dirname ) ) );

app.get( '/', (req, res, next ) =>
{
    res.sendFile( path.join( __dirname + '/index.html' ), ( err ) =>
    {
        if ( err )
        {
            console.log( 'error occurred for "html send file"' );
        }

        else console.log( 'html send file done without errors' );
    });
});

app.listen( 8080, () => { console.log( 'server started' ); } );