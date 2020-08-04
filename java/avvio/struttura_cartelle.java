package avvio;
import java.io.File;

public class struttura_cartelle implements Runnable{
    protected File f=null;
    
    public void visita1(File x)
    { 
        if (!x.isHidden()){
            f=x;
            this.run();
            if (x.isDirectory())
                for (File y : x.listFiles())
                    visita1(y);
        }
    }
    
    @Override public void run() {;}
}