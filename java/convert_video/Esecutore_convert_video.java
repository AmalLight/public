package convert_video;

import avvio.bash;
import avvio.input_bash_and_read_out;
import avvio.size;
import java.io.File;
import java.util.Scanner;

public class Esecutore_convert_video extends avvio.struttura_cartelle
{
    protected File posizione;
    protected int filtro_video=0;
    protected Integer[] load_info;
    protected bash B = new bash();

    @SuppressWarnings("empty-statement")
    public Esecutore_convert_video(File F)
    {
        System.out.println("\n\t# (Precondition: Handbreake version >= 1.0.7_(x86_64)).");
        System.out.println("\t# (Precondition2: No doppie estensioni nei file,\n"
                + "\t\ttipo: nome_file.mp4.mp4).");
        System.out.println("\n\tConversione di tutti i file video,\n"
                + "\t# (di una cartella con il rispettivo size >= size_in_input).");

        Scanner input = new Scanner(System.in);
        this.load_info = new Integer[4];
        this.load_info[0] = 0; this.load_info[1] = 0;
        this.load_info[2] = 0; this.load_info[3] = 0;
        this.posizione = F;
        
        if (this.posizione.exists()) 
        {            
            System.out.print("\t\tPrego(Inserire un filtro in megabyte, solo numeri >= di 0): ");
            String tmp = input.nextLine();
            if (tmp.length()==0) tmp="0";
            this.filtro_video = Integer.parseInt(tmp);
            
            System.out.println("\n\tAttendere che il Caricamento sia Completato!\n");        
            this.visita1(posizione);
            System.out.println();
            System.out.println();
            System.out.println("File con size adatta: " + load_info[0] + "\n"
                             + "File con size adatta, ma non è un video: " + load_info[1] + "\n"
                             + "File con size non adatta: " + load_info[2] + "\n"
                             + "File convertiti: " + load_info[3] + "\n");
            System.out.println(); 
            System.out.print("\t\tFinire con Invio:"); 
            new Scanner(System.in).nextLine();
        }
    }
    
    @Override
    public void run()
    {
        if (filtro_video>0)
        {
            input_bash_and_read_out contatto1;
            try
            {
                contatto1 = B.getSizeOfFileX(this.f);
                size tmp; tmp = new size(contatto1.get_one_word_from_out(1));
                
                if (tmp.get_b_k_m_g('m') >= filtro_video)
                {
                    System.out.println();
                    System.out.println("Trovato file con size >= size_in_input..");    
                    load_info[0] += 1;                    
                    if (this.f.getAbsolutePath().contains(".mp4")) HandbrakeVideo(".mp4");
                    else if (this.f.getAbsolutePath().contains(".flv")) HandbrakeVideo(".flv");
                    else if (this.f.getAbsolutePath().contains(".m4v")) HandbrakeVideo(".m4v");
                    else if (this.f.getAbsolutePath().contains(".mkv")) HandbrakeVideo(".mkv");
                    else if (this.f.getAbsolutePath().contains(".avi")) HandbrakeVideo(".avi");
                    else if (this.f.getAbsolutePath().contains(".webm"))HandbrakeVideo(".webm");
                    else {System.out.println("..Ma il file non è un video."); load_info[1] += 1;}
                }
                else {System.out.println("File con size < size_in_input.");load_info[2] += 1;}
            
            } catch ( Exception ex ) {;}
        }
    }
    
    public void HandbrakeVideo(String x) throws Exception
    {
        System.out.println("..Ho Verificato che il file è un video "+x);
        System.out.println("Sto Convertendo, attendere.");
        
        B.execHandbreakCli(this.f, x);
        System.out.println("Ho quasi convertito il video!");        
        B.rmX(this.f);

        File pp= this.f.getParentFile().getParentFile();
        String pps= pp.getAbsolutePath();
        B.mvXtoY( new File( pps+"/"+this.f.getName().replaceAll(x, ".m4v")),
                                    this.f.getParentFile());
        
        System.out.println("Ho Convertito il video!"); load_info[3] += 1;
    }
}