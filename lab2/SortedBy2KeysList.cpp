#include <iostream>

using namespace std; 

template <typename T1, typename T2>
class SortedBy2KeysList
{
    private:
        struct Node
        {
            T1 key1;
            T2 key2;
            Node* next;
            Node(T1 val1, T2 val2): key1(val1), key2(val2), next(nullptr) {}
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
            
            return showFromTailRecursive(node -> next) + node->key1 + ":" + to_string(node->key2) + " ";
        }

    public:
        SortedBy2KeysList(): head(nullptr) {}

        /*
            @brief Добавление нового элемента

            @param Значение, которое будет хранить новый элемент 
        */
       void add(T1 value1, T2 value2)
       {
            Node* newNode = new Node(value1, value2);

            if (!head || value1 < head->key1 && value2 < head->key2) // встает перед головой
            {
                newNode->next = head;
                head = newNode;
            }
            else // встает после головы
            {
                Node* current = head;
                while (current->next && current->next->key1 <= value1 && current->next->key2 <= value2) // проходим до тех пор, пока не встретим большее значение, это будет местом, где должен будет стоять наш элемент
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
                result += current->key1 + ":" + to_string(current->key2) + " ";
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

            return result;
        }


        /*
            @brief Удаляет элементы с заданным значение

            @param Значение элемента для удаления
        */
        void remove(T1 value1, T2 value2)
        {
            Node* current = head;
            Node* prev = nullptr;

            while (current != nullptr)
            {
                if (current->key1 == value1 && current->key2 == value2)
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
        int count (T1 value1, T2 value2) const
        {
            int count = 0;
            Node* current = head; 

            while (current != nullptr)
            {
                if (current -> key1 == value1 && current->key2 == value2)
                    count++;
                current = current -> next;
            }

            return count;
        }
};

int main()
{
    SortedBy2KeysList<string, int> list;

    list.add("Мусихин", 6);
    list.add("Иванов", 10);
    list.add("Иванов", 3);
    list.add("Шаравьев", 15);
    list.add("Мусихин", 6);
    list.add("Худеньких", 10);

    cout << "list from head: " << list.showFromHead() << endl;
    cout << "list from tail: " << list.showFromTail() << endl;
    cout << "Elements with data = Мусихин, 6: " << list.count("Мусихин", 6) << endl;

    list.remove("Мусихин", 6);
    cout << "list from head: " << list.showFromHead() << endl;
    cout << "Elements with data = Мусихин, 6: " << list.count("Мусихин", 6) << endl;
}