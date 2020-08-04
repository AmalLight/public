#include "mylistQMediaPlayer.h"
#include <iostream>
using namespace std;

/*mylist *uno = new mylist();
QString tmp = "";
QObject::connect(uno, &mylist::add_recive, [&]() {

    tmp += "aggiunto testo a lista\n";
    ui->out3->setText(tmp);
});*/

/*DIFFERENZA TRA &mylist::add_recive E SIGNAL(add_recive(pippo))*/
//SIGNAL(add_recive(pippo)) richiede SLOT(....(pippo)),
//non permetterà [&]().

mylistQMediaPlayer::mylistQMediaPlayer(QObject *parent): QObject(parent)
{
    this->testa = nullptr;
    this->coda = this->testa;
    this->iteratore = this->testa;
    this->Pnext = this->testa;
    this->Pprec = this->testa;

    this->index = 0;
    this->lunghezza_lista = 0;
}

void mylistQMediaPlayer::add(pippo *&canzoneX)
{
    if (this->testa == nullptr)
    {
        this->testa = new mylistQMediaPlayer();
        this->coda = this->testa;
        this->lunghezza_lista = 1;

        this->testa->oggetto = canzoneX;
        this->testa->index = 1;
        this->testa->Pnext = this->coda;
        this->testa->Pprec = this->coda;

        this->coda->Pnext = this->testa;
        this->coda->Pprec = this->testa;
        this->iteratore = this->testa;
    }

    else
    {
        mylistQMediaPlayer *tmp = new mylistQMediaPlayer();
        tmp->oggetto = canzoneX;

        this->coda->Pnext = tmp;
        tmp->Pprec = this->coda,
        tmp->index = this->coda->index+1;

        tmp->Pnext = this->testa;
        this->testa->Pprec = tmp;

        this->lunghezza_lista += 1;
        this->coda = tmp;
    }

    emit this->add_recive(canzoneX);
}

pippo*& mylistQMediaPlayer::Inext()
{
    this->iteratore = this->iteratore->Pnext;
    return this->iteratore->oggetto;
}

pippo*& mylistQMediaPlayer::Iprec()
{
    this->iteratore = this->iteratore->Pprec;
    return this->iteratore->oggetto;
}

pippo*& mylistQMediaPlayer::readIterator()
{
    return this->iteratore->oggetto;
}

pippo*& mylistQMediaPlayer::readCoda()
{
    return this->coda->oggetto;
}

void mylistQMediaPlayer::view(QString &Terminale2)
{
    mylistQMediaPlayer *ctesta = this->testa;

    Terminale2 = "";
    ctesta = ctesta->Pnext;
    while (ctesta != this->testa)
    {
        Terminale2 += ctesta->oggetto->objectName() + "\n";
        ctesta = ctesta->Pnext;
    }   Terminale2 += ctesta->objectName();
}
