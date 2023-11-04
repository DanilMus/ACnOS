#include <iostream>

using namespace std;

template <typename T>
class Stack
{
    private:
        struct Node
        {
            T data;
            Node* next;
            Node(T val): data(val), next(nullptr) {}
        };

        Node* head;

        /*
            @brief Рекурсивно выводает список с хвоста

            @param Нода для взятия из нее данных для вывода

            @return Строка с элементами стэка с хвоста
        */
        void showFromTailRecursive(Node* node) const 
        {
            if (node == nullptr)
                return;
            
            showFromTailRecursive(node->next);
            cout << node->data << " ";
        }

    public:
        Stack(): head(nullptr) {}

        /*
            @brief Добавление нового элемента

            @param Значение, которое будет хранить новый элемент 
        */
        void add(T value)
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
        */
        void showFromHead() const 
        {
            if (head == nullptr)
            {
                cout << "stack is empty" << endl;
                return;
            }

            Node* current = head;

            while (current != nullptr)
            {
                cout << current->data << " ";
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
                cout << "stack is empty" << endl;
                return;
            }

            showFromTailRecursive(head);
            cout << endl;
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
    Stack<bool> stack;

    stack.add(true);
    stack.add(true);
    stack.add(false);
    stack.showFromTail();

    cout << stack.count(true) << endl;
    stack.remove(true);
    stack.showFromTail();
}