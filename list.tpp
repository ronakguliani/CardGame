// Ronak Guliani
#include <type_traits>

using namespace std;

// Node implementation

// Default constructor
template <typename T>
Node<T>::Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}

// Node destructor
template <typename T>
Node<T>::~Node() {

	// Check if T is a pointer
	if constexpr(is_pointer<T>::value)
		if (data)
			delete data;

	next = nullptr;
	prev = nullptr;
}

template <typename T>
T& Node<T>::getData() {
    return data;
}

template <typename T>
const T& Node<T>::getData() const {
	return data;
}

template <typename T>
void Node<T>::setData(const T& data) {
    this->data = data;
}

template <typename T>
Node<T>* Node<T>::getNext() const {
    return next;
}

template <typename T>
void Node<T>::setNext(Node<T>* next) {
    this->next = next;
}

template <typename T>
Node<T>* Node<T>::getPrev() const {
    return prev;
}

template <typename T>
void Node<T>::setPrev(Node<T>* prev) {
    this->prev = prev;
}

// LLL implementation
template <typename T>
LLL<T>::LLL() : head(nullptr) {}

template <typename T>
LLL<T>::~LLL() {
    removeAll();
}


template <typename T>
LLL<T>& LLL<T>::operator= (const LLL<T>& other) {
	if (this != &other) {
		removeAll();
		copyRecursive(head, other.head);
	}
	return *this;
}

template <typename T>
void LLL<T>::copyRecursive(Node<T>*& current, const Node<T>* otherCurrent) {
    if (otherCurrent != nullptr) {
        insert(otherCurrent->getData());
        copyRecursive(current->getNext(), otherCurrent->getNext());
    }
}


template <typename T>
LLL<T>& LLL<T>::operator+=(const LLL<T>& other) {
    appendRecursive(head, other.head);
		return *this;
}

template <typename T>
void LLL<T>::appendRecursive(Node<T>*& current, const Node<T>* otherCurrent) {
    if (otherCurrent != nullptr) {
        insert(otherCurrent->getData());
        appendRecursive(current->getNext(), otherCurrent->getNext());
    }
}

// Insert new node to a new list and return it
template <typename T>
LLL<T> LLL<T>::operator+(const T& data) const {
    LLL<T> newList = *this;
    newList.insert(data);
    return newList;
}

template <typename T>
LLL<T> LLL<T>::operator+(const LLL<T>& other) const {
    LLL<T> newList;
    newList += *this;
    newList += other;
    return newList;
}


// Insert data to list
template <typename T>
void LLL<T>::insert(const T& data) {
/*
		if (head == nullptr) {
			head = new Node<T>(data); 
			head->setNext(nullptr);
			return;
		}
*/
    insertRecursive(head, data);
}

template <typename T>
bool LLL<T>::remove(const T& data) {
    return removeRecursive(head, data);
}

template <typename T>
T& LLL<T>::retrieve(const T& data) const {
    return retrieveRecursive(head, data);
}

template <typename T>
void LLL<T>::removeAll() {
    removeAllRecursive(head);
		head = nullptr;
}

template <typename T>
void LLL<T>::display() const {
    displayRecursive(head);
    cout << endl;
}

template <typename T>
void LLL<T>::insertRecursive(Node<T>*& current, const T& data) {
    if (!current) {
			current = new Node<T>(data); 
    } else {
				Node<T>* nextNode = current->getNext();
        insertRecursive(nextNode, data);
				current->setNext(nextNode);
    	}
}

template <typename T>
bool LLL<T>::removeRecursive(Node<T>*& head, const T& data) {
    if (!head) 
        return false;
    if (head->getData() == data) {
        Node<T>* temp = head;
        head = head->getNext();
        delete temp;
        return true;
    } 
    
		Node<T>* next = head->getNext();    
		return removeRecursive(next, data);
}

template <typename T>
T& LLL<T>::retrieveRecursive(Node<T>* current, const T& data) const {
    if (!current) {
			throw out_of_range("Data not found");
    } else if (current->getData() == data) {
        return current->getData();
    } else {
        return retrieveRecursive(current->getNext(), data);
    }
}

template <typename T>
void LLL<T>::removeAllRecursive(Node<T>*& head) {
    if (head) {
				Node<T>* next = head->getNext();
        removeAllRecursive(next);
        delete head;
        head = nullptr;
    }
}

template <typename T>
void LLL<T>::displayRecursive(Node<T>* head) const {
    if (head) {
        cout << *head->getData() << endl;
        displayRecursive(head->getNext());
    }
}

// Get a random card from the list
template <typename T>
T LLL<T>::getRandomCard() {
    if (!head) {
			throw runtime_error("List is empty, cannot get a random card");
    }

    int index = rand() % length() + 1;
    return getRandomCardRecursive(head, index, 1);
}

