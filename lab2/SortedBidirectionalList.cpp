#include <iostream>

using namespace std; 

template <typename T>
class SortedBidirectionalList
{
    private:
        struct Node
        {
            T key;
            Node* next;
            Node* prev;
            Node(T val): key(val), next(nullptr), prev(nullptr) {}
        };
        Node* head;

    public:
        SortedBidirectionalList(): head(nullptr) {}

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
                if (head)
                    head->prev = newNode;
                head = newNode;
            }
            else // встает после головы
            {
                Node* current = head;
                while (current->next && current->next->key <= value) // проходим до тех пор, пока не встретим большее значение, это будет местом, где должен будет стоять наш элемент
                    current = current->next;
                // по итогу current - это элемент, который меньше или равен, которому вставляем, но после которого идет эл-т больше вставляемого
                

                newNode->next = current->next;
                if (current->next)
                    current->next->prev = newNode;
                current->next = newNode;
                newNode->prev = current;
                // после всех вставок должно получится
                // current <-> newNode <-> current->next
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
            if (head == nullptr)
                return "sorted list is empty";

            Node* current = head;
            while (current->next != nullptr)
                current = current->next; // доходим до конца
            
            string result;
            while (current != nullptr)
            {
                result += to_string(current -> key) + " ";
                current = current -> prev;
            }

            return result;
        }


        /*
            @brief Удаляет элементы с заданным значение

            @param Значение элемента для удаления
        */
        void remove(T value)
        {
            Node* current = head;

            while (current != nullptr)
            {
                if (current -> key == value)
                {
                    if (current->prev == nullptr) // если текущий элемент - это голова
                    {
                        head = head -> next;
                        head->prev = nullptr;
                        delete current;
                        current = head; 
                    }
                    else // если текущий элемент это все последующие
                    {
                        current->prev -> next = current->next;
                        current->next -> prev = current->prev;
                        Node* remember = current->next;
                        delete current;
                        current = remember;
                        remember = nullptr;
                    }
                }
                else
                    current = current -> next;
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
    SortedBidirectionalList<int> list;

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