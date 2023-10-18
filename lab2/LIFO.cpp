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
        Stack(): head(nullptr) {}

        /*
            @brief Добавление нового элемента

            @param Значение, которое будет хранить новый элемент 
        */
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
        
        /*
            @brief Выдает список с головы

            @return Строка с элементами с головы
        */
        string showFromHead() const 
        {
            if (head == nullptr)
                return "stack is empty";

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
                return "stack is empty";

            return showFromTailRecursive(head);
        }

        /*
            @brief Удаляет элементы с заданным значение

            @param Значение элемента для удаления
        */
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

        /*
            @brief Считает элементы с заданным значением

            @param Значение

            @return Количество элементов
        */
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