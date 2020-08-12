#include "mainwindow.h"
#include <iostream>
#include <QTime>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->dieTime = QTime::currentTime();
    this->tmp_hpMOB = 0;
    this->connect_per_fase_finita = false;
    this->connect_per_input_invio = false;

    this->musiche_per_linterfaccia = new managerMusic;
    this->datiDiGioco = new dati_Globali_di_gioco;
    this->Terminale2 = "";
    this->Terminale1 = "";
    this->per_input = nullptr;

    this->ui->setupUi(this);

    //con ..->setFocus() filtra gli arrowKeys;
    this->setFocus();

    //abilità scorrimento orizzontale;
    //this->ui->out2->setLineWrapMode(QTextBrowser::NoWrap);

    this->ui->procedi->setDisabled(true);
    this->ui->input->setReadOnly(true);
    this->setMusic();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ifPlayChangeNameEstampMessage(pippo *&x)
{
    int comparsion =x->objectName().length() - 1;
    string tmp_string = x->objectName().toStdString();
    QString for_Pezzo = "";
    for (int i=0; i<comparsion; i++)
        for_Pezzo.append(tmp_string[i]);

    this->ui->Pezzo->setText(for_Pezzo);
    this->ui->play->setDisabled(true);
    this->ui->pause->setDisabled(false);
    this->ui->out3->append("play: " + x->objectName());
}

void MainWindow::ifPauseStampMessage(pippo *&x)
{
    this->ui->pause->setDisabled(true);
    this->ui->play->setDisabled(false);
    this->ui->out3->append("pause: " + x->objectName());
}

void MainWindow::ifNextStampMessage(pippo *&x)
{
    this->ui->out3->append("--> go to: " + x->objectName());
}

void MainWindow::ifPrecStampMessage(pippo *&x)
{
    this->ui->out3->append("<-- go to: " + x->objectName());
}

void MainWindow::ifChangeVolumeValueSetVolume(int x)
{
    this->musiche_per_linterfaccia->getMyList()->readIterator()->setVolume(x);
    this->ui->int_2->setText(this->QStringFromInt(x));
}

void MainWindow::setMusic()
{
   this-> ui->out3->append("programma caricato;\nmusiche in caricamento;");

    QObject::connect(this->ui->Volume, SIGNAL(valueChanged(int)), this, SLOT(ifChangeVolumeValueSetVolume(int)));
    QObject::connect(this->musiche_per_linterfaccia->getMyList(), &mylistQMediaPlayer::add_recive, [&]() {

       this->ui->out3->append("aggiunta musica: " + this->musiche_per_linterfaccia->getMyList()->readCoda()->objectName());

    });

    QObject::connect(this->musiche_per_linterfaccia, SIGNAL(play_recive(pippo*&)), this, SLOT(ifPlayChangeNameEstampMessage(pippo*&)));
    QObject::connect(this->musiche_per_linterfaccia, SIGNAL(pause_recive(pippo*&)), this, SLOT(ifPauseStampMessage(pippo*&)));
    QObject::connect(this->musiche_per_linterfaccia, SIGNAL(next_recive(pippo*&)), this, SLOT(ifNextStampMessage(pippo*&)));
    QObject::connect(this->musiche_per_linterfaccia, SIGNAL(prec_recive(pippo*&)), this, SLOT(ifPrecStampMessage(pippo*&)));

    QObject::connect(this->musiche_per_linterfaccia, &managerMusic::my_playlist_is_created, [&]() {


        this->ui->out3->append("la lista di musiche é stata settata correttamente;\n"
            "ora stampa a video delle informazioni riguardanti i singoli file musicali;\n"
            + this->musiche_per_linterfaccia->getTextFinishLoad());

        this->ui->Volume->setValue(this->musiche_per_linterfaccia->getMyList()->readIterator()->volume());
        this->ui->int_2->setText(this->QStringFromInt(this->musiche_per_linterfaccia->getMyList()->readIterator()->volume()));
        this->musiche_per_linterfaccia->play();
    });

    QObject::connect(this->ui->play, &QPushButton::clicked, this->musiche_per_linterfaccia, &managerMusic::play);
    QObject::connect(this->ui->pause, &QPushButton::clicked, this->musiche_per_linterfaccia, &managerMusic::pause);
    QObject::connect(this->ui->next, &QPushButton::clicked, this->musiche_per_linterfaccia, &managerMusic::next);
    QObject::connect(this->ui->prec, &QPushButton::clicked, this->musiche_per_linterfaccia, &managerMusic::prec);

    this->musiche_per_linterfaccia->create_playlist();
}

