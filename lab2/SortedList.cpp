#include <iostream>

using namespace std; 

template <typename T>
class SortedList
{
    private:
        struct Node
        {
            T key;
            Node* next;
            Node(T val): key(val), next(nullptr) {}
        };
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
            
            return showFromTailRecursive(node -> next) + to_string(node -> key) + " ";
        }

    public:
        SortedList(): head(nullptr) {}

        /*
            @brief Добавление нового элемента

            @param Значение, которое будет хранить новый элемент 
        */
       void add(T value)
       {
            Node* newNode = new Node(value);

            if (!head || value < head->key) // встает перед головой
            {
                newNode->next = head;
                head = newNode;
            }
            else // встает после головы
            {
                Node* current = head;
                while (current->next && current->next->key <= value) // проходим до тех пор, пока не встретим большее значение, это будет местом, где должен будет стоять наш элемент
                    current = current->next;
                // по итогу current - это элемент, который меньше или равен, которому вставляем, но после которого идет эл-т больше вставляемого    
                
                newNode->next = current->next;
                current->next = newNode;
                // после всех вставок должно получится
                // current -> newNode -> current->next
            }
       }

       /*
            @brief Выдает список с головы

            @return Строка с элементами с головы
        */
        string showFromHead() const 
        {
            if (head == nullptr)
                return "sorted list is empty";

            string result;
            Node* current = head;

            while (current != nullptr)
            {
                result += to_string(current -> key) + " ";
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
        void remove(T value)
        {
            Node* current = head;
            Node* prev = nullptr;

            while (current != nullptr)
            {
                if (current -> key == value)
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
                if (current -> key == value)
                    count++;
                current = current -> next;
            }

            return count;
        }
};

int main()
{
    SortedList<int> list;

    list.add(6);
    list.add(10);
    list.add(15);
    list.add(10);

    cout << "list from head: " << list.showFromHead() << endl;
    cout << "list from tail: " << list.showFromTail() << endl;
    cout << "Elements with data = 10: " << list.count(10) << endl;

    list.remove(10);
    cout << "list from head: " << list.showFromHead() << endl;
    cout << "Elements with data = 10: " << list.count(10) << endl;
}