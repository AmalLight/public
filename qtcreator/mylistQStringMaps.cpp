#include "mylistQStringMaps.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <QTimer>
#include <QTime>
#include <QDebug>
using namespace std;

mylistQStringMaps::mylistQStringMaps(QObject *parent) : QObject(parent)
{
    this->altezza = 16;
    this->lunghezza = 27;
    this->index = 0;
    this->numero_di_mappe = 0;
    this->p1_x = 0;
    this->p1_y = 0;
    this->mob_x = 0;
    this->mob_y = 0;
    this->x_attuale = 0;
    this->y_attuale = 0;

    this->testa = nullptr;
    this->coda = nullptr;
    this->Mappa = nullptr;
    this->up = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->Iteratore1 = nullptr;
    this->save_ctesta = nullptr;
    this->main = this;

    this->Mappa_aggiunta = false;
    this->simbolo_vuoto = " ";
    this->simbolo_tree = "♧";
    this->simbolo_pieno = "▤";
    this->simbolo_porta = "◧";
    this->simbolo_scala = "▣";
    this->puoi_entrare_in_una_porta = false;
    this->puoi_entrare_in_unLivello = false;

    this->up_non_fallito = true;
    this->down_non_fallito = true;
    this->right_non_fallito = true;
    this->left_non_fallito = true;

    this->simbolo_P1 = "◑";
    this->simbolo_mob = "◉";
    this->simbolo_NPC = "☯";
    this->Iteratore_fallimenti = nullptr;
    this->movimenti = 0;
    this->valore_per_i_movimenti = true;

    this->PointerCordinataXtmp = nullptr;
    this->PointerCordinataYtmp = nullptr;
    this->PointerSimbolToMoveTmp = "";
    this->nelPercorsOincontroFreccia = false;
    this->connect_avvenuto = false;
}

int mylistQStringMaps::get_numero_di_mappe()
{
    return this->main->numero_di_mappe;
}

void mylistQStringMaps::addRoom()
{
    if (this->main->Mappa_aggiunta == true) return;

    else
    {
        this->Mappa = new mylistQString;
        for (int y=0; y < this->main->altezza; y++) {
            if ((y == 0) || (y == this->main->altezza-1))
                for (int x = 0; x < this->main->lunghezza; x++)
                    this->Mappa->add(this->main->simbolo_pieno);
            else
                for (int x=0; x < this->main->lunghezza; x++) {

                    if ((x == 0) || (x == this->main->lunghezza-1))
                        this->Mappa->add(this->main->simbolo_pieno);
                    else if ((x == 12) || (y == 8) ||
                             (x == 11) || (x == 13))
                        this->Mappa->add(this->main->simbolo_vuoto);
                    else
                        this->Mappa->add(this->main->simbolo_tree);
                }
        }

        this->main->Mappa_aggiunta = true;

        this->setPlayer("⇦", 2, 8);
        this->setPlayer("⇧", 12, 1);
        this->setPlayer("⇨", this->main->lunghezza-3, 8);
        this->setPlayer("⇩", 12, this->main->altezza-2);

        if (this->index == 1)
            this->setPlayer(this->main->simbolo_P1, 3, 8);
    }
}

void mylistQStringMaps::sendMapToTextBrowser1(QString &Terminale1,
                                              Ui::MainWindow *&Ui)
{
    if (this->left != nullptr) {

        if ((this->main->p1_x != 3) || (this->main->p1_y != 8))
            this->setPlayer(this->main->simbolo_porta, 3, 8);
    }

    if (this->up != nullptr) {

        if ((this->main->p1_x != 12) || (this->main->p1_y != 2))
            this->setPlayer(this->main->simbolo_porta, 12, 2);
    }

    if (this->right != nullptr) {

        if ((this->main->p1_x != this->main->lunghezza-4) || (this->main->p1_y != 8))
            this->setPlayer(this->main->simbolo_porta, this->main->lunghezza-4, 8);
    }

    if (this->down!= nullptr) {

        if ((this->main->p1_x != 12) || (this->main->p1_y != this->main->altezza-3))
            this->setPlayer(this->main->simbolo_porta, 12, this->main->altezza-3);
    }

    if (this->main->puoi_entrare_in_unLivello == true) {

        if ((this->main->p1_x != 12) || (this->main->p1_y != 8))
            this->setPlayer(this->main->simbolo_scala, 12, 8);
    }

    if (
            (this->index > 1)
        &&
            (
                ((this->left != nullptr) &&
                 (this->left->index > this->index))
        ||
                ((this->up != nullptr) &&
                 (this->up->index > this->index))
        ||
                ((this->right != nullptr) &&
                 (this->right->index > this->index))
        ||
                ((this->down != nullptr) &&
                 (this->down->index > this->index))
            )
        )
    {
        this->setPlayer(this->main->simbolo_NPC, 12, 8);

        int mobX = 0; int mobY = 0;

        this->identify(this->main->getSimboloMOB(),
                       mobX, mobY);

        if ((mobX == 0) && (mobY == 0))
        {
            int random = 0;
            loopSETmob:;

            //da 0 a 4
            random = rand() % 5;

            if (random == 0)
                goto loopSETmob;

            //1=up
            else if ((random == 1) &&
                     (this->up != nullptr) &&
                     (this->up->index <= this->index-1))
                goto loopSETmob;

            //2=right
            else if ((random == 2) &&
                     (this->right != nullptr) &&
                     (this->right->index <= this->index-1))
                goto loopSETmob;

            //3=down
            else if ((random == 3) &&
                     (this->down != nullptr) &&
                     (this->down->index <= this->index-1))
                goto loopSETmob;

            //4=left
            else if ((random == 4) &&
                     (this->left != nullptr) &&
                     (this->left->index <= this->index-1))
                goto loopSETmob;

            if (random == 1)
            {
                mobX = 12; mobY = 2;
                this->setPlayer
                        (this->main->simbolo_mob,
                         mobX, mobY);
            }

            else if (random == 2)
            {
                mobX = this->main->lunghezza-4; mobY = 8;
                this->setPlayer(this->main->simbolo_mob,
                                mobX, mobY);
            }

            else if (random == 3)
            {
                mobX = 12; mobY = this->main->altezza-3;
                this->setPlayer(this->main->simbolo_mob,
                                mobX, mobY);
            }

            else if (random == 4)
            {
                mobX = 3; mobY = 8;
                this->setPlayer(this->main->simbolo_mob,
                                mobX, mobY);
            }
        }

        this->main->mob_x = mobX;
        this->main->mob_y = mobY;
    }

    Terminale1 = "";

    for (int y=0; y < this->main->altezza; y++)
        for (int x=0; x < this->main->lunghezza; x++) {

            if ((x == 0) && (y == 0))
                Terminale1.append("\n");

            if (x == 0)
                Terminale1.append("  ");

            Terminale1.append
            (this->Mappa->readIterator()->getOggetto());

            if (x == this->main->lunghezza-1)
                Terminale1.append("\n");

            this->Mappa->Inext();
        }

    Ui->out1->setText(Terminale1);
    this->Mappa->resetIteratorToTesta();
}

