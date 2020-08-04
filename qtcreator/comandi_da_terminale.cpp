#include "comandi_da_terminale.h"
#include <iostream>
using namespace std;

comandi_da_terminale::comandi_da_terminale(QObject *parent) : QObject(parent)
{
    this->freccia_su = false;
    this->freccia_giu = false;

    this->pausa = new QTimer();
    this->lista_help = new mylistQString();
    this->save_text_change = "";
    this->automap = false;
    this->open_world_on = false;
    this->libroDegliIncantesimi = new mylistQString();

    this->stanze_visitate = new mylistQString;
    this->stanze_visitate->add("1");
    this->play_game.start();
    this->cronologia = "";
}

QTimer*& comandi_da_terminale::getTimer()
{
    return this->pausa;
}

void comandi_da_terminale::elaborazione_comando_dal_terminale
(dati_Globali_di_gioco *&DatiDiGioco, managerMusic *&ManagerMusic,
 QString &Terminale1, QString &Terminale2,
 QString QLineEdit, Ui::MainWindow *&Ui)
{
    Ui->input->setDisabled(true);

    //da 0 a 1
    if ((QLineEdit == "help()")
     && (DatiDiGioco->getStatus() != 2)
     && (DatiDiGioco->getStatus() != 3))
    {
        Ui->input->setDisabled(true);

        if (DatiDiGioco->getStatus() == 0)
        {
            this->setHelp();
            this->save_text_change = "help()";
            DatiDiGioco->setStatus(1);
            this->autocomplete(DatiDiGioco, Ui);
            Ui->out3->append("Auto-Complete abilitato, per i caratteri dal 2° in poi(in una parola);");
        }

        this->lista_help->view(Terminale2, Ui);
        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");

        Ui->input->setDisabled(false);
    }

    //da 1 a 2 e poi 3
    else if ((QLineEdit == "go()") && (DatiDiGioco->getStatus() == 1))
    {
        Ui->input->setDisabled(true);

        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
        this->lista_help->remove("go() //inizia il gioco;");
        this->lista_help->remove("presentazione() //ripresentazione del gioco;");
        this->lista_help->add("move(up) //muoviti per andare in alto, nella stanza;");
        this->lista_help->add("move(down) //muoviti per andare in basso, nella stanza;");
        this->lista_help->add("move(left) //muoviti per andare a sinistra, nella stanza;");
        this->lista_help->add("move(right) //muoviti per andare a destra, nella stanza;");
        DatiDiGioco->setStatus(2);

        DatiDiGioco->getLivelli()->add_liv();
        DatiDiGioco->getLivelli()->getMappeIT1()->getI1()
                ->sendMapToTextBrowser1(Terminale1, Ui);

        this->prima_fase_finita();

        Ui->input->setDisabled(false);
    }

    else if (((QLineEdit == "move(up)")
            ||(QLineEdit == "move(right)")
            ||(QLineEdit == "move(down)")
            ||(QLineEdit == "move(left)")
            ||(QLineEdit == "move(center)"))
            &&(DatiDiGioco->getStatus() > 3))
    {
        Ui->input->setDisabled(true);

        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
        string tmp_string = QLineEdit.toStdString();
        QString tmp_string2;

        int i=0;
        for (; i<tmp_string.length(); i++)
            if (tmp_string[i] == '(') break;

        i += 1;
        for (; tmp_string[i] != ')'; i++)
            tmp_string2 += tmp_string[i];

        DatiDiGioco->getLivelli()->getMappeIT1()->
                getI1()->move(tmp_string2,
                              DatiDiGioco->getLivelli()->
                              getMappeIT1()->getSimboloPg1(),
                              Terminale1, Ui);

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "clear(top)") && (DatiDiGioco->getStatus() > 0)
             && (DatiDiGioco->getStatus() != 2)
             && (DatiDiGioco->getStatus() != 3))
    {
        Ui->input->setDisabled(true);

        Ui->out3->setText("");
        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "clear(right)") && (DatiDiGioco->getStatus() > 0)
             && (DatiDiGioco->getStatus() != 2)
             && (DatiDiGioco->getStatus() != 3))
    {
        Ui->input->setDisabled(true);

        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
        Terminale2 = "";
        Ui->out2->setText(Terminale2);

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "list(music)") && (DatiDiGioco->getStatus() > 0)
             && (DatiDiGioco->getStatus() != 2)
             && (DatiDiGioco->getStatus() != 3))
    {
        Ui->input->setDisabled(true);

        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
        ManagerMusic->getMyList()->view(Terminale2);
        Ui->out2->setText(Terminale2);

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "exit()") && (DatiDiGioco->getStatus() > 0)
             && (DatiDiGioco->getStatus() != 2)
             && (DatiDiGioco->getStatus() != 3))
    {
        Ui->input->setDisabled(true);

        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
        this->IWantExit(Ui, ManagerMusic);

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "map()") && (DatiDiGioco->getStatus() > 3))
    {
        Ui->input->setDisabled(true);
        this->map(DatiDiGioco, Terminale2, QLineEdit, Ui);
        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "status()") && (DatiDiGioco->getStatus() > 3))
    {
        Ui->input->setDisabled(true);
        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
        this->status(Terminale2, Ui, DatiDiGioco, QLineEdit);
        Ui->input->setDisabled(false);
    }

    //da 3 a 4
    else if ((QLineEdit == "pg(m)") && (DatiDiGioco->getStatus() == 3))
    {
        Ui->input->setDisabled(true);

        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");

        DatiDiGioco->getLivelli()->getMappeIT1()->setSimboloPg1("☻");
        DatiDiGioco->getLivelli()->getMappeIT1()->getTesta()->setSimboloPg1("☻");
        DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->setEmpty(3, 8);

        DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->setPlayer(
                    DatiDiGioco->getLivelli()->getMappeIT1()->getSimboloPg1(), 3, 8);
        DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->sendMapToTextBrowser1(Terminale1, Ui);
        Ui->out3->append("scelta dell'avatar .. di genere maschile, scelta accettata;");
        DatiDiGioco->setStatus(4);

        Terminale2 = "\nscelta dell'avatar  .. di genere maschile, scelta accettata.";
        Ui->out2->setText(Terminale2);

        this->conclusione_per_il_pg_scelto(Terminale1, DatiDiGioco, Ui);

        Ui->input->setDisabled(false);
    }

    //da 3 a 4
    else if ((QLineEdit == "pg(f)") && (DatiDiGioco->getStatus() == 3))
    {
        Ui->input->setDisabled(true);

        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");

        DatiDiGioco->getLivelli()->getMappeIT1()->setSimboloPg1("☺");
        DatiDiGioco->getLivelli()->getMappeIT1()->getTesta()->setSimboloPg1("☺");
        DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->setEmpty(3, 8);

        DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->setPlayer(
                    DatiDiGioco->getLivelli()->getMappeIT1()->getSimboloPg1(), 3, 8);
        DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->sendMapToTextBrowser1(Terminale1, Ui);
        Ui->out3->append("scelta dell'avatar  .. di genere femminile, scelta accettata;");
        DatiDiGioco->setStatus(4);

        Terminale2 = "\nscelta dell'avatar  .. di genere femminile, scelta accettata.";
        Ui->out2->setText(Terminale2);

        this->conclusione_per_il_pg_scelto(Terminale1, DatiDiGioco, Ui);

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "open(door)") && (DatiDiGioco->getStatus() > 3))
    {
        Ui->input->setDisabled(true);

        if (DatiDiGioco->getLivelli()->getMappeIT1()->get_puoi_entrare_in_una_porta())
        {
            DatiDiGioco->getLivelli()->getMappeIT1()->set_puoi_entrare_in_unLivello(false);

            int x = DatiDiGioco->getLivelli()->getMappeIT1()->getP1X();
            int y = DatiDiGioco->getLivelli()->getMappeIT1()->getP1Y();
            mylistQStringMaps *main = DatiDiGioco->getLivelli()->getMappeIT1();
            int arrivoX, arrivoY;

            //if ((this->p1_x == 3) && (this->p1_y == 8))
            if ((x == 3) && (y == 8))
            {
                if ((main->getI1()->getLeft()->getIndex() >
                     main->getI1()->getIndex()+1)
                   && (DatiDiGioco->getNEXT() == false))
                {
                    Ui->input->setText("non puoi");
                    Ui->input->setDisabled(false);
                    return;
                }

                else if
                   ((main->getI1()->getLeft()->getIndex() <
                     main->getI1()->getIndex())
                   && (DatiDiGioco->getBACK() == false))
                {
                    Ui->input->setText("non puoi");
                    Ui->input->setDisabled(false);
                    return;
                }

                arrivoX = main->getLunghezza()-4;
                arrivoY = 8;

                main->setI1(main->getI1()->getLeft());
            }

            //else if ((this->p1_x == this->lunghezza-4) && (this->p1_y == 8))
            else if ((x == main->getLunghezza()-4) && (y == 8))
            {
                if ((main->getI1()->getRight()->getIndex() >
                     main->getI1()->getIndex()+1)
                   && (DatiDiGioco->getNEXT() == false))
                {
                    Ui->input->setText("non puoi");
                    Ui->input->setDisabled(false);
                    return;
                }

                else if
                   ((main->getI1()->getRight()->getIndex() <
                     main->getI1()->getIndex())
                   && (DatiDiGioco->getBACK() == false))
                {
                    Ui->input->setText("non puoi");
                    Ui->input->setDisabled(false);
                    return;
                }

                arrivoX = 3;
                arrivoY = 8;

                main->setI1(main->getI1()->getRight());
            }

            //else if ((this->p1_x == 12) && (this->p1_y == 2))
            else if ((x == 12) && (y == 2))
            {
                if ((main->getI1()->getUp()->getIndex() >
                     main->getI1()->getIndex()+1)
                   && (DatiDiGioco->getNEXT() == false))
                {
                    Ui->input->setText("non puoi");
                    Ui->input->setDisabled(false);
                    return;
                }

                else if
                   ((main->getI1()->getUp()->getIndex() <
                     main->getI1()->getIndex())
                   && (DatiDiGioco->getBACK() == false))
                {
                    Ui->input->setText("non puoi");
                    Ui->input->setDisabled(false);
                    return;
                }

                arrivoX = 12;
                arrivoY = main->getAltezza()-3;

                main->setI1(main->getI1()->getUp());
            }

            //else if ((this->p1_x == 12) && (this->p1_y == this->altezza-3))
            else if ((x == 12) && (y == main->getAltezza()-3))
            {
                if ((main->getI1()->getDown()->getIndex() >
                     main->getI1()->getIndex()+1)
                   && (DatiDiGioco->getNEXT() == false))
                {
                    Ui->input->setText("non puoi");
                    Ui->input->setDisabled(false);
                    return;
                }

                else if
                   ((main->getI1()->getDown()->getIndex() <
                     main->getI1()->getIndex())
                   && (DatiDiGioco->getBACK() == false))
                {
                    Ui->input->setText("non puoi");
                    Ui->input->setDisabled(false);
                    return;
                }

                arrivoX = 12;
                arrivoY = 2;

                main->setI1(main->getI1()->getDown());
            }

            //debug this->main->p1_x, this->main->p1_y <-- setPlayerToNewRoom
            main->getI1()->setPlayer(main->getSimboloPg1(), arrivoX, arrivoY);

            emit this->emitIstampMAPx(main->getI1());

            main->getI1()->sendMapToTextBrowser1(Terminale1, Ui);

            if (!this->stanze_visitate->IfxExistInList
                    (QString::number(DatiDiGioco->getLivelli()->
                                     getMappeIT1()->getI1()->getIndex())))

                this->stanze_visitate->add
                    (QString::number(DatiDiGioco->getLivelli()->
                                     getMappeIT1()->getI1()->getIndex()));

            Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
            Ui->out3->append("porta aperta;");

            if (this->automap == true)
                this->map(DatiDiGioco, Terminale2, QLineEdit, Ui);

            //disgrazia
            //--------------------------------------------------------------
            if (
                    (main->getI1()->getIndex() > 1)
              &&
                    (
                        ((main->getI1()->getUp() == nullptr)
                      || (main->getI1()->getUp()->getIndex()
                        < main->getI1()->getIndex()))
                  &&
                        ((main->getI1()->getRight() == nullptr)
                      || (main->getI1()->getRight()->getIndex()
                        < main->getI1()->getIndex()))
                  &&
                        ((main->getI1()->getDown() == nullptr)
                      || (main->getI1()->getDown()->getIndex()
                        < main->getI1()->getIndex()))
                  &&
                        ((main->getI1()->getLeft() == nullptr)
                      || (main->getI1()->getLeft()->getIndex()
                        < main->getI1()->getIndex()))
                    )
             &&
                    (main->getI1() != main->getMain()->getCoda())
               )
            {
                Ui->input->setText("disgrazia");
                DatiDiGioco->setATTp1(1);
                DatiDiGioco->setMyPa(1);
                DatiDiGioco->setHPp1(1);

                if (DatiDiGioco->getBACK() == false)
                {
                    Terminale2 = "";
                    Terminale2 += "\n\n"
                                  "Ti, trovi in una stanza che é sprovvista di collegamenti ad altre stanze,\n"
                                  "che siano con numero stanza, maggiore a quella in cui ti trovi attualmente.\n"
                                  "Pertanto non avendo mai comprato un 'buy(BACK)'...\n"
                                  "...non puoi tornare indietro. Hai perso il gioco,";

                    Ui->out2->setText(Terminale2);
                    this->IWantExit(Ui, ManagerMusic);
                }
            }
        }

        else {

            Ui->out3->append("nessuna porta da aprire");
            Ui->input->setText("nessuna porta da aprire");
        }

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "open(level)") && (DatiDiGioco->getStatus() > 3))
    {
        Ui->input->setDisabled(true);

        if ((DatiDiGioco->getLivelli()->getMappeIT1()->getI1() == DatiDiGioco->getLivelli()->getMappeIT1()->getMain()->getCoda())
           && (DatiDiGioco->getLivelli()->getIteratore1()->getUscita() != nullptr)
           || ((DatiDiGioco->getLivelli()->getMappeIT1()->getI1() == DatiDiGioco->getLivelli()->getMappeIT1()->getMain()->getTesta())
           && (DatiDiGioco->getLivelli()->getIteratore1()->getEntrata() != nullptr)))
        {   
            if ((DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->getP1X() == 12)
               && (DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->getP1Y() == 8))
            {
                this->stanze_visitate->deleteLater();
                this->stanze_visitate = nullptr;
                this->stanze_visitate = new mylistQString;

                if (DatiDiGioco->getLivelli()->getMappeIT1()->getI1() ==
                        DatiDiGioco->getLivelli()->getMappeIT1()->getMain()->getCoda())
                {
                    if (DatiDiGioco->getLivelli()->getIteratore1()->getUscita()->get_index_livello() >
                            DatiDiGioco->getLivelli()->getIteratore2()->get_index_livello())
                        DatiDiGioco->getLivelli()->setIteratore2(DatiDiGioco->getLivelli()->getIteratore1()->getUscita());

                    DatiDiGioco->getLivelli()->setIteratore1(DatiDiGioco->getLivelli()->getIteratore1()->getUscita());
                    this->stanze_visitate->add("1");

                    DatiDiGioco->getLivelli()->getMappeIT1()->setI1(DatiDiGioco->getLivelli()->getMappeIT1()->getMain()->getTesta());

                    DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->setEmpty(3, 8);

                    DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->setPlayer(DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->getSimboloPg1(), 12, 8);
                    DatiDiGioco->getLivelli()->getMappeIT1()->set_puoi_entrare_in_unLivello(true);
                    DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->sendMapToTextBrowser1(Terminale1, Ui);
                }

                else if (DatiDiGioco->getLivelli()->getMappeIT1()->getI1() ==
                         DatiDiGioco->getLivelli()->getMappeIT1()->getMain()->getTesta())
                {
                    if (DatiDiGioco->getLivelli()->getIteratore1()->getEntrata()->get_index_livello() >
                            DatiDiGioco->getLivelli()->getIteratore2()->get_index_livello())
                        DatiDiGioco->getLivelli()->setIteratore2(DatiDiGioco->getLivelli()->getIteratore1()->getEntrata());

                    DatiDiGioco->getLivelli()->setIteratore1(DatiDiGioco->getLivelli()->getIteratore1()->getEntrata());
                    this->meta(DatiDiGioco, QLineEdit, Ui, Terminale2);

                    DatiDiGioco->getLivelli()->getMappeIT1()->setI1(DatiDiGioco->getLivelli()->getMappeIT1()->getMain()->getCoda());

                    DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->setEmpty(3, 8);

                    DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->setPlayer(DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->getSimboloPg1(), 12, 8);
                    DatiDiGioco->getLivelli()->getMappeIT1()->set_puoi_entrare_in_unLivello(true);
                    DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->sendMapToTextBrowser1(Terminale1, Ui);
                }

                Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
                Ui->out3->append("scale usate;");

                if (this->automap == true)
                    this->map(DatiDiGioco, Terminale2, QLineEdit, Ui);
            }

            else
            {
                Ui->out3->append("errore, posizione xy non adatta");
                Ui->input->setText("errore, posizione xy non adatta");
                Ui->input->setDisabled(false);
                return;
            }
        }

        else
        {
            Ui->out3->append("nessun livello da raggiungere con questa mappa");
            Ui->input->setText("nessun livello da raggiungere con questa mappa");
        }

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "open(world)") && (DatiDiGioco->getStatus() > 3))
    {
        Ui->input->setDisabled(true);

        QTime dieTime = QTime::currentTime().addMSecs(500);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );

        if (open_world_on == false)
        {
            Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");

            int tmp_index_livello =
                    DatiDiGioco->getLivelli()->getCoda()->
                    get_index_livello();

            DatiDiGioco->getLivelli()->getCoda()->
                    set_index_livello(999);

            DatiDiGioco->getLivelli()->getCoda()->
                    getMappe()->getCoda()->setPlayer
                    (DatiDiGioco->getLivelli()->getTesta()->
                     getMappe()->getSimboloScala(), 12, 8);

            DatiDiGioco->getLivelli()->add_liv();

            DatiDiGioco->getLivelli()->getCoda()->
                    getMappe()->getTesta()->setPlayer
                    (DatiDiGioco->getLivelli()->getTesta()->
                     getMappe()->getSimboloScala(), 12, 8);

            DatiDiGioco->getLivelli()->getCoda()->getEntrata()->
                    set_index_livello(tmp_index_livello);

            DatiDiGioco->getLivelli()->getMappeIT1()->
                    getI1()->sendMapToTextBrowser1(Terminale1, Ui);

            this->open_world_on = true;

            Ui->input->setText
                    ("Nuovo livello 'open world' creato");
        }

        else
        {
            Ui->out3->append
                    ("Comando Valido, ma non posso eseguire "
                     + QLineEdit + " causa: già usato!;");

            Ui->input->setText
                    ("Comando Non Valido, cancellare e reinserire");
        }

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "new(level)") && (DatiDiGioco->getStatus() > 3))
    {
        Ui->input->setDisabled(true);

        int x, y = 0;
        DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->identify
                (DatiDiGioco->getLivelli()->
                 getMain()->getTesta()->
                 getMappe()->getSimboloScala(), x, y);

        if ((DatiDiGioco->getLivelli()->getMappeIT1()->getI1() ==
             DatiDiGioco->getLivelli()->getMappeIT1()->getMain()->getCoda())
           && ((x == 0) && (y == 0)))
        {
            DatiDiGioco->getLivelli()->add_liv();
            DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->sendMapToTextBrowser1(Terminale1, Ui);

            Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
            Ui->out3->append("nuovo livello creato;");
            Ui->input->setText("nuovo livello creato");
        }

        else {

            Ui->out3->append("errore, impossibile creare un nuovo livello;");
            Ui->input->setText("non puoi creare un nuovo livello");
        }

        Ui->input->setDisabled(false);
    }

    else if ((DatiDiGioco->getStatus() > 3)
             && (QLineEdit.toStdString()[0] == 'i' )
             && (QLineEdit.toStdString()[1] == 'n' )
             && (QLineEdit.toStdString()[2] == 'f' )
             && (QLineEdit.toStdString()[3] == 'o' )
             && (QLineEdit.toStdString()[4] == '(' ))
    {
        Ui->input->setDisabled(true);

        QString tmp_Empty = "";

        for (int i = 5; i < QLineEdit.length(); i++) {

            if (QLineEdit.toStdString()[i] == ')') break;
            else tmp_Empty += QLineEdit.toStdString()[i];
        }

        int for_switch = tmp_Empty.toInt();
        if ((for_switch > 0) && (for_switch < 9))
        {
            Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");

            switch (for_switch)
            {

            case (1):
                Terminale2 = "\nSe ti trovi sul QLineEdit e premi 'LA FRECCIA_DIREZIONALE_UP DELLA TUA TASTIERA',\n"
                             "puoi richiamare comandi a partire dal comando corretto scritto in precedenza.\n"
                             "\nSe ti trovi sul QLineEdit e premi 'LA FRECCIA_DIREZIONALE_DOWN DELLA TUA TASTIERA',\n"
                             "puoi richiamare comandi a partire dal primo comando corretto.\n"
                             "\nConsidera che i comandi corretti sono messi in una lista circolare,\n"
                             "quindi prima o poi ricapiterai sullo stesso comando.";
            break;
            case (2):
                Terminale2 = "\nSe ti trovi al di fuori del QLineEdit o è disabilitata e premi 'IL_TASTO_K' della tua tastiera,\n"
                             "puoi mettere in pausa la musica.\n"
                             "\nSe ti trovi al di fuori del QLineEdit o è disabilitata e premi 'IL_TASTO_N' della tua tastiera,\n"
                             "puoi andare a sentire la prossima canzone.\n"
                             "\nSe ti trovi al di fuori del QLineEdit o è disabilitata e premi 'IL_TASTO_P' della tua tastiera,\n"
                             "puoi andare a sentire la precedente canzone.\n"
                             "\nConsidera che le canzoni sono messe in una lista circolare,\n"
                             "quindi prima o poi ricapiterai sulla stessa canzone.\n"
                             "\nSe ti trovi al di fuori del QLineEdit o è disabilitata e premi 'IL_TASTO_T' della tua tastiera,\n"
                             "puoi rientrarci; automaticamente e ti verrà selezionato tutto il testo, così da poterlo cancellare.";
            break;
            case (3):
                Terminale2 = "\nSe ti trovi sul QLineEdit e sei alla fine di un livello,\n"
                             "scrivi new(level) per creare un nuovo livello!";
            break;
            case (4):
                Terminale2 = "\nCon il comando getTarget() si otterranno informazioni riguardanti il punteggio voluto dal gioco (il target).\n"
                             "\nIn oltre verranno mostrati i punti attualmente totalizzati, e i restanti punti da totalizzare.\n"
                             "\nCon il comando map() si ottiene la mappa di gioco con debita notazione sulla posizione attuale.\n"
                             "\nCon il comando automap(1) si richiede al programma di stampare la mappa di gioco a ogni cambio di stanza o di livello.\n"
                             "\nIl comando automap(0) annulla tale cambiamento.";
            break;
            case (5):
                Terminale2 = "\nNote sui mob: '◉' questi simboli sono visibili solo nelle stanze che non sono ne la prima, ne l'ultima ne sono stanze isolate.\n"
                             "I mob sono gli antagonisti del gioco, sono stati introdotti per attaccare e togliere vita al giocatore umano,\n"
                             "ed hanno un proprio livello ATT(attacco) e un proprio livello di HP(vita) che aumenta gradualmente.\n"
                             "Il giocatore può scontrarsi con loro e quindi proseguire nel gioco, quando con un move(..) (dove .. è una direzione) si imbatte in esso.\n"
                             "Una volta agganciato il mob sul proprio percorso inizia lo scontro e automaticamente a turno e in autonomia i 2 combattenti si attaccano.\n"
                             "Il mob ha attacco e HP pari al numero della stanza in cui si trova, infatti anche il suo livello è considerato in base a questo criterio.\n"
                             "Un mob ingaggiato in combattimento alla stanza 142 avrà attacco e HP e livello pari a 142.\n\n"

                             "*Nota1: Ricorda che se i tuoi HP scendono a 0 o a meno di 0, perdi la partita!\n"
                             "*Nota2: Non è possibile fuggire, interrompere o mettere in pausa un combattimento.\n"
                             "*Nota3: Contrariamente al giocatore umano, il mob può anche scegliere di non muoversi nel suo turno.\n"
                             "*Nota4: il combattimento termina quando uno dei due (mob o giocatore umano), ha HP <= 0.\n"

                             "\nUna volta ucciso il mob controllato dal PC guadagni una ricompensa in soldi pari a 1+1+1+1 + (livello_mob * 2).\n"
                             "Questa ricompensa è spendibile dall'NPC in tutte le stanze in cui è presente, vedi 'info(6)'.\n"
                             "Notare che quando un mob viene sconfitto non scompare ma resta attivo,\n"
                             "il giocatore umano invece viene posto al centro dell'attuale stanza.\n"

                             "\nCon il comando 'status()' ottieni la stampa a video dei dati riguardanti:\n"
                             "vita, massima_vita, attacco, difesa, PA, target, soldi, numero_del_livello, numero_della_stanza, HP_del_mob e attacco_del_mob.\n"
                             "Il comando 'status()' mostra la difesa in 2 varianti separate tra loro col simbolo '|'.\n"
                             "La prima è il valore difensivo collezionato, la seconda è la protezione reale che offre,\n"
                             "difesa/10 è la reale protezione offerta."
                             "Il comando 'status()' mostra l'attacco in 2 varianti separate tra loro col simbolo '|'.\n"
                             "La prima è il valore d'attacco collezionato, la seconda è il danno effettivo che effettua,\n"
                             "attacco/10 è l'effettivo danno effettuato.";
            break;
            case (6):
                Terminale2 = "\nL'NPC '☯', può vendere diverse cose in cambio di soldi virtuali."
                             "\nL'NPC può vendere solo quando è presente nella tua stessa stanza e non è coperto dal giocatore umano."
                             "\nEsso può vendere tali cose:\n\n"

                             "\tbuy(DEF:x), aggiunge difesa, costo intero x, ottieni x;\n"
                             "\tbuy(ATT::x), aggiunge attacco, costo intero x, ottieni x;\n"
                             "\tbuy(HP:x), recupero vita, costo intero x, ottieni x;\n"
                             "\tbuy(PA:x), aggiunge punti azione, costo intero x, ottieni x;\n"
                             "\tbuy(MAX:x), aggiunge x al massimo dei punti vita, costo intero x, ottieni x;\n"
                             "\tbuy(ELISIR:100), aggiunge al massimo dei punti vita, costo intero 100, ottieni 200;\n"
                             "\tbuy(LEGEND:100), aggiunge attacco, costo intero 100, ottieni 200;\n"
                             "\tbuy(SCUDO:100), recupero vita, costo intero 100, ottieni 200;\n"
                             "\tbuy(DIO:100), aggiunge difesa, costo intero 100, ottieni 200;\n"

                             "\tbuy(DEIFY:x), mono uso, cambia l'attacco e la difesa del mob in x, costo intero x+100;\n"
                             "\tbuy(meta:x), mono uso, si mostrano al giocatore tutte le stanze del livello fino a x, costo intero x+100;\n"
                             "\tbuy(STORM:100), mono uso, al prossimo mob sconfitto aggiungi TOT soldi alla tua ricompensa dove TOT era il suo livello, costo intero 100;\n"
                             "\tbuy(NEXT:100), ad uso prolungato, puoi anche andare da un'attuale stanza ad una > di quella attuale +1, costo intero 100;\n"
                             "\tbuy(BACK:100), ad uso prolungato, puoi anche andare da un'attuale stanza ad una < di quella attuale, costo intero 100;\n"
                             "\tbuy(MANOd:100), mono uso, i mob ti attaccano, costo intero 100;\n"
                             "\tbuy(MANOs:100), mono uso, i mob non ti attaccano, costo intero 100;\n"
                             "\tbuy(ASURA:1000), vinci il gioco, costo intero 1000;\n"

                             "\nEsempio:\n"
                             "\nAcquista HP con 'buy(HP:x)' dove x sono un numero intero di soldi virtuali che sei disposto a dare all'NPC.\n"
                             "Notare che i soldi virtuali che sei disposto a dare all'NPC devono essere realmente da te posseduti nel gioco.\n"
                             "Per esempio puoi fare buy(HP:5),\n"
                             "Oppure buy(SCUDO:100),\n"
                             "Oppure buy(DEIFY:150).";
            break;
            case (7):
                Terminale2 = "\nScopo del gioco è ottenere PA (punti azione), in ugual misura al Target impostato.\n"
                             "\nValore standard: 50, ma è modificabile con un comando setTarget(x) dove x è un numero intero > 1.\n"
                             "Se il numero è <= agli attuali PA totalizzati, vinci il gioco.";
            break;
            case (8):
                Terminale2 = "\nComando/trucco disponibile nel gioco:\n"
                             "\n'open(world)' è un comando che aggiunge un livello di 1000 stanze, dopo l'ultimo livello visitato."
                             "\n*Regola D'Oro: una stanza non può essere connessa a una stanza > di se stessa +1, a meno che:\n"
                             "non sia connessa a una stanza == se stessa +1.";
            break;

            }

            Ui->out2->setText(Terminale2);
        }

        else {

            Ui->out3->append("Comando Non Valido, cancellare e reinserire");
            Ui->input->setText("Comando Non Valido, cancellare e reinserire");
            Ui->input->setDisabled(false);
            return;
        }

        Ui->input->setDisabled(false);
    }

    else if ((DatiDiGioco->getStatus() > 3)
             && (QLineEdit.toStdString()[0] == 's' )
             && (QLineEdit.toStdString()[1] == 'e' )
             && (QLineEdit.toStdString()[2] == 't' )
             && (QLineEdit.toStdString()[3] == 'T' )
             && (QLineEdit.toStdString()[4] == 'a' )
             && (QLineEdit.toStdString()[5] == 'r' )
             && (QLineEdit.toStdString()[6] == 'g' )
             && (QLineEdit.toStdString()[7] == 'e' )
             && (QLineEdit.toStdString()[8] == 't' )
             && (QLineEdit.toStdString()[9] == '(' ))
    {
        Ui->input->setDisabled(true);

        QString tmp_Empty = "";

        for (int i = 10; i < QLineEdit.length(); i++) {

            if (QLineEdit.toStdString()[i] == ')') break;
            else tmp_Empty += QLineEdit.toStdString()[i];
        }

        int for_switch = tmp_Empty.toInt();

        if (for_switch > 1 )
        {
            DatiDiGioco->setTarget(for_switch);
            Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
            Ui->out3->append("nuovo obiettivo settato;");
            Ui->input->setText("c'è un nuovo target");

            if (DatiDiGioco->getMyPa() >= DatiDiGioco->getTarget())
            {
                Ui->input->setText("gioco concluso, PA >= Target, hai vinto il gioco");
                Ui->out2->setText(
                            "\nHai finito il videogioco in:\n"
                            + QString::number(this->play_game.elapsed()/60000)
                            + " minuto/i");

                this->IWantExit(Ui, ManagerMusic);
            }
        }

        else {

            Ui->out3->append("Comando Non Valido, cancellare e reinserire");
            Ui->input->setText("Comando Non Valido, cancellare e reinserire");
            Ui->input->setDisabled(false);
            return;
        }

        Ui->input->setDisabled(false);
    }

    else if ((DatiDiGioco->getStatus() > 3)
             && (QLineEdit.toStdString()[0] == 'b' )
             && (QLineEdit.toStdString()[1] == 'u' )
             && (QLineEdit.toStdString()[2] == 'y' )
             && (QLineEdit.toStdString()[3] == '(' ))
    {
        Ui->input->setDisabled(true);

        //dentro parentesi
        QString tmp_raccolta_comando = "";
        //prima dei :
        QString tmp_raccolta_comando2 = "";
        //dopo i :
        QString tmp_raccolta_comando3 = "";
        int soldi_in_input = -1;
        bool controllo_errore = false;

        for(int controllo=4; true; controllo++)
        {
            if (QLineEdit.toStdString()[controllo] == ')')
                break;

            else if (controllo == QLineEdit.length())
                controllo_errore = true;
        }

        if (controllo_errore == false)
        {
            for(int i=4; QLineEdit.toStdString()[i] != ')'; i++)
                tmp_raccolta_comando += QLineEdit.toStdString()[i];

            for(int controllo2=0; true; controllo2++)
            {
                if (tmp_raccolta_comando.toStdString()[controllo2] == ':')
                    break;

                else if (controllo2 == tmp_raccolta_comando.length())
                    controllo_errore = true;
            }

            if (controllo_errore == false)
            {
                for(int i2=0; tmp_raccolta_comando.toStdString()[i2] != ':'; i2++)
                    tmp_raccolta_comando2 += tmp_raccolta_comando.toStdString()[i2];

                for(int i3=tmp_raccolta_comando.length()-1; tmp_raccolta_comando.toStdString()[i3] != ':'; i3--)
                    tmp_raccolta_comando3 = tmp_raccolta_comando.toStdString()[i3] + tmp_raccolta_comando3;

                //se non é convertibile restituisce 0
                soldi_in_input = tmp_raccolta_comando3.toInt();

              if (((tmp_raccolta_comando2 != "DEF")
                && (tmp_raccolta_comando2 != "ATT")
                && (tmp_raccolta_comando2 != "HP")
                && (tmp_raccolta_comando2 != "PA")
                && (tmp_raccolta_comando2 != "MAX")
                && (tmp_raccolta_comando2 != "ELISIR")
                && (tmp_raccolta_comando2 != "SCUDO")
                && (tmp_raccolta_comando2 != "LEGEND")
                && (tmp_raccolta_comando2 != "DIO")

                && (tmp_raccolta_comando2 != "DEIFY")
                && (tmp_raccolta_comando2 != "meta")
                && (tmp_raccolta_comando2 != "STORM")
                && (tmp_raccolta_comando2 != "NEXT")
                && (tmp_raccolta_comando2 != "BACK")
                && (tmp_raccolta_comando2 != "ASURA")
                && (tmp_raccolta_comando2 != "MANOd")
                && (tmp_raccolta_comando2 != "MANOs"))
                || (soldi_in_input <= 0))
                {
                    Ui->out3->append("Comando Non Valido, cancellare e reinserire");
                    Ui->input->setText("Comando Non Valido, cancellare e reinserire");
                    Ui->input->setDisabled(false);
                    return;
                }

              else
              {
                  int x_NPC = 0;
                  int y_NPC = 0;

                  DatiDiGioco->getLivelli()->getMappeIT1()->
                          getI1()->identify(
                              DatiDiGioco->getLivelli()->
                              getMappeIT1()->
                              getSimboloNPC(), x_NPC, y_NPC);

                  if ((x_NPC == 0) && (y_NPC == 0))
                  {
                      Ui->input->setText("non puoi");
                      Ui->input->setDisabled(false);
                      return;
                  }

                  else if (soldi_in_input > DatiDiGioco->getMoney())
                  {
                      Ui->input->setText("transazione rifiutata");
                      Ui->input->setDisabled(false);
                      return;
                  }

                  else
                  {
                      //Base
                      //------------------------------------------------------------

                      if (tmp_raccolta_comando2 == "DEF")
                      {
                          DatiDiGioco->setDEFp1(
                          DatiDiGioco->getDEFp1() + soldi_in_input);
                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      else if (tmp_raccolta_comando2 == "ATT")
                      {
                          DatiDiGioco->setATTp1(
                          DatiDiGioco->getATTp1() + soldi_in_input);
                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      else if (tmp_raccolta_comando2 == "HP")
                      {
                          DatiDiGioco->setHPp1(
                          DatiDiGioco->getHPp1() + soldi_in_input);
                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);

                          if (DatiDiGioco->getHPp1() > DatiDiGioco->getMAXhpP1())
                          {
                              int credito =
                              DatiDiGioco->getHPp1()
                              - DatiDiGioco->getMAXhpP1();

                              DatiDiGioco->setHPp1(DatiDiGioco->getMAXhpP1());

                              DatiDiGioco->setMoney(
                                          DatiDiGioco->getMoney()
                                          + credito);
                          }

                          Ui->input->setText("transazione avvenuta");
                      }

                      else if (tmp_raccolta_comando2 == "PA")
                      {
                          DatiDiGioco->setMyPa(
                          DatiDiGioco->getMyPa() + soldi_in_input);
                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");

                          if (DatiDiGioco->getMyPa() >= DatiDiGioco->getTarget())
                          {
                              Ui->input->setText("gioco concluso, PA >= Target, hai vinto il gioco");
                              Ui->out2->setText(
                                          "\nHai finito il videogioco in:\n"
                                          + QString::number(this->play_game.elapsed()/60000)
                                          + " minuto/i");

                              this->IWantExit(Ui, ManagerMusic);
                          }
                      }

                      else if (tmp_raccolta_comando2 == "MAX")
                      {
                          DatiDiGioco->setMAXhpP1(
                          DatiDiGioco->getMAXhpP1() + soldi_in_input);
                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      else if (tmp_raccolta_comando2 == "LEGEND")
                      {
                          if (soldi_in_input != 100)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          DatiDiGioco->setATTp1(
                                      DatiDiGioco->getATTp1() + 200);

                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      else if (tmp_raccolta_comando2 == "ELISIR")
                      {
                          if (soldi_in_input != 100)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          DatiDiGioco->setMAXhpP1(
                                      DatiDiGioco->getMAXhpP1() + 200);

                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      else if (tmp_raccolta_comando2 == "SCUDO")
                      {
                          if (soldi_in_input != 100)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          DatiDiGioco->setHPp1(
                                      DatiDiGioco->getHPp1() + 200);

                          if (DatiDiGioco->getHPp1() > DatiDiGioco->getMAXhpP1())
                              DatiDiGioco->setHPp1(DatiDiGioco->getMAXhpP1());

                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      else if (tmp_raccolta_comando2 == "DIO")
                      {
                          if (soldi_in_input != 100)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          DatiDiGioco->setDEFp1(
                                      DatiDiGioco->getDEFp1() + 200);

                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      //Magie
                      //------------------------------------------------------------

                      else if (tmp_raccolta_comando2 == "DEIFY")
                      {
                          if (soldi_in_input <= 100)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          else {

                              int livello = DatiDiGioco->getLivelli()->
                                            getIteratore1()->get_index_livello();
                              int stanza = DatiDiGioco->getLivelli()->
                                           getIteratore1()->getMappeIT1()->
                                           getI1()->getIndex();

                              QString per_il_libro = "Ho comprato: " + tmp_raccolta_comando2
                                                   + "\nal livello: " + QString::number(livello)
                                                   + "\nalla stanza numero: "
                                                   + QString::number(stanza)
                                                   + "\nspendendo: "
                                                   + QString::number(soldi_in_input);

                              this->libroDegliIncantesimi->add(per_il_libro);

                              int ottenere = soldi_in_input - 100;
                              DatiDiGioco->setMOBhp(ottenere);
                              DatiDiGioco->setMOBatt(ottenere);

                              DatiDiGioco->setMoney(
                              DatiDiGioco->getMoney() - soldi_in_input);
                              Ui->input->setText("transazione avvenuta");
                          }
                      }

                      else if (tmp_raccolta_comando2 == "meta")
                      {
                          if (soldi_in_input <= 100)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          else
                          {
                              int ottenere = soldi_in_input - 100;
                              this->stanze_visitate->deleteLater();
                              this->stanze_visitate = nullptr;
                              this->stanze_visitate = new mylistQString;

                              int traguardo = ottenere;

                              if (traguardo >
                                      DatiDiGioco->getLivelli()->
                                      getMappeIT1()->
                                      getCoda()->getIndex())
                              {
                                  int credito =
                                  traguardo - DatiDiGioco->getLivelli()->
                                              getMappeIT1()->
                                              getCoda()->getIndex();

                                  traguardo = DatiDiGioco->getLivelli()->
                                              getMappeIT1()->
                                              getCoda()->getIndex();

                                  DatiDiGioco->setMoney(
                                              DatiDiGioco->getMoney()
                                              + credito);
                              }

                              this->stanze_visitate->add("1");
                              for (int i = 2; i <= traguardo; i++)
                                  if (!this->stanze_visitate->IfxExistInList(QString::number(i)))
                                      this->stanze_visitate->add(QString::number(i));

                              DatiDiGioco->setMoney(
                              DatiDiGioco->getMoney() - soldi_in_input);
                              Ui->input->setText("transazione avvenuta");

                              if (this->automap == true)
                                  this->map(DatiDiGioco, Terminale2, QLineEdit, Ui);
                          }
                      }

                      else if (tmp_raccolta_comando2 == "STORM")
                      {
                          if (soldi_in_input != 100)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          DatiDiGioco->setSTORM(true);

                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      else if (tmp_raccolta_comando2 == "NEXT")
                      {
                          if (soldi_in_input != 100)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          DatiDiGioco->setNEXT(true);

                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      else if (tmp_raccolta_comando2 == "BACK")
                      {
                          if (soldi_in_input != 100)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          DatiDiGioco->setBACK(true);

                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      else if (tmp_raccolta_comando2 == "ASURA")
                      {
                          if (soldi_in_input < 1000)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");

                          DatiDiGioco->setMyPa(DatiDiGioco->getTarget());

                          if (DatiDiGioco->getMyPa() >= DatiDiGioco->getTarget())
                          {
                              Ui->input->setText("gioco concluso, ASURA comprato, hai vinto il gioco");
                              Ui->out2->setText(
                                          "\nHai finito il videogioco in:\n"
                                          + QString::number(this->play_game.elapsed()/60000)
                                          + " minuto/i");

                              this->IWantExit(Ui, ManagerMusic);
                          }
                      }

                      else if (tmp_raccolta_comando2 == "MANOd")
                      {
                          if (soldi_in_input != 100)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          DatiDiGioco->setMANOd(true);
                          DatiDiGioco->setMANOs(false);

                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      else if (tmp_raccolta_comando2 == "MANOs")
                      {
                          if (soldi_in_input != 100)
                          {
                              Ui->input->setText("transazione rifiutata");
                              Ui->input->setDisabled(false);
                              return;
                          }

                          DatiDiGioco->setMANOd(false);
                          DatiDiGioco->setMANOs(true);

                          DatiDiGioco->setMoney(
                          DatiDiGioco->getMoney() - soldi_in_input);
                          Ui->input->setText("transazione avvenuta");
                      }

                      int livello = DatiDiGioco->getLivelli()->
                                    getIteratore1()->get_index_livello();
                      int stanza = DatiDiGioco->getLivelli()->
                                   getIteratore1()->getMappeIT1()->
                                   getI1()->getIndex();

                      if (tmp_raccolta_comando2 != "DEIFY")
                      {
                          QString per_il_libro = "Ho comprato: " + tmp_raccolta_comando2
                                               + "\nal livello: " + QString::number(livello)
                                               + "\nalla stanza numero: "
                                               + QString::number(stanza)
                                               + "\nspendendo: "
                                               + QString::number(soldi_in_input);

                          this->libroDegliIncantesimi->add(per_il_libro);
                      }

                      if ((tmp_raccolta_comando2 != "meta")
                       && (tmp_raccolta_comando2 != "ASURA")
                       && ((tmp_raccolta_comando2 != "PA")
                        || (DatiDiGioco->getMyPa() <
                            DatiDiGioco->getTarget())))

                          this->status(Terminale2, Ui, DatiDiGioco, QLineEdit);
                  }
              }
            }

            else if (controllo_errore == true)
            {
                Ui->out3->append("Comando Non Valido, cancellare e reinserire");
                Ui->input->setText("Comando Non Valido, cancellare e reinserire");
                Ui->input->setDisabled(false);
                return;
            }
        }

        else if (controllo_errore == true)
        {
            Ui->out3->append("Comando Non Valido, cancellare e reinserire");
            Ui->input->setText("Comando Non Valido, cancellare e reinserire");
            Ui->input->setDisabled(false);
            return;
        }

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "getTarget()")  && (DatiDiGioco->getStatus() > 3))
    {
        Ui->input->setDisabled(true);

        QString for_out_input = "target attuale: ";
        for_out_input += QString::number(DatiDiGioco->getTarget());
        for_out_input += "; punti attualmente totalizzati: ";
        for_out_input += QString::number(DatiDiGioco->getMyPa());
        for_out_input += "; restanti punti da totalizzare: ";
        for_out_input += QString::number((DatiDiGioco->getTarget())-(DatiDiGioco->getMyPa()));
        for_out_input += ".";

        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
        Ui->out3->append(for_out_input);
        Ui->input->setText(for_out_input);

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "automap(0)")  && (DatiDiGioco->getStatus() > 3))
    {
        Ui->input->setDisabled(true);

        this->automap = false;
        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
        Ui->input->setText("automap off");

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "automap(1)")  && (DatiDiGioco->getStatus() > 3))
    {
        Ui->input->setDisabled(true);

        this->automap = true;
        Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
        Ui->input->setText("automap on");

        Ui->input->setDisabled(false);
    }

    else if ((QLineEdit == "1nc4nt351m1()") && (DatiDiGioco->getStatus() > 3))
    {
        Ui->input->setDisabled(true);
        libroDegliIncantesimi->view(Terminale2, Ui);
        Ui->input->setDisabled(false);
    }

    else {

        Ui->out3->append("Comando Non Valido, cancellare e reinserire");
        Ui->input->setText("Comando Non Valido, cancellare e reinserire");
        Ui->input->setDisabled(false);
        return;
    }

    if ((DatiDiGioco->getListaComandiCorretti()->readTesta() == nullptr)
      ||(QLineEdit != DatiDiGioco->getListaComandiCorretti()->
                      readCoda()->getOggetto()))
    {
        DatiDiGioco->getListaComandiCorretti()->add(QLineEdit);
        DatiDiGioco->getListaComandiCorretti()->setIteratore
       (DatiDiGioco->getListaComandiCorretti()->readCoda());
    }

    Ui->input->setDisabled(false);
}

int comandi_da_terminale::getTempoStandardPerPausa()
{
    return this->tempo_standard_per_pausa;
}

void comandi_da_terminale::setTempoStandardPerPausa(int x)
{
    this->tempo_standard_per_pausa = x;
}

void comandi_da_terminale::setHelp()
{
    this->lista_help->add("go() //inizia il gioco;");
    this->lista_help->add("help() //lista dei comandi;");
    this->lista_help->add("exit() //uscita dal gioco;");
    this->lista_help->add("presentazione() //ripresentazione del gioco;");
    this->lista_help->add("clear(top) //pulisce i messaggi nella finestra in alto;");
    this->lista_help->add("clear(right) //pulisce i messaggi nella finestra a destra;");
    this->lista_help->add("list(music) //mostra la lista delle musiche nella finestra a destra;");
}

mylistQString*& comandi_da_terminale::getListaHelp()
{
    return this->lista_help;
}

void comandi_da_terminale::autocomplete(dati_Globali_di_gioco *&DatiDiGioco, Ui::MainWindow *&Ui)
{
    connect(Ui->input, &QLineEdit::textChanged, [&]() {

        //no frecce premute, premuti tasti alternativi
        //debug keyPressEvent, perché non prende tutti i tasti
        if (!DatiDiGioco->getListaComandiCorretti()->
             IfxExistInList(Ui->input->text()))
        {
            DatiDiGioco->getListaComandiCorretti()->setIteratore
           (DatiDiGioco->getListaComandiCorretti()->readCoda());

            this->freccia_su = false;
            this->freccia_giu = false;
        }

       if ((this->cronologia.length() == 1)
        || (this->cronologia.length() == 2))
       {
           QString tmp_text_save = Ui->input->text();
           if ((tmp_text_save == "") ||
               (tmp_text_save.length() == 1))
           {
               this->save_text_change = "";
               return;
           }

           string for_read_index_tmp = tmp_text_save.toStdString();
           int max_index = for_read_index_tmp.length() - 1;

           //da 0 a 2
           //--------------------------------------

           if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'r')
            && (for_read_index_tmp[max_index - 1] == 'p')
            && ((tmp_text_save + "esentazione()") != this->save_text_change)
            && (DatiDiGioco->getStatus() < 2)) {

               tmp_text_save += "esentazione()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           //--------------------------------------

           //solo 1
           //--------------------------------------

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'o')
            && (for_read_index_tmp[max_index - 1] == 'g')
            && ((tmp_text_save + "()") != this->save_text_change)
            && (DatiDiGioco->getStatus() == 1)) {

               tmp_text_save += "()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           //--------------------------------------

           //da 0 in poi, escluso 2 e 3
           //--------------------------------------

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'e')
            && (for_read_index_tmp[max_index - 1] == 'h')
            && ((tmp_text_save + "lp()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 0)
            && (DatiDiGioco->getStatus() != 2)
            && (DatiDiGioco->getStatus() != 3)) {

               tmp_text_save += "lp()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'i')
            && (for_read_index_tmp[max_index - 1] == 'l')
            && ((tmp_text_save + "st()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 0)
            && (DatiDiGioco->getStatus() != 2)
            && (DatiDiGioco->getStatus() != 3)) {

               tmp_text_save += "st()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'x')
            && (for_read_index_tmp[max_index - 1] == 'e')
            && ((tmp_text_save + "it()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 0)
            && (DatiDiGioco->getStatus() != 2)
            && (DatiDiGioco->getStatus() != 3)) {

               tmp_text_save += "it()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'l')
            && (for_read_index_tmp[max_index - 1] == 'c')
            && ((tmp_text_save + "ear()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 0)
            && (DatiDiGioco->getStatus() != 2)
            && (DatiDiGioco->getStatus() != 3)) {

               tmp_text_save += "ear()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           //--------------------------------------

           //solo 3
           //--------------------------------------

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'g')
            && (for_read_index_tmp[max_index - 1] == 'p')
            && ((tmp_text_save + "()") != this->save_text_change)
            && (DatiDiGioco->getStatus() == 3)) {

               tmp_text_save += "()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           //--------------------------------------

           //dal 3 in poi
           //--------------------------------------

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'o')
            && (for_read_index_tmp[max_index - 1] == 'm')
            && ((tmp_text_save + "ve()") != this->save_text_change)
            && (DatiDiGioco->getStatus() >  3)) {

               tmp_text_save += "ve()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'p')
            && (for_read_index_tmp[max_index - 1] == 'o')
            && ((tmp_text_save + "en()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 3)) {

               tmp_text_save += "en()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'e')
            && (for_read_index_tmp[max_index - 1] == 'n')
            && ((tmp_text_save + "w()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 3)) {

               tmp_text_save += "w()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'n')
            && (for_read_index_tmp[max_index - 1] == 'i')
            && ((tmp_text_save + "fo()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 3)) {

               tmp_text_save += "fo()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'e')
            && (for_read_index_tmp[max_index - 1] == 's')
            && ((tmp_text_save + "tTarget()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 3)) {

               tmp_text_save += "tTarget()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'e')
            && (for_read_index_tmp[max_index - 1] == 'g')
            && ((tmp_text_save + "tTarget()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 3)) {

               tmp_text_save += "tTarget()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'a')
            && (for_read_index_tmp[max_index - 1] == 'm')
            && ((tmp_text_save + "p()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 3)) {

               tmp_text_save += "p()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'u')
            && (for_read_index_tmp[max_index - 1] == 'a')
            && ((tmp_text_save + "tomap()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 3)) {

               tmp_text_save += "tomap()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 't')
            && (for_read_index_tmp[max_index - 1] == 's')
            && ((tmp_text_save + "atus()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 3)) {

               tmp_text_save += "atus()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'u')
            && (for_read_index_tmp[max_index - 1] == 'b')
            && ((tmp_text_save + "y()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 3)) {

               tmp_text_save += "y()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }

           else if ((tmp_text_save.length() == 2)
            && (for_read_index_tmp[max_index] == 'n')
            && (for_read_index_tmp[max_index - 1] == '1')
            && ((tmp_text_save + "c4nt351m1()") != this->save_text_change)
            && (DatiDiGioco->getStatus() > 3)) {

               tmp_text_save += "c4nt351m1()";
               Ui->input->setText(tmp_text_save);
               this->save_text_change = tmp_text_save;
           }
       }

       this->cronologia = Ui->input->text();
    });
}

void comandi_da_terminale::conclusione_per_il_pg_scelto(QString &Terminale1, dati_Globali_di_gioco *&DatiDiGioco, Ui::MainWindow *&Ui)
{

    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );

    this->lista_help->add("info(..) //richiedi informazioni, .. deve essere riempito con un numero intero che va da 1 a 8;");
    this->lista_help->add("move(center) //muoviti per andare al centro della stanza, possibile nella prima e nell'ultima stanza del livello;");
    this->lista_help->add("open(level) //per andare ad un nuovo/vecchio livello, seguire l'indicatore level, simbolo: '▣'.\n"
                          "Se vai in un livello precedente vedrai sulla mappa tutte le stanze, altrimenti vedrai sulla mappa solo la prima stanza;");
    this->lista_help->add("open(door) //per aprire una porta. seguire l'indicatore door, simbolo: '◧';");
    this->lista_help->add("1nc4nt351m1() //...");

    Ui->out2->append("\nPer i comandi di gioco, (di movimento e quant'altro c'è), scrivere 'help()'.\n"
                     "Scrivere poi 'info(..)' dove .. deve essere riempito con un numero intero che va da 1 a 8 (estremi compresi).\n"
                     "[1, 8], questo comando può essere utile per capire come funziona il gioco e come completarlo.\n"
                     "\nOra invece vi verra introdotta la nozione più basilare del gioco: 'la fine del turno'.\n"
                     "Il giocatore umano e il mostro controllato dal pc, hanno a disposizione un movimento per turno.\n");
    //add.liv.3
    //-------------------------------------------------------
    DatiDiGioco->getLivelli()->getCoda()->
            set_index_livello(DatiDiGioco->getLivelli()->
                              getCoda()->
                              get_index_livello()+1);

    DatiDiGioco->getLivelli()->add_liv();

    DatiDiGioco->getLivelli()->getCoda()->
            getEntrata()->
            set_index_livello(DatiDiGioco->getLivelli()->
                              getCoda()->
                              getEntrata()->
                              get_index_livello()-1);
    //-------------------------------------------------------

    DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->sendMapToTextBrowser1(Terminale1, Ui);
    Ui->out2->append("\nLivello 1 superato, Livello 3 aggiunto, il 2 manca.");
}

void comandi_da_terminale::map(dati_Globali_di_gioco *&DatiDiGioco,
                               QString &Terminale2, QString QLineEdit,
                               Ui::MainWindow *&Ui)
{
    int Cstanze_visitate = this->stanze_visitate->getLenght();

    Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");
    Terminale2 = "";
    Terminale2 = "\nSei arrivato fino al livello: " + QString::number(DatiDiGioco->getLivelli()->getIteratore2()->get_index_livello()) + ";\n"
                 "Ora ti trovi al livello: " + QString::number(DatiDiGioco->getLivelli()->getIteratore1()->get_index_livello()) + ".\n"
                 "\nIl livello in cui ti trovi ora contiente: " +  QString::number(DatiDiGioco->getLivelli()->
                                                                                   getMappeIT1()->getMain()->getCoda()->getIndex()) + " stanze/a;\n"
                 "Per un totale di " + QString::number(DatiDiGioco->getLivelli()->getIteratore1()->get_index_livello()) + " stanza/e, " +
                 "ne hai (invece) visitate: " + QString::number(Cstanze_visitate) + "\n"
                 "Ora ti trovi nella stanza numero: " + QString::number(DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->getIndex()) + "\n\n";

    Terminale2 += DatiDiGioco->getLivelli()->getMappeIT1()->
            getOggettoMiniMap()->getThisMiniMap(DatiDiGioco->getLivelli()->
                                                getIteratore1()->get_index_livello(),
                                                this->stanze_visitate);

    Ui->out2->setText(Terminale2);
}

void comandi_da_terminale::meta(dati_Globali_di_gioco *&DatiDiGioco,
                                QString QLineEdit, Ui::MainWindow *&Ui,
                                QString &Terminale2)
{
    Ui->out3->append("Comando Valido, eseguo " + QLineEdit + ";");

    this->stanze_visitate->deleteLater();
    this->stanze_visitate = nullptr;
    this->stanze_visitate = new mylistQString;

    int traguardo = DatiDiGioco->getLivelli()->getIteratore1()->getMappe()->getCoda()->getIndex();

    this->stanze_visitate->add("1");
    for (int i = 2; i <= traguardo; i++)
        if (!this->stanze_visitate->IfxExistInList(QString::number(i)))
            this->stanze_visitate->add(QString::number(i));

    this->map(DatiDiGioco, Terminale2, QLineEdit, Ui);
}

void comandi_da_terminale::IWantExit(Ui::MainWindow *&Ui,
                                     managerMusic *&ManagerMusic)
{
    this->pausa->singleShot(500, [&]() {

        Ui->input->setDisabled(true);
        Ui->out3->setText("");
        Ui->out3->append("in uscita.....");
        Ui->out1->setText("");

        this->pausa->singleShot(500, [&]() {

            ManagerMusic->getMyList()->readIterator()->pause();
            ManagerMusic->getMyList()->readIterator()->stop();

            Ui->procedi->setEnabled(true);
            Ui->out2->append("\n\nO hai vinto, o hai perso o volevi uscire.\n"
                             "Ora puoi solo uscire.\n"
                             "Per procedere,\n"
                             "premi il Tasto/Pulsante/Bottone: procedi (..).");

            connect(Ui->procedi, &QPushButton::clicked, [&]() {

                exit(-1);
            });
        });
    });
}

void comandi_da_terminale::set_save_text_change(QString x)
{
    this->save_text_change = x;
}

mylistQString*& comandi_da_terminale::getLibroDegliIncantesimi()
{
    return this->libroDegliIncantesimi;
}

void comandi_da_terminale::status
(QString &Terminale2, Ui::MainWindow *&Ui,
 dati_Globali_di_gioco *&DatiDiGioco, QString QLineEdit)
{
    Ui->input->setDisabled(true);

    Terminale2 = "";

    Terminale2 += "\n\n\tVita: " +
            QString::number(DatiDiGioco->getHPp1());

    Terminale2 += "\n\tVita_massima: " +
            QString::number(DatiDiGioco->getMAXhpP1());

    int minio_attP1 = DatiDiGioco->getATTp1()
                     /DatiDiGioco->getDEFp1();

    if (minio_attP1 < 1) minio_attP1 = 1;

    Terminale2 += "\n\tAttacco: " +
            QString::number(DatiDiGioco->getATTp1())
            + " | " + (QString::number
                       (DatiDiGioco->getATTp1()/10));

    Terminale2 += "\n\tDifesa: " +
            QString::number(DatiDiGioco->getDEFp1())
            + " | " + (QString::number
                      (DatiDiGioco->getDEFp1()/10));

    Terminale2 += "\n\tPA: " +
            QString::number(DatiDiGioco->getMyPa());

    Terminale2 += "\n\tTarget: " +
            QString::number(DatiDiGioco->getTarget());

    Terminale2 += "\n\tSoldi: " +
            QString::number(DatiDiGioco->getMoney()) + "\n\n";

    Terminale2 += "\n\tNumero del livello: " +
            QString::number(DatiDiGioco->getLivelli()->
                            getIteratore1()->
                            get_index_livello());

    Terminale2 += "\n\tNumero della stanza: " +
            QString::number(DatiDiGioco->getLivelli()->
                            getMappeIT1()->
                            getI1()->
                            getIndex());

    int x = 0;
    int y = 0;
    DatiDiGioco->getLivelli()->getMappeIT1()->getI1()->
            identify(DatiDiGioco->getLivelli()->getMappeIT1()->
                     getSimboloMOB(),
                     x, y);

    if ( (x != 0) || (y != 0))
    {
        Terminale2 += "\n\tMob HP: " +
                QString::number(DatiDiGioco->getMOBhp());

        Terminale2 += "\n\tMob Attacco: " +
                QString::number(DatiDiGioco->getMOBatt());
    }

    else
    {
        Terminale2 += "\n\tMob HP: MOB '◉' non presente in questa stanza.";
        Terminale2 += "\n\tMob Attacco: MOB '◉' non presente in questa stanza.";
    }

    Ui->out2->setText(Terminale2);

    Ui->input->setDisabled(false);
}

void comandi_da_terminale::setFrecciaSu(bool x)
{
    this->freccia_su = x;
}

void comandi_da_terminale::setFrecciaGiu(bool x)
{
    this->freccia_giu = x;
}

bool comandi_da_terminale::getFrecciaSu()
{
    return this->freccia_su;
}

bool comandi_da_terminale::getFrecciaGiu()
{
    return this->freccia_giu;
}

void comandi_da_terminale::setCronologia(QString x)
{
    this->cronologia = x;
}