QString MainWindow::QStringFromInt(int x)
{
    QString di_ritorno = "";
    int tmp = 0;

    if (x > 9) {

        tmp = (x /= 10);

        if (x == 1) di_ritorno.append("1");
        if (x == 2) di_ritorno.append("2");
        if (x == 3) di_ritorno.append("3");
        if (x == 4) di_ritorno.append("4");
        if (x == 5) di_ritorno.append("5");
        if (x == 6) di_ritorno.append("6");
        if (x == 7) di_ritorno.append("7");
        if (x == 8) di_ritorno.append("8");
        if (x == 9) di_ritorno.append("9");
        if (x == 0) di_ritorno.append("0");
    }

    x = tmp;

    if (x == 1) di_ritorno.append("1");
    if (x == 2) di_ritorno.append("2");
    if (x == 3) di_ritorno.append("3");
    if (x == 4) di_ritorno.append("4");
    if (x == 5) di_ritorno.append("5");
    if (x == 6) di_ritorno.append("6");
    if (x == 7) di_ritorno.append("7");
    if (x == 8) di_ritorno.append("8");
    if (x == 9) di_ritorno.append("9");
    if (x == 0) di_ritorno.append("0");

    return di_ritorno;
}

void MainWindow::prima_fase()
{
    if (this->per_input == nullptr) {

        this->per_input = new comandi_da_terminale();
        connect(this->per_input, SIGNAL(emitIstampMAPx(mylistQStringMaps*&)),
                this, SLOT(reciveEmitIstampMAPx(mylistQStringMaps*&)));
    }

    if (this->connect_per_fase_finita == false)
    {
        this->connect_per_fase_finita = true;

        QObject::connect(this->per_input, &comandi_da_terminale::prima_fase_finita, [&]() {

            this->datiDiGioco->setStatus(3);

            this->Terminale2 = "";
            this->Terminale2 = "\nEcco, ora il gioco inizia, Per favore scegliere un proprio Avatar per il gioco;\n\n"
                               "pg maschio: ☻, per scegliere questo avatar scrivere in QLineEdit, scrivere: 'pg(m)';\n"
                               "pg femmina: ☺, per scegliere questo avatar scrivere in QLineEdit, scrivere: 'pg(f)'.\n";

            this->ui->out2->setText(this->Terminale2);
        });
    }

    this->per_input->setTempoStandardPerPausa(500);
    this->Terminale2 = "TextBrowser2.\n\n\n"
                       "Ei ciao, Benvenuta/o. Purtroppo ti sei svegliata/o solo ora, tardi.\n"
                       "La buona notizia è che sei viva/o, la brutta è che non si sa chi tu sia.\n"
                       "Ma se ti guardi intorno capirai da subito dove sei, in una foresta fitta fitta.\n"
                       "attraversando la foresta capirai che in certi punti,\n"
                       "chiamati dai costruttori 'fine della stanza' essa è bloccata da muri di cemento,\n"
                       "attraversabili solo con l'ausilio di porte e scale, ma di questo ancora non dirò nulla.\n"
                       "Quello che si presenta ora come una foresta non può essere di certo stata fatta in natura,\n"
                       "bensì è un uno strano ibrido, esperimento atto a capire come te la cavi in situazioni difficili.\n"
                       "Qui potrai divertirti, raccogliere incantesimi rari ed usarli oppure affrontare i più pericolosi mostri e morire XD.\n"
                       "Lo scopo di questo gioco, è questo! farvi divertire e sopratutto farvi morire dal nervoso.\n\n"
                       "Giusto per darvi una dritta ora vi verrà introdotta la meccanica di console,\n"
                       "ovvero come eseguire azioni di gioco o azioni gestionali. Pronti?\n"
                       "Viaaaaaaaaaa .... !!!";

    this->Terminale1 = "TextBrowser1.\n\n\n"
                       "\n\n\tWELCOME!!!";

    this->per_input->getTimer()->singleShot(this->per_input->getTempoStandardPerPausa(), [&]() {

        this->ui->out3->append("Stampa primo messaggio sul TextBrowser1, e TextBrowser2;");
        this->per_input->getTimer()->singleShot(this->per_input->getTempoStandardPerPausa(), [&]() {

            this->ui->out2->setText(this->Terminale2);
            this->ui->out1->setText(this->Terminale1);

            this->per_input->getTimer()->singleShot(this->per_input->getTempoStandardPerPausa(), [&]() {

               this->ui->out2->append("\n\nPer procedere con i messaggi a video premi il Tasto: procedi (..).");

                this->ui->procedi->setDisabled(false);
                connect(this->ui->procedi, &QPushButton::clicked, [&]() {

                    this->ui->procedi->setDisabled(true);
                    disconnect(this->ui->procedi, &QPushButton::clicked, nullptr, nullptr);

                    this->per_input->getTimer()->singleShot(this->per_input->getTempoStandardPerPausa(), [&]() {

                        this->ui->out3->append("Sblocco comando di input, QlineEdit --->\t\t ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓");
                        this->ui->input->setReadOnly(false);
                        this->ui->input->setText("QlineEdit");

                        this->Terminale2 = " ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑\n"
                                          "Quella indicata dalle frecce é la linea QlineEdit che consente l'immissione di comandi per questo tipo di gioco.\n";
                        this->ui->out2->setText(this->Terminale2);

                        this->per_input->getTimer()->singleShot(this->per_input->getTempoStandardPerPausa(), [&]() {

                            this->ui->out2->append("Cancella il testo su scritto, e prova il comando 'help()' ,\n"
                                                   "a fine digitazione resta sul QlineEdit, e premi invio.");

                            if (this->connect_per_input_invio == false)
                            {
                                this->connect_per_input_invio = true;

                                connect(this->ui->input, &QLineEdit::returnPressed, [&]() {

                                    if ((this->ui->input->text() == "presentazione()")
                                        && (this->datiDiGioco->getStatus() < 2))
                                    {
                                        this->tmp_debug_repeat_input = this->ui->input->text();
                                        this->ui->out3->append("Comando Valido, eseguo " + this->ui->input->text() + ";");
                                        this->datiDiGioco->setStatus(0);
                                        this->per_input->getListaHelp()->remove("go() //inizia il gioco;");
                                        this->per_input->getListaHelp()->remove("help() //lista dei comandi;");
                                        this->per_input->getListaHelp()->remove("exit() //uscita dal gioco;");
                                        this->per_input->getListaHelp()->remove("presentazione() //ripresentazione del gioco;");
                                        this->per_input->getListaHelp()->remove("clear(top) //pulisce i messaggi nella finestra in alto;");
                                        this->per_input->getListaHelp()->remove("clear(right) //pulisce i messaggi nella finestra a destra;");
                                        this->per_input->getListaHelp()->remove("list(music) //mostra la lista delle musiche nella finestra a destra;");
                                        this->ui->input->setText("");
                                        this->ui->input->setReadOnly(true);
                                        prima_fase();
                                    }

                                    // && == punti fermi, // || == punti dinamici
                                    else if ((this->datiDiGioco->getListaComandiCorretti()->
                                             readCoda() != nullptr) &&
                                            ((
                                                (this->ui->input->text() == "Comando Non Valido, cancellare e reinserire")
                                             || (this->ui->input->text() == "Comando che comporta un movimento errato")
                                             || (this->ui->input->text() == "QlineEdit")
                                             || (this->ui->input->text() == "nessuna porta da aprire")
                                             || (this->ui->input->text() == "nessun livello da raggiungere con questa mappa")
                                             || (this->ui->input->text() == "errore, posizione xy non adatta")
                                             || (this->ui->input->text() == "non puoi creare un nuovo livello")
                                             || (this->ui->input->text() == "nuovo livello creato"
                                             || (this->ui->input->text() == "non puoi")
                                             || (this->ui->input->text() == "automap off")
                                             || (this->ui->input->text() == "automap on")
                                             || (this->ui->input->text() == "disgrazia")
                                             || (this->ui->input->text() == "transazione avvenuta")
                                             || (this->ui->input->text() == "transazione rifiutata")
                                             || (this->ui->input->text() == "Nuovo livello 'open world' creato")
                                             || (this->ui->input->text() == "c'è un nuovo target"))
                                             || ((this->ui->input->text().toStdString()[0] == 't')
                                                && (this->ui->input->text().toStdString()[1] == 'a')
                                                && (this->ui->input->text().toStdString()[2] == 'r'))
                                             ))
                                              );

                                    else {

                                        this->tmp_debug_repeat_input = this->ui->input->text();
                                        this->per_input->elaborazione_comando_dal_terminale
                                                (this->datiDiGioco,
                                                 this->musiche_per_linterfaccia,
                                                 this->Terminale1,
                                                 this->Terminale2,
                                                 this->ui->input->text(), this->ui);
                                    }
                                });
                            }
                        });
                    });
                });
            });
        });
    });
}

