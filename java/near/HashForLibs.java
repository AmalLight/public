package near;

public class HashForLibs {
 
        static public int switchString( char x)
        {
                int i = 0;
                if ( ++i > 0 && x ==  'a' ) return i;                
                else if ( ++i > 0 && x ==  'b' ) return i;
                else if ( ++i > 0 && x ==  'c' ) return i;
                else if ( ++i > 0 && x ==  'd' ) return i;
                else if ( ++i > 0 && x ==  'e' ) return i;
                else if ( ++i > 0 && x ==  'f' ) return i;
                else if ( ++i > 0 && x ==  'g' ) return i;
                else if ( ++i > 0 && x ==  'h' ) return i;
                else if ( ++i > 0 && x ==  'i' ) return i;
                else if ( ++i > 0 && x ==  'j' ) return i;
                else if ( ++i > 0 && x ==  'k' ) return i;
                else if ( ++i > 0 && x ==  'l' ) return i;
                else if ( ++i > 0 && x ==  'm' ) return i;
                else if ( ++i > 0 && x ==  'n' ) return i;
                else if ( ++i > 0 && x ==  'o' ) return i;
                else if ( ++i > 0 && x ==  'p' ) return i;
                else if ( ++i > 0 && x ==  'q' ) return i;
                else if ( ++i > 0 && x ==  'r' ) return i;
                else if ( ++i > 0 && x ==  's' ) return i;
                else if ( ++i > 0 && x ==  't' ) return i;
                else if ( ++i > 0 && x ==  'u' ) return i;
                else if ( ++i > 0 && x ==  'v' ) return i;
                else if ( ++i > 0 && x ==  'w' ) return i;
                else if ( ++i > 0 && x ==  'x' ) return i;
                else if ( ++i > 0 && x ==  'y' ) return i;
                else if ( ++i > 0 && x ==  'z' ) return i;
                else return ++i;
        }
        
        static public int hashLibs( String el )
        {
                if ( el.isEmpty() || el.length() < 3 ) return 0;
                else
                {
                        String el2 = el.substring( 0, 3 ).toLowerCase();
                        return ( switchString( el2.toCharArray()[0] ) * 1 +
                                 switchString( el2.toCharArray()[1] ) * 2 +
                                 switchString( el2.toCharArray()[2] ) * 3 );
                }
                
                //caso 1 word : 1° sw( el[0] ), 2° sw( el[0] ), 3° sw (  )
        }
        
        static public int maxHash( ) { return ( hashLibs( "   " ) + 1 ); }
}