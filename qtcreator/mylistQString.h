#ifndef MYLISTQSTRING_H
#define MYLISTQSTRING_H
#include <QObject>
#include "ui_mainwindow.h"
typedef QString stiro;

class mylistQString : public QObject
{
    Q_OBJECT
private:
    mylistQString *testa;
    mylistQString *coda;
    mylistQString *iteratore;
    mylistQString *Pnext;
    mylistQString *Pprec;

    stiro oggetto;
    int index;
    int lunghezza_lista;

public:
    explicit mylistQString(QObject *parent = nullptr);

public slots:
    mylistQString*& Inext();
    QString InextSimilarToTErminal();
    mylistQString*& Iprec();
    QString IprecSimilarToTErminal();
    mylistQString*& readCoda();
    mylistQString*& readTesta();
    mylistQString*& readIterator();
    mylistQString*& getQStringX(int x);

    stiro& getOggetto();
    void setOggetto(QString x);

    void add(QString x);
    void view(QString &Terminale2, Ui::MainWindow *&Ui);
    void remove(stiro x);
    void ricalcolaLunghezzaEindex();
    int getLenght();
    void resetIteratorToTesta();
    void resetIteratorToCoda();
    void setIteratore(mylistQString*& puntatore);
    mylistQString*& getPrec();
    mylistQString*& getNext();
    bool IfxExistInList(QString x);

signals:
};

#endif // MYLISTQSTRING_H
