package near;

import java.io.File;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class Main extends Application {
    
        protected Parent root;
        protected Scene scene;
        protected String url = "/home/kaumi/my_software/java/Near/img";
        protected File ico = new File( url+"/img.png" );

        @Override
        public void start( Stage stage ) throws Exception
        {
                Image img = new Image( ico.toURI().toString(), 0, 0, false, false );
                stage.getIcons().add( img );

                root = FXMLLoader.load( getClass().getResource( "Window.fxml" ) );
                scene = new Scene( root, 900, 700 );
                stage.setTitle( "More Near To All" );
                stage.setScene( scene );
                stage.show();
        }
        
        public static void main(String[] args) { Application.launch(args); }
}