Ui::MainWindow*& MainWindow::getUi()
{
    return this->ui;
}

QString &MainWindow::getTerminale1()
{
    return this->Terminale1;
}

//void &MainWindow::keyPressEvent
//sovrascrittura di funzione ereditata;
void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if (this->datiDiGioco->getStatus() < 1);

    else
    {
        //debug comandi_da_terminale::autocomplete
        if ((evento->key() == 16777249)
         || (evento->key() == 16777223)
         || (evento->key() == 16777219))
        {
            this->per_input->setFrecciaSu(false);
            this->per_input->setFrecciaGiu(false);
            this->per_input->set_save_text_change("");

            this->datiDiGioco->getListaComandiCorretti()->setIteratore
           (this->datiDiGioco->getListaComandiCorretti()->readCoda());
        }

        else if (evento->key() == Qt::Key_N)
            this->musiche_per_linterfaccia->next();

        else if (evento->key() == Qt::Key_P)
            this->musiche_per_linterfaccia->prec();

        else if (evento->key() == Qt::Key_K) {

            if (!this->ui->play->isEnabled())
                this->musiche_per_linterfaccia->pause();
            else this->musiche_per_linterfaccia->play();
        }

        else if (evento->key() == Qt::Key_T)
        {
            this->per_input->set_save_text_change("");
            this->ui->input->selectAll();
            this->ui->input->setFocus();
        }

        else if (evento->key() == Qt::Key_Up)
        {
            if (this->per_input->
                getFrecciaGiu() == true) {

                this->datiDiGioco->getListaComandiCorretti()->
                        Iprec();

                this->datiDiGioco->getListaComandiCorretti()->
                        Iprec();
            }

            else if (this->ui->input->text() == this->datiDiGioco->
                getListaComandiCorretti()->readIterator()->
                getOggetto())
                this->datiDiGioco->
                getListaComandiCorretti()->
                    Iprec();

            this->per_input->setFrecciaSu(true);
            this->per_input->setFrecciaGiu(false);

            this->ui->input->setText(this->datiDiGioco->
            getListaComandiCorretti()->
            IprecSimilarToTErminal());
        }

        else if (evento->key() == Qt::Key_Down)
        {
            if (this->per_input->
                getFrecciaSu() == true) {

                this->datiDiGioco->getListaComandiCorretti()->
                        Inext();

                this->datiDiGioco->getListaComandiCorretti()->
                        Inext();
            }

            else if (this->ui->input->text() == this->datiDiGioco->
                getListaComandiCorretti()->readIterator()->
                getOggetto())
                this->datiDiGioco->
                getListaComandiCorretti()->
                    Inext();

            this->per_input->setFrecciaSu(false);
            this->per_input->setFrecciaGiu(true);

            this->ui->input->setText(this->datiDiGioco->
            getListaComandiCorretti()->
            InextSimilarToTErminal());
        }
    }
}