void mylistQStringMaps::add1map(int index_livello)
{
    if (this->testa == nullptr)
    {        
        this->testa = new mylistQStringMaps;

        this->coda = this->testa;
        this->testa->index = 1;
        this->numero_di_mappe = 1;
        this->testa->main = this;
        this->save_ctesta = this->testa;

        this->testa->addRoom();
        this->testa->up = nullptr;
        this->testa->down = nullptr;
        this->testa->left = nullptr;
        this->testa->right = nullptr;

        this->Iteratore1 = this->testa;
        this->Iteratore_fallimenti = this->testa;

        int new_tmpy = 0;
        int new_tmpx = 0;
        this->main->oggetto_MiniMap = new MiniMap;
        this->main->oggetto_MiniMap->create_new_miniMap(new_tmpy, new_tmpx,
            this->main->oggetto_MiniMap->stampQStringRoomNumber(index_livello, 1),
                                                        index_livello);
    }

    else
    {
        int valore_direzionale = 0;
        int tmp_valore_direzionale = 0;
        int new_tmpy = 0, new_tmpx = 0;

        mylistQStringMaps *tmp = new mylistQStringMaps;
        tmp->main = this->coda->main;
        tmp->index = this->coda->index+1;
        tmp->setSimboloPg1(this->coda->main->getSimboloPg1());
        tmp->addRoom();

        tmp->up = nullptr;
        tmp->left = nullptr;
        tmp->right = nullptr;
        tmp->down = nullptr;
        this->numero_di_mappe += 1;

        loop:;

        if ((this->main->up_non_fallito != true)
        && (this->main->right_non_fallito != true)
        && (this->main->down_non_fallito != true)
        && (this->main->left_non_fallito != true))
        {
            new_tmpy = 0;
            new_tmpx = 0;
            loop2:;

            /*
            cout << "debug casual map" << endl;
            cout << "livello: " << index_livello << endl;
            cout << "cerco: " << this->main->Iteratore_fallimenti->index+1 << endl;
            cout << "devo inserire: " << tmp->index << endl;
            cout << "save_ctesta: " << this->main->save_ctesta->index << endl << endl;
            cout << this->oggetto_MiniMap->
                    getThisMiniMapNoLimit().toStdString() << endl;
            */

            this->main->oggetto_MiniMap->
                    getXYFromNumber(index_livello,
                                    this->main->Iteratore_fallimenti->index,
                                    new_tmpy,
                                    new_tmpx);
            //1 = up
            if ((this->main->Iteratore_fallimenti->up == nullptr) &&
                (this->main->oggetto_MiniMap->
                 getQStringFromXY(index_livello, new_tmpy-1, new_tmpx) ==
                 this->main->oggetto_MiniMap->stampQStringSpace(index_livello)))
            {
                this->main->Iteratore_fallimenti->up = tmp;
                this->main->Iteratore_fallimenti->up->down =
                        this->main->Iteratore_fallimenti;

                this->main->coda = tmp;
                tmp_valore_direzionale = 1;
            }

            //3 = down
            else if ((this->main->Iteratore_fallimenti->down == nullptr)
                 && (this->main->oggetto_MiniMap->
                     getQStringFromXY(index_livello, new_tmpy+1, new_tmpx) ==
                     this->main->oggetto_MiniMap->stampQStringSpace(index_livello)))
            {
                this->main->Iteratore_fallimenti->down = tmp;
                this->main->Iteratore_fallimenti->down->up =
                        this->main->Iteratore_fallimenti;

                this->main->coda = tmp;
                tmp_valore_direzionale = 3;
            }

            //2 = right
            else if ((this->main->Iteratore_fallimenti->right == nullptr)
                 && (this->main->oggetto_MiniMap->
                     getQStringFromXY(index_livello, new_tmpy, new_tmpx+1) ==
                     this->main->oggetto_MiniMap->stampQStringSpace(index_livello)))
            {
                this->main->Iteratore_fallimenti->right = tmp;
                this->main->Iteratore_fallimenti->right->left =
                        this->main->Iteratore_fallimenti;

                this->main->coda = tmp;
                tmp_valore_direzionale = 2;
            }

            //4 = left
            else if ((this->main->Iteratore_fallimenti->left == nullptr)
                 && (this->main->oggetto_MiniMap->
                     getQStringFromXY(index_livello, new_tmpy, new_tmpx-1) ==
                     this->main->oggetto_MiniMap->stampQStringSpace(index_livello)))
            {
                this->main->Iteratore_fallimenti->left = tmp;
                this->main->Iteratore_fallimenti->left->right =
                        this->main->Iteratore_fallimenti;

                this->main->coda = tmp;
                tmp_valore_direzionale = 4;
            }

            else if (tmp_valore_direzionale == 0)
            {
                while (true)
                {
                    if ((this->main->Iteratore_fallimenti->up != nullptr) &&
                        (this->main->Iteratore_fallimenti->up->index ==
                         this->main->Iteratore_fallimenti->index+1)) {

                            this->main->Iteratore_fallimenti =
                                this->main->Iteratore_fallimenti->up;

                            break;
                        }

                    else if ((this->main->Iteratore_fallimenti->down != nullptr) &&
                             (this->main->Iteratore_fallimenti->down->index ==
                              this->main->Iteratore_fallimenti->index+1)) {

                            this->main->Iteratore_fallimenti =
                                this->main->Iteratore_fallimenti->down;

                            break;
                        }

                    else if ((this->main->Iteratore_fallimenti->left != nullptr) &&
                             (this->main->Iteratore_fallimenti->left->index ==
                              this->main->Iteratore_fallimenti->index+1)) {

                            this->main->Iteratore_fallimenti =
                                this->main->Iteratore_fallimenti->left;

                            break;
                        }

                    else if ((this->main->Iteratore_fallimenti->right != nullptr) &&
                             (this->main->Iteratore_fallimenti->right->index ==
                              this->main->Iteratore_fallimenti->index+1)) {

                            this->main->Iteratore_fallimenti =
                                this->main->Iteratore_fallimenti->right;

                            break;
                        }

                    else
                    {
                        int tentativi = 0;

                        while (!this->inThisThereISx(this->main->Iteratore_fallimenti->index+1))
                        {
                            tentativi+=1;
                            if (tentativi >= 500)
                            {
                                emit this->main->
                                        emitRifaiOpenWorld(this->main);
                                return;
                            }

                            if ((this->main->save_ctesta->left != nullptr) &&
                                (this->main->save_ctesta->left->index == this->main->save_ctesta->index+1))
                                 this->main->save_ctesta = this->main->save_ctesta->left;

                            else if ((this->main->save_ctesta->up != nullptr) &&
                                     (this->main->save_ctesta->up->index == this->main->save_ctesta->index+1))
                                      this->main->save_ctesta = this->main->save_ctesta->up;

                            else if ((this->main->save_ctesta->right != nullptr) &&
                                     (this->main->save_ctesta->right->index == this->main->save_ctesta->index+1))
                                      this->main->save_ctesta = this->main->save_ctesta->right;

                            else if ((this->main->save_ctesta->down != nullptr) &&
                                     (this->main->save_ctesta->down->index == this->main->save_ctesta->index+1))
                                      this->main->save_ctesta = this->main->save_ctesta->down;
                        }


                        mylistQStringMaps *ctesta = this->main->save_ctesta;

                        //Logica dell'orologio.
                        while (ctesta->index != this->main->Iteratore_fallimenti->index+1)
                        {
                            if ((ctesta->left != nullptr) &&
                                (ctesta->left->index <=
                                 this->main->Iteratore_fallimenti->index+1))
                            {
                                if ((ctesta->up != nullptr) &&
                                    (ctesta->up->index <= this->main->Iteratore_fallimenti->index+1)
                                 && (ctesta->up->index > ctesta->left->index)) goto step2;

                                else if ((ctesta->right != nullptr) &&
                                         (ctesta->right->index <= this->main->Iteratore_fallimenti->index+1)
                                      && (ctesta->right->index > ctesta->left->index))goto step3;

                                else if ((ctesta->down != nullptr) &&
                                         (ctesta->down->index <= this->main->Iteratore_fallimenti->index+1)
                                      && (ctesta->down->index > ctesta->left->index)) goto step4;

                                ctesta = ctesta->left;
                                goto finish;
                            }

                            step2:;
                            if ((ctesta->up != nullptr) &&
                                (ctesta->up->index <=
                                 this->main->Iteratore_fallimenti->index+1))
                            {
                                if ((ctesta->right != nullptr) &&
                                    (ctesta->right->index <= this->main->Iteratore_fallimenti->index+1)
                                 && (ctesta->right->index > ctesta->up->index)) goto step3;

                                if ((ctesta->down != nullptr) &&
                                    (ctesta->down->index <= this->main->Iteratore_fallimenti->index+1)
                                 && (ctesta->down->index > ctesta->up->index)) goto step4;

                                ctesta = ctesta->up;
                                goto finish;
                            }

                            step3:;
                            if ((ctesta->right != nullptr) &&
                                (ctesta->right->index <=
                                 this->main->Iteratore_fallimenti->index+1))
                            {
                                if ((ctesta->down != nullptr) &&
                                    (ctesta->down->index <= this->main->Iteratore_fallimenti->index+1)
                                 && (ctesta->down->index > ctesta->right->index)) goto step4;

                                ctesta = ctesta->right;
                                goto finish;
                            }

                        step4:;
                        if ((ctesta->down != nullptr) &&
                            (ctesta->down->index <=
                             this->main->Iteratore_fallimenti->index+1))
                            ctesta = ctesta->down;

                        finish:;
                    }

                        this->main->Iteratore_fallimenti = ctesta;
                        break;
                    }
                }

                this->main->coda =
                        this->main->Iteratore_fallimenti;

                goto loop2;
            }

            //1 = up
            if (tmp_valore_direzionale == 1)
               new_tmpy-=1;

            //2 = right
            else if (tmp_valore_direzionale == 2)
                new_tmpx+=1;

            //3 = down
            else if (tmp_valore_direzionale == 3)
                new_tmpy+=1;

            //4 = left
            else if (tmp_valore_direzionale == 4)
                new_tmpx-=1;

            this->main->oggetto_MiniMap->create_new_miniMap(new_tmpy, new_tmpx,
                this->main->oggetto_MiniMap->stampQStringRoomNumber(index_livello, tmp->index),
                                                            index_livello);
            this->setPlayerToNewRoom(this->coda);

            //4 = left
            if (tmp_valore_direzionale == 4)
                this->oggetto_MiniMap->TramuteQStringRoomByPOINTER(index_livello,
                this->oggetto_MiniMap->getPOINTERFromXY(index_livello, new_tmpy, new_tmpx));

            //2 = right
            else if (tmp_valore_direzionale == 2)
                this->oggetto_MiniMap->TramuteQStringRoomByPOINTER(index_livello,
                this->oggetto_MiniMap->getPOINTERFromXY(index_livello, new_tmpy, new_tmpx-1));

            this->main->up_non_fallito = true;
            this->main->right_non_fallito = true;
            this->main->down_non_fallito = true;
            this->main->left_non_fallito = true;
            this->main->y_attuale = new_tmpy;
            this->main->x_attuale = new_tmpx;
            return;
        }

        //da 0 a 4
        valore_direzionale = rand() % 5;

        new_tmpy = 0;
        new_tmpx = 0;

        if (valore_direzionale == 0) goto loop;

        new_tmpy = this->main->y_attuale;
        new_tmpx = this->main->x_attuale;

        if (valore_direzionale == 1)
        {
            if ((this->coda->up != nullptr)
            || (this->main->oggetto_MiniMap->getQStringFromXY(index_livello,
                this->main->y_attuale-1, this->main->x_attuale) !=
                this->main->oggetto_MiniMap->stampQStringSpace(index_livello)))
            {
                this->main->up_non_fallito = false;
                goto loop;
            }

            this->coda->up = tmp;
            this->coda->up->down = this->coda;
            this->coda = this->coda->up;

            new_tmpy-=1;
        }

        else if (valore_direzionale == 2)
        {
            if ((this->coda->right != nullptr)
            || (this->main->oggetto_MiniMap->getQStringFromXY(index_livello,
                this->main->y_attuale, this->main->x_attuale+1) !=
                this->main->oggetto_MiniMap->stampQStringSpace(index_livello)))
            {
                this->main->right_non_fallito = false;
                goto loop;
            }

            this->coda->right = tmp;
            this->coda->right->left = this->coda;
            this->coda = this->coda->right;

            new_tmpx+=1;
        }

        else if (valore_direzionale == 3)
        {
            if ((this->coda->down != nullptr)
            || (this->main->oggetto_MiniMap->getQStringFromXY(index_livello,
                this->main->y_attuale+1, this->main->x_attuale) !=
                this->main->oggetto_MiniMap->stampQStringSpace(index_livello)))
            {
                this->main->down_non_fallito = false;
                goto loop;
            }

            this->coda->down = tmp;
            this->coda->down->up = this->coda;
            this->coda = this->coda->down;

            new_tmpy+=1;
        }

        else if (valore_direzionale == 4)
        {
            if ((this->coda->left != nullptr)
            || (this->main->oggetto_MiniMap->getQStringFromXY(index_livello,
                this->main->y_attuale, this->main->x_attuale-1) !=
                this->main->oggetto_MiniMap->stampQStringSpace(index_livello)))
            {
                this->main->left_non_fallito = false;
                goto loop;
            }

            this->coda->left = tmp;
            this->coda->left->right = this->coda;
            this->coda = this->coda->left;

           new_tmpx-=1;
        }

        this->main->oggetto_MiniMap->create_new_miniMap(new_tmpy, new_tmpx,
            this->main->oggetto_MiniMap->stampQStringRoomNumber(index_livello, tmp->index),
                                                        index_livello);
        this->main->y_attuale = new_tmpy;
        this->main->x_attuale = new_tmpx;

        this->setPlayerToNewRoom(this->coda);

        mylistQString *save_pointer =
                this->main->oggetto_MiniMap->getPOINTERFromXY(index_livello,
                                                              this->main->y_attuale,
                                                              this->main->x_attuale-1);
        if (save_pointer != nullptr )
        {
            if ((save_pointer->getOggetto().toStdString()[0] == '[')
               && ((save_pointer->getOggetto().toStdString()
                   [save_pointer->getOggetto().length()-1] == ' ')
                || (save_pointer->getOggetto().toStdString()
                   [save_pointer->getOggetto().length()-1] == '-')))

                if (this->oggetto_MiniMap->
                        ExtractNumberToQstringRoom(save_pointer->getOggetto())
                                                   == tmp->index-1)

                    this->oggetto_MiniMap->
                        TramuteQStringRoomByPOINTER(index_livello,
                                                    save_pointer);
        }

        mylistQString *save_pointer2 =
                this->main->oggetto_MiniMap->getPOINTERFromXY(index_livello,
                                                              this->main->y_attuale,
                                                              this->main->x_attuale+1);
        mylistQString *save_pointer3 =
                this->main->oggetto_MiniMap->getPOINTERFromXY(index_livello,
                                                              this->main->y_attuale,
                                                              this->main->x_attuale);
        if (save_pointer2 != nullptr)
        {
            if ((save_pointer2->getOggetto().toStdString()[0] == '[')
               && ((save_pointer2->getOggetto().toStdString()
                   [save_pointer2->getOggetto().length()-1] == ' ')
                || (save_pointer2->getOggetto().toStdString()
                   [save_pointer2->getOggetto().length()-1] == '-')))

                if (this->oggetto_MiniMap->
                        ExtractNumberToQstringRoom(save_pointer2->getOggetto())
                                                   == tmp->index-1)

                    this->oggetto_MiniMap->
                        TramuteQStringRoomByPOINTER(index_livello,
                                                    save_pointer3);
        }

        this->main->up_non_fallito = true;
        this->main->right_non_fallito = true;
        this->main->down_non_fallito = true;
        this->main->left_non_fallito = true;
    }
}

