package near;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.List;

public class ThreadLibs extends useSuggest
{
        /* i can only read line in only 1 thread, because i can't open file more times */
        public Runnable libsImport( List<File> FilesNear )
        {
                Runnable exec = () -> { try 
                {
                        lifeFile = true;
                        for ( File F : FilesNear )
                        {
                                String line = "";
                                BufferedReader reader = new BufferedReader( new FileReader( F ) );
                                while ( lifeFile && ( line = reader.readLine() ) != null )
                                {
                                        line = line + ";";
                                        
                                        if ( !line.isEmpty() )                                            
                                            while ( line.substring( 0,1 ).equals( " " ) ) line = line.substring( 1 );
                                        
                                        if ( !line.isEmpty() && !line.substring( 0,1 ).equals( "#" ) )
                                                if ( line.length() > 4 )
                                                        insert_SqlAPI( line.substring( 0,line.length()-1 ) );
                                } reader.close();
                        }
                } catch ( Exception e2 ) {;}}; return exec;
        }
               
        public void resetImportFile( List<File> FilesNear ) throws Exception
        {
                if ( importFILE != null ) lifeFile = false; /* new interrupt idea */
                
                while ( importFILE != null && 
                      ( importFILE.isAlive() ||
                        importFILE.isDaemon() )) Thread.sleep( sleepmilli1 );
                
                if ( importFILE != null ) importFILE = null;
                
                ( importFILE = new Thread( libsImport( FilesNear ) )).start();
        }
}