void MainWindow::reciveEmitIstampMAPx(mylistQStringMaps *&pointer)
{
    this->datiDiGioco->setMOBhp(pointer->getIndex());
    this->datiDiGioco->setMOBatt(pointer->getIndex());

    if (pointer->getConnect_avvenuto() == false)
    {
        connect(pointer, SIGNAL(emitCombattimento(QString)),
                this, SLOT(reciveCombattimento(QString)));

        connect(pointer, &mylistQStringMaps::emitILmobSIdeveMuovere,
                [&]() {

            this->ui->input->setDisabled(true);

            int x = 0;
            int y = 0;

            pointer->identify(this->datiDiGioco->getLivelli()->
                              getMappeIT1()->
                              getSimboloPg1(), x, y);

            if (this->datiDiGioco->getMANOd() == false)
            {
                int random = 0;

                //da 0 a 4
                loopRandomMoveMOB:;
                random = rand() % 5;

                if (this->datiDiGioco->getMANOs() == true)
                {
                    if ((random == 1) &&
                       ((x == 12) && (y == 2)))
                        goto loopRandomMoveMOB;

                    else if ((random == 2) &&
                             ((x == this->datiDiGioco->
                               getLivelli()->
                               getMappeIT1()->
                               getLunghezza()-4)
                           && (y == 8)))
                        goto loopRandomMoveMOB;

                    else if ((random == 3) &&
                            ((x == 12) &&
                             (y == this->datiDiGioco->
                              getLivelli()->
                              getMappeIT1()->
                              getAltezza()-3)))
                        goto loopRandomMoveMOB;

                    else if ((random == 4) &&
                            ((x == 3) && (y == 8)))
                        goto loopRandomMoveMOB;

                    this->datiDiGioco->setMANOs(false);
                    this->datiDiGioco->setMANOd(false);

                    this->per_input->getLibroDegliIncantesimi()->
                            add("Ho usato: MANOs\n"
                                "al livello: "
                                + QString::number(this->datiDiGioco->getLivelli()->
                                                  getIteratore1()->
                                                  get_index_livello())
                                + "\nalla stanza: "
                                + QString::number(this->datiDiGioco->getLivelli()->
                                                  getMappeIT1()->
                                                  getI1()->getIndex()));
                }

                if (random == 0)
                    goto loopRandomMoveMOB;

                else if (random == 1)
                    pointer->move("up",
                                  pointer->getMain()->getSimboloMOB(),
                                  this->Terminale1, this->ui);

                else if (random == 2)
                    pointer->move("right",
                                  pointer->getMain()->getSimboloMOB(),
                                  this->Terminale1, this->ui);

                else if (random == 3)
                    pointer->move("down",
                                  pointer->getMain()->getSimboloMOB(),
                                  this->Terminale1, this->ui);

                else if (random == 4)
                    pointer->move("left",
                                  pointer->getMain()->getSimboloMOB(),
                                  this->Terminale1, this->ui);
            }

            else if (this->datiDiGioco->getMANOd() == true)
            {
                if ((x == 3) && (y == 8))
                    pointer->move("left",
                                  pointer->getMain()->getSimboloMOB(),
                                  this->Terminale1, this->ui);

                else if ((x == 12) && (y == 2))
                    pointer->move("up",
                                  pointer->getMain()->getSimboloMOB(),
                                  this->Terminale1, this->ui);

                else if ((x == 12) &&
                         (y == this->datiDiGioco->
                          getLivelli()->
                          getMappeIT1()->getAltezza()-3))
                    pointer->move("down",
                                  pointer->getMain()->getSimboloMOB(),
                                  this->Terminale1, this->ui);

                else if ((x == this->datiDiGioco->
                          getLivelli()->
                          getMappeIT1()->getLunghezza()-4)
                       &&
                         (y == 8))
                    pointer->move("right",
                                  pointer->getMain()->getSimboloMOB(),
                                  this->Terminale1, this->ui);

                this->datiDiGioco->setMANOs(false);
                this->datiDiGioco->setMANOd(false);

                this->per_input->getLibroDegliIncantesimi()->
                        add("Ho usato: MANOd\n"
                            "al livello: "
                            + QString::number(this->datiDiGioco->getLivelli()->
                                              getIteratore1()->
                                              get_index_livello())
                            + "\nalla stanza: "
                            + QString::number(this->datiDiGioco->getLivelli()->
                                              getMappeIT1()->
                                              getI1()->getIndex()));
            }

            this->ui->input->setDisabled(false);
        });

        pointer->setConnect_avvenuto(true);
    }
}