bool mylistQStringMaps::setPlayer(QString pg, int x, int y)
{
    if ((x<=0) || (x>=this->main->lunghezza-1)) return false;
    if ((y<=0) || (y>=this->main->altezza-1)) return false;

    if (this->main->Mappa_aggiunta == true)
        this->main->Mappa_aggiunta = false;

    if ((pg == this->main->simbolo_P1) ||
        (pg == this->main->simbolo_mob))
    {
        if (pg == this->main->simbolo_P1)
        {
            if ((this->return_xy_Mappa(x, y) == this->main->simbolo_vuoto)
            || (this->return_xy_Mappa(x, y) == this->main->simbolo_porta)
            || (this->return_xy_Mappa(x, y) == this->main->simbolo_P1)
            || (this->return_xy_Mappa(x, y) == this->main->simbolo_scala)
            || (this->return_xy_Mappa(x, y) == this->main->simbolo_NPC))
            {
                this->main->p1_x = x;
                this->main->p1_y = y;
            }

            for (int tmpy=0; tmpy < this->main->altezza; tmpy++)
                for (int tmpx=0; tmpx < this->main->lunghezza; tmpx++)
                {
                    if ((tmpy == y) && (tmpx == x)) {

                        if ((this->Mappa->readIterator()->getOggetto() == this->main->simbolo_vuoto)
                        || (this->Mappa->readIterator()->getOggetto() == this->main->simbolo_porta)
                        || (this->Mappa->readIterator()->getOggetto() == this->main->simbolo_P1)
                        || (this->Mappa->readIterator()->getOggetto() == this->main->simbolo_scala)
                        || (this->Mappa->readIterator()->getOggetto() == this->main->simbolo_NPC))
                        {
                            if (this->Mappa->readIterator()->getOggetto() ==
                                    this->main->simbolo_porta)
                                this->main->puoi_entrare_in_una_porta = true;

                            else if (this->Mappa->readIterator()->getOggetto() ==
                                     this->main->simbolo_scala)
                                this->main->puoi_entrare_in_unLivello = true;

                            else if (this->Mappa->readIterator()->getOggetto() ==
                                     this->main->simbolo_vuoto)
                                this->main->puoi_entrare_in_una_porta = false;

                            this->Mappa->readIterator()->setOggetto(pg);
                            this->Mappa->resetIteratorToTesta();
                            return true;
                        }

                        else if ((this->Mappa->readIterator()->getOggetto() ==
                                  this->main->simbolo_mob))
                        {
                            this->main->puoi_entrare_in_unLivello = false;
                            this->main->puoi_entrare_in_una_porta = false;
                            this->Mappa->resetIteratorToTesta();
                            emit this->emitCombattimento(pg);
                            return false;
                        }

                        else //if la QString == simbolo_freccia
                        {
                            this->Mappa->resetIteratorToTesta();

                            if (
                                    (this->index > 1)
                              &&
                                    (
                                        ((this->up != nullptr) &&
                                         (this->up->index >
                                          this->index))
                                   ||
                                        ((this->right != nullptr) &&
                                         (this->right->index >
                                          this->index))
                                   ||
                                        ((this->down != nullptr) &&
                                         (this->down->index >
                                          this->index))
                                   ||
                                        ((this->left != nullptr) &&
                                         (this->left->index >
                                          this->index))
                                    )
                               )
                                this->main->
                                nelPercorsOincontroFreccia = true;

                            return false;
                        }
                    }

                    else this->Mappa->Inext();
                }
        }

        else if (pg == this->main->simbolo_mob)
        {
            if ((this->return_xy_Mappa(x, y) == this->main->simbolo_vuoto)
            || (this->return_xy_Mappa(x, y) == this->main->simbolo_porta)
            || (this->return_xy_Mappa(x, y) == this->main->simbolo_scala)
            || (this->return_xy_Mappa(x, y) == this->main->simbolo_NPC))
            {
                this->main->mob_x = x;
                this->main->mob_y = y;
            }

            for (int tmpy=0; tmpy < this->main->altezza; tmpy++)
                for (int tmpx=0; tmpx < this->main->lunghezza; tmpx++)
                {
                    if ((tmpy == y) && (tmpx == x)) {

                        if ((this->Mappa->readIterator()->getOggetto() == this->main->simbolo_vuoto)
                        || (this->Mappa->readIterator()->getOggetto() == this->main->simbolo_porta)
                        || (this->Mappa->readIterator()->getOggetto() == this->main->simbolo_NPC))
                        {
                            this->Mappa->readIterator()->setOggetto(pg);
                            this->Mappa->resetIteratorToTesta();
                            return true;
                        }

                        else if (this->Mappa->readIterator()->getOggetto() ==
                                 this->main->simbolo_P1)
                        {
                            this->main->puoi_entrare_in_unLivello = false;
                            this->main->puoi_entrare_in_una_porta = false;
                            this->Mappa->resetIteratorToTesta();
                            emit this->emitCombattimento(pg);
                            return false;
                        }

                        else //if la QString == simbolo_freccia
                        {
                            this->Mappa->resetIteratorToTesta();
                            return false;
                        }
                    }

                    else this->Mappa->Inext();
                }
        }
    }

    else if ((pg == this->main->simbolo_porta) ||
        (pg == this->main->simbolo_scala) ||
        (pg == this->main->simbolo_NPC) ||
        (pg == "⇦") || (pg == "⇧") ||
        (pg == "⇨") || (pg == "⇩"))
    {
        for (int tmpy=0; tmpy < this->main->altezza; tmpy++)
            for (int tmpx=0; tmpx < this->main->lunghezza; tmpx++) {
                if ((tmpy == y) && (tmpx == x)) {

                    if (this->Mappa->readIterator()->getOggetto() ==
                        this->main->simbolo_vuoto)
                    {
                        this->Mappa->readIterator()->setOggetto(pg);
                        this->Mappa->resetIteratorToTesta();
                        return true;
                    }

                    else {

                        this->Mappa->resetIteratorToTesta();
                        return false;
                    }
                }

                else this->Mappa->Inext();
            }
    }
}

