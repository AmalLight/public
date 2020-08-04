#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTime>
#include <QMainWindow>
#include "managermusic.h"
#include "mylistQMediaPlayer.h"
#include "comandi_da_terminale.h"
#include "dati_globali_di_gioco.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setMusic();
    QString QStringFromInt(int x);

public slots:
    void ifPlayChangeNameEstampMessage(pippo*&);
    void ifPauseStampMessage(pippo*&);
    void ifNextStampMessage(pippo*&);
    void ifPrecStampMessage(pippo*&);
    void ifChangeVolumeValueSetVolume(int);
    void prima_fase();
    Ui::MainWindow*& getUi();
    QString& getTerminale1();

    //void &MainWindow::keyPressEvent
    //sovrascrittura di funzione ereditata;
    void keyPressEvent(QKeyEvent *evento);

    void reciveEmitIstampMAPx(mylistQStringMaps *&pointer);
    void reciveCombattimento(QString simbolo_istigatoreXD);
    void attMOB();
    void attP1();

private:
    Ui::MainWindow *ui;
    managerMusic *musiche_per_linterfaccia;
    comandi_da_terminale *per_input;
    dati_Globali_di_gioco *datiDiGioco;

    QString Terminale2;
    QString Terminale1;
    QString tmp_debug_repeat_input;

    QTime dieTime;
    int tmp_hpMOB;

    bool connect_per_fase_finita;
    bool connect_per_input_invio;

signals:
};

#endif // MAINWINDOW_H
