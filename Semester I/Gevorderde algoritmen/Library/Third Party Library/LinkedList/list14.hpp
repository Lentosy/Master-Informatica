//C++14 compatible singly linked list
#ifndef __LIST14_HPP
#define __LIST14_HPP
//
#define DEBUG
//
//#define ITERATOR

#include <iostream>
#include <memory>
#include <algorithm>
using std::endl;
using std::ostream;

template <class T>
class ListNode;
template <class T>
class List;

template <class T>
using ListNodeptr = std::unique_ptr<ListNode<T>>;

template <class T>
ostream &operator<<(ostream &os, const List<T> &l);

template <class T>
void swap(List<T> &, List<T> &);

template <class T>
bool operator==(const List<T> &, const List<T> &);

template <class T>
bool operator!=(const List<T> &, const List<T> &);

template <class T>
class List : private ListNodeptr<T>
{
    // Constructors, default, copy & move
  public:
    List() { std::cout << "\t List()" << endl; };

  public:
    List(const List<T> &l)
    {
        std::cout << "\t List(const List<T> &)" << endl;
        if (this != &l)
        {
            this->reset(nullptr);
            int l_size = l.size();
            ListNode<T> *tmparr[l_size];

            int idx = 0;
            ListNode<T> *tmp = l.get();
            while (tmp != nullptr)
            {
                tmparr[idx++] = tmp;
                tmp = tmp->next.get();
            }

            for (int i = idx - 1; i >= 0; i--)
            {
                this->add(tmparr[i]->item);
            }
        }
        else
            std::cout << "\t you tried to copy construct yourself, won't do the copy" << endl;
    };

  public:
    List(List<T> &&l) : ListNodeptr<T>(std::move(l))
    {
        std::cout << "\t List(List<T> &&)" << endl;
    };

  public:
    List<T> &operator=(const List<T> &l)
    {
        std::cout << "\t operator=(const List<T> &)" << endl;
        if (this != &l)
        {
            this->reset(nullptr);
            int l_size = l.size();
            ListNode<T> *tmparr[l_size];

            int idx = 0;
            ListNode<T> *tmp = l.get();
            while (tmp != nullptr)
            {
                tmparr[idx++] = tmp;
                tmp = tmp->next.get();
            }

            for (int i = idx - 1; i >= 0; i--)
            {
                this->add(tmparr[i]->item);
            }
        }
        else
            std::cout << "\t you tried to copy operator on yourself, won't do the copy\n";
        return *this;
    };

  public:
    // works with List<T> &operator=(List<T> &&l) = default;
    List<T> &operator=(List<T> &&l)
    {
        std::cout << "\t &operator=(List<T>&&)" << endl;
        *this = std::move(*(dynamic_cast<ListNodeptr<T> *>(&l)));
        return *this;
    };

  public:
    List<T> &operator=(ListNodeptr<T> &&l)
    {
        std::cout << "\t &operator=(ListNodeptr<T> &&)" << endl;
        (*this).ListNodeptr<T>::operator=(std::move(l));
        return *this;
    };

    // Taking unique_ptr's constructors
    using ListNodeptr<T>::ListNodeptr;

    // Index operator

  public:
    const T &operator[](int location) const
    {
        int size = this->size();
        if (location >= size)
        {
            throw std::out_of_range("List index out of range");
        }
        else
        {
            int index = 0;
            const List<T> *current = this;
            while (index != location)
            {
                current = &(this->get()->next);
                location++;
            }
            return current->get()->item;
        }
    };

    // Operations

  public:
    // Duplicates are allowed
    void add(const T &item)
    {
        // C++11     ListNodeptr<T> nieuw(new ListNode<T>(item));
        ListNodeptr<T> nieuw = std::make_unique<ListNode<T>>(item);
        ListNodeptr<T>::swap(nieuw->next);
        *this = std::move(nieuw);
    };

  public:
    // Number of times the supplied key is found in the list
    int getTimesFound(const T &item) const
    {
        const List<T> *plaats = search(item);
        //noot: plaats==0 is false zelfs als plaats een nulpointer is
        if (*plaats)
            return 1 + plaats->get()->next.size(item);
        else
            return 0;
    };

  public:
    // List size
    int size() const
    {
        if (*this)
            return 1 + this->get()->next.size();
        else
            return 0;
    };

  public:
    // Only removes the first occurrence of the argument
    void remove(const T &item)
    {
        search(item)->removeFirst();
    };

  public:
    // Removes the first node
    void removeFirst()
    {
        if (this->get() != 0)
        {
            ListNodeptr<T> staart(std::move(this->get()->next));
            this->reset();
            ListNodeptr<T>::swap(staart);
        }
    };

  public:
    void insertionsort()
    {
        ListNodeptr<T> unsorted = std::move(*this);
        while (unsorted)
        {
            List *plaats = searchInSorted(unsorted.get()->item);
            ListNodeptr<T> dummy = std::move(unsorted);
            //vermits unsorted een nullpointer is, is het equivalent van de volgende lijnen ongeveer
            //unsorted=std::move(dummy.get()->next);
            //std::swap(*plaats,dummy.get()->next);
            std::swap(unsorted, dummy.get()->next);
            dummy.get()->next = std::move(*plaats);
            *plaats = std::move(dummy);
        };
    };

