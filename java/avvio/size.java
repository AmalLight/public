package avvio;

public class size {    
    private long s_byte;
    private long s_kilobyte;
    private long s_megabyte;
    private long s_gigabyte;
    
    public long get_b_k_m_g(char scelta) {
        switch (scelta) {
            case 'b': return s_byte;
            case 'k': return s_kilobyte;
            case 'm': return s_megabyte;
            case 'g': return s_gigabyte;
            default: return 0;
        }
    }
    
    // precondiction: "stat -c --format=%y"
    public size(String stat_y) {
        s_byte= s_kilobyte= s_megabyte= 0;
        String tmp = "";        
        for (int i=9; i<stat_y.toCharArray().length; i++) tmp+=stat_y.toCharArray()[i];        
        s_byte= Long.parseLong(tmp); s_kilobyte= s_byte/1024;        
        s_megabyte= s_kilobyte/1000; s_gigabyte= s_megabyte/1000;
    }    
}