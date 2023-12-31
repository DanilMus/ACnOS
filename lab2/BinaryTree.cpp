// Создание бинарного дерева и работа с ним
#include <iostream>

using namespace std;

template <typename T>
class BinaryTree
{
private:
    struct Node
    {
        T data;
        Node* right;
        Node* left;
        int height;
        Node(T val): data(val), right(nullptr), left(nullptr), height(1) {}
    };
    
    Node* root;

    // для добовления
    Node* addRecursive(Node* current, T value)
    {
        if (current == nullptr)
            return new Node(value);

        if (value < current->data)
            current->left = addRecursive(current->left, value);
        else if (value > current->data)
            current->right = addRecursive(current->right, value);

        return balance(current);    
    }

    // для вывода 
    void showRecursive(Node* current, int l) const
    {
        if (current == nullptr)
            return;
        
        showRecursive(current->left, l+1);
        for (int i = 0; i < l; i++)
            cout << "\t";
        cout << current->data << endl;
        showRecursive(current->right, l+1);

        cout << endl;
    }
    void showRightToLeftRecursive(Node* current, int l) const
    {
        if (current == nullptr)
            return;
        
        showRecursive(current->right, l+1);
        for (int i = 0; i < l; i++)
            cout << "\t";
        cout << current->data << endl;
        showRecursive(current->left, l+1);

        cout << endl;
    }

    // балансировка
    Node* balance(Node* node)
    {
        updateHeight(node);

        int balanceFactor = height(node->left) - height(node->right);

        // проверяем нарушение баланса
        if (balanceFactor > 1)
        {
            if (height(node->left->left) >= height(node->left->left))
                return rightRotate(node);
            else
            {
                leftRotate(node);
                return rightRotate(node);
            }
        }
        else if (balanceFactor < -1)
        {
            if (height(node->right->left) <= height(node->right->right))
                return leftRotate(node);
            else
            {
                rightRotate(node);
                return leftRotate(node);
            }
        }

        return node;
    }
    int height(Node* node) const
    {
        if (node)
            return node->height;
        else
            return 0;
    }

    void updateHeight(Node* node)
    {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    Node* leftRotate(Node* y)
    {
        Node* x = y->right;
        Node* T2 = x->left;

        x->left = y;
        y->right = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // удаление
    Node* findMin(Node* current)
    {
        while (current->left)
            current = current->left;
        return current;
    }

    Node* removeRecursive(Node* current, T value)
    {
        if (current == nullptr)
            return current;

        if (value < current->data)
            current->left = removeRecursive(current->left, value);
        else if (value > current->data)
            current->right = removeRecursive(current->right, value);
        else
        {
            Node* T2;
            if (current->left == nullptr)
            {
                T2 = current->right;
                delete current;
                return T2;
            }
            if (current->right == nullptr)
            {
                T2 = current->left;
                delete current;
                return T2;
            }
            T2 = findMin(current->right);
            current->data = T2->data;
            removeRecursive(current->right, T2->data);
        }

        return balance(current);
    }

    void delRecursive(Node* current)
    {
        if (current == nullptr)
            return;

        delRecursive(current->left);
        delRecursive(current->right);
        delete current;
    }

    // поиск
    Node* findRecursive(Node* current, T value) const
    {
        if (current == nullptr)
            return current;

        Node* T2;
        if (value < current->data)
        {
            T2 = findRecursive(current->left, value);
            if (T2)
                current = T2;
        }
        else if (value > current->data)
        {
            T2 = findRecursive(current->right, value);
            if (T2)
                current = T2;
        }

        return current;   
    }

public:
    BinaryTree(): root(nullptr) {}

    /*
        @brief Добавляет новый элемент

        @param Значение, которое будет хранить переменная
    */
    void add(T value)
    {
        root = addRecursive(root, value);
    }

    /*
        @brief Показ дерева слева-направо
    */
    void show() const
    {
        if (root)
            showRecursive(root, 0);
        else
            cout << "tree is empty" << endl;
    }
    /*
        @brief Показ дерева справа-налево
    */
    void showRightToLeft() const
    {
        if (root)
            showRightToLeftRecursive(root, 0);
        else
            cout << "tree is empty" << endl;
    }

    /*
        @brief Удаление элемента

        @param Значение для элемента, который удаляем
    */
    void remove(T value)
    {
        root = removeRecursive(root, value);
    }
    /*
        @brief Удаление всего дерева
    */
    void del()
    {
        delRecursive(root);
        root = nullptr;
    }

    /*
        @brief Поиск элемента

        @param Значение для элемента, который ищем
    */
    void find(T value) const
    {
        Node* node = findRecursive(root, value);
        if (node->data == value)
            showRecursive(node, 0);
        else
            cout << "there is no such element with value " << value << endl;
    }
};

int main()
{
    BinaryTree<int> tree;

    tree.add(1);
    tree.add(4);
    tree.add(7);
    tree.add(10);
    tree.show();
    tree.showRightToLeft();

    tree.add(-1);
    tree.add(-4);
    tree.show();

    tree.find(7);

    tree.remove(7);
    tree.show();

    tree.find(7);

    tree.del();
    tree.show();
}