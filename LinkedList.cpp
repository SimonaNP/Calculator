#include <iostream>

template <typename T>
struct LinkedListElement
{

    LinkedListElement(T const& _data, LinkedListElement* _next = nullptr) :
        data(_data), next(_next) {}

    T data;
    LinkedListElement* next;
};

template <typename T>
class LinkedListIterator;

template <typename T>
class LinkedList
{
public:

    using I = LinkedListIterator<T>;

private:

    using LLE = LinkedListElement<T>;

    LLE *front, *back;

    // O(n) �� �����, O(1) �� �����
    void copy(LinkedList const& l)
    {
        for(I it = l.begin(); it; ++it)
            insertEnd(*it);
    }

    // O(n) �� �����, O(1) �� �����


    // O(n) �� �����, O(1) �� �����
    I findPrev(I it)
    {
        I pit = begin();
        while (pit && pit.ptr->next != it.ptr)
            ++pit;
        return pit;
    }


public:

    // O(1)
    // ��������� �� ������ ������
    LinkedList() : front(nullptr), back(nullptr) {}

    // ����������� �� ��������
    LinkedList(LinkedList const& l) : front(nullptr), back(nullptr)
    {
        copy(l);
    }

    // �������� �� �����������
    LinkedList& operator=(LinkedList const& l)
    {
        if (this != &l)
        {
            clean();
            copy(l);
        }
        return *this;
    }

    void clean()
    {
        while(!empty())
        {
            T tmp;
            deleteBegin(tmp);
        }
    }

    // ����������
    ~LinkedList()
    {
        clean();
    }

    // O(1)
    // �������� ���� ������ � ������
    bool empty() const
    {
        return front == nullptr;
    }

    // O(n) �� �����, O(1) �� �����
    // �������� ����� �������
    bool insertBefore(T const& x, I it)
    {
        if (it == begin())
        {
            LLE* p = new LLE(x, front);
            if (empty())
                // ��� �������� � ��� ������, ������ ������ back ���� �� ���� ��� p
                back = p;
            front = p;
            return true;
        }

        if (!it || empty())
            return false;

        // ���������� � ������� � �������� � ��������
        // ���������� �� ���� ��� ������ �������
        // ���������� �� ����������� �� �� �������� �� insertAfter
        return insertAfter(x, findPrev(it));
    }

    // O(1)
    // �������� ���� �������
    bool insertAfter(T const& x, I it)
    {
        if (it == end() && empty())
        {
            // ��������� �� ����� ������� � ������ ������
            front = back = new LLE(x);
            return true;
        }
        else
        {
            if (!it)
                return false;
            // it � ������� ��������

            // ��������� ���� ���������� �������
            // ��� it == end(), ������ it.ptr == back, � it.next().ptr == nullptr
            LLE* p = new LLE(x, it.next().ptr);
            it.ptr->next = p;
            if (it == end())
                back = p;
        }
        return true;
    }

    // ���������� �� ������� �� �������
    // O(n) �� ����� � O(1) �� �����
    bool deleteAt(T& x, I it)
    {
        if (empty() || !it)
            return false;
        // �������� �� � ������
        // ���������� � �������

        if (it == begin())
        {
            // ���������� �� ������� �� �������� �� �������
            // front != nullptr
            x = front->data;
            LLE* p = front;
            front = front->next;
            if (front == nullptr)
                back = nullptr;
            delete p;
            return true;
        }

        // ���������� �� ���� � �������� �� �������
        return deleteAfter(x, findPrev(it));
    }

    // ���������� �� ������� ����� �������
    // O(n) �� ����� � O(1) �� �����
    bool deleteBefore(T& x, I it)
    {
        if (empty() || !it || it == begin())
            return false;
        // �������� � ��������
        // ���������� � ������� � �� ���� ��� ��������
        return deleteAt(x, findPrev(it));
    }

    // O(1)
    // ���������� �� ������� ���� �������
    bool deleteAfter(T& x, I it)
    {
        if (empty() || !it || it == end())
            return false;
        // it �� � � ���� �� ������� � � �������
        // �������� � ��������
        LLE* p = it.ptr->next; // �� ���� �� � nullptr
        it.ptr->next = p->next; // ���� �� � nullptr
        x = p->data;
        delete p;
        if (back == p)
            back = it.ptr;
        return true;
    }

