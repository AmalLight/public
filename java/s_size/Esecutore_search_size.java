package s_size;

import avvio.bash;
import avvio.size;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Esecutore_search_size extends avvio.struttura_cartelle
{    
    protected File posizione;
    protected int filtro=0;
    protected List<File> GetFile;
    protected bash B = new bash();
    
    public Esecutore_search_size(File F)
    {
        this.GetFile = new ArrayList<>();
        Scanner input = new Scanner(System.in);        
        System.out.println("\n\tPresentazione di file con size.");
        this.posizione = F;
        
        if (this.posizione.exists()) 
        {
            System.out.print("\t\tPrego(Inserire un filtro in megabyte, solo numeri > di 0): ");
            String tmp = input.nextLine();
            if (tmp.length()==0) tmp="0";
            this.filtro = Integer.parseInt(tmp);
            
            System.out.println("\n\tAttendere che il Caricamento sia Completato!\n");        
            this.visita1(this.posizione);       
            System.out.println();
            System.out.println();
            
            if (this.filtro>0)
            {
                int i=0;
                for (File x: GetFile)
                    System.out.println("\tid: "+i+") File: "+GetFile.get(i++).getAbsolutePath());
            }
            
            System.out.print("\t\tFinire con Invio:"); 
            new Scanner(System.in).nextLine();
        }
    }
    
    @Override
    public void run(){
        if (this.f.isFile() && (this.filtro>0))
        {
            size mega;
            try 
            {
                mega = new size( B.getSizeOfFileX( this.f ).get_one_word_from_out(1) );
                long value = mega.get_b_k_m_g('m');
                    
                if (value >= this.filtro)
                {
                    GetFile.add(this.f);
                    System.out.println("\nHo aggiunto " + this.f.getName() 
                                      +" ai file selezionati,"+ "\nSize di questo: " + value
                                      +", mio size: " + this.filtro);
                }
                else
                {
                    System.out.println("\nNon ho aggiunto " + this.f.getName()
                                      +" ai file selezionati,"+ "\nSize di questo: " + value
                                      +", mio size: " + this.filtro);
                }
            }
            catch ( Exception ex ) {;}
        }
    }
}