#ifndef MYLISTQSTRINGMAPS_H
#define MYLISTQSTRINGMAPS_H
#include <QObject>
#include <mylistQString.h>
#include "MiniMap.h"
#include <iostream>
using namespace std;

class mylistQStringMaps : public QObject
{
    Q_OBJECT

private:
    int numero_di_mappe;
    int lunghezza;
    int altezza;
    int index;

    int movimenti;
    QString simbolo_vuoto;
    QString simbolo_tree;
    QString simbolo_pieno;
    QString simbolo_porta;
    QString simbolo_scala;
    bool Mappa_aggiunta;
    bool valore_per_i_movimenti;

    mylistQString *Mappa;
    bool up_non_fallito;
    bool down_non_fallito;
    bool right_non_fallito;
    bool left_non_fallito;

    mylistQStringMaps *Iteratore_fallimenti;
    int x_attuale;
    int y_attuale;

    QString simbolo_P1;
    QString simbolo_mob;
    QString simbolo_NPC;
    int p1_x;
    int p1_y;
    int mob_x;
    int mob_y;
    bool puoi_entrare_in_una_porta;
    bool puoi_entrare_in_unLivello;

    //salvo la home della classe;
    mylistQStringMaps *main;
    //iteratore per posizione pg
    mylistQStringMaps *Iteratore1;
    //Mini-mappa per questa mappa
    mylistQStringMaps *save_ctesta;
    MiniMap *oggetto_MiniMap;

    mylistQStringMaps *testa;
    mylistQStringMaps *coda;
    mylistQStringMaps *up;
    mylistQStringMaps *down;
    mylistQStringMaps *left;
    mylistQStringMaps *right;

    int *PointerCordinataXtmp;
    int *PointerCordinataYtmp;
    QString PointerSimbolToMoveTmp;
    bool nelPercorsOincontroFreccia;
    bool connect_avvenuto;

public:
    explicit mylistQStringMaps(QObject *parent = nullptr);

public slots:
    int get_numero_di_mappe();
    void set_numero_di_mappe(int x);
    void setSimboloPg1(QString x);
    QString getSimboloPg1();
    QString getSimboloScala();
    QString getSimboloNPC();
    QString getSimboloMOB();
    int getLunghezza();
    int getAltezza();

    void add1map(int index_livello);
    void addRoom();
    void sendMapToTextBrowser1(QString &Terminale1, Ui::MainWindow *&Ui);
    bool getValore_per_i_movimenti();
    void setValore_per_i_movimenti(bool x);
    bool getConnect_avvenuto();
    void setConnect_avvenuto(bool x);

    bool inThisThereISx(int x);
    bool get_puoi_entrare_in_una_porta();
    bool get_puoi_entrare_in_unLivello();
    void set_puoi_entrare_in_una_porta(bool x);
    void set_puoi_entrare_in_unLivello(bool x);
    void setPlayerToNewRoom(mylistQStringMaps *&stanza_attuale);

    int& getP1X();
    int& getP1Y();
    void setP1X(int x);
    void setP1Y(int y);
    int& getMOBx();
    int& getMOBy();
    void setMOBx(int x);
    void setMOBy(int y);

    int getIndex();
    void setIndex(int x);
    void simple_algorithm_move(QString simbolo_da_muovere, int x, int y,
                               QString &Terminale1, Ui::MainWindow *&Ui);

    //si parte da 0, non da 1
    bool setPlayer(QString pg, int x, int y);
    //si parte da 0, non da 1
    void setEmpty(int x, int y);
    //si parte da 0, non da 1
    void identify(QString simbolo_pg, int &myX, int &myY);
    //si parte da 0, non da 1
    QString return_xy_Mappa(int Mx, int My);
    MiniMap*& getOggettoMiniMap();
    void setOggettoMiniMap(MiniMap *&x);

    mylistQStringMaps*& getI1();
    void move(QString direzione, QString simbolo_da_muovere,
              QString &Terminale1, Ui::MainWindow *&Ui);

    void setI1(mylistQStringMaps*& puntatore);
    mylistQStringMaps*& getUp();
    mylistQStringMaps*& getDown();
    mylistQStringMaps*& getLeft();
    mylistQStringMaps*& getRight();
    mylistQStringMaps*& getTesta();
    mylistQStringMaps*& getCoda();
    mylistQStringMaps*& getMain();

    void NULLtesta();
    void NULLcoda();
    void NULLiteratore();
    void NULLiteratore_fallimenti();
    void NULLsave_ctesta();
    void NULLup();
    void NULLright();
    void NULLdown();
    void NULLleft();
    void setCoda(mylistQStringMaps *&x);
    void setIteratoreFallimenti(mylistQStringMaps *&x);
    void setSaveCtesta(mylistQStringMaps *&x);

signals:
    void emitILmobSIdeveMuovere();
    void emitCombattimento(QString simbolo_istigatoreXD);
    void emitRifaiOpenWorld(mylistQStringMaps *&pointer);
};

#endif // MYLISTQSTRINGMAPS_H
