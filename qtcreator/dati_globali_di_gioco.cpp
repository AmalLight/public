#include "dati_globali_di_gioco.h"

dati_Globali_di_gioco::dati_Globali_di_gioco(QObject *parent) : QObject(parent)
{
    this->stato_attuale = 0;
    this->Livelli = new livelli;
    this->lista_dei_comandi_corretti = new mylistQString;

    this->Target = 50;
    this->PA = 1;
    this->soldi = 99999999;

    this->hpP1 = 10;
    this->maxHPp1 = 10;
    this->attP1 = 10;
    this->defP1 = 10;

    this->hpMob = 0;
    this->attMob = 0;

    this->potere_STORM = false;
    this->value_REBIRTH = 0;
    this->potere_NEXT = false;
    this->potere_BACK = false;

    this->MANOd = false;
    this->MANOs = false;
}

int dati_Globali_di_gioco::getStatus()
{
    return this->stato_attuale;
}

void dati_Globali_di_gioco::setStatus(int x)
{
    this->stato_attuale = x;
}
livelli*& dati_Globali_di_gioco::getLivelli()
{
    return this->Livelli;
}

mylistQString*& dati_Globali_di_gioco::getListaComandiCorretti()
{
    return this->lista_dei_comandi_corretti;
}

void dati_Globali_di_gioco::setTarget(int x)
{
    this->Target = x;
}

int dati_Globali_di_gioco::getTarget()
{
    return this->Target;
}

int dati_Globali_di_gioco::getMyPa()
{
    return this->PA;
}

int dati_Globali_di_gioco::getHPp1()
{
    return this->hpP1;
}

int dati_Globali_di_gioco::getMAXhpP1()
{
    return this->maxHPp1;
}

int dati_Globali_di_gioco::getATTp1()
{
    return this->attP1;
}

int dati_Globali_di_gioco::getDEFp1()
{
    return this->defP1;
}

int dati_Globali_di_gioco::getMoney()
{
    return this->soldi;
}

void dati_Globali_di_gioco::setMOBhp(int x)
{
    this->hpMob = x;
}

void dati_Globali_di_gioco::setMOBatt(int x)
{
    this->attMob = x;
}

int dati_Globali_di_gioco::getMOBhp()
{
    return this->hpMob;
}

int dati_Globali_di_gioco::getMOBatt()
{
    return this->attMob;
}

void dati_Globali_di_gioco::setHPp1(int x)
{
    this->hpP1 = x;
}

void dati_Globali_di_gioco::setMAXhpP1(int x)
{
    this->maxHPp1 = x;
}

void dati_Globali_di_gioco::setDEFp1(int x)
{
    this->defP1 = x;
}

void dati_Globali_di_gioco::setATTp1(int x)
{
    this->attP1 = x;
}

void dati_Globali_di_gioco::setMoney(int x)
{
    this->soldi = x;
}

void dati_Globali_di_gioco::setMyPa(int x)
{
    this->PA = x;
}

bool dati_Globali_di_gioco::getSTORM()
{
    return this->potere_STORM;
}

int dati_Globali_di_gioco::getREBIRTH()
{
    return this->value_REBIRTH;
}

bool dati_Globali_di_gioco::getNEXT()
{
    return this->potere_NEXT;
}

bool dati_Globali_di_gioco::getBACK()
{
    return this->potere_BACK;
}

void dati_Globali_di_gioco::setSTORM(bool x)
{
    this->potere_STORM = x;
}

void dati_Globali_di_gioco::setREBIRTH(int x)
{
    this->value_REBIRTH = x;
}

void dati_Globali_di_gioco::setNEXT(bool x)
{
    this->potere_NEXT = x;
}

void dati_Globali_di_gioco::setBACK(bool x)
{
    this->potere_BACK = x;
}

bool dati_Globali_di_gioco::getMANOd()
{
    return this->MANOd;
}

void dati_Globali_di_gioco::setMANOd(bool x)
{
    this->MANOd = x;
}

bool dati_Globali_di_gioco::getMANOs()
{
    return this->MANOs;
}

void dati_Globali_di_gioco::setMANOs(bool x)
{
    this->MANOs = x;
}
