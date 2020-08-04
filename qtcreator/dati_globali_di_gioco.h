#ifndef DATI_GLOBALI_DI_GIOCO_H
#define DATI_GLOBALI_DI_GIOCO_H
#include <QKeyEvent>
#include "livelli.h"

class dati_Globali_di_gioco : public QObject
{
    Q_OBJECT
public:
    explicit dati_Globali_di_gioco(QObject *parent = nullptr);

signals:

public slots:
    int getStatus();
    int getTarget();
    void setStatus(int x);
    void setTarget(int x);

    int getHPp1();
    int getMAXhpP1();
    int getATTp1();
    int getDEFp1();

    void setHPp1(int x);
    void setMAXhpP1(int x);
    void setDEFp1(int x);
    void setATTp1(int x);

    int getMoney();
    int getMyPa();
    void setMoney(int x);
    void setMyPa(int x);

    void setMOBhp(int x);
    void setMOBatt(int x);
    int getMOBhp();
    int getMOBatt();

    bool getSTORM();
    int getREBIRTH();
    bool getNEXT();
    bool getBACK();
    void setSTORM(bool x);
    void setREBIRTH(int x);
    void setNEXT(bool x);
    void setBACK(bool x);
    bool getMANOd();
    void setMANOd(bool x);
    bool getMANOs();
    void setMANOs(bool x);

    mylistQString*& getListaComandiCorretti();
    livelli*& getLivelli();

private:
    //0: no-help;
    //1: si-help;
    //2: gioco-partito;
    int stato_attuale;

    livelli *Livelli;
    mylistQString *lista_dei_comandi_corretti;

    int Target;
    int PA;
    int soldi;

    int hpP1;
    int maxHPp1;
    int attP1;
    int defP1;

    int hpMob;
    int attMob;

    bool potere_STORM;
    int value_REBIRTH;
    bool potere_NEXT;
    bool potere_BACK;
    bool MANOd;
    bool MANOs;
};

#endif // DATI_GLOBALI_DI_GIOCO_H