void MainWindow::reciveCombattimento(QString simbolo_istigatoreXD)
{
    this->ui->out2->setText("");
    this->ui->out3->append("ingaggio battaglia, istigatore: "
                           + simbolo_istigatoreXD);
    this->ui->input->setDisabled(true);

    datiDiGioco->getLivelli()->getMappeIT1()->
                setValore_per_i_movimenti(true);

    this->ui->out2->append(
                "\nnumero Livello: "
                + QString::number(this->datiDiGioco->getLivelli()->
                              getIteratore1()->
                              get_index_livello()));

    this->ui->out2->append(
                "numero Stanza: "
                + QString::number(this->datiDiGioco->getLivelli()->
                              getMappeIT1()->
                              getI1()->
                              getIndex()));

    this->ui->out2->append(
                "ingaggio battaglia, istigatore: "
                + simbolo_istigatoreXD + "\n");

    this->dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < this->dieTime )
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );

    //------------------------------------------------------------------

    this->ui->out2->append(
                "vita(hp) giocatore umano = "
                + QString::number(this->datiDiGioco->getHPp1()));

    this->ui->out2->append(
                "attacco(att) giocatore umano = "
                + QString::number(this->datiDiGioco->getATTp1())
                + " | "
                + QString::number(this->datiDiGioco->getATTp1()/10));

    this->ui->out2->append(
                "difesa(def) giocatore umano = "
                + QString::number(this->datiDiGioco->getDEFp1())
                + " | "
                + QString::number(this->datiDiGioco->getDEFp1()/10));

    this->dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < this->dieTime )
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );

    //------------------------------------------------------------------

    this->ui->out2->append(
                "\nvita(hp) mob = "
                + QString::number(this->datiDiGioco->getMOBhp()));


    this->ui->out2->append(
                "attacco(att) mob = "
                + QString::number(this->datiDiGioco->getMOBatt()));

    this->dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < this->dieTime )
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );

    //------------------------------------------------------------------

    QString chi_inizia = "";

    if (simbolo_istigatoreXD ==
            datiDiGioco->getLivelli()->
            getMappeIT1()->
            getSimboloMOB())

        chi_inizia = "giocatore umano";
    else
        chi_inizia = "mob";

    this->ui->out2->append(
                "\nInizia la sfida il: "
                + chi_inizia);

    this->dieTime = QTime::currentTime().addMSecs(500);
    while( QTime::currentTime() < this->dieTime )
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );

    //------------------------------------------------------------------

    this->tmp_hpMOB = this->datiDiGioco->getMOBhp();

    while ((this->datiDiGioco->getHPp1() > 0)
          && (tmp_hpMOB > 0))
    {
        if (chi_inizia == "giocatore umano")
        {
            this->attP1();

            if (tmp_hpMOB > 0)
            {
                this->attMOB();
            }
        }

        else if (chi_inizia == "mob")
        {
            this->attMOB();

            if (this->datiDiGioco->getHPp1() > 0)
            {
                this->attP1();
            }
        }
    }

    //------------------------------------------------------------------

    if (this->datiDiGioco->getHPp1() <= 0)
    {
        this->ui->input->setDisabled(true);
        this->ui->input->setText("game over, HP <= 0, hai perso il gioco");
        this->per_input->IWantExit(this->ui, musiche_per_linterfaccia);
    }

    else
    {
        if (chi_inizia == "giocatore umano")
        {
            int x = 0;
            int y = 0;
            this->datiDiGioco->getLivelli()->getMappeIT1()->
                    getI1()->identify(this->datiDiGioco->getLivelli()->
                             getMappeIT1()->
                             getSimboloPg1(), x, y);
            this->datiDiGioco->getLivelli()->getMappeIT1()->
                    getI1()->setEmpty(x, y);

            int x2 = 0;
            int y2 = 0;
            this->datiDiGioco->getLivelli()->getMappeIT1()->
                    getI1()->identify(this->datiDiGioco->getLivelli()->
                             getMappeIT1()->
                             getSimboloMOB(), x2, y2);
            this->datiDiGioco->getLivelli()->getMappeIT1()->
                    getI1()->setEmpty(x2, y2);


            this->datiDiGioco->getLivelli()->getMappeIT1()->
                    getI1()->setPlayer(this->datiDiGioco->getLivelli()->
                              getMappeIT1()->
                              getSimboloMOB(), x, y);

            this->datiDiGioco->getLivelli()->getMappeIT1()->
                    getI1()->setPlayer(this->datiDiGioco->getLivelli()->
                              getMappeIT1()->
                              getSimboloPg1(), 12, 8);

            this->datiDiGioco->getLivelli()->
                    getMappeIT1()->getI1()->
                    sendMapToTextBrowser1(Terminale1, this->ui);
        }

        else if (chi_inizia == "mob")
        {
            int x = 0;
            int y = 0;
            this->datiDiGioco->getLivelli()->getMappeIT1()->
                    getI1()->identify(this->datiDiGioco->getLivelli()->
                             getMappeIT1()->
                             getSimboloPg1(), x, y);
            this->datiDiGioco->getLivelli()->getMappeIT1()->
                    getI1()->setEmpty(x, y);

            this->datiDiGioco->getLivelli()->getMappeIT1()->
                    getI1()->setPlayer(this->datiDiGioco->getLivelli()->
                              getMappeIT1()->
                              getSimboloPg1(), 12, 8);

            this->datiDiGioco->getLivelli()->
                    getMappeIT1()->getI1()->
                    sendMapToTextBrowser1(Terminale1, this->ui);
        }

        this->ui->out2->append("\nmomento ricompensa");

        this->ui->out2->append("ricompensa = 1+1+1+1");
        this->ui->out2->append(
                    QString::number(
                    this->datiDiGioco->getMOBhp()*2)
                    + "(livello_del_mob * 2)");

        this->datiDiGioco->setMoney(
                    this->datiDiGioco->getMoney()
                    + 4 + (this->datiDiGioco->getMOBhp()*2));

        if (this->datiDiGioco->getSTORM() == true)
        {
            this->ui->out2->append(
                        "+ "
                        + QString::number(
                        this->datiDiGioco->getMOBhp())
                        + "(STORM)");

            this->per_input->getLibroDegliIncantesimi()->
                    add("Ho usato: STORM\n"
                        "al livello: "
                        + QString::number(this->datiDiGioco->getLivelli()->
                                          getIteratore1()->
                                          get_index_livello())
                        + "\nalla stanza: "
                        + QString::number(this->datiDiGioco->getLivelli()->
                                          getMappeIT1()->
                                          getI1()->getIndex()));

            this->datiDiGioco->setSTORM(false);

            this->datiDiGioco->setMoney(
                        this->datiDiGioco->getMoney()
                        + this->datiDiGioco->getMOBhp());
        }

        this->ui->out2->append(
                    "\nsoldi giocatore umano = "
                    + QString::number(this->datiDiGioco->getMoney()));

        this->dieTime = QTime::currentTime().addMSecs(1000);
        while( QTime::currentTime() < this->dieTime )
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );

        this->ui->input->setDisabled(false);
    }
}

