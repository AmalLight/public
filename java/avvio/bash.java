
package avvio;

import java.io.File;

public class bash {
    
    input_bash_and_read_out i = new input_bash_and_read_out();
    
    public void mvXtoY(File x, File y) throws Exception
    {
        String daX = x.getAbsolutePath();
        String daY = y.getAbsolutePath();
        i.load( "mv|||"+daX+"|||"+daY );
    }
    
    public void rmX(File x) throws Exception
    {
        String daX = x.getAbsolutePath();        
        i.load( "rm|||-r|||"+daX );
    }
    
    public void cpXtoDirY(File x, File y) throws Exception
    {
        String daX = x.getAbsolutePath();
        String daY = y.getAbsolutePath();
        i.load( "cp|||"+daX+"|||"+daY+"/" );
    }
    
    public void cpDirXtoDirY( File x, File y ) throws Exception
    {
        String daX = x.getAbsolutePath();
        String daY = y.getAbsolutePath();
        i.load( "cp|||-r|||"+daX+"|||"+daY+"/" );
    }
    
    public void syncMediaX( String X ) throws Exception
    {
        i.load( "sync|||/media/"+System.getProperty("user.name")+"/"+X+"/" );
        System.out.println( "\n\t\tsync : " + X + " ...ok" );
    }
    
    public void convertJPGto50(File x) throws Exception
    {
        String daX = x.getAbsolutePath();
        String PdaX = x.getParentFile().getParent();
        String xName = x.getName();        
        i.load( "convert|||"+ daX +"|||-quality|||50|||"+ PdaX +"/"+ 
                              xName.replaceAll(".JPG", ".jpg") );
    }

    public input_bash_and_read_out getSizeOfFileX(File x) throws Exception
    {
        String daX = x.getAbsolutePath();
        i.load( "stat|||-c|||--format=%s|||"+daX );
        return i;
    }
 
    public input_bash_and_read_out getMd5sum(File x) throws Exception
    {
        String daX = x.getAbsolutePath();
        i.load( "md5sum|||"+ daX );
        return i;
    }
    
    public void execHandbreakCli(File x, String y) throws Exception
    {
        String daX = x.getAbsolutePath();
        String PdaX = x.getParentFile().getParent();
        String xName = x.getName();        
        i.load( "handbrake-cli|||-i|||"+ daX +"|||-o|||"+ PdaX + "/"+ xName.replaceAll(y, ".m4v") +
                "|||--preset|||Very Fast 480p30" );        
    }
}