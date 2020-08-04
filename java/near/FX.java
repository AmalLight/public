package near;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.SplitPane;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Circle;

public class FX {

    protected @FXML TextField option;
    protected @FXML Button Op;
    protected @FXML Button M;
    
    protected @FXML TextArea write;
    
    // Start Big VBox, H: ( 8 * 32 = 256 + 30 = 286 + 10 ) = 296.
    
    protected @FXML TextField Line;     // H: 32
    protected @FXML TextField search;   // H: 32
    protected @FXML TextField subs;     // H: 32
    protected @FXML TextField number;   // H: 32
    
    protected @FXML Button Prev;        // H: 32 + 5
    protected @FXML Button Minus;       // H: 32
    protected @FXML Button Plus;        // H: 32
    protected @FXML Button Next;        // H: 32
    
    protected @FXML Button View;        // H: 32
    protected @FXML Button clear;       // H: 32
    
    protected @FXML Button BShiftL;      // H: 32
    protected @FXML Button BShiftR;      // H: 32 + 5
    protected @FXML Button Past;         // H: 32
    
    protected @FXML Circle monitor1;     // H: 30
    protected @FXML Label Action;        // H: 30
    
    // End Big VBox
    
    protected @FXML SplitPane splitpane;            /* used for background interface */
    protected @FXML ScrollPane scrollpane;
    protected @FXML VBox RightVBox;
}