void mylistQStringMaps::setEmpty(int x, int y)
{
    if ((x<=0) || (x>=this->main->lunghezza-1)) return;
    if ((y<=0) || (y>=this->main->altezza-1)) return;

    for (int tmpy=0; tmpy < this->main->altezza; tmpy++)
        for (int tmpx=0; tmpx < this->main->lunghezza; tmpx++) {
            if ((tmpy == y) && (tmpx == x)) {

                if (this->Mappa->readIterator()->getOggetto()
                        != this->main->simbolo_pieno)
                this->Mappa->readIterator()->setOggetto(this->main->simbolo_vuoto);
                this->Mappa->resetIteratorToTesta();
                return;
            }

            else this->Mappa->Inext();
        }
}

void mylistQStringMaps::move(QString direzione,
           QString simbolo_da_muovere,
           QString &Terminale1, Ui::MainWindow *&Ui)
{
    if (simbolo_da_muovere == this->main->simbolo_P1)
    {
        //debug this->main->p1_x, this->main->p1_y <-- setPlayerToNewRoom
        this->identify(simbolo_da_muovere,
                       this->main->p1_x,
                       this->main->p1_y);

        this->main->PointerSimbolToMoveTmp = simbolo_da_muovere;
        this->main->PointerCordinataXtmp = &this->main->p1_x;
        this->main->PointerCordinataYtmp = &this->main->p1_y;
    }

    else if (simbolo_da_muovere == this->main->simbolo_mob)
    {
        //debug this->main->mob_x, this->main->mob_y <-- setPlayerToNewRoom
        this->identify(simbolo_da_muovere,
                       this->main->mob_x,
                       this->main->mob_y);

        this->main->PointerSimbolToMoveTmp = simbolo_da_muovere;
        this->main->PointerCordinataXtmp = &this->main->mob_x;
        this->main->PointerCordinataYtmp = &this->main->mob_y;
    }

    this->main->valore_per_i_movimenti = true;

    //up
    if ((*this->main->PointerCordinataXtmp == 12) &&
        (*this->main->PointerCordinataYtmp == 2))
    {
        if (direzione == "left")
        {
            while (this->main->movimenti < 6)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp+1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, 1, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            while (this->main->valore_per_i_movimenti != false)//poi
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp-1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            (-1), 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "right")
        {
            while (this->main->movimenti < 6) {

                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp+1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, 1, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            while (this->main->valore_per_i_movimenti != false)//poi
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp+1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            1, 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "down")
        {
            while (this->main->valore_per_i_movimenti != false)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp+1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, 1,
                                            Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "center")
        {
            int x = 0;
            int y = 0;
            this->identify(this->main->simbolo_scala,
                           x, y);

            if ((x != 0) && (y != 0))
            {
                while (this->main->movimenti < 6)
                {
                    this->main->valore_per_i_movimenti =
                            this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                            *this->main->PointerCordinataXtmp,
                                            *this->main->PointerCordinataYtmp+1);

                    this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                                0, 1, Terminale1, Ui);

                    QTime dieTime = QTime::currentTime().addMSecs(100);
                    while( QTime::currentTime() < dieTime )
                        QCoreApplication::processEvents(
                                    QEventLoop::AllEvents, 100);
                }
            }

            else Ui->input->setText("Comando che comporta un movimento errato");
        }

        else if (simbolo_da_muovere == this->main->simbolo_P1)
            Ui->input->setText("Comando che comporta un movimento errato");
    }

    //right
    else if ((*this->main->PointerCordinataXtmp == this->main->lunghezza-4) &&
             (*this->main->PointerCordinataYtmp == 8))
    {
        if (direzione == "left")
        {
            while (this->main->valore_per_i_movimenti != false)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp-1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            (-1), 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "down")
        {
            while (this->main->movimenti < 11)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp-1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            (-1), 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            while (this->main->valore_per_i_movimenti != false)//poi
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp+1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, 1, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "up")
        {
            while (this->main->movimenti < 11)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp-1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            (-1), 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            while (this->main->valore_per_i_movimenti != false)//poi
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp-1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, (-1), Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "center")
        {
            int x = 0;
            int y = 0;
            this->identify(this->main->simbolo_scala,
                           x, y);

            if ((x != 0) && (y != 0))
            {
                while (this->main->movimenti < 11)
                {
                    this->main->valore_per_i_movimenti =
                            this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                            *this->main->PointerCordinataXtmp-1,
                                            *this->main->PointerCordinataYtmp);

                    this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                                (-1), 0, Terminale1, Ui);

                    QTime dieTime = QTime::currentTime().addMSecs(100);
                    while( QTime::currentTime() < dieTime )
                        QCoreApplication::processEvents(
                                    QEventLoop::AllEvents, 100);
                }
            }

            else Ui->input->setText("Comando che comporta un movimento errato");
        }

        else if (simbolo_da_muovere == this->main->simbolo_P1)
            Ui->input->setText("Comando che comporta un movimento errato");
    }

    //down
    else if ((*this->main->PointerCordinataXtmp == 12) &&
             (*this->main->PointerCordinataYtmp == this->main->altezza-3))
    {
        if (direzione == "left")
        {
            while (this->main->movimenti < 5)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp-1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, (-1), Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            while (this->main->valore_per_i_movimenti != false)//poi
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp-1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            (-1), 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "right")
        {
            while (this->main->movimenti < 5)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp-1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, (-1), Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            while (this->main->valore_per_i_movimenti != false)//poi
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp+1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            1, 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "up")
        {
            while (this->main->valore_per_i_movimenti != false)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp-1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, (-1), Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "center")
        {
            int x = 0;
            int y = 0;
            this->identify(this->main->simbolo_scala,
                           x, y);

            if ((x != 0) && (y != 0))
            {
                while (this->main->movimenti < 5)
                {
                    this->main->valore_per_i_movimenti =
                            this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                            *this->main->PointerCordinataXtmp,
                                            *this->main->PointerCordinataYtmp-1);

                    this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                                0, (-1), Terminale1, Ui);

                    QTime dieTime = QTime::currentTime().addMSecs(100);
                    while( QTime::currentTime() < dieTime )
                        QCoreApplication::processEvents(
                                    QEventLoop::AllEvents, 100);
                }
            }

            else Ui->input->setText("Comando che comporta un movimento errato");
        }

        else if (simbolo_da_muovere == this->main->simbolo_P1)
            Ui->input->setText("Comando che comporta un movimento errato");
    }

    //left
    else if ((*this->main->PointerCordinataXtmp == 3) &&
             (*this->main->PointerCordinataYtmp == 8))
    {
        if (direzione == "right")
        {
            while (this->main->valore_per_i_movimenti != false)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp+1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            1, 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "up")
        {
            while (this->main->movimenti < 9)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp+1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            1, 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            while (this->main->valore_per_i_movimenti != false)//poi
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp-1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, (-1), Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "down")
        {
            while (this->main->movimenti < 9)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp+1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            1, 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            while (this->main->valore_per_i_movimenti != false)//poi
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp+1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, 1, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "center")
        {
            int x = 0;
            int y = 0;
            this->identify(this->main->simbolo_scala,
                           x, y);

            if ((x != 0) && (y != 0))
            {
                while (this->main->movimenti < 9)
                {
                    this->main->valore_per_i_movimenti =
                            this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                            *this->main->PointerCordinataXtmp+1,
                                            *this->main->PointerCordinataYtmp);

                    this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                                1, 0, Terminale1, Ui);

                    QTime dieTime = QTime::currentTime().addMSecs(100);
                    while( QTime::currentTime() < dieTime )
                        QCoreApplication::processEvents(
                                    QEventLoop::AllEvents, 100);
                }
            }

            else Ui->input->setText("Comando che comporta un movimento errato");
        }

        else if (simbolo_da_muovere == this->main->simbolo_P1)
            Ui->input->setText("Comando che comporta un movimento errato");
    }

    //center
    else if ((*this->main->PointerCordinataXtmp == 12) &&
             (*this->main->PointerCordinataYtmp == 8))
    {
        if (direzione == "left")
        {
            while (this->main->valore_per_i_movimenti != false)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp-1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            (-1), 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "up")
        {
            while (this->main->valore_per_i_movimenti != false)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp-1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, (-1), Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "right")
        {
            while (this->main->valore_per_i_movimenti != false)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp+1,
                                        *this->main->PointerCordinataYtmp);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            1, 0, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else if (direzione == "down")
        {
            while (this->main->valore_per_i_movimenti != false)
            {
                this->main->valore_per_i_movimenti =
                        this->setPlayer(this->main->PointerSimbolToMoveTmp,
                                        *this->main->PointerCordinataXtmp,
                                        *this->main->PointerCordinataYtmp+1);

                this->simple_algorithm_move(this->main->PointerSimbolToMoveTmp,
                                            0, 1, Terminale1, Ui);

                QTime dieTime = QTime::currentTime().addMSecs(100);
                while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
            }

            if (this->main->nelPercorsOincontroFreccia == true)
            {
                this->main->nelPercorsOincontroFreccia = false;
                this->emitILmobSIdeveMuovere();
            }
        }

        else Ui->input->setText("Comando che comporta un movimento errato");
    }
}

