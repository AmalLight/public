package near;

import javafx.scene.input.Clipboard;
import javafx.scene.input.ClipboardContent;

public class MrRobot
{
        public static String copy( String input ) throws Exception
        {
                Clipboard clipboard = Clipboard.getSystemClipboard();
                ClipboardContent content = new ClipboardContent();
                content.putString( input );
                clipboard.setContent( content );
                return input;
        }
        
        public static String paste() throws Exception
        {
                try { return Clipboard.getSystemClipboard().getString(); }
                catch ( Exception e2 ) {;}
                return "";
        }    
}
