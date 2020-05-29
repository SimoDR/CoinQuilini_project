#ifndef DLIST_H
#define DLIST_H
#include <iostream>
using std::cout;
using std::endl;

//operatore di output
template <class T>
class dList;

template <class T> //dichiarazione perché è necessario che compaia quando viene dichiarata l'amicizia su trialbero
std::ostream &operator<<(std::ostream &, const dList<T> &);

template <class T>
class dList
{
    friend std::ostream &operator<<<T>(std::ostream &, const dList &);

private:
    class nodo
    {
    public:
        T info;
        nodo *prev, *next;
        nodo(const T &t = T(), nodo *p = nullptr, nodo *n = nullptr);
        ~nodo();
    };

    nodo *last, *first; // lista vuota iff first==last==nullptr    per garantire inserimento in testa e coda in tempo costante
    static nodo *copy(nodo *p, nodo *&l);
    static bool isLess(nodo *d1, nodo *d2);

public:
    ~dList();
    dList(const dList &d);
    dList(unsigned int k, const T &t);
    dList();
    dList &operator=(const dList &d);
    void insertFront(const T &t);
    void insertBack(const T &t);
    void popFront();
    void popBack();
    bool operator<(const dList &d) const;

    class iterator
    {
        friend class dList<T>;
        friend class const_iterator; //per accedere a p e pte

    private:
        nodo *ptr;
        bool pastTheEnd;                     // true iff iterator e' "past-the-end"
        iterator(nodo *p, bool pte = false); // conversione nodo* => iterator

    public:
        iterator();
        T &operator*() const;
        T *operator->() const;
        iterator &operator++();
        iterator &operator--();
        bool operator==(const iterator &x) const;
        bool operator!=(const iterator &x) const;
    };
    iterator begin() const;
    iterator end() const;
    iterator insert(iterator i, const T &t);
    iterator remove(iterator i);

    class const_iterator
    {
        friend class dList<T>;

    private:
        nodo *ptr;
        bool pastTheEnd;                           // true iff constiterator e' "past-the-end"
        const_iterator(nodo *p, bool pte = false); // conversione nodo* => const_iterator

    public:
        const_iterator();
        const_iterator(iterator &i); //conversione iterator->const_iterator
        const T &operator*() const;
        const T *operator->() const;
        const_iterator &operator++();
        const_iterator &operator--();
        bool operator==(const const_iterator &x) const;
        bool operator!=(const const_iterator &x) const;
    };
    const_iterator cbegin() const;
    const_iterator cend() const;
};

/*********************************************IMPLEMENTAZIONE************************************************/

/**********************************NODO**********************************/

template <class T>
dList<T>::nodo::nodo(const T &t, dList<T>::nodo *p, dList::nodo *n) : info(t), prev(p), next(n) {}

template <class T>
dList<T>::nodo::~nodo() { delete next; }

/**********************************DLIST**********************************/

template <class T>
typename dList<T>::nodo *dList<T>::copy(nodo *p, nodo *&l) //si passa last per riferimento perché ancora non si sa quale sia l'ultimo nodo (il primo si)
{
    if (p == nullptr) //lista da copiare vuota
        return l = nullptr;
    nodo *prec = new nodo(p->info, nullptr, nullptr); //lista da copiare ha almeno un nodo
    nodo *succ = prec;                                //da inizializzare qui per l=succ
    nodo *start = prec;
    while (p->next != nullptr) // lista da copiare ha almeno 2 nodi
    {
        succ = new nodo(p->next->info, prec, nullptr);
        prec->next = succ;
        p = p->next;
        prec = prec->next;
    }
    l = succ;
    return start;
}

template <class T>
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

template <class T>
dList<T>::dList(const dList<T> &d) : first(copy(d.first, last)) // first è ritornato dalla funzione, last viene modificato da copy
{                                                               //grazie all'aliasing
    // first=copy(d.first,last);
}

template <class T>
dList<T> &dList<T>::operator=(const dList<T> &d)
{
    if (this != &d)
    {
        delete first;
        first = copy(d.first, last);
    }
    return *this;
}

template <class T>
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

template <class T>
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

template <class T>
void dList<T>::popFront()
{
    if (first) //se la lista ha almeno un elemento
    {
        nodo *temp = first;

        if (first->next) //se la lista ha almeno 2 elementi
        {
            first = first->next;
            temp->next = nullptr;
            first->prev = nullptr;
        }
        else //la lista ha esattamente un elemento
        {
            first = last = nullptr;
        }
        delete temp;
    }
}

template <class T>
void dList<T>::popBack()
{
    if (first)
    {
        nodo *temp = last;
        if (first->next)
        {
            last = last->prev;
            last->next = nullptr;
        }
        else
        {
            first = last = nullptr;
        }
        delete temp;
    }
}

template <class T>
typename dList<T>::iterator dList<T>::insert(iterator i, const T &t) //inseruisce t prima del nodo puntato da i e ritorna l'iteratore che punta al nuovo nodo
{
    if (i.ptr == nullptr) //la lista è vuota
    {
        insertFront(t);
        return begin();
    }
    else //lista non vuota
    {
        if (i == end()) //iteratore past the end
        {
            insertBack(t);
            return --end(); //cerca il past the end della lista aggiornata e ne ritorna il precedente (ultimo)
        }
        else if (i == begin()) //iteratore primo elemento
        {
            insertFront(t);
            return begin(); //ritorna il primo, avendo inserito t prima del primo (che diventa quindi il primo)
        }
        else //caso generale
        {
            nodo *temp = new nodo(t, i.ptr->prev, i.ptr);
            (i.ptr->prev)->next = temp;
            return temp;
        }
    }
}

