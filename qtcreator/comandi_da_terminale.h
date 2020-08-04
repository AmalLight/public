#ifndef COMANDI_DA_TERMINALE_H
#define COMANDI_DA_TERMINALE_H
#include <QObject>
#include <QTimer>
#include <QTime>
#include "ui_mainwindow.h"
#include "mylistQString.h"
#include "managermusic.h"
#include "dati_globali_di_gioco.h"

class comandi_da_terminale : public QObject
{
    Q_OBJECT
private:
    QTimer *pausa;
    mylistQString *lista_help;
    bool open_world_on;

    bool automap;
    int tempo_standard_per_pausa;
    QString save_text_change;
    mylistQString *stanze_visitate;
    mylistQString *libroDegliIncantesimi;

    QTime play_game;
    bool freccia_su;
    bool freccia_giu;
    QString cronologia;

public:
    explicit comandi_da_terminale(QObject *parent = 0);

public slots:
    void elaborazione_comando_dal_terminale(dati_Globali_di_gioco *&DatiDiGioco,
                                            managerMusic *&ManagerMusic,
                                            QString &Terminale1,
                                            QString &Terminale2,
                                            QString QLineEdit,
                                            Ui::MainWindow *&Ui);
    QTimer*& getTimer();
    int getTempoStandardPerPausa();
    void setTempoStandardPerPausa(int x);
    void setHelp();
    mylistQString*& getListaHelp();
    void autocomplete(dati_Globali_di_gioco *&DatiDiGioco,
                      Ui::MainWindow *&Ui);

    void conclusione_per_il_pg_scelto(QString &Terminale1,
                                      dati_Globali_di_gioco *&DatiDiGioco,
                                      Ui::MainWindow *&Ui);

    void map(dati_Globali_di_gioco *&DatiDiGioco, QString &Terminale2,
             QString QLineEdit, Ui::MainWindow *&Ui);

    void meta(dati_Globali_di_gioco *&DatiDiGioco, QString QLineEdit,
              Ui::MainWindow *&Ui, QString &Terminale2);

    void IWantExit(Ui::MainWindow *&Ui, managerMusic *&ManagerMusic);
    void set_save_text_change(QString x);
    mylistQString *&getLibroDegliIncantesimi();

    void status(QString &Terminale2, Ui::MainWindow *&Ui,
                dati_Globali_di_gioco *&DatiDiGioco, QString QLineEdit);

    void setCronologia(QString x);
    bool getFrecciaSu();
    bool getFrecciaGiu();
    void setFrecciaSu(bool x);
    void setFrecciaGiu(bool x);

signals:
    void prima_fase_finita();
    void emitIstampMAPx(mylistQStringMaps *&pointer);
};

#endif // COMANDI_DA_TERMINALE_H