    // O(1)
    // ������ �� ������� �� ������� � ���������� �� �������
    T& getAt(I it) const
    {
        return it.get();
    }

    // O(1)
    // �������� �� �������
    I begin() const
    {
        return I(front);
    }

    // O(1)
    // ����� �� �������
    I end() const
    {
        return I(back);
    }

    // �������� � �������� �� ������
    void insertBegin(T const& x)
    {
        insertBefore(x, begin());
    }

    // O(1)
    // �������� � ���� �� ������
    void insertEnd(T const& x)
    {
        insertAfter(x, end());
    }

    // O(1)
    // ��������� �� ������ �������
    bool deleteBegin(T& x)
    {
        return deleteAt(x, begin());
    }

    // ��������� �� ��������� �������
    bool deleteEnd(T& x)
    {
        return deleteAt(x, end());
    }

    // ����������� �����
    LinkedList& operator+=(T const& x)
    {
        insertEnd(x);
    }

    // O(n)
    void print(std::ostream& os = std::cout) const
    {
        for(I it = begin(); it; ++it)
            os << *it << ' ';
        os << std::endl;
    }

    void append(LinkedList& l)
    {
        if (back != nullptr)
            back->next = l.front;
        else
            // ������� ������ � ������, ��������� front � ��������
            front = l.front;

        if (l.back != nullptr)
            back = l.back;
        l.front = l.back = nullptr;
    }

    void reverse()
    {
        // TODO: �� �� ��������� �������� �� �����
    }

    // O(n) �� ����� � O(1) �� ��������
    int length() const
    {
        int n = 0;
        for(I it = begin(); it; ++it)
            ++n;
        return n;
    }
};

// ������ �������� �� O(1)
template <typename T>
class LinkedListIterator
{
private:

    using LLE = LinkedListElement<T>;

    LLE* ptr;

    //  static T error;

public:

    using I = LinkedListIterator<T>;
    friend class LinkedList<T>;

    // ����������� �� ��������
    LinkedListIterator(LLE* _ptr = nullptr) : ptr(_ptr) {}

    // ���� ����� �� ������ ��������!

    // �������� �������
    I next() const
    {
        // �������, �� ���������� � �������
        // if (!valid())
        //  return *this;

        return I(ptr->next);
    }

    // �������� �������
    I prev() const;

    // ������ �� ������� � ����� �� �������
    T& get() const
    {
        // ���������, �� ���������� � �������
        // if (!valid())
        //  return error;
        return ptr->data;
    }

    // ������ �� ������� ��� ����� �� �������
    T const& getConst() const;

    // �������� �� ���������
    bool valid() const
    {
        return ptr != nullptr;
    }

    // ��������� �� ��� ���������
    bool operator==(I const& it) const
    {
        return ptr == it.ptr;
    }

    bool operator!=(I const& it) const
    {
        return !(*this == it);
    }

    // ����������� �����

    // *it <-> it.get()
    T& operator*() const
    {
        return get();
    }

    // it++ <-> it = it.next(), ����� ������� �������� �� it
    I operator++(int)
    {
        I prev = *this;
        ++(*this);
        return prev;
    }

    // ++it <-> it = it.next(), ����� ������ �������� �� it
    I& operator++()
    {
        // ptr = ptr->next;
        // return *this;
        return *this = next();
    }

    // it <-> it.valid()
    operator bool() const
    {
        return valid();
    }
};

// O(n) �� ����� � O(1) �� �����
template <typename T>
void append(LinkedList<T>& l1, LinkedList<T> const& l2)
{
    for(LinkedListIterator<int> it = l2.begin(); it; ++it)
        l1 += *it;
}

// O(n) �� ����� � O(1) �� �����
template <typename T>
void reverse(LinkedList<T>& l)
{
    LinkedListIterator<T> it = l.begin();
    T x;
    while(l.deleteAfter(x, it))
        l.insertBegin(x);
}
