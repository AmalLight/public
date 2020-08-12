package near;

import java.io.File;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import javafx.scene.control.Button;

public class Vars extends FX
{
        protected String cs   = "\\ | ! \" $ % & / ( ) = ? \' ` ~ [ ] { } + * @ # < > , ; . : - \n \t";
        protected String aTab = "    ";         /* you can't change this */
        protected String bTab = "\r\r\r\r";     /* you can't change this */
        protected String last = "";             /* you can't change this */

        protected int car    = 0;               /* you can't change this */
        protected int ll     = 0;               /* you can't change this */
        
        protected List<String> find      = new ArrayList<>();   /* you can't change this */
        protected List<String> dirs      = new ArrayList<>();
        protected List<Button> suggest   = new ArrayList<>();
        
        protected File x = null;                                /* you can't change this */
        
        protected Double scrollTop  = 0.0;
        protected Double scrollLeft = 0.0;

        protected String match = "";                           /* you can't change this */
        protected Integer index = (-1);                        /* you don't change this */
        
        protected String Select = "";
        protected String Paste  = "";
        protected boolean EvidenceMouse = false;
        
        // -------------------------------------------------------------------------------------------
        /* Struct Plane for Archive libs and OldWrite */
                
        protected int maxHistory = 10; /* Low cost for few memory */
        protected int freeH = -1;
        protected History H[] = new History[ maxHistory ];
        
        /* Thread autoCompleteBottom */
        protected Thread importFILE = null;
        protected boolean lifeFile = false;
        
        /* Thread monitorRobot */
        protected boolean onWork   = false; /* running: if OnWork => ( done = false ) */
        protected boolean done     = true;  /* you don't change this */
        
        /* For Threads */
        protected int sleepmilli1 = 500, sleepmilli2 = 2000;
        
        // -------------------------------------------------------------------------------------------
        // pseudo Robot for suggest >> for RightVBox:
        boolean lifeSuggest = false;
        
        // -------------------------------------------------------------------------------------------
        // Help users:
        String Help = "\n    Welcome, This is my Private Ide for Any Language of Programming that you know:"
                    + "\n    My Names are: Kaumi, Samir, Mohammad, Emanuele, chose you once for talk with Me."
                    + "\n    My number of cell is 338 362 3465, my email address is ilovenewblood@gmail.com"
                    + "\n"
                    + "\n    For autocomplete option, make you a x.near File, x is a name that you have chosen."
                    + "\n    This ide will be save your work every 1 second, so attention!!"
                    + "\n    ByeBye, Good Job"
                    + "\n"
                    + "\n    Please contact me for any Question you have, thx ^..^ ..."
                    + "\n,";
        
        //--------------------------------------------------------------------------------------------
        // SqlAPI:
        String fileSAVEdb = "/home/kaumi/my_software/java/Near/src/database.db";
        Connection c; Statement s;
}