void mylistQStringMaps::identify(QString simbolo_pg, int &myX, int &myY)
{
    for (int y=0; y < this->main->altezza; y++) {
        for (int x=0; x < this->main->lunghezza; x++) {

            if (this->Mappa->readIterator()->getOggetto()
                    == simbolo_pg)
            {
                myX = x;
                myY = y;
                this->Mappa->resetIteratorToTesta();
                return;
            }

            else this->Mappa->Inext();
        }
    }

    myX = 0; myY = 0;
    this->Mappa->resetIteratorToTesta();
    return;
}

QString mylistQStringMaps::return_xy_Mappa(int Mx, int My)
{
    if ((Mx<=0) || (Mx>=this->main->lunghezza-1)) return "r";
    if ((My<=0) || (My>=this->main->altezza-1)) return "r";

    for (int y=0; y < this->main->altezza; y++)
        for (int x=0; x < this->main->lunghezza; x++) {
            if ((x == Mx) && (y == My)) {

                QString save_for_return = this->Mappa->readIterator()->getOggetto();
                this->Mappa->resetIteratorToTesta();
                return save_for_return;
            }

            else this->Mappa->Inext();
        }
}

void mylistQStringMaps::setSimboloPg1(QString x)
{
    this->simbolo_P1 = x;
}

