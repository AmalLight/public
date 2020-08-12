package convert_jpg;

import avvio.*;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Esecutore_convert_jpg extends avvio.struttura_cartelle
{
    protected File posizione;
    protected List<File> GetFile;
    protected bash B= new bash();

    public Esecutore_convert_jpg(File F)
    {
        this.GetFile= new ArrayList<>();
        Scanner input = new Scanner( System.in );
        System.out.println( "\n\tConversione immagini .JPG in immagini .jpg a minor qualità." );
        this.posizione = F;

        if ( this.posizione.exists() )
        {
            System.out.println( "\n\tAttendere che il Caricamento sia Completato!\n" );
            this.visita1(posizione);
            System.out.println();
            System.out.println();            
            int i=0;
            for (File x: GetFile)
                System.out.println( "\tid: "+i+") File: "+GetFile.get(i++).getAbsolutePath() );
            System.out.print( "\t\tFinire con Invio:" );
            new Scanner(System.in).nextLine();
        }
    }

    public void run()
    {
        if (this.f.isFile() && this.f.getAbsolutePath().contains(".JPG")) 
        {
            size tmp;   
            try
            {
                tmp = new size( B.getSizeOfFileX( this.f ).get_one_word_from_out(1) );
                
                if ( tmp.get_b_k_m_g( 'm' ) >= 2 )
                {
                    GetFile.add(this.f);
                    System.out.println("\n\tsize is ok");   

                    B.convertJPGto50(this.f); B.rmX(this.f);
                    
                    File pp= this.f.getParentFile().getParentFile();
                    String pps= pp.getAbsolutePath();
                    B.mvXtoY(new File( pps+"/"+this.f.getName().replaceAll(".JPG", ".jpg") ),this.f.getParentFile() );
                }                
                else System.out.println("\n\tsize over short.");
            }
            catch ( Exception ex ) {;}
        }
    }
}