package near;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import org.apache.commons.io.FileUtils;

public class Top extends OptionRW
{
        public void include( File x ) throws Exception
        {
                List<File> FilesNear = new ArrayList<>();
                
                if ( x.exists() && x.isFile() )
                        for ( File F : x.getParentFile().listFiles() )
                                if ( !F.isHidden() && F.getName().contains( ".near" ) )
                                        FilesNear.add( F );

                resetImportFile( FilesNear );
        }
        
        public void onWriteTop( String input, String top ) throws Exception
        {
                newTextTop( input );
                
                if ( top.equals( "/" ) || x.getParentFile() != null && x.getParentFile().exists() )
                        if ( completeTop() )
                                if ( !x.exists() ) Op.setText( "w" );
                                else if ( x.isDirectory() ) Op.setText( "Op." );
                                else;
                        else if ( x.isFile() )
                                if ( !Op.getText().equals( "d" ) ) Op.setText( "r" );
                                else;
                        else;
                else { option.setText( "/" ); onWriteTop( "", option.getText() ); option.end(); }
                
                Op.setDisable( !( x.exists() && x.isFile() ) );
                Past.setDisable( !( x.exists() && option.getLength() > 2 && 
                                    x.getParentFile().exists() ) );
        }
        
        private File copyFile( File source ) throws Exception
        {
                if ( !source.getAbsolutePath().contains( "/home/" ) )
                {
                        File dest = new File( "/home/kaumi/" + source.getName() );
                        try
                        {
                            FileUtils.copyFile( source, dest );
                            option.setText( (x = dest).getAbsolutePath() );
                            completeTop(); return dest;
                        }
                        catch( Exception e ){;}        
                }
                return source; 
        }

        public boolean newTextTop( String input ) throws Exception
        {
                if ( input.equals( "ENTER" ) )
                {
                        if ( Op.getText().equals( "r" ) ) include( readAFile( copyFile( x ) ) );
                                            
                        else if ( Op.getText().equals( "w" ) && x.getParentFile().canWrite() )
                        {
                                x.createNewFile();
                                x.setReadable  ( true );
                                x.setWritable  ( true );
                                x.setExecutable( true );
                                
                                RightVBox.getOnMouseClicked().handle( null ); // save write on file
                                
                                /* il salvataggio contiene un keyPressed quindi di fatto in questo caso,
                                // il salvataggio costa come costerebbe di normale + un keyPressed Extra */
                        }
                        
                        else if ( Op.getText().equals( "d" ) && x.canWrite() ) x.delete();
                        
                        option.end();
                }
                return reset();
        }

        public boolean completeTop() throws Exception
        {
                if ( x.exists() && x.isDirectory() ) { option.setText( x.getAbsolutePath() + '/' ); option.end(); }
                else if ( x.exists() && x.isFile() ) return false;
                
                for ( File F : ( x.exists() ? x.listFiles() : x.getParentFile().listFiles() ) )
                    if ( x.exists() || F.getName().toLowerCase().contains( x.getName().toLowerCase() ))
                        if( !F.isHidden() )
                        {
                            dirs.add( F.getAbsolutePath() );
                            suggest.add( shortFunction.myNewButton( ( F.isDirectory() ? F.getName() + '/' : F.getName() )));
                        }
                
                if ( !dirs.isEmpty() ) { Action.setText( "Find on Top" ); SuggestLoad(); }
                
                return true;
        }
}