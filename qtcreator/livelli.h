#ifndef LIVELLI_H
#define LIVELLI_H
#include <QObject>
#include "mylistQStringMaps.h"

class livelli : public QObject
{
    Q_OBJECT
private:
    mylistQStringMaps *mappe_per_questo_livello;
    int index_livello;
    int numero_di_livelli;

    livelli *prec;
    livelli *next;
    livelli *main;
    livelli *Iteratore1;
    livelli *Iteratore2;
    livelli *testa;
    livelli *coda;

public:
    explicit livelli(QObject *parent = nullptr);

signals:

public slots:
    void add_liv();
    mylistQStringMaps*& getMappeIT1();
    mylistQStringMaps*& getMappe();

    void setIteratore1(livelli *&x);
    livelli*& getEntrata();
    livelli*& getUscita();
    livelli*& getMain();
    livelli*& getTesta();
    livelli*& getCoda();

    int get_index_livello();
    void set_index_livello(int x);
    livelli*& getIteratore1();
    livelli*& getIteratore2();
    void setIteratore2(livelli *&x);
    void reciveRifaiOpenWorld(mylistQStringMaps *&pointer);
};

#endif // LIVELLI_H