QString mylistQStringMaps::getSimboloPg1()
{
    return this->main->simbolo_P1;
}

int mylistQStringMaps::getLunghezza()
{
    return this->main->lunghezza;
}

int mylistQStringMaps::getAltezza()
{
    return this->main->altezza;
}

mylistQStringMaps*& mylistQStringMaps::getI1()
{
    return this->main->Iteratore1;
}

void mylistQStringMaps::setI1(mylistQStringMaps *&puntatore)
{
    this->main->Iteratore1 = puntatore;
}

mylistQStringMaps*& mylistQStringMaps::getTesta()
{
    return this->main->testa;
}

mylistQStringMaps*& mylistQStringMaps::getCoda()
{
    return this->main->coda;
}

mylistQStringMaps*& mylistQStringMaps::getUp()
{
    return this->up;
}

mylistQStringMaps*& mylistQStringMaps::getDown()
{
    return this->down;
}

mylistQStringMaps*& mylistQStringMaps::getLeft()
{
    return this->left;
}

mylistQStringMaps*& mylistQStringMaps::getRight()
{
    return this->right;
}

bool mylistQStringMaps::get_puoi_entrare_in_una_porta()
{
    return this->main->puoi_entrare_in_una_porta;
}

int& mylistQStringMaps::getP1X()
{
    return this->main->p1_x;
}

