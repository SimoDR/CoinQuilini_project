#ifndef DLIST_H
#define DLIST_H
#include<iostream>
using std::cout;
using std::endl;

template <class T>
class dList
{
private:
    class nodo
    {
    public:
        T info;
        nodo *prev, *next;
        nodo(const T &t = T(), nodo *p = nullptr, nodo *n = nullptr); //costruttore di default di nodo
        ~nodo(); //chiamata ricorsiva a distruttore di nodo (sennò la delete su dList first dealloca solo il primo nodo della lista)
    };

    nodo *last, *first; // lista vuota iff first==last==nullptr    per garantire inserimento in testa e coda in tempo costante
    static nodo *copy(nodo *p, nodo *&l);
    static bool isLess(nodo *d1, nodo *d2);

public:
    ~dList();
    dList(const dList &d);
    dList(unsigned int k, const T &t);
    dList &operator=(const dList &d);
    void insertFront(const T &t);
    void insertBack(const T &t);
    bool operator<(const dList &d) const;

    class const_iterator
    {
        friend class dList<T>;
    private:
        nodo *ptr;
        bool pastTheEnd; // true iff constiterator e' "past-the-end"
        const_iterator(nodo *p, bool pte = false);// conversione nodo* => constiterator

    public:
        const_iterator();
        const T &operator*() const;
        const T *operator->() const;
        const_iterator &operator++();
        const_iterator &operator--();
        bool operator==(const const_iterator &x) const;
        bool operator!=(const const_iterator &x) const;
    };
    const_iterator begin() const;
    const_iterator end() const;
};



/*********************************************IMPLEMENTAZIONE************************************************/



/**********************************NODO**********************************/

template<class T>
dList<T>::nodo::nodo(const T &t, dList<T>::nodo *p, dList::nodo *n) : info(t), prev(p), next(n) {}

template<class T>
dList<T>::nodo::~nodo() { delete next; }

/**********************************DLIST**********************************/

template<class T>
typename dList<T>::nodo * dList<T>::copy(nodo *p, nodo *&l) //si passa last per riferimento perché ancora non si sa quale sia l'ultimo nodo (il primo si)
{
    if (p == nullptr) //lista da copiare vuota
        return l = nullptr;
    nodo *prec = new nodo(p->info, nullptr, nullptr); //lista da copiare ha almeno un nodo
    nodo *succ = prec;    //da inizializzare qui per l=succ
    nodo *start = prec;
    while (p->next != nullptr)  // lista da copiare ha almeno 2 nodi
    {
        succ = new nodo(p->next->info, prec, nullptr);
        prec->next = succ;
        p = p->next;
        prec = prec->next;
    }
    l = succ;
    return start;
}

template<class T>
bool dList<T>::isLess(nodo *d1, nodo *d2)
{
    if (d2 == nullptr)
        return false;
    // d2 NON e' vuota
    if (d1 == nullptr)
        return true;
    // d1 e d2 NON vuote
    return d1->info < d2->info ||
            (d1->info == d2->info && isLess(d1->next, d2->next));
}

template<class T>
dList<T>::dList (const dList<T> &d) : first(copy(d.first, last)) // first è ritornato dalla funzione, last viene modificato da copy
{                                                  //grazie all'aliasing
    // first=copy(d.first,last);
}

template<class T>
dList<T>& dList<T>::operator=(const dList<T> &d)
{
    if (this != &d)
    {
        delete first;
        first = copy(d.first, last);
    }
    return *this;
}

template<class T>
void dList<T>::insertFront(const T &t)
{
    first = new nodo(t, nullptr, first);
    if (first->next == nullptr)
    {
        // lista di invocazione era vuota
        last = first;
    }
    else
    {
        // lista di invocazione NON era vuota
        (first->next)->prev = first;
    }
}

template<class T>
void dList<T>::insertBack(const T &t)
{
    last = new nodo(t, last, nullptr);
    if (last->prev == nullptr)
    {
        // lista di invocazione era vuota
        first = last;
    }
    else
    {
        // lista di invocazione NON era vuota
        (last->prev)->next = last;
    }
}

template<class T>
dList<T>::dList(unsigned int k, const T &t) : last(nullptr), first(nullptr)
{
    for (unsigned int i = 0; i < k; ++i)
        insertFront(t);
}

template<class T>
bool dList<T>::operator<(const dList<T> &d) const
{
    return isLess(first, d.first);
}

/**********************************CONST_ITERATOR**********************************/

template<class T>
typename dList<T>::const_iterator dList<T>::begin() const
{
    return first;
}

template<class T>
typename dList<T>::const_iterator dList<T>::end() const
{
    if (last == nullptr) //dList vuota ritorna 0
        return nullptr;
    return const_iterator(last + 1, true); // dList ha almeno un nodo ritorna iterator pte
}

template<class T>
dList<T>::const_iterator::const_iterator(dList<T>::nodo *p, bool pte) : ptr(p), pastTheEnd(pte) {}

template<class T>
dList<T>::const_iterator::const_iterator() : ptr(nullptr), pastTheEnd(false) {}

template<class T>
const T &dList<T>::const_iterator::operator*() const
{
    return ptr->info;
}

template<class T>
const T *dList<T>::const_iterator::operator->() const
{
    return &(ptr->info);
}

template<class T>
typename dList<T>::const_iterator &dList<T>::const_iterator::operator++()
{
    if (ptr != nullptr)
    {
        if (!pastTheEnd)
        {
            if (ptr->next == nullptr)
            {
                ++ptr;   //chiamata al ++ prefisso sugli interi: ptr è un indirizzo
                pastTheEnd = true;
            }
            else
            {
                ptr = ptr->next;
            }
        }
    }
    return *this;
}

template<class T>
typename dList<T>::const_iterator &dList<T>::const_iterator::operator--()
{
    if (ptr != nullptr)
    {
        if (pastTheEnd)
        {
            --ptr;
            pastTheEnd = false;
        }
        else
            ptr = ptr->prev;
    }
    return *this;
}

template<class T>
bool dList<T>::const_iterator::operator==(const dList<T>::const_iterator &x) const
{
    return ptr == x.ptr;
}

template<class T>
bool dList<T>::const_iterator::operator!=(const dList<T>::const_iterator &x) const
{
    return ptr != x.ptr;
}





#endif // DLIST_H
