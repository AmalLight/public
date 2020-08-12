#include "MiniMap.h"
#include <iostream>
using namespace std;

MiniMap::MiniMap(QObject *parent) : QObject(parent)
{
    this->Matrice = nullptr;
    this->altezzaY = 0;
    this->lunghezzaX = 0;

    this->altezza_aggiunta = false;
    this->lunghezza_aggiunta = false;

    //y = -1;
    this->altezza_aggiunta_up = false;
    //y = this->lunghezzaX;
    this->altezza_aggiunta_down = false;
    //x = -1;
    this->lunghezza_aggiunta_left = false;
    //x = this->altezzaY;
    this->lunghezza_aggiunta_right = false;
}

void MiniMap::create_new_miniMap(int &y, int &x, QString symbol, int index_livello)
{
    if (this->Matrice == nullptr) {

        this->Matrice = new mylistQString;
        this->Matrice->add(symbol);
        this->altezzaY = 1;
        this->lunghezzaX = 1;
    }

    else
    {
        if ((x < this->lunghezzaX && x != -1)
           && (y < this->altezzaY && y != -1)) {

            for (int tmp_y = 0; tmp_y < this->altezzaY; tmp_y++)
                for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++) {

                    if (tmp_x == x && tmp_y == y) {

                        this->Matrice->readIterator()->setOggetto(symbol);
                        this->Matrice->resetIteratorToTesta();
                        return;
                    }

                    else this->Matrice->Inext();
                }
        }

        else  {

            mylistQString *tmp_Matrice = new mylistQString;

            if (x == -1)
            {
                    for (int tmp_y = 0; tmp_y < this->altezzaY; tmp_y++)
                    {
                        for (int tmp_x = 0; tmp_x < this->lunghezzaX+1; tmp_x++)
                            tmp_Matrice->add(this->stampQStringSpace(index_livello));
                    }

                    this->lunghezzaX += 1;

                    for (int tmp_y = 0; tmp_y < this->altezzaY; tmp_y++)
                    {
                        for (int tmp_x = 0; tmp_x < this->lunghezzaX-1; tmp_x++)
                        {
                            if (tmp_x == 0)
                                tmp_Matrice->Inext();

                            tmp_Matrice->readIterator()->setOggetto(this->Matrice->readIterator()->getOggetto());
                            this->Matrice->Inext();
                            tmp_Matrice->Inext();
                        }
                    }
            }

            else if (x == this->lunghezzaX)
            {
                    for (int tmp_y = 0; tmp_y < this->altezzaY; tmp_y++)
                    {
                        for (int tmp_x = 0; tmp_x < this->lunghezzaX+1; tmp_x++)
                            tmp_Matrice->add(this->stampQStringSpace(index_livello));
                    }

                    this->lunghezzaX += 1;

                    for (int tmp_y = 0; tmp_y < this->altezzaY; tmp_y++)
                    {
                        for (int tmp_x = 0; tmp_x < this->lunghezzaX-1; tmp_x++)
                        {
                            tmp_Matrice->readIterator()->setOggetto(this->Matrice->readIterator()->getOggetto());
                            this->Matrice->Inext();
                            tmp_Matrice->Inext();

                            if (tmp_x == this->lunghezzaX-2)
                                tmp_Matrice->Inext();
                        }
                    }
            }

            else if (y == -1)
            {
                    for (int tmp_y = 0; tmp_y < this->altezzaY+1; tmp_y++)
                    {
                        for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++)
                            tmp_Matrice->add(this->stampQStringSpace(index_livello));
                    }

                    this->altezzaY += 1;

                    for (int tmp_y = 0; tmp_y < 1; tmp_y++)
                        for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++)
                            tmp_Matrice->Inext();

                    for (int tmp_y = 0; tmp_y < this->altezzaY-1; tmp_y++)
                    {
                        for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++)
                        {
                            tmp_Matrice->readIterator()->setOggetto(this->Matrice->readIterator()->getOggetto());
                            this->Matrice->Inext();
                            tmp_Matrice->Inext();
                        }
                    }
            }

            else if (y == this->altezzaY)
            {
                    for (int tmp_y = 0; tmp_y < this->altezzaY+1; tmp_y++)
                    {
                        for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++)
                            tmp_Matrice->add(this->stampQStringSpace(index_livello));
                    }

                    this->altezzaY += 1;

                    for (int tmp_y = 0; tmp_y < this->altezzaY-1; tmp_y++)
                    {
                        for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++)
                        {
                            tmp_Matrice->readIterator()->setOggetto(this->Matrice->readIterator()->getOggetto());
                            this->Matrice->Inext();
                            tmp_Matrice->Inext();
                        }
                    }
            }

            tmp_Matrice->resetIteratorToTesta();
            this->Matrice->deleteLater();
            this->Matrice = tmp_Matrice;

            if (x == -1) x = 0;
            else if (y == -1) y = 0;

            for (int tmp_y = 0; tmp_y < this->altezzaY; tmp_y++)
                for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++) {

                    if (tmp_y == y && tmp_x == x)
                    {
                        this->Matrice->readIterator()->setOggetto(symbol);
                        this->Matrice->resetIteratorToTesta();
                        return;
                    }

                    else this->Matrice->Inext();
                }
        }
    }

}

