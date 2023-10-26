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

            @return Строка с элементами стэка с хвоста
        */
        string showFromTailRecursive(Node* node) const 
        {
            if (node == nullptr)
                return "";
            
            return showFromTailRecursive(node -> next) + to_string(node -> data) + " ";
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

            @return Строка с элементами с головы
        */
        string showFromHead() const 
        {
            if (head == nullptr)
                return "queue is empty";

            string result;
            Node* current = head;

            while (current != nullptr)
            {
                result += to_string(current -> data) + " ";
                current = current -> next;
            }

            return result;
        }

        /*
            @brief Выдает элементы с хвоста

            @return Строка с элементами с хвоста
        */
        string showFromTail() const 
        {
            string result = showFromTailRecursive(head);
            
            if (result == "")
                return "queue is empty";

            return showFromTailRecursive(head);
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

    queue.add(5);
    queue.add(10);
    queue.add(15);
    queue.add(10);

    cout << "queue from head: " << queue.showFromHead() << endl;
    cout << "queue from tail: " << queue.showFromTail() << endl;
    cout << "Elements with data = 10: " << queue.count(10) << endl;

    queue.remove(10);
    cout << "queue from head: " << queue.showFromHead() << endl;
    cout << "Elements with data = 10: " << queue.count(10) << endl;

    queue.remove(15);
    cout << "queue from head: " << queue.showFromHead() << endl;
    queue.remove(4);
    queue.remove(5);
    queue.remove(4);
    cout << "queue from head: " << queue.showFromHead() << endl;
}   