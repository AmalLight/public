package near;

import javafx.scene.paint.Paint;
import javafx.scene.text.Font;

public class RightDown extends RightUp
{        
        public int sizeHused()
        {
                for ( int i = 0; i < maxHistory; i++ ) if ( H[ i ] == null ) return i;
                return maxHistory;
        }
        
        public boolean RDsetWriteWithStack()
        {
                History tmp = H[ freeH ];
                
                write.setText      ( tmp.getText()       );
                write.positionCaret( tmp.getCar()        );
                write.setScrollTop ( tmp.getTopScroll()  );
                write.setScrollLeft( tmp.getLeftScroll() );
                
                return true;
        }
        
        public boolean RDcanUseButtomStack( boolean isChange )
        {
                Next.setDisable( !( freeH < sizeHused()-1 ) );
                Prev.setDisable( !( freeH > 0 ) );
                monitor1.setFill( Paint.valueOf( done ? "green" : "red" ) );
                
                option.setDisable ( !done );
                clear.setDisable  ( !done );
                
                return isChange;
        }
        
        public void RDPrevNext( boolean Prev )
        {
                if ( Prev ) freeH--; else freeH++;
                if ( RDcanUseButtomStack( RDsetWriteWithStack() ) ) write.requestFocus();
        }
        
        public void RDMinusPlus( boolean Minus )
        {
                write.setFont( new Font( write.getFont().getName(), ( Minus ? write.getFont().getSize() - 4 :
                                                                              write.getFont().getSize() + 4 ) ) );
                write.requestFocus();
        }
        
        public boolean RDOnKeyPressed( String LoadText )
        {
                if ( freeH < 0 ) H[ ++freeH ] = new History( LoadText, car, scrollTop, scrollLeft );
                else if ( isChanged() )
                        if ( freeH < maxHistory-1 )
                        {
                                freeH++;
                                while ( sizeHused() > freeH ) H[ sizeHused()-1 ] = null;
                                H[ freeH ] = new History( LoadText, car, scrollTop, scrollLeft );
                        }
                        
                        else if ( freeH == maxHistory-1 )
                        {
                                for ( int i = 0; i < maxHistory-1; i++ ) H[ i ] = H[ i+1 ];
                                H[ maxHistory-1 ] = new History( LoadText, car, scrollTop, scrollLeft );
                        }
                else return false;
                return true;
        }
        
        public boolean isChanged() { return ( !H[ freeH ].getText().equals( write.getText() ) ); }
}