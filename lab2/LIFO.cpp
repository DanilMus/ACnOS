#include <iostream>

using namespace std;

struct Node 
{
    int data; 
    Node* next;
    Node(int val): data(val), next(nullptr) {}
};

class Stack
{
    private: 
        Node* head;

        string showFromTailRecursive(Node* node) const 
        {
            if (node == nullptr)
                return "";
            
            return showFromTailRecursive(node -> next) + to_string(node -> data) + " ";
        }

    public:
        Stack(): head(nullptr) {}

        void add(int value)
        {
            Node* newNode = new Node(value);
            if (head == nullptr)
                head = newNode;
            else
            {
                newNode -> next = head; // присваиваем следующее значение next для head 
                head = newNode; // а новое значение head примет next
                // это соответствует структуре LIFO
            }
        }
        
        string showFromHead() const 
        {
            string result;
            Node* current = head;

            while (current != nullptr)
            {
                result += to_string(current -> data) + " ";
                current = current -> next;
            }

            return result;
        }

        string showFromTail() const 
        {
            return showFromTailRecursive(head);
        }

        void remove(int value)
        {
            Node* current = head;
            Node* prev = nullptr;

            while (current != nullptr)
            {
                if (current -> data == value)
                {
                    if (prev == nullptr) // если текущий элемент - это голова
                    {
                        head = head -> next;
                        delete current;
                        current = head; 
                    }
                    else // есди текущий элемент это все последующие
                    {
                        prev -> next = current -> next;
                        delete current;
                        current = prev -> next;
                    }
                }
                else
                {
                    prev = current;
                    current = current -> next;
                }
            }
        }

        int count (int value) const
        {
            int count = 0;
            Node* current = head; 

            while (current != nullptr)
            {
                if (current -> data == value)
                    count++;
                current = current -> next;
            }

            return count;
        }
};

int main()
{
    Stack stack;

    stack.add(5);
    stack.add(10);
    stack.add(15);
    stack.add(10);

    cout << "Stack from head: " << stack.showFromHead() << endl;
    cout << "Stack from tail: " << stack.showFromTail() << endl;
    cout << "Elements with data = 10: " << stack.count(10) << endl;

    stack.remove(10);
    cout << "Stack from head: " << stack.showFromHead() << endl;
    cout << "Elements with data = 10: " << stack.count(10) << endl;
}