template <typename T>
T LLL<T>::getRandomCardRecursive(Node<T>* current, int index, int counter) {
		if (!current) {
        throw runtime_error("Unexpected end of list encountered");
		}

    if (counter == index) {
        return current->getData();
    }
    
    return getRandomCardRecursive(current->getNext(), index, counter + 1);
}


template <typename T>
int LLL<T>::length() const {
    return lengthRecursive(head);
}

template <typename T>
int LLL<T>::lengthRecursive(Node<T>* current) const {
    if (!current) {
        return 0;
    }
    return 1 + lengthRecursive(current->getNext());
}

// DLL implementation
template <typename T>
DLL<T>::DLL() : head(nullptr), tail(nullptr) {}

template <typename T>
DLL<T>::~DLL() {
    removeAll();
}

template <typename T>
void DLL<T>::insert(const T& data) {
    insertRecursive(head, tail, data);
}

template <typename T>
bool DLL<T>::remove(const T& data) {
    return removeRecursive(head, tail, data);
}

template <typename T>
T& DLL<T>::retrieve(const T& data) const {
    return retrieveRecursive(head, data);
}

template <typename T>
T& DLL<T>::retrieveByIndex(int index) const {
	try {
		return retrieveByIndexRecursive(head, index);
	} catch (const out_of_range& e) {
			throw e;
		}
}

template <typename T>
T& DLL<T>::retrieveByIndexRecursive(Node<T>* current, int index) const {
    if (current == nullptr) {
			throw out_of_range("Index out of range");
    }
    if (index == 0) {
        return current->getData();
    }
    return retrieveByIndexRecursive(current->getNext(), index - 1);
}


template <typename T>
void DLL<T>::removeAll() {
    removeAllRecursive(head, tail);
		head = nullptr;
		tail = nullptr;
}

template <typename T>
void DLL<T>::display() const {
    displayRecursive(head);
    cout << endl;
}

template <typename T>
void DLL<T>::insertRecursive(Node<T>*& head, Node<T>*& tail, const T& data) {
    if (!head) {
        head = new Node<T>(data);
        tail = head;
    } else {
        tail->setNext(new Node<T>(data));
        tail->getNext()->setPrev(tail);
        tail = tail->getNext();
    }
}

template <typename T>
bool DLL<T>::removeRecursive(Node<T>* head, Node<T>*& tail, const T& data) {
    if (!head) {
        return false;
    } else if (head->getData() == data) {
        Node<T>* temp = head;
        head = head->getNext();
        if (head) {
            head->setPrev(nullptr);
        } else {
            tail = nullptr;
        }
        delete temp;
        return true;
    } else {
        return removeRecursive(head->getNext(), tail, data);
    }
}

template <typename T>
T& DLL<T>::retrieveRecursive(Node<T>* current, const T& data) const {
    if (current == nullptr) {
        throw out_of_range("Data not found");
    }
    if (current->getData() == data) {
        return current->getData();
    }
    return retrieveRecursive(current->getNext(), data);
}


template <typename T>
void DLL<T>::removeAllRecursive(Node<T>*& head, Node<T>*& tail) {
    if (head) {
        Node<T>* next = head->getNext();
        if (head == tail) {
            tail = nullptr;
        }
        delete head;
        head = nullptr;
        removeAllRecursive(next, tail);
    }
}

template <typename T>
DLL<T> DLL<T>::operator+(const T& data) const {
    DLL<T> newList = *this;
    newList.insert(data);
    return newList;
}

template <typename T>
DLL<T> DLL<T>::operator+(const DLL<T>& other) const {
    DLL<T> newList;
    newList += *this;
    newList += other;
    return newList;
}

template <typename T>
DLL<T>& DLL<T>::operator=(const DLL<T>& other) {
    if (this != &other) {
        removeAll();
        copyRecursive(head, tail, other.head);
    }
    return *this;
}

template <typename T>
void DLL<T>::copyRecursive(Node<T>*& currentHead, Node<T>*& currentTail, const Node<T>* otherCurrent) {
    if (otherCurrent != nullptr) {
        insert(otherCurrent->getData());
        copyRecursive(currentHead->getNext(), currentTail, otherCurrent->getNext());
    }
}


template <typename T>
DLL<T>& DLL<T>::operator+=(const DLL<T>& other) {
    appendRecursive(head, tail, other.head);
		return *this;
}


template <typename T>
void DLL<T>::appendRecursive(Node<T>*& currentHead, Node<T>*& currentTail, const Node<T>* otherCurrent) {
    if (otherCurrent != nullptr) {
        insert(otherCurrent->getData());
        appendRecursive(currentHead->getNext(), currentTail, otherCurrent->getNext());
    }
}

template <typename T>
void DLL<T>::displayRecursive(Node<T>* head) const {
    if (head) {
        cout << head->getData() << endl;
        displayRecursive(head->getNext());
    }
}
