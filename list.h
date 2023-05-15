#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
class Node {
public:
    Node(const T& data);
    T& getData();
		const T& getData() const;
    void setData(const T& data);
    Node<T>* getNext() const;
    void setNext(Node<T>* next);
    Node<T>* getPrev() const;
    void setPrev(Node<T>* prev);

private:
    T data;
    Node<T>* next;
    Node<T>* prev;
};

template <typename T>
class AbstractList {
public:
    virtual ~AbstractList() = default;
    virtual void insert(const T& data) = 0;
    virtual bool remove(const T& data) = 0;
    virtual T& retrieve(const T& data) const = 0;
    virtual void removeAll() = 0;
    virtual void display() const = 0;
};

template <typename T>
class LLL : public AbstractList<T> {
public:
    LLL();
    ~LLL();
    void insert(const T& data) override;
    bool remove(const T& data) override;
    T& retrieve(const T& data) const override;
    void removeAll() override;
    void display() const override;
		int length() const;
		T getRandomCard();

private:
    Node<T>* head;

    void insertRecursive(Node<T>*& head, const T& data);
    bool removeRecursive(Node<T>*& head, const T& data);
    T& retrieveRecursive(Node<T>* current, const T& data) const;
    void removeAllRecursive(Node<T>* head);
    void displayRecursive(Node<T>* head) const;
		int lengthRecursive(Node<T>* current) const;
		T getRandomCardRecursive(Node<T>* current, int index, int counter);
};

template <typename T>
class DLL : public AbstractList<T> {
public:
    DLL();
    ~DLL();
    void insert(const T& data) override;
    bool remove(const T& data) override;
    T& retrieve(const T& data) const override;
		T& retrieveByIndex(int index) const;
    void removeAll() override;
    void display() const override;

private:
    Node<T>* head;
    Node<T>* tail;

    void insertRecursive(Node<T>*& head, Node<T>*& tail, const T& data);
    bool removeRecursive(Node<T>* head, Node<T>*& tail, const T& data);
    T& retrieveRecursive(Node<T>* head, const T& data) const;
		T& retrieveByIndexRecursive(Node<T>* head, int index) const;
    void removeAllRecursive(Node<T>*& head, Node<T>*& tail);
    void displayRecursive(Node<T>* head) const;
};

#include "list.tpp"

#endif // LIST_H

