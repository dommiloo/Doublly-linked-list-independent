
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

struct Node {
    int   data;
    Node* prev;
    Node* next;

    explicit Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};


class DoublyLinkedList {
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size_(0) {}
    ~DoublyLinkedList();

  
    void push_front(int value);
    void push_back(int value);
    int  pop_front();
    int  pop_back();
=
    std::size_t size() const { return size_; }
    bool        empty() const { return size_ == 0; }
    void        print_forward()  const;
    void        print_backward() const;

private:
    Node* head;
    Node* tail;
    std::size_t size_;

    
    DoublyLinkedList(const DoublyLinkedList&)            = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
};

/* 
 Destructor – walk from head and delete nodes.
  O(n) time, O(1) extra space.
 */
DoublyLinkedList::~DoublyLinkedList() {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
}


void DoublyLinkedList::push_front(int value) {
    Node* n = new Node(value);
    n->next = head;         // new node points forward
    if (head) head->prev = n;
    head = n;
    if (!tail) tail = n;    // list was empty
    ++size_;
}

/* 
 push_back – append a new value in symmetric fashion.
 */
void DoublyLinkedList::push_back(int value) {
    Node* n = new Node(value);
    n->prev = tail;
    if (tail) tail->next = n;
    tail = n;
    if (!head) head = n;
    ++size_;
}


int DoublyLinkedList::pop_front() {
    if (empty()) throw std::underflow_error("pop_front on empty list");
    Node* n = head;
    int   val = n->data;
    head = head->next;
    if (head) head->prev = nullptr;
    else      tail = nullptr;  // list became empty
    delete n;
    --size_;
    return val;
}

int DoublyLinkedList::pop_back() {
    if (empty()) throw std::underflow_error("pop_back on empty list");
    Node* n = tail;
    int   val = n->data;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else      head = nullptr;
    delete n;
    --size_;
    return val;
}

/*  print_forward / print_backward –  traversals to
 verify links
 */
void DoublyLinkedList::print_forward() const {
    cout << "[head] ";
    for (Node* cur = head; cur; cur = cur->next)
        cout << cur->data << " ";
    cout << "[null]" << endl;
}

void DoublyLinkedList::print_backward() const {
    cout << "[tail] ";
    for (Node* cur = tail; cur; cur = cur->prev)
        cout << cur->data << " ";
    cout << "[null]" << endl;
}

//Builds a list, shows its state after each operation, then  it pops from both ends.
 
int main() {
    DoublyLinkedList dll;

    cout << "Pushing 3, 2, 1 at the front…" << endl;
    dll.push_front(3);
    dll.push_front(2);
    dll.push_front(1);
    dll.print_forward();   // 1 2 3
    dll.print_backward();  // 3 2 1

    cout << "\nPushing 4, 5 at the back…" << endl;
    dll.push_back(4);
    dll.push_back(5);
    dll.print_forward();   // 1 2 3 4 5
    dll.print_backward();  // 5 4 3 2 1

    cout << "\nPopping front:  " << dll.pop_front() << endl; // 1
    cout << "Popping back:   " << dll.pop_back()  << endl;   // 5
    dll.print_forward();                                      // 2 3 4
    cout << "\nSize now: " << dll.size() << endl;
}
