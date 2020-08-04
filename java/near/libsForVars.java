package near;

import javafx.scene.control.TextArea;

public class libsForVars extends Vars
{
        // tools for all:
    
        public void nextDEL( boolean chose, String cs2 ) /* maybe, delete next chars */
        {
                while ( car < write.getLength() )
                        if ( cs2.contains( write.getText( car, car+1 ) ) == chose )
                                { write.deleteNextChar(); saveConfigWrite(); }
                        else break;
        }
        
        public void prevDEL( boolean chose, String cs2 )
        {
                while ( car > 0 )
                        if ( cs2.contains( write.getText( car-1, car ) ) == chose )
                                { write.deletePreviousChar(); saveConfigWrite(); }
                        else break;
        }
        
        public void nextPOS( String match, boolean result )
        {
                while ( car < write.getLength() )
                        if ( ( write.getText( car, car+1 ).equals( match ) ) == result )
                               write.positionCaret( ++car );
                        else break;
        }
        
        public void prevPOS( String match, boolean result )
        {
                while ( car > 0 ) 
                        if ( ( write.getText( car-1, car ).equals( match ) ) == result )
                               write.positionCaret( --car );
                        else break;
        }
        
        // --------------------------------------------------------------------------------------------------
        
        public String cureSelectedWord( String selectedWord ) /* maybe, delete from start chars */
        {
                while (  !selectedWord.isEmpty() && (
                          selectedWord.substring( 0, 1 ).equals( " " ) ||
                          selectedWord.substring( 0, 1 ).equals( "\n" ) ) )
                          selectedWord = selectedWord.substring( 1 );
                
                return ( selectedWord.isEmpty() ? "" : selectedWord );
        }
        
        public boolean getThisWord() throws Exception
        {
                String word = ""; int car2 = car = write.getCaretPosition();
                
                for ( ; car2 > 0 && !cs.contains( write.getText( car2-1, car2 ) ); ) car2--;    /* like --car */
                
                for ( ; car2 < write.getLength() && !cs.contains( write.getText( car2, car2+1 ) ); car2++ )
                       search.setText( word += write.getText( car2, car2+1 ) );                 /* like ++car */
                                
                return ( Paste = MrRobot.copy( ( word.isEmpty() ? Paste : word ) ) ).equals( word );
        }
        
        public String getThisLine()
        {
                String line = ""; int car2 = car = write.getCaretPosition();
                
                for ( ; car2 > 0 && !write.getText( car2-1, car2 ).equals( "\n" ); ) car2--;   /* like --car */
                
                for ( ; car2 < write.getLength() && !write.getText( car2, car2+1 ).equals( "\n" ); car2++ )
                       line += write.getText( car2, car2+1 );                                  /* like ++car */
                
                return line;
        }
        
        // --------------------------------------------------------------------------------------------------
        // don't touch this, it'is perfect:
        
        public boolean saveConfigWrite()
        {
                car = write.getCaretPosition();   /* you don't change this */
                
                if ( write.isFocused() )
                {
                        scrollTop  = write.getScrollTop();
                        scrollLeft = write.getScrollLeft();
                        
                        /* debug Caret error */
                        if ( Select.isEmpty() && car > 0 ) write.positionCaret( car-1 );
                        if ( Select.isEmpty()            ) write.positionCaret( car   );
                }
                
                return true; /* return for write easy code */
        }
        
        public void insTextANDpos( TextArea T, Integer index, String W  )
        {
                T.insertText( index, W );
                T.positionCaret( index + W.length() );
                
                saveConfigWrite(); /* for update car */
        }
        
        public String getStartSpace( boolean newLine ) /* used only in newTextBot, implicto saveConfigWrite() */
        {
                Integer index, i = 0;
                String da_ritorno = "", tmp = "";
                
                tmp = ( newLine ? write.getText( 0, car-1 ) : write.getText( 0, car ) );
                tmp = ( ( index = tmp.lastIndexOf( "\n" ) ) > (-1) ? tmp.substring( index + 1 ) : tmp );
                
                while ( i < tmp.length() && tmp.toCharArray()[ i++ ] == ' ' ) da_ritorno += " ";
                return da_ritorno;
        }
        
        public String cureLibs( String x )
        {
                if ( x == null || x.isEmpty() ) return "";
                
                x = x.substring( x.contains( "@dl:" ) ? x.indexOf( "@dl:" ) + 4 : 0 ).replaceAll( "@tb:", aTab );
                
                return x.replaceAll( "@nl:", ( "\n" + getStartSpace( false ) ) ).replaceAll( "@cr:", bTab );
        }
}