  protected:
    // Search returns a pointer to a list, containing the key (argument)
    // or a pointer to an empty list if the key isn't found
    const List *search(const T &item) const
    {
        const List<T> *pl = this;
        while (*pl && pl->get()->item != item)
            pl = &(pl->get()->next);
        return pl;
    };

  protected:
    // Search returns a pointer to a list, containing the key (argument)
    // or a pointer to an empty list if the key isn't found
    List *search(const T &item)
    {
        List *pl = this;
        while (*pl && pl->get()->item != item)
            pl = &(pl->get()->next);
        return pl;
    };

  protected:
    // searchInSorted assumes a sorted list and returns a list where the key should be
    List<T> *searchInSorted(const T &item)
    {
        List *plaats = this;
        while (*plaats && plaats->get()->item < item)
            plaats = &plaats->get()->next;
        return plaats;
    };

    // Output operator overwrite
    friend ostream &operator<<<>(ostream &os, const List &l);
    // // Swap operation
    friend void swap<>(List<T> &, List<T> &);

    friend bool operator==<>(const List &a, const List &b);
    friend bool operator!=<>(const List &a, const List &b);

  public:
    void output(ostream &os) const;

  public:
    class iterator
    {
      public:
        iterator(ListNode<T> *l = 0);
        const T &operator*() const;
        const iterator &operator++();
        bool operator!=(const iterator &i);
    };
    iterator begin() const;
    iterator end() const;
};

template <class T>
void swap(List<T> &a, List<T> &b)
{
    std::cout << "a before swap: ";
    a.output(std::cout);
    std::cout << endl
              << "b before swap: ";
    b.output(std::cout);
    std::cout << endl;

    List<T> tmp;
    tmp = std::move(b);
    b = std::move(a);
    a = std::move(tmp);

    std::cout << "a after swap: ";
    a.output(std::cout);
    std::cout << endl
              << "b after swap: ";
    b.output(std::cout);
    std::cout << endl;
}

template <class T>
class ListNode
{
    friend class List<T>;

  public:
    List<T> next;
    ListNode(const T &_item) : item(_item)
    {
        std::cout << "ListNode with " << item << " is constructed" << endl;
        numberMade++;
    };

  public:
    ~ListNode()
    {
        std::cout << "ListNode with " << item << " gets destroyed" << endl;
        numberRemoved++;
    };

  public:
    const T &getItem() const { return item; };

  protected:
    T item;
#ifdef DEBUG
  public:
    static bool control(int made, int removed)
    {
        if (numberMade == made && numberRemoved == removed)
        {
            std::cout << "Succeeded control routine:" << endl;
            std::cout << "Total nodes constructed: " << numberMade << " is " << made << endl;
            std::cout << "Total nodes removed: " << numberRemoved << " is " << removed << endl;
            return true;
        }

        else
        {
            std::cout << "Error during control routine:" << endl;
            std::cout << "Total nodes constructed: " << numberMade << " should be " << made << endl;
            std::cout << "Total nodes removed: " << numberRemoved << " should be " << removed << endl;
            return false;
        };
    };

  protected:
    static int numberMade;
    static int numberRemoved;
#endif
};

template <class T>
int ListNode<T>::numberMade = 0;
template <class T>
int ListNode<T>::numberRemoved = 0;

template <class T>
ostream &operator<<(ostream &os, const List<T> &l)
{
#ifdef ITERATOR
    for (auto &&item : l)
        os << item << ", ";
#else
    if (l.get())
    {
        os << l.get()->item << ", ";
        os << l.get()->next;
    }
#endif
    return os;
}

template <class T>
void List<T>::output(ostream &os) const
{
#ifdef ITERATOR
    if (this->get() != 0)
    {
        os << this->get()->item;
        std::for_each(++begin(), end(), [&](const T &item) { os << " . " << item; });
    }
#else
    {
        ListNode<T> *kn = this->get();
        if (kn != 0)
        {
            os << kn->item;
            kn = kn->next.get();
        };
        while (kn != 0)
        {
            os << " . " << kn->item;
            kn = kn->next.get();
        };
    }
#endif
}

template <class T>
bool operator==(const List<T> &a, const List<T> &b)
{
    // SHALLOW return *(dynamic_cast<const ListNodeptr<T> *>(&a)) == *(dynamic_cast<const ListNodeptr<T> *>(&b));
    int a_size = a.size();
    int b_size = b.size();
    if (a_size != b_size)
    {
        return false;
    }
    else
    {
        const List<T> *a_ptr = &a;
        const List<T> *b_ptr = &b;

        while (a_ptr->get() && b_ptr->get() && a_ptr->get()->getItem() == b_ptr->get()->getItem())
        {
            a_ptr = &(a_ptr->get()->next);
            b_ptr = &(b_ptr->get()->next);
        }
        return a_ptr->get() == nullptr && b_ptr->get() == nullptr;
    }
}

template <class T>
bool operator!=(const List<T> &a, const List<T> &b)
{
    return !(a == b);
}

#endif
