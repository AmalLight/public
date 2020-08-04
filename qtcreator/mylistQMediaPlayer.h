#ifndef MYLISTQMEDIAPLAYER_H
#define MYLISTQMEDIAPLAYER_H
#include <QObject>
#include <QtMultimedia/QMediaPlayer>
#include <QDir>
typedef QMediaPlayer pippo;

class mylistQMediaPlayer : public QObject
{
    Q_OBJECT
private:
    mylistQMediaPlayer *testa;
    mylistQMediaPlayer *coda;
    mylistQMediaPlayer *iteratore;
    mylistQMediaPlayer *Pnext;
    mylistQMediaPlayer *Pprec;

    pippo *oggetto;
    int index;
    int lunghezza_lista;

public:
    explicit mylistQMediaPlayer(QObject *parent = 0);

public slots:
    pippo*& Inext();
    pippo*& Iprec();
    void add(pippo *&canzoneX);
    pippo*& readIterator();
    pippo*& readCoda();
    void view(QString &Terminale2);

signals:
    void add_recive(pippo*&);
};

#endif // MYLISTQMEDIAPLAYER_H
