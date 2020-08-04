package near;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class Bottom extends ThreadLibs
{
        public String setLastAndll( String last ) /* delete saveConfigWrite( true ), already invoked in onWriteBottom */
        {
                for ( int car2 = car ; car2 > 0 && !cs.contains( write.getText( car2-1, car2 ) ); )
                       last = ( write.getText( car2-1, car2-- ) + last );
                
                return last;
        }
        
        public void resetCaret( boolean resetPosition ) throws Exception
        {
                if ( reset() && write.getLength() < 1 ) return;
                else if ( resetPosition )
                {
                        Integer value = ( car = 1 );
                        scrollTop = scrollLeft = value.doubleValue()-1.00;
                        write.deselect();
                }
                
                write.setScrollTop ( scrollTop  );
                write.setScrollLeft( scrollLeft );
                write.requestFocus();
                
                if ( Select.isEmpty() ) write.positionCaret( car );
        }
        
        public boolean reset()
        {
                if ( !onWork && done ) x = null;
                
                x = ( x == null ? new File( option.getText() ) : x );
                find = new ArrayList<>();
                dirs = new ArrayList<>();
                
                number.clear();
                Action.setText( "Action" );
                return SuggestClear();
        }

        public void onWriteBottom( String input ) throws Exception
        {
                if ( saveConfigWrite() && newTextBot( input, write.getText() ) && reset() ) completeBot();
        }

        public boolean newTextBot( String input, String LoadText ) throws Exception
        {
                if ( input.equals( "DELETE" ) ) nextDEL( true, " " );
                else if ( input.equals( "TAB" ) ) { write.deletePreviousChar(); saveConfigWrite(); }
                
                if ( input.equals( "TAB" ) || input.equals( "ENTER" ) )
                     insTextANDpos( write, car, ( input.equals( "TAB" ) ? aTab : getStartSpace( true ) ) );
                
                return saveConfigWrite();
        }

        public void completeBot() throws Exception /* create or manage cache */
        {
                if ( ( ll = ( last = setLastAndll( last = "" ) ).length() ) <= 2 ) return ;
                
                List<String> list = select_SqlAPI( last );
                
                if ( !list.isEmpty() )
                        for ( String el : list )
                        {
                                find.add( el );
                                suggest.add( shortFunction.myNewButton( el ) );
                        }
                if ( !find.isEmpty() ) { Action.setText( "Find on Write" ); SuggestLoad(); }
        }
}