void MainWindow::attMOB()
{
    this->ui->out2->append("\natt mob");

    int minimo_danno = this->datiDiGioco->getMOBatt()
                     -(this->datiDiGioco->getDEFp1()/10);

    if (minimo_danno < 0) minimo_danno = 0;

    this->ui->out2->append(
                "il mob toglie su un attacco di "
                + QString::number(this->datiDiGioco->getMOBatt()));

    this->ui->out2->append(
                "toglie al giocatore umano solo "
                + QString::number(minimo_danno));

   this->ui->out2->append(
                "vita(hp) giocatore umano = "
                + QString::number(this->datiDiGioco->getHPp1()
                                  - minimo_danno));

    this->datiDiGioco->setHPp1(this->datiDiGioco->getHPp1()
                               - minimo_danno);

    this->dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < this->dieTime )
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
}

void MainWindow::attP1()
{
    this->ui->out2->append("\natt giocatore umano");

    this->ui->out2->append(
                "il giocatore umano toglie su un attacco di "
                + QString::number(this->datiDiGioco->getATTp1()));

    this->ui->out2->append(
                "toglie al mob solo "
                + QString::number(this->datiDiGioco->getATTp1()/10));

    this->ui->out2->append(
                "vita(hp) mob = "
                + QString::number(this->tmp_hpMOB -=
                (this->datiDiGioco->getATTp1()/10)));

    this->dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < this->dieTime )
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
}
