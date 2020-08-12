package near;

import java.io.File;
import javafx.event.Event;
import javafx.scene.input.DragEvent;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;

public class Interface extends Top
{
        public boolean saveText() throws Exception 
        {
                if ( !onWork ) { new Thread( writeOnFile() ).start(); return true; }
                else return false;
        }
        
        //-----------------------------------------------------------------------------------------------------------------------------------
    
        public void EvidenceMouse() throws Exception
        {
                if ( getThisWord() && RUsearchAction( null, write.getText() ) ) search.requestFocus();
        }
        
        public void getLineNumber()
        {
                String line = getThisLine(); int i = 0;
                
                for( String words : write.getText().split( "\n" ) )
                { i++;
                        if ( words.equals( line ) ) { number.setText( String.valueOf( i ) ); break; }
                }
        }
        
        //-----------------------------------------------------------------------------------------------------------------------------------

        /* ther'is a bug with mouse ( right button of mouse ):
        // you can't use paste from mouse ( right and left )
        // this way to paste your copied text,
        // is wrong for this java's TextArea */
        
        @SuppressWarnings("empty-statement")
        public void onWriteInBot( Event e ) throws Exception
        {
                /* fix the first write ( input ) in TextArea */
                if ( freeH < 0 ) readAFile( null );
                
                Paste = MrRobot.paste(); /* for external copy, other Paste = .. are for internal copy */
                Paste = MrRobot.copy( ( Select = cureSelectedWord( write.getSelectedText() ) ).isEmpty() ? Paste : Select );
                
                if ( Select.isEmpty() && write.isFocused() )
                        if ( e.getClass() == MouseEvent.class && reset() )
                                if ( ( ( MouseEvent ) e ).getButton().toString().equals( "MIDDLE" ) )
                                        if ( !Paste.isEmpty() ) insTextANDpos( write, write.getCaretPosition(), Paste );
                                        else saveConfigWrite();
                                
                                else if ( EvidenceMouse ) EvidenceMouse();
                                else { saveConfigWrite(); completeBot(); getLineNumber(); }
                        
                        else if ( e.getClass() == KeyEvent.class ) onWriteBottom( ( ( KeyEvent ) e ).getCode().toString() );
                
                search.setText( Select.isEmpty() ? "" : ( Paste = MrRobot.copy( Select ) ) );
                
                if ( write.isFocused() && isChanged() ) saveText();
        }

        public void onWriteInTop( Event e ) throws Exception
        {
                /* fix the first create new file in option */
                if ( freeH < 0 ) readAFile( null );
                
                Paste = MrRobot.paste(); /* for external copy, other Paste = .. are for internal copy */
                Paste = MrRobot.copy( ( Select = cureSelectedWord( option.getSelectedText() ) ).isEmpty() ? Paste : Select );
                
                if ( Select.isEmpty() && option.isFocused() ) /* more easy to understand */
                        if ( e.getClass() == MouseEvent.class )
                        {
                                if ( ( ( MouseEvent ) e ).getButton().toString().equals( "MIDDLE" ) &&
                                   ( !Paste.isEmpty() ) ) option.appendText( Paste );
                                onWriteTop( "", option.getText() );
                        }
                        else onWriteTop( ( ( KeyEvent ) e ).getCode().toString(), option.getText() );
                
                search.setText( Select.isEmpty() ? "" : ( Paste = MrRobot.copy( Select ) ) );
        }
        
        //-----------------------------------------------------------------------------------------------------------------------------------
        
        public void LineAction() { if ( RULineAction() ) search.setText( Select ); }
                
        public void searchAction( Event e ) throws Exception
        {
                RUsearchAction( ( e.getClass() == MouseEvent.class ? null : ( KeyEvent ) e ), write.getText() );
                /* search.setText( Select ) is automatic */
        }
        
        public void subsAction( Event e ) throws Exception
        {
                if ( RUsubsAction( ( e.getClass() == KeyEvent.class ? ( KeyEvent ) e : null ), write.getText() ) ) saveText();
                /* search.setText( Select ) are internal on recursion */
        }
        
        //-----------------------------------------------------------------------------------------------------------------------------------
        
        public void onClickOp() { Op.setText( Op.getText().equals( "r" ) ? "d" : "r" ); }
        public void OnClickM() { M.setText( ( EvidenceMouse = !EvidenceMouse ) ? "MT" : "MF" ); search.clear(); }
        
        public void Prev() throws Exception { RDPrevNext( true ); saveText(); }
        public void Minus() { RDMinusPlus( true  ); saveConfigWrite(); } /* saveConfig --> reset caret */
        public void Plus()  { RDMinusPlus( false ); saveConfigWrite(); } /* saveConfig --> reset caret */
        public void Next() throws Exception { RDPrevNext( false ); saveText(); }
        public void OnClickC() { reset(); option.clear(); write.clear(); }
        public void OnClickV() throws Exception { resetCaret( false ); }

        //-----------------------------------------------------------------------------------------------------------------------------------
        
        public void OnClickRVBox( ) throws Exception
        {
                if ( !find.isEmpty() ) { saveText(); reset(); completeBot(); }
                else if ( !dirs.isEmpty() ) { reset(); onWriteTop( "", option.getText() ); }
                else { saveText(); resetCaret( true ); }
        }
        
        public void OnClickEnd()  { option.requestFocus(); option.end(); }
        
        //-----------------------------------------------------------------------------------------------------------------------------------
        
        public void ShiftL()
        {
                prevPOS( "\n", false ); nextPOS( " ", true );
                reset();
        }
        
        public void ShiftR()
        {
                nextPOS( "\n", false ); prevPOS( " ", true );
                reset();
        }
        
        public void Past() throws Exception
        {
                option.setText( x.getParent() );
                onWriteTop( "", option.getText() );
        }
        
        //-----------------------------------------------------------------------------------------------------------------------------------
        
        public void FileOnOption( DragEvent e )
        {try {            
                File f = e.getDragboard().getFiles().get( 0 );
                if ( f.exists() )
                {
                        option.setText( f.getAbsolutePath() );
                        option.requestFocus();
                        option.end();
                        
                        onWriteTop( "", option.getText() );
                }

        } catch( Exception e2 ) {;}}
}