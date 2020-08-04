#include "livelli.h"

livelli::livelli(QObject *parent) : QObject(parent)
{
    this->mappe_per_questo_livello = nullptr;
    this->index_livello = 0;
    this->numero_di_livelli = 0;
    this->prec = nullptr;
    this->next = nullptr;
    this->main = this;
    this->Iteratore1 = nullptr;
    this->Iteratore2 = nullptr;
    this->testa = nullptr;
    this->coda = nullptr;
}

void livelli::add_liv()
{
    if (this->testa == nullptr)
    {
        this->testa = new livelli;
        this->coda = this->testa;
        this->testa->index_livello = 1;
        this->numero_di_livelli = 1;
        this->testa->main = this;
        this->prec = nullptr;
        this->next = nullptr;
        this->testa->mappe_per_questo_livello = new mylistQStringMaps;
        this->testa->mappe_per_questo_livello->add1map(1);
        this->Iteratore1 = this->testa;
        this->Iteratore2 = this->testa;
    }

    else
    {
        livelli *tmp = new livelli;
        tmp->mappe_per_questo_livello = new mylistQStringMaps;
        connect(tmp->mappe_per_questo_livello,
                SIGNAL(emitRifaiOpenWorld(mylistQStringMaps*&)),
                tmp, SLOT(reciveRifaiOpenWorld(mylistQStringMaps*&)));

        tmp->main = this->coda->main;
        tmp->index_livello = this->coda->index_livello+1;
        this->main->numero_di_livelli += 1;
        this->coda->next = tmp;
        tmp->prec = this->coda;

        tmp->getMappe()->setSimboloPg1(this->coda->getMappe()->getSimboloPg1());
        tmp->mappe_per_questo_livello->add1map(tmp->index_livello);
        tmp->getMappe()->getTesta()->setSimboloPg1(tmp->getMappe()->getSimboloPg1());

        if (this->main->getMappeIT1()->getI1() ==
            this->main->getMappeIT1()->getCoda())
            this->main->getMappeIT1()->getI1()->
                getMain()->set_puoi_entrare_in_unLivello(true);

        for (int i=1; i < tmp->index_livello; i++)
            if (tmp->mappe_per_questo_livello->getCoda()->getIndex()
                    < tmp->index_livello)
                tmp->mappe_per_questo_livello->add1map(tmp->index_livello);

        if (this->main->coda->next != nullptr)
            this->main->coda = this->main->coda->next;
    }
}

mylistQStringMaps*& livelli::getMappeIT1()
{
    return this->main->Iteratore1->mappe_per_questo_livello;
}

mylistQStringMaps*& livelli::getMappe()
{
    return this->mappe_per_questo_livello;
}

livelli*& livelli::getEntrata()
{
    return this->prec;
}

livelli*& livelli::getUscita()
{
    return this->next;
}

livelli*& livelli::getIteratore1()
{
    return this->main->Iteratore1;
}

livelli*& livelli::getIteratore2()
{
    return this->main->Iteratore2;
}

livelli*& livelli::getMain()
{
    return this->main;
}

livelli*& livelli::getTesta()
{
    return this->main->testa;
}

livelli*& livelli::getCoda()
{
    return this->main->coda;
}

void livelli::setIteratore1(livelli *&x)
{
    this->main->Iteratore1 = x;
}

void livelli::setIteratore2(livelli *&x)
{
    this->main->Iteratore2 = x;
}

int livelli::get_index_livello()
{
    return this->index_livello;
}

void livelli::set_index_livello(int x)
{
    this->index_livello = x;
}

void livelli::reciveRifaiOpenWorld(mylistQStringMaps *&pointer)
{
    //mylistQStringMaps *&pointer
    //== main di mappe_per_questo_livello
    //tmp == this
    //main del vecchio this == this->main
    livelli *main = this->main;
    pointer->set_numero_di_mappe(1);
    pointer->NULLiteratore_fallimenti();
    pointer->NULLsave_ctesta();

    pointer->getTesta()->getUp()->deleteLater();
    pointer->getTesta()->getRight()->deleteLater();
    pointer->getTesta()->getDown()->deleteLater();
    pointer->getTesta()->getLeft()->deleteLater();

    pointer->getTesta()->NULLup();
    pointer->getTesta()->NULLright();
    pointer->getTesta()->NULLdown();
    pointer->getTesta()->NULLleft();

    pointer->setCoda(pointer->getTesta());
    pointer->setIteratoreFallimenti(pointer->getTesta());
    pointer->setSaveCtesta(pointer->getTesta());

    int tmp_per_minimapX = 0;
    int tmp_per_minimapY = 0;
    MiniMap *da_dare_a_pointer = new MiniMap;
    da_dare_a_pointer->create_new_miniMap(tmp_per_minimapX, tmp_per_minimapY,
                       da_dare_a_pointer->stampQStringRoomNumber(this->index_livello, 1),
                                          this->index_livello);
    pointer->setOggettoMiniMap(da_dare_a_pointer);

    for (int i=1; i < this->index_livello; i++)
        if (this->mappe_per_questo_livello->getCoda()->getIndex()
                < this->index_livello)
            this->mappe_per_questo_livello->add1map(this->index_livello);

    if (main->coda->next != nullptr)
        main->coda = main->coda->next;
}
