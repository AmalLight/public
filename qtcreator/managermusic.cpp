#include "managermusic.h"
#include <iostream>
using namespace std;

//apt-get install qtmultimedia5-*
//apt-get install -f
//apt-get install qtmultimedia5-*
//QT += multimedia
//QT += widgets

#include <QFile>

managerMusic::managerMusic(QObject *parent): QObject(parent)
{
    this->playlist = new mylistQMediaPlayer();
    this->my_dir = my_dir.currentPath();
    text_finish_load = "R = Ritmo;"
                "\nA = Allegra (medio veloce);"
                "\nS = Serena (volume basso);"
                "\nM = Agitata (volume medio-alto);"
                "\nV = Veloce;"
                "\nB = Beat;"
                "\nD = Melodia;"
                "\nP = Piano (musica lenta);";

    this->remaningtime = 174968 + 1000;
}

void managerMusic::create_playlist()
{
    QMediaPlayer *tmp_song;

    this->my_dir.setPath(this->my_dir.currentPath() + "/OZ_Game_sound/");
    QStringList lista = this->my_dir.entryList();
    QString debug_takeList = "";
    QFile *open_flag;

    while (!lista.empty()) {

        debug_takeList = lista.takeLast();
        while ((debug_takeList.length() <= 5) && (!lista.empty()))
            debug_takeList = lista.takeLast();

        if (debug_takeList.length()<=5) debug_takeList = "";

        if (debug_takeList != "") {

            tmp_song = new QMediaPlayer;
            tmp_song->setMedia(QUrl::fromLocalFile(this->my_dir.path() + "/" + debug_takeList));

            open_flag = new QFile;
            open_flag->setFileName(this->my_dir.path() + "/" + debug_takeList);
            open_flag->open(QIODevice::ReadOnly);

            tmp_song->setObjectName(debug_takeList + ";");
            this->playlist->add(tmp_song);

            delete open_flag;
        }
    }

    emit this->my_playlist_is_created();
}

void managerMusic::pause()
{
    this->remaningtime = (this->playlist->readIterator()->duration() -
                          (this->playlist->readIterator()->position()));

    this->timer_temporaneo->stop();
    delete this->timer_temporaneo;
    this->timer_temporaneo = nullptr;

    this->playlist->readIterator()->pause();
    emit this->pause_recive(this->playlist->readIterator());
}

void managerMusic::play()
{
    //non é possibile stoppare this->timer_temporaneo->singleShot(..);
    //per stoppare ho usato: setInterval(..), poi start();

    this->timer_temporaneo = new QTimer;
    int tmp = this->remaningtime;

    if (this->remaningtime == 999999999) {

        tmp = this->playlist->readIterator()->duration();
        this->timer_temporaneo->setInterval(tmp);
        connect(this->timer_temporaneo, &QTimer::timeout, [&]() {

            this->next();
        }); this->timer_temporaneo->start();
    }

    else
    {
        this->timer_temporaneo->setInterval(tmp);
        connect(this->timer_temporaneo, &QTimer::timeout, [&]() {

            this->next();
        }); this->timer_temporaneo->start();
    }

    this->playlist->readIterator()->play();
    emit this->play_recive(this->playlist->readIterator());
}

void managerMusic::next()
{
    this->remaningtime = 999999999;
    if (this->timer_temporaneo != nullptr)
    delete this->timer_temporaneo;

    this->playlist->readIterator()->stop();
    int tmp_volume = this->playlist->readIterator()->volume();
    this->playlist->Inext();
    this->playlist->readIterator()->setVolume(tmp_volume);
    emit this->next_recive(this->playlist->readIterator());
    this->play();
}

void managerMusic::prec()
{
    this->remaningtime = 999999999;
    if (this->timer_temporaneo != nullptr)
    delete this->timer_temporaneo;

    this->playlist->readIterator()->stop();
    int tmp_volume = this->playlist->readIterator()->volume();
    this->playlist->Iprec();
    this->playlist->readIterator()->setVolume(tmp_volume);
    emit this->prec_recive(this->playlist->readIterator());
    this->play();
}

QTimer*& managerMusic::getTimer()
{
    return this->timer_temporaneo;
}

QDir managerMusic::getMyDir()
{
    return this->my_dir;
}

mylistQMediaPlayer*& managerMusic::getMyList()
{
    return this->playlist;
}

QString managerMusic::getTextFinishLoad()
{
    return this->text_finish_load;
}