template <class T>
typename dList<T>::iterator dList<T>::remove(iterator i) //rimuove il nodo puntato da i iteratore valido, restituisce l'iteratore al nodo successivo
{
    if (i != end())
    {
        if (i == begin())
        {
            ++i;
            popFront();
        }
        else if (i == --end())
        {
            ++i;
            popBack();
        }
        else
        {
            nodo * temp = i.ptr; //nodo da eliminare
            ++i;                //iteratore da restituire
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            temp->next = nullptr;
            delete temp;
        }
    }
    return i;
}

template <class T>
dList<T>::dList(unsigned int k, const T &t) : last(nullptr), first(nullptr)
{
    for (unsigned int i = 0; i < k; ++i)
        insertFront(t);
}
template <class T>
dList<T>::dList() : last(nullptr), first(nullptr) {}

template <class T>
dList<T>::~dList()
{
    delete first;
}

template <class T>
bool dList<T>::operator<(const dList<T> &d) const
{
    return isLess(first, d.first);
}

/**********************************CONST_ITERATOR**********************************/

template <class T>
typename dList<T>::const_iterator dList<T>::cbegin() const
{
    return first;
}

template <class T>
typename dList<T>::const_iterator dList<T>::cend() const
{
    if (last == nullptr) //dList vuota ritorna 0
        return nullptr;
    return const_iterator(last + 1, true); // dList ha almeno un nodo ritorna iterator pte
}

template <class T>
dList<T>::const_iterator::const_iterator(dList<T>::nodo *p, bool pte) : ptr(p), pastTheEnd(pte) {}

template <class T>
dList<T>::const_iterator::const_iterator() : ptr(nullptr), pastTheEnd(false) {}

template <class T>
dList<T>::const_iterator::const_iterator(iterator &i) : ptr(i.ptr), pastTheEnd(i.pte) {}

template <class T>
const T &dList<T>::const_iterator::operator*() const
{
    return ptr->info;
}

template <class T>
const T *dList<T>::const_iterator::operator->() const
{
    return &(ptr->info);
}

template <class T>
typename dList<T>::const_iterator &dList<T>::const_iterator::operator++()
{
    if (ptr != nullptr)
    {
        if (!pastTheEnd)
        {
            if (ptr->next == nullptr)
            {
                ++ptr; //chiamata al ++ prefisso sugli interi: ptr è un indirizzo
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

template <class T>
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

template <class T>
bool dList<T>::const_iterator::operator==(const dList<T>::const_iterator &x) const
{
    return ptr == x.ptr;
}

template <class T>
bool dList<T>::const_iterator::operator!=(const dList<T>::const_iterator &x) const
{
    return ptr != x.ptr;
}

/**********************************ITERATOR**********************************/

template <class T>
typename dList<T>::iterator dList<T>::begin() const
{
    return first;
}

template <class T>
typename dList<T>::iterator dList<T>::end() const
{
    if (last == nullptr) //dList vuota ritorna 0
        return nullptr;
    return iterator(last + 1, true); // dList ha almeno un nodo ritorna iterator pte
}

template <class T>
dList<T>::iterator::iterator(dList<T>::nodo *p, bool pte) : ptr(p), pastTheEnd(pte) {}

template <class T>
dList<T>::iterator::iterator() : ptr(nullptr), pastTheEnd(false) {}

template <class T>
T &dList<T>::iterator::operator*() const
{
    return ptr->info;
}

template <class T>
T *dList<T>::iterator::operator->() const
{
    return &(ptr->info);
}

template <class T>
typename dList<T>::iterator &dList<T>::iterator::operator++()
{
    if (ptr != nullptr)
    {
        if (!pastTheEnd)
        {
            if (ptr->next == nullptr)
            {
                ++ptr; //chiamata al ++ prefisso sugli interi: ptr è un indirizzo
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

template <class T>
typename dList<T>::iterator &dList<T>::iterator::operator--()
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

template <class T>
bool dList<T>::iterator::operator==(const dList<T>::iterator &x) const
{
    return ptr == x.ptr;
}

template <class T>
bool dList<T>::iterator::operator!=(const dList<T>::iterator &x) const
{
    return ptr != x.ptr;
}

template <class T> //dichiarazione perché è necessario che compaia quando viene dichiarata l'amicizia su trialbero
std::ostream &operator<<(std::ostream &os, const dList<T> &l)
{
    for (typename dList<T>::const_iterator c = l.cbegin(); c != l.cend(); ++c)
        std::cout << *c << ' ';
    std::cout << std::endl;
    return os;
}

#endif // DLIST_H

/* 
DONE:
- iteratori 
- inserimento dato l'iteratore (bug)
- pop front e pop back
- eliminazione ad iteratore

TODO (forse):
- eliminazione ad iteratore
- eccezioni all'inserimento e modifica?
- input e output?
questi due non presenti in stl::list
 */
