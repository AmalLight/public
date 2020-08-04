package near;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;

public class OptionRW extends RightDown
{    
        public Runnable writeOnFile() throws Exception
        {
                Runnable exec = new Runnable()
                {
                        @Override
                        public void run()
                        { try {
                                onWork = true;
                                RDcanUseButtomStack( done = false );
                                Thread.sleep( sleepmilli2 );
                                
                                if ( RDOnKeyPressed( write.getText() ) &&
                                     x != null && x.exists() && x.isFile() && x.canWrite() )
                                {                                
                                    BufferedWriter writeable = new BufferedWriter( new FileWriter( x ) );
                                    writeable.write( write.getText() );
                                    writeable.close();
                                }

                                RDcanUseButtomStack( done = true );
                                onWork = false;
                        }
                        catch ( Exception e2 ) {;}}
                };
                return exec;
        }
        
        public File readAFile( File F ) throws Exception
        {
                while ( !done ) Thread.sleep( sleepmilli1 );
                init_SqlAPI();
                
                Line.setDisable( false ); search.setDisable( false );
                subs.setDisable( false );
                
                Minus.setDisable( false ); Plus.setDisable( false );
                BShiftL.setDisable( false ); BShiftR.setDisable( false );
                
                char[] alloc1 = new char[ 1 ];
                
                if ( F != null && F.exists() && F.isFile() && F.canRead() )
                {
                        BufferedReader reader = new BufferedReader( new FileReader( F ) );
                        
                        write.clear(); while ( reader.read( alloc1 ) > -1 )
                        write.appendText( String.valueOf( alloc1 ).replaceAll( "\\\t", aTab ) );
                        reader.close();
                }
                
                else if ( F == null ) write.setText( Help );
                                
                H = new History[ maxHistory ]; freeH = -1;
                for ( int i = 0; i < maxHistory; i++ ) H[ i ] = null;
                
                resetCaret( write.getLength() > 0 );
                RDcanUseButtomStack( RDOnKeyPressed( write.getText() ) );
                
                return F;
        }
}