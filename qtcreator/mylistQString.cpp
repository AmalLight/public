#include "mylistQString.h"
#include <iostream>
using namespace std;

mylistQString::mylistQString(QObject *parent) : QObject(parent)
{
    this->testa = nullptr;
    this->coda = this->testa;
    this->iteratore = this->testa;
    this->Pnext = this->testa;
    this->Pprec = this->testa;

    this->index = 0;
    this->lunghezza_lista = 0;
}

void mylistQString::add(QString x)
{
    if (this->testa == nullptr)
    {
        this->testa = new mylistQString();
        this->coda = this->testa;
        this->lunghezza_lista = 1;

        this->testa->oggetto = x;
        this->testa->index = 1;
        this->testa->Pnext = this->coda;
        this->testa->Pprec = this->coda;

        this->coda->Pnext = this->testa;
        this->coda->Pprec = this->testa;
        this->iteratore = this->testa;
    }

    else
    {
        mylistQString *tmp = new mylistQString();
        tmp->oggetto = x;

        this->coda->Pnext = tmp;
        tmp->Pprec = this->coda,
        tmp->index = this->coda->index+1;

        tmp->Pnext = this->testa;
        this->testa->Pprec = tmp;

        this->lunghezza_lista += 1;
        this->coda = tmp;
    }
}

mylistQString*& mylistQString::Inext()
{
    this->iteratore = this->iteratore->Pnext;
    return this->iteratore;
}

QString mylistQString::InextSimilarToTErminal()
{
    QString tmp = this->iteratore->getOggetto();
    this->iteratore = this->iteratore->Pnext;
    return tmp;
}

QString mylistQString::IprecSimilarToTErminal()
{
    QString tmp = this->iteratore->getOggetto();
    this->iteratore = this->iteratore->Pprec;
    return tmp;
}

mylistQString*& mylistQString::Iprec()
{
    this->iteratore = this->iteratore->Pprec;
    return this->iteratore;
}

mylistQString*& mylistQString::readCoda()
{
    return this->coda;
}

mylistQString*& mylistQString::readTesta()
{
    return this->testa;
}

void mylistQString::view(QString &Terminale2, Ui::MainWindow *&Ui)
{
    if (this->testa == nullptr) {

        Ui->out2->append("\n\nNon ci sono elementi da stampare, la lista é vuota.");
        return;
    }

    Terminale2 = "";
    mylistQString *ctesta = testa;
    ctesta = ctesta->Pnext;
    while (ctesta != this->testa)
    {
        Terminale2 += ctesta->oggetto + "\n\n";
        ctesta = ctesta->Pnext;
    }   Terminale2 += ctesta->oggetto;

    Ui->out2->setText(Terminale2);
}

mylistQString*& mylistQString::readIterator()
{
    return this->iteratore;
}

void mylistQString::remove(stiro x)
{
    if (this->testa == nullptr) return;
    mylistQString *ctesta = this->testa;

    if (ctesta->oggetto != x)
        while ((ctesta->Pnext->oggetto != x) && (ctesta != coda))
            ctesta = ctesta->Pnext;

    if ((ctesta->Pnext->oggetto != x)
     && (ctesta->oggetto != x)) return;

    mylistQString *ctesta2;

    if (this->lunghezza_lista == 1)
    {
        ctesta2 = ctesta;
        delete ctesta2;
        ctesta2 = nullptr;

        this->testa = ctesta2;
        this->coda = ctesta2;
        this->iteratore = ctesta2;
        this->Pnext = ctesta2;
        this->Pprec = ctesta2;
    }

    else if (ctesta->oggetto == x) {

         ctesta2 = ctesta;
         this->testa = this->testa->Pnext;
         this->testa->Pprec = this->coda;
         this->coda->Pnext = this->testa;

         this->iteratore = this->testa;
         delete ctesta2;
    }

    else  if (ctesta->oggetto != x) {

        ctesta2 = ctesta->Pnext;

        if ((ctesta == this->testa)
         && (ctesta2 == this->coda)) {

            ctesta->Pprec = ctesta;
            this->coda = ctesta;
        }

        else if (ctesta2 == this->coda) {

            ctesta->Pnext = this->coda->Pnext;
            this->testa->Pprec = ctesta;
            this->coda = ctesta;
        }

        else if (ctesta2 != this->coda)
            ctesta->Pnext = ctesta2->Pnext;

        this->iteratore = this->testa;
        delete ctesta2;
    }

    this->ricalcolaLunghezzaEindex();
}

void mylistQString::ricalcolaLunghezzaEindex()
{
    mylistQString *ctesta = this->testa;

    if (this->testa == nullptr) {

        this->lunghezza_lista  = 0;
        return;
    }

    else {

        ctesta = ctesta->Pnext;

        this->testa->index = 1;
        this->lunghezza_lista = 1;

        while (ctesta != this->testa)
        {
            ctesta->index = ctesta->Pprec->index+1;
            this->lunghezza_lista += 1;

            ctesta = ctesta->Pnext;
        }
    }
}

int mylistQString::getLenght()
{
    return this->lunghezza_lista;
}

mylistQString*& mylistQString::getQStringX(int x)
{
    mylistQString *ctesta = this->testa;
    int myQStringIterator = 1;

    if ((x <= 0) || (ctesta == nullptr)) {

        mylistQString *ctesta2 = nullptr;
        return ctesta2;
    }

    while (myQStringIterator < x) {

        ctesta = ctesta->Pnext;
        if (ctesta == nullptr) return ctesta;
        else myQStringIterator++;
    }

    return ctesta;
}

void mylistQString::resetIteratorToTesta()
{
    this->iteratore = this->testa;
}

stiro& mylistQString::getOggetto()
{
    return this->oggetto;
}

void mylistQString::setOggetto(QString x)
{
   this->oggetto = x;
}

void mylistQString::resetIteratorToCoda()
{
    this->iteratore = this->coda;
}

void mylistQString::setIteratore(mylistQString *&puntatore)
{
    this->iteratore = puntatore;
}

mylistQString*& mylistQString::getNext()
{
    return this->Pnext;
}

mylistQString*& mylistQString::getPrec()
{
    return this->Pprec;
}

bool mylistQString::IfxExistInList(QString x)
{
    mylistQString *ctesta = this->testa;

    if (ctesta->Pnext != nullptr)
        ctesta = ctesta->Pnext;

    while (ctesta != this->testa)
    {
        if (ctesta->getOggetto() == x)
            return true;

        else ctesta = ctesta->Pnext;
    }

    if (ctesta->getOggetto() == x)
        return true;

    else return false;
}
