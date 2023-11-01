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
    string showRecursive(Node* current, int l) const
    {
        if (current == nullptr)
            return " ";
        
        string result = showRecursive(current->left, l+1);
        for (int i = 0; i < l; i++)
            result += "\t";
        result += to_string(current->data) + "\n";
        result += showRecursive(current->right, l+1);

        return result;
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

public:
    BinaryTree(): root(nullptr) {}

    // добавление
    void add(T value)
    {
        root = addRecursive(root, value);
    }

    // просмотр
    string show() const
    {
        if (root)
            return showRecursive(root, 0);
        else
            return "tree is empty";
    }
};

int main()
{
    BinaryTree<int> tree;

    tree.add(1);
    tree.add(4);
    tree.add(7);
    tree.add(10);
    cout << tree.show() << endl;

    tree.add(-1);
    tree.add(-4);

    cout << tree.show();
}