int& mylistQStringMaps::getP1Y()
{
    return this->main->p1_y;
}

void mylistQStringMaps::setP1X(int x)
{
    this->main->p1_x = x;
}

void mylistQStringMaps::setP1Y(int y)
{
    this->main->p1_y = y;
}

int& mylistQStringMaps::getMOBx()
{
    return this->main->mob_x;
}

int& mylistQStringMaps::getMOBy()
{
    return this->main->mob_y;
}

void mylistQStringMaps::setMOBx(int x)
{
    this->main->mob_x = x;
}

void mylistQStringMaps::setMOBy(int y)
{
    this->main->mob_y = y;
}

void mylistQStringMaps::simple_algorithm_move(QString simbolo_da_muovere,
                  int x, int y,  QString &Terminale1, Ui::MainWindow *&Ui)
{
    if (this->main->valore_per_i_movimenti == false)
        this->main->movimenti = 0;

    else {

        int my_p1X = 0;
        int my_p1Y = 0;

        if (simbolo_da_muovere == this->main->simbolo_P1)
        {
            //SimbolPG1
            my_p1X = this->main->p1_x;
            my_p1Y = this->main->p1_y;
        }

        else if (simbolo_da_muovere == this->main->simbolo_mob)
        {
            //SimboloMOB
            my_p1X = this->main->mob_x;
            my_p1Y = this->main->mob_y;
        }

        if (x != 0)
            my_p1X += (x*(-1));

        if (y != 0)
            my_p1Y += (y*(-1));

        this->main->movimenti += 1;
        this->setEmpty(my_p1X, my_p1Y);
        this->sendMapToTextBrowser1(Terminale1, Ui);
    }
}

mylistQStringMaps*& mylistQStringMaps::getMain()
{
    return this->main;
}

QString mylistQStringMaps::getSimboloScala()
{
    return this->main->simbolo_scala;
}

QString mylistQStringMaps::getSimboloNPC()
{
    return this->main->simbolo_NPC;
}

QString mylistQStringMaps::getSimboloMOB()
{
    return this->main->simbolo_mob;
}

bool mylistQStringMaps::get_puoi_entrare_in_unLivello()
{
    return this->main->puoi_entrare_in_unLivello;
}

void mylistQStringMaps::set_puoi_entrare_in_una_porta(bool x)
{
    this->main->puoi_entrare_in_una_porta = x;
}

