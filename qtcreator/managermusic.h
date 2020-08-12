#ifndef MANAGERMUSIC_H
#define MANAGERMUSIC_H
#include <QScrollBar>
#include <QTextBrowser>
#include <QKeyEvent>
#include <QTimer>
#include "mylistQMediaPlayer.h"

class managerMusic : public QObject
{
    Q_OBJECT
private:
    mylistQMediaPlayer *playlist;
    QTimer *timer_temporaneo;

    QString text_finish_load;
    QDir my_dir;
    quint64 remaningtime;

public:
    explicit managerMusic(QObject *parent = nullptr);

public slots:
    void create_playlist();
    void pause();
    void play();
    void next();
    void prec();
    QDir getMyDir();
    mylistQMediaPlayer*& getMyList();
    QString getTextFinishLoad();
    QTimer*& getTimer();

signals:
    void my_playlist_is_created();
    void play_recive(pippo*&);
    void pause_recive(pippo*&);
    void next_recive(pippo*&);
    void prec_recive(pippo*&);
};

#endif // MANAGERMUSIC_H