QString MiniMap::getQStringFromXY(int index_livello, int y, int x)
{
    if ((y < 0) || (y > this->altezzaY-1))
        return this->stampQStringSpace(index_livello);

    if ((x < 0) || (x > this->lunghezzaX-1))
        return this->stampQStringSpace(index_livello);

    for (int tmp_y = 0; tmp_y < this->altezzaY; tmp_y++)
        for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++) {
            if ((tmp_y == y) && (tmp_x == x))
            {
                QString da_ritorno = this->Matrice->readIterator()->getOggetto();
                this->Matrice->resetIteratorToTesta();
                return da_ritorno;
            }

            else this->Matrice->Inext();
        }
}

mylistQString*& MiniMap::getPOINTERFromXY(int index_livello, int y, int x)
{
    mylistQString *tmp_point = nullptr;

    if (y < 0 || y > this->altezzaY-1)
        return tmp_point;

    if (x < 0 || x > this->lunghezzaX-1)
        return tmp_point;

    for (int tmp_y = 0; tmp_y < this->altezzaY; tmp_y++)
        for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++) {
            if (tmp_y == y && tmp_x == x)
            {
                mylistQString *da_ritorno = this->Matrice->readIterator();
                this->Matrice->resetIteratorToTesta();
                return da_ritorno;
            }

            else this->Matrice->Inext();
        }
}

QString MiniMap::getThisMiniMap(int index_livello, mylistQString *stanze_visitate)
{
    QString tmp = "";

    for (int tmp_y = 0; tmp_y < this->altezzaY; (tmp_y++, tmp += "\n"))
    {
        for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++)
        {
            if (
                    (stanze_visitate->IfxExistInList(this->Matrice->readIterator()->getOggetto()))
            ||
                    (stanze_visitate->IfxExistInList
                     (QString::number
                      (MiniMap::ExtractNumberToQstringRoom
                       (this->Matrice->readIterator()->getOggetto())
                      )
                     )
                    )
               )

                tmp += this->Matrice->readIterator()->getOggetto();

            else tmp += this->stampQStringSpace(index_livello);

            this->Matrice->Inext();
        }
    }

    this->Matrice->resetIteratorToTesta();
    return tmp;
}

QString MiniMap::getThisMiniMapNoLimit()
{
    QString tmp = "";

    for (int tmp_y = 0; tmp_y < this->altezzaY; (tmp_y++, tmp += "\n"))
    {
        for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++)
        {
            tmp += this->Matrice->readIterator()->getOggetto();

            this->Matrice->Inext();
        }
    }

    this->Matrice->resetIteratorToTesta();
    return tmp;
}

//static be only specifed inside the class definition.
QString MiniMap::stampQStringSpace(int index_livello)
{
    QString tmp1_QString = QString::number(index_livello);
    int tmp1_int = tmp1_QString.length();

    QString da_ritorno = "";
    da_ritorno = "  ";

    for (int i = 0; i < tmp1_int; i++)
        da_ritorno += " ";

    return da_ritorno;
}

//static be only specifed inside the class definition.
QString MiniMap::stampQStringRoomNumber(int index_livello, int Number)
{
    QString da_ritorno = "[" + QString::number(Number) + "]";
    int lenght_Number = QString::number(Number).length();
    int lenght_index_livello = QString::number(index_livello).length();

    for (int i = lenght_Number; i < lenght_index_livello; i++)
        da_ritorno += " ";

    return da_ritorno;
}

//static be only specifed inside the class definition.
int MiniMap::ExtractNumberToQstringRoom(QString x)
{
    if (x.toStdString()[0] == ' ')
        return 0;

    QString tmpQString = x;
    string tmpstring = tmpQString.toStdString();
    tmpQString = "";

    for (int i = 1; true; i++) {

        if (tmpstring[i] == ']') break;

        else tmpQString += tmpstring[i];
    }

    int tmpNumberInQString = tmpQString.toInt();

    return tmpNumberInQString;
}

void MiniMap::getXYFromNumber(int index_livello, int Number, int &y, int &x)
{
    QString tmpQString = "[" + QString::number(Number) + "]";
    QString tmpQString2 = "[" + QString::number(Number) + "]";

    int lenght_Number = QString::number(Number).length();
    int lenght_index_livello = QString::number(index_livello).length();

    for (int i = lenght_Number; i < lenght_index_livello; i++) {
        tmpQString += " ";
        tmpQString2 += "-";
    }

    for (int tmp_y = 0; tmp_y < this->altezzaY; tmp_y++)
        for (int tmp_x = 0; tmp_x < this->lunghezzaX; tmp_x++)
        {
            if ((this->Matrice->readIterator()->getOggetto() == tmpQString)
               || (this->Matrice->readIterator()->getOggetto() == tmpQString2))
            {
                y = tmp_y;
                x = tmp_x;
            }

            this->Matrice->Inext();
        }
}

void MiniMap::TramuteQStringRoomByPOINTER(int index_livello, mylistQString *&pointer)
{
    QString tmp_possibileSostituto = pointer->getOggetto();
    int tmp_lenght = tmp_possibileSostituto.length();
    QString QStringSostituto = "";

    for (int i = tmp_lenght-1; i > -1; i--)
    {
        if (tmp_possibileSostituto.toStdString()[i] == ' ')
            QStringSostituto += '-';

        else if (tmp_possibileSostituto.toStdString()[i] != ' ')
            QStringSostituto =
                    (tmp_possibileSostituto.toStdString()[i]
                     + QStringSostituto);
    }

    pointer->setOggetto(QStringSostituto);
}

mylistQString *&MiniMap::getMatrice()
{
    return this->Matrice;
}

int MiniMap::getAltezzaY()
{
    return this->altezzaY;
}

int MiniMap::getLunghezzaX()
{
    return this->lunghezzaX;
}
