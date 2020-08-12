package near;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
// https://bitbucket.org/xerial/sqlite-jdbc/downloads

public class SqlAPI extends libsForVars
{
        public void Connect_SqlAPI() throws Exception
        {
            if ( c!=null ) c.close();
            if ( s!=null ) s.close();
            
            c = DriverManager.getConnection( "jdbc:sqlite:" + fileSAVEdb );
            c.setAutoCommit( false );
        }
        
        public void init_SqlAPI() throws Exception // nuovo save, chiudo e apro e aggiorno
        {
            Connect_SqlAPI();
            s = c.createStatement();

            try{ s.executeUpdate( "CREATE TABLE SAVE (VALUE TEXT);" ); }
            catch ( Exception e ) {;}
            
            s.executeUpdate( "DELETE FROM SAVE" ); c.commit();
        }
        
        public void insert_SqlAPI( String string ) throws Exception // insert, apro e aggiorno
        {
            s.executeUpdate( "INSERT INTO SAVE (VALUE) VALUES ('"+string+"');" );
            c.commit();
        }
        
        public List<String> select_SqlAPI( String string ) throws Exception // select, apro
        {
            ResultSet rs = s.executeQuery( "SELECT * FROM SAVE WHERE VALUE LIKE '%"+string+"%'" );
            
            List<String> list = new ArrayList<>();
            while ( rs.next() ) { list.add( rs.getString( "VALUE" ) ); }
            return list;
        }
}