// Ronak Guliani
// This class defines a Node, an abstract list, a Linear linked list, and a doubly linked list. All classes use templates to allow for flexibility of storing any data type. The lists contain various recursive methods for managing the list

#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
class Node {
public:
    Node(const T& data);
		~Node();
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

		// Overload operators
		LLL<T>& operator=(const LLL<T>& other);
		LLL<T> operator+(const LLL<T>& other) const;
		LLL<T> operator+(const T& data) const;
		LLL<T>& operator+=(const LLL<T>& other);


private:
    Node<T>* head;

    void insertRecursive(Node<T>*& head, const T& data);
    bool removeRecursive(Node<T>*& head, const T& data);
    T& retrieveRecursive(Node<T>* current, const T& data) const;
    void removeAllRecursive(Node<T>*& head);
    void displayRecursive(Node<T>* head) const;
		int lengthRecursive(Node<T>* current) const;
		T getRandomCardRecursive(Node<T>* current, int index, int counter);
		
		// Helper functions for overloading
		void copyRecursive(Node<T>*&, const Node<T>*);
		void appendRecursive(Node<T>*&, const Node<T>*);
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

		// Overload operators
		DLL<T>& operator=(const DLL<T>& other);
    DLL<T> operator+(const DLL<T>& other) const;
		DLL<T> operator+(const T& data) const;
    DLL<T>& operator+=(const DLL<T>& other);

private:
    Node<T>* head;
    Node<T>* tail;

    void insertRecursive(Node<T>*& head, Node<T>*& tail, const T& data);
    bool removeRecursive(Node<T>* head, Node<T>*& tail, const T& data);
    T& retrieveRecursive(Node<T>* head, const T& data) const;
		T& retrieveByIndexRecursive(Node<T>* head, int index) const;
    void removeAllRecursive(Node<T>*& head, Node<T>*& tail);
    void displayRecursive(Node<T>* head) const;

		// Helper functions for overloading
		void copyRecursive(Node<T>*&, Node<T>*&, const Node<T>*);
		void appendRecursive(Node<T>*&, Node<T>*&, const Node<T>*);
};

#include "list.tpp"

#endif // LIST_H

