#ifndef MINIMAP_H
#define MINIMAP_H
#include "mylistQString.h"
#include <QObject>

class MiniMap : public QObject
{
    Q_OBJECT
private:
    mylistQString *Matrice;

    //partendo da 0
    int altezzaY;
    //partendo da 1
    int lunghezzaX;

    bool altezza_aggiunta;
    bool lunghezza_aggiunta;
    bool altezza_aggiunta_up;
    bool altezza_aggiunta_down;
    bool lunghezza_aggiunta_left;
    bool lunghezza_aggiunta_right;

public:
    explicit MiniMap(QObject *parent = nullptr);

signals:

public slots:
    mylistQString *&getPOINTERFromXY(int index_livello, int y, int x);
    mylistQString*& getMatrice();

    QString getThisMiniMap(int index_livello, mylistQString *stanze_visitate);
    QString getThisMiniMapNoLimit();
    QString getQStringFromXY(int index_livello, int y, int x);

    static QString stampQStringSpace(int index_livello);
    static QString stampQStringRoomNumber(int index_livello, int Number);
    static int ExtractNumberToQstringRoom(QString x);

    void create_new_miniMap(int &y, int &x, QString symbol, int index_livello);
    void getXYFromNumber(int index_livello, int Number, int &y, int &x);
    void TramuteQStringRoomByPOINTER(int index_livello, mylistQString *&pointer);

    int getAltezzaY();
    int getLunghezzaX();
};

#endif // MYLISTQSTRINGMINIMAP_H
