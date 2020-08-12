package near;

import java.util.ArrayList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;

public class useSuggest extends SqlAPI {
    
        public boolean SuggestReset() { return ( suggest = new ArrayList<>() ).isEmpty(); }
        
        public Button SuggestCure( Button x )
        {
                x.setMinSize(  RightVBox.getWidth(), 30 );
                x.setPrefSize( RightVBox.getWidth(), 30 );
                x.setMaxSize(  RightVBox.getWidth(), 30 );
                
                return SuggestOnAction( x );
        }
        
        public Runnable SuggestRefreshThread() /* thread is necessary for delay ( update scrollpane ) */
        {
                Runnable exec = new Runnable()
                {
                        @Override
                        public void run()
                        { try {
                                Thread.sleep( sleepmilli1 );
                                for ( Object el : RightVBox.getChildren() )
                                {                        
                                        ( ( Button ) el ).setMinSize( scrollpane.getWidth()-40, 30 );
                                        ( ( Button ) el ).setMaxSize( scrollpane.getWidth()-40, 30 );
                                }
                        } catch ( Exception e2 ) {;}}
                };
                return exec;
        }
        
        public void SuggestLoad()
        {
                for ( Button el : suggest ) RightVBox.getChildren().add( SuggestCure( el ) );
                
                if ( !lifeSuggest && ( lifeSuggest |= true ) )
                        splitpane.getDividers().get( 0 ).positionProperty().addListener(
                                ( obsVal, oldVal, newVal ) -> { new Thread( SuggestRefreshThread() ).start(); });
        }
        
        public boolean SuggestClear()
        {
                for ( Button el : suggest ) RightVBox.getChildren().remove( el );
                return SuggestReset();
        }
        
        public Button SuggestOnAction( Button y )
        {
                y.setOnAction( new EventHandler<ActionEvent>()
                {
                        @Override
                        public void handle(ActionEvent event)
                        {
                                String fGet = y.getText().replaceAll( "__", "_" );
                                
                                if ( !find.isEmpty() )
                                {
                                        prevDEL( false, cs );
                                        insTextANDpos( write, car, cureLibs( fGet ) );
                                        nextDEL( false, cs );

                                        write.requestFocus();
                                }
                                
                                else if ( !dirs.isEmpty() )
                                {
                                        String Parent = ( x.exists() && x.isDirectory() ?
                                                          x.getPath() : x.getParent() );
                                        
                                        option.setText( Parent + '/' + fGet );
                                        option.requestFocus();
                                        option.end();
                                }
                                
                                /* salvataggio + ricarcica Bottom, oppure, ricarcica Top */
                                RightVBox.getOnMouseClicked().handle( null );
                        }
                }); return y;
        }
}