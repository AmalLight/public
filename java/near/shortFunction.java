package near;

import javafx.scene.control.Button;
import javafx.scene.control.TextArea;

public class shortFunction {

        public static String mySelect( TextArea w, int i1, int i2 )
        {
                w.selectRange( i1, i2 );
                return w.getSelectedText();
        }
        
        public static Button myNewButton( String text )
        {
                Button B = new Button();
                B.setText( text.replaceAll( "_", "__" ) ); /* fix bugs on show text */
                return B;
        }
        
        public static String[] initLoadText( int line )
        {
                String[] arr = new String[ line ];
                for( int i=0; i < line; i++ ) arr[ i ] = new String();
                
                return arr;
        }
}