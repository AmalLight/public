package avvio;

import convert_jpg.Esecutore_convert_jpg;
import convert_video.Esecutore_convert_video;
import java.io.File;
import java.util.Scanner;
import s_size.Esecutore_search_size;

public class EsecutoreProgramma {
    
    @SuppressWarnings("empty-statement")
    public static void main(String[] args) throws Exception 
    {
        Integer Scelta = 1;
        File F= null;
        try{ F= new File(args[0]); }
        catch( Exception e5 ) {;}
        
        Scanner inScanner = new Scanner(System.in);
        System.out.print("\n\t\tProgrammi:\n\n"
                + "\t1) jpg, 2) video, 3) size, 4) vack.\n"
                + "\n\t\tScegli il programma da lanciare da 1 a 4 :: ");
        
        try { Scelta = Integer.parseInt(inScanner.nextLine()); }
        catch ( Exception e2 ) { return; }
        
        if (Scelta>0 && Scelta<7)
            if (Scelta<4 && (F==null || !F.exists())) return;
            else switch (Scelta)
            {
                case 1:
                    convert_jpg.Esecutore_convert_jpg e1= new Esecutore_convert_jpg(F);
                    break;
                    
                case 2:
                    convert_video.Esecutore_convert_video e3= new Esecutore_convert_video(F);
                    break;

                case 3:
                    s_size.Esecutore_search_size e6= new Esecutore_search_size(F);
                    break;
                    
                case 4:
                    vack.Esecutore_vack exec12 =
                    new vack.Esecutore_vack();
                    exec12.start();
                    break;
            }
    }
}