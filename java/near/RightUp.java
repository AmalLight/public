package near;

import javafx.scene.input.KeyEvent;

public class RightUp extends Bottom
{
        public boolean RULineAction()
        {
                if ( write.getLength() > 0 && Line.getLength() > 0 )
                try {
                        int value = Integer.parseInt( Line.getText() );
                        if ( value < 1 ) Action.setText( "L. !Find" );
                        else {
                                int line = 1;
                                int preLine = 0;
                                String LoadText = write.getText();
                                
                                while ( line < value )
                                {
                                        if ( LoadText.indexOf( '\n' ) < 0 ) { Action.setText( "L. outRange" ); return false; }
                                        
                                        preLine += LoadText.substring( 0, LoadText.indexOf( '\n' ) ).length() +1;
                                        LoadText = LoadText.substring( LoadText.indexOf( '\n' ) +1 );
                                        
                                line++; }
                                
                                if ( line == value )
                                {
                                        Select = cureSelectedWord( shortFunction.mySelect( write, preLine, 
                                                ( LoadText.indexOf( '\n' ) < 0 ?
                                                  write.getLength() : preLine + LoadText.indexOf( '\n' ) ) ) );
                                        
                                        Paste  = MrRobot.copy( ( Select.isEmpty() ? Paste : Select ) );
                                        
                                        if ( !Select.equals( "\n" ) && !Select.equals( "" ) )
                                             Action.setText( "L. Find" );                                        
                                        else Action.setText( "L. Empty" );
                                }
                        }
                } catch ( Exception e2 ) { Action.setText( "L. !number" ); }
                else Action.setText( "W. or L. clear" );
                
                return Action.getText().equals( "L. Find" );
        }

        /* search more line is possible but not usable for subs ( ReplaceAll limit recursion ) */
        public boolean RUsearchAction( KeyEvent e, String LoadText ) throws Exception
        {
                Select = cureSelectedWord( write.getSelectedText() ); /* for more security */
                
                if ( write.getLength() < 1 || search.getLength() < 1 ) { Action.setText( "W. or S. clear" ); return false; }
                
                if ( !Select.toLowerCase().equals( search.getText().toLowerCase() ) ||
                     !search.getText().toLowerCase().equals( match.toLowerCase() ) ) { index = -1; match = ""; }
                
                if ( ( index ) > -1 )
                        switch ( ( e == null ? "" : e.getCode().toString() ) )
                        {
                                case "LEFT":  index = ( LoadText.toLowerCase().substring( 0, index ).lastIndexOf(      match.toLowerCase() )     ); break;
                                case "RIGHT": index = ( index + LoadText.toLowerCase().substring( index + 1 ).indexOf( match.toLowerCase() ) + 1 ); break;
                        }
                
                else if ( ( index = LoadText.toLowerCase().indexOf( search.getText().toLowerCase() ) ) > -1 ) match = search.getText();
                else { index = -1; match = ""; Action.setText( "S. !exists" ); }
                        
                if ( index > -1 )
                {
                        Select = cureSelectedWord( shortFunction.mySelect( write, index, index + match.length() ) );
                        Paste  = MrRobot.copy( ( Select.isEmpty() ? Paste : Select ) );
                        Action.setText( "S. Find" );
                }
                return Action.getText().equals( "S. Find" );
        }
        
        /* subs more line is not possible ( ReplaceAll limit recursion ) */
        public boolean RUsubsAction( KeyEvent e, String LoadText ) throws Exception /* substitution */
        {
                String se = search.getText();
                String su = subs.getText();
                
                if ( e != null && e.getCode().toString().equals( "ENTER" ) && !su.isEmpty() && Select.equals( se ) )
                {                        
                        write.setText( LoadText = FixReplaceAll( write.getText(), se, su ) );
                        search.setText( su ); subs.clear();
                                        
                        if ( RUsearchAction( null, LoadText ) ) search.requestFocus();
                        Action.setText( "S. Work" ); return true;
                }
                else { Action.setText( "S. !Work" ); return false; }
        }
        
        // -----------------------------------------------------------------------------------------------------------------
        
        public String FixReplaceAll( String x, String y, String z )
        {
                /* limit recursion by java, in my desktop pc (home) limit is 5k. 
                // baypass it ( this limit ) with a << while or a << for >> >> */
            
                /* limit for this function: ReplaceAll foreach 1 line on recursion */
                
                String da_ritorno = "";
                
                for( String line : x.split( "\n" ) )
                         da_ritorno += ( ReplaceAll( line, y, z ) + "\n" );
                
                return ( da_ritorno.isEmpty() ? "" :
                         da_ritorno.substring( 0, da_ritorno.length()-1 ) );
        }
        
        public String ReplaceAll( String x, String y, String z ) /* fix bugs in java's replaceAll */
        {
                if ( !x.isEmpty() && !y.isEmpty() && x.length() >= y.length() )
                {
                        if ( x.substring( 0, y.length() ).equals( y ) )
                             return z + ReplaceAll( x.substring( y.length() ), y, z );
                        else return x.substring( 0, 1 ) + ReplaceAll( x.substring( 1 ), y, z );
                }
                return x;
        }
}