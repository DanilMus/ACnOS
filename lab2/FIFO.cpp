#include <iostream>

using namespace std;

template <typename T>
class Queue
{
    private:
        struct Node
        {
            T data;
            Node* next;
            Node(T val): data(val), next(nullptr) {}
        };

        Node* head;
        Node* tail;

        /*
            @brief Рекурсивно выводает список с хвоста

            @param Нода для взятия из нее данных для вывода
        */
        void showFromTailRecursive(Node* node) const 
        {
            if (node == nullptr)
                return;
            
            showFromTailRecursive(node -> next);
            cout << node -> data << " ";
        }
    
    public:
        Queue(): head(nullptr), tail(nullptr) {}

        /*
            @brief Добавление нового элемента

            @param Значение, которое будет хранить новый элемент 
        */
        void add(T value)
        {
            Node* newNode = new Node(value);
            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail -> next = newNode;
                tail = newNode;
            }
        }

        /*
            @brief Удаляет элементы с заданным значение

            @param Значение элемента для удаления
        */
        void remove(T value)
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

        /*
            @brief Выдает список с головы
        */
        void showFromHead() const 
        {
            if (head == nullptr)
            {
                cout << "queue is empty" << endl;
                return;
            }

            Node* current = head;

            while (current != nullptr)
            {
                cout << current -> data << " ";
                current = current -> next;
            }

            cout << endl;
        }

        /*
            @brief Выдает элементы с хвоста
        */
        void showFromTail() const 
        {
            if (head == nullptr)
            {
                cout << "queue is empty" << endl;
                return;
            }

            showFromTailRecursive(head);

            cout << endl;
        }


        /*
            @brief Считает элементы с заданным значением

            @param Значение

            @return Количество элементов
        */
        int count (T value) const
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
    Queue<int> queue;

    queue.add(1);
    queue.add(1);
    queue.add(3);
    queue.showFromHead();
    cout << queue.count(1) << endl;
    queue.remove(1);
    queue.showFromHead();
}   