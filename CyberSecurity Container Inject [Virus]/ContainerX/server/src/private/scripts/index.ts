import express, {Express} from 'express'
import path from 'path';
import { fsclass } from './fileManager'

const app : Express = express();

app.use( '/static', express.static( path.join( __dirname + '/../../public' ) ) );

app.get( '/', (req, res, next ) =>
{
    res.sendFile( path.join( __dirname + '/../../public/html/index.html' ), ( err ) =>
    {
        if ( err )
        {
            console.log( 'error occurred for "html send file"' );
        }

        else console.log( `html send file done without error with the root: ${__dirname + '/../../public'}` );
    });
});

app.listen( 8080, () => { console.log( 'server started 2' ); } );