void mylistQStringMaps::set_puoi_entrare_in_unLivello(bool x)
{
    this->main->puoi_entrare_in_unLivello = x;
}

int mylistQStringMaps::getIndex()
{
    return this->index;
}

MiniMap*& mylistQStringMaps::getOggettoMiniMap()
{
    return this->oggetto_MiniMap;
}

void mylistQStringMaps::setPlayerToNewRoom(mylistQStringMaps*& stanza_attuale)
{
    if (stanza_attuale->index != 1)
    {
        if (stanza_attuale->left != nullptr)
            stanza_attuale->setPlayer(stanza_attuale->main->simbolo_P1, 3, 8);

        else if (stanza_attuale->up != nullptr)
            stanza_attuale->setPlayer(stanza_attuale->main->simbolo_P1, 12, 2);

        else if (stanza_attuale->right != nullptr)
            stanza_attuale->setPlayer(stanza_attuale->main->simbolo_P1, this->main->lunghezza-4, 8);

        else if (stanza_attuale->down!= nullptr)
            stanza_attuale->setPlayer(stanza_attuale->main->simbolo_P1, 12, this->main->altezza-3);
    }
}

bool mylistQStringMaps::inThisThereISx(int x)
{
    mylistQStringMaps *copia_save_ctesta =
            this->main->save_ctesta;

    int maggiore = 0;
    int fase = 0;

    while (true)
    {
        fase++;

        if (copia_save_ctesta->left != nullptr)
            if ((copia_save_ctesta->left->index > maggiore)
               && (copia_save_ctesta->left->index <= x))
                maggiore = copia_save_ctesta->left->index;

        if (copia_save_ctesta->up != nullptr)
            if ((copia_save_ctesta->up->index > maggiore)
               && (copia_save_ctesta->up->index <= x))
                maggiore = copia_save_ctesta->up->index;

        if (copia_save_ctesta->right != nullptr)
            if ((copia_save_ctesta->right->index > maggiore)
               && (copia_save_ctesta->right->index <= x))
                maggiore = copia_save_ctesta->right->index;

        if (copia_save_ctesta->down != nullptr)
            if ((copia_save_ctesta->down->index > maggiore)
               && (copia_save_ctesta->down->index <= x))
                maggiore = copia_save_ctesta->down->index;

        //------------------------------------------------

        if ((fase == 1) &&
            ((maggiore == copia_save_ctesta->index+1) ||
             (maggiore == copia_save_ctesta->index-1)))
            return false;

        else if ((copia_save_ctesta->left != nullptr) &&
                 (copia_save_ctesta->left->index == maggiore))
                copia_save_ctesta = copia_save_ctesta->left;

        else if ((copia_save_ctesta->up != nullptr) &&
                 (copia_save_ctesta->up->index == maggiore))
                    copia_save_ctesta = copia_save_ctesta->up;

        else if ((copia_save_ctesta->right != nullptr) &&
                 (copia_save_ctesta->right->index == maggiore))
                    copia_save_ctesta = copia_save_ctesta->right;

        else if ((copia_save_ctesta->down != nullptr) &&
                 (copia_save_ctesta->down->index == maggiore))
                    copia_save_ctesta = copia_save_ctesta->down;

        if (copia_save_ctesta->index == x)
            return true;

        else if
                (
                 ((copia_save_ctesta->left == nullptr) ||
                  (copia_save_ctesta->left->index < copia_save_ctesta->index))

                 &&

                 ((copia_save_ctesta->up == nullptr) ||
                  (copia_save_ctesta->up->index < copia_save_ctesta->index))

                 &&

                 ((copia_save_ctesta->right == nullptr) ||
                  (copia_save_ctesta->right->index < copia_save_ctesta->index))

                 &&

                 ((copia_save_ctesta->down == nullptr) ||
                  (copia_save_ctesta->down->index < copia_save_ctesta->index))
                )

            return false;
    }
}

bool mylistQStringMaps::getValore_per_i_movimenti()
{
    return this->main->valore_per_i_movimenti;
}

void mylistQStringMaps::setValore_per_i_movimenti(bool x)
{
    this->main->valore_per_i_movimenti = x;
}

bool mylistQStringMaps::getConnect_avvenuto()
{
    return this->connect_avvenuto;
}

void mylistQStringMaps::setConnect_avvenuto(bool x)
{
    this->connect_avvenuto = x;
}

void mylistQStringMaps::set_numero_di_mappe(int x)
{
    this->main->numero_di_mappe = x;
}

void mylistQStringMaps::NULLcoda()
{
    this->main->coda = nullptr;
}

void mylistQStringMaps::NULLiteratore()
{
    this->main->Iteratore1 = nullptr;
}

void mylistQStringMaps::NULLiteratore_fallimenti()
{
    this->main->Iteratore_fallimenti->deleteLater();
    this->main->Iteratore_fallimenti = nullptr;
}

void mylistQStringMaps::NULLsave_ctesta()
{
    this->main->save_ctesta->deleteLater();
    this->main->save_ctesta = nullptr;
}

void mylistQStringMaps::NULLtesta()
{
    this->main->save_ctesta = nullptr;
}

void mylistQStringMaps::NULLup()
{
    this->up = nullptr;
}

void mylistQStringMaps::NULLright()
{
    this->right = nullptr;
}

void mylistQStringMaps::NULLdown()
{
    this->down = nullptr;
}

void mylistQStringMaps::NULLleft()
{
    this->left = nullptr;
}

void mylistQStringMaps::setCoda(mylistQStringMaps *&x)
{
    this->main->coda = x;
}

void mylistQStringMaps::setOggettoMiniMap(MiniMap *&x)
{
    this->main->oggetto_MiniMap->deleteLater();
    this->main->oggetto_MiniMap = nullptr;
    this->main->oggetto_MiniMap = x;
}

void mylistQStringMaps::setIteratoreFallimenti(mylistQStringMaps *&x)
{
    this->main->Iteratore_fallimenti = x;
}

void mylistQStringMaps::setSaveCtesta(mylistQStringMaps *&x)
{
    this->main->save_ctesta = x;
}

void mylistQStringMaps::setIndex(int x)
{
    this->index = x;
}
