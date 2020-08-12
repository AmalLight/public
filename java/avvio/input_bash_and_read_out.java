package avvio;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public final class input_bash_and_read_out {    
    private List<String> commands;
    private Process nuovo_processo;
    private List<String> collect_out;
    
    public String get_one_word_from_out(int iwantReadThis)
    {
        List<String> collect_Words = new ArrayList<>();
        for ( String string : collect_out ) collect_Words.addAll( Arrays.asList(string.split(" ")) );
        if ( iwantReadThis <= collect_Words.size() ) return collect_Words.get( iwantReadThis-1 );
        else return null;
    }
    
    public List<String> my_split_function(String input)
    {
        String comando="";
        List<String> da_ritorno = new ArrayList<>();
        for ( String string : input.split("\\|\\|\\|") )
            { da_ritorno.add(string); comando+=" "+string; }
        System.out.println("Eseguo: "+comando);
        return da_ritorno;
    }
    
    public input_bash_and_read_out()
    {       
        commands = null;
        commands = new ArrayList<>();
    }
    
    public void load( String input ) throws Exception
    {
            commands = null;
            commands = new ArrayList<>();
            
            if ( !input.isEmpty() )
            {
                    commands = my_split_function(input);
                    nuovo_processo = new ProcessBuilder(commands).start();

                    InputStream lettore = nuovo_processo.getInputStream();
                    BufferedReader buffer_lettore = new BufferedReader(new InputStreamReader(lettore));

                    String line;
                    collect_out = new ArrayList<>();
                    while ( (line = buffer_lettore.readLine()) != null ) collect_out.add(line);
            }
    }
}