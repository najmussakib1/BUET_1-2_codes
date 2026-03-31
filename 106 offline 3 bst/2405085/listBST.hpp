#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>

/**
 * Binary Search Tree implementation using linked list structure
 *
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
using namespace std;

template <typename Key, typename Value>
class ListBST : public BST<Key, Value>
{
private:
    /**
     * Node class for the binary search tree
     */
    class Node
    {
    public:
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node *root;
    size_t node_count;

    // TODO: Implement private helper functions as needed
    // Start your private helper functions here
    Node *insertnode(Node *node, Key key, Value value, bool &inserted)
    {
        if (node == nullptr)
        {
            inserted = true;
            node_count++;
            return new Node(key, value);
        }
        if (key < node->key)
        {
            node->left = insertnode(node->left, key, value, inserted);
        }
        else if (key > node->key)
        {
            node->right = insertnode(node->right, key, value, inserted);
        }
        else
        {
            inserted = false; // Key already exists
        }
        return node;
    }
    Node *removenode(Node *node, Key key, bool &removed)
    {
        if (node == nullptr)
        {
            removed = false;
            return node;
        }
        if (key < node->key)
        {
            node->left = removenode(node->left, key, removed);
        }
        else if (key > node->key)
        {
            node->right = removenode(node->right, key, removed);
        }
        else
        {
            removed = true;
            node_count--;
            if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node *temp = findMinNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = removenode(node->right, temp->key, removed);
            node_count++;
        }
        return node;
    }

    Node *findMinNode(Node *node) const
    {
        while (node && node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }
    Node *findnode(Node *node, Key key) const
    {
        if (!node)
            return nullptr;
        if (key < node->key)
            return findnode(node->left, key);
        if (key > node->key)
            return findnode(node->right, key);
        return node;
    }
    // End your private helper functions here
    void cleartree(Node *node)
    {
        if (!node)
            return;
        cleartree(node->left);
        cleartree(node->right);
        delete node;
    }
    void printDefault(Node *node) const
    {
        if (!node)
            return;

        cout << "(" << node->key << ":" << node->value;
        if (node->left || node->right)
        {
            cout << " ";
            if (node->left) printDefault(node->left);
            else cout << "()";

            if (node->right){
                cout << " ";
                printDefault(node->right);
            }
        }

        cout << ")";
    }
    void printIn(Node *node) const
    {
        if (!node)
            return;
        printIn(node->left);
        cout << "(" << node->key << ":" << node->value << ") ";
        printIn(node->right);
    }
    void printPre(Node *node) const
    {
        if (!node)
            return;
        cout << "(" << node->key << ":" << node->value << ") ";
        printPre(node->left);
        printPre(node->right);
    }

    void printPost(Node *node) const
    {
        if (!node)
            return;
        printPost(node->left);
        printPost(node->right);
        cout << "(" << node->key << ":" << node->value << ") ";
    }

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}

    /**
     * Destructor
     */
    ~ListBST()
    {
        // TODO: Implement destructor to free memory
        clear();
    }

    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override
    {
        // TODO: Implement insertion logic
        bool inserted = false;
        root = insertnode(root, key, value, inserted);
        return inserted;
    }

    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override
    {
        // TODO: Implement removal logic
        bool removed = false;
        root = removenode(root, key, removed);
        return removed;
    }

    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override
    {
        // TODO: Implement find logic
        return findnode(root, key) != nullptr;
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override
    {
        // TODO: Implement get logic
        Node *n = findnode(root, key);
        if (!n)
        {
            cerr << "Key not found" << endl;
            throw runtime_error("Key not found");
        }
        return n->value;
    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override
    {
        // TODO: Implement update logic
        Node *n = findnode(root, key);
        if (!n)
        {
            cerr << "Key not found" << endl;
            throw runtime_error("Key not found");
        }
        n->value = value;
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override
    {
        // TODO: Implement clear logic
        cleartree(root);
        root = nullptr;
        node_count = 0;
    }

    /**
     * Get the number of keys in the BST
     */
    size_t size() const override
    {
        // TODO: Implement size logic
        return node_count;
    }
    /**
     * Check if the BST is empty
     */
    bool empty() const override
    {
        // TODO: Implement empty check logic
        return node_count == 0;
    }

    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override
    {
        // TODO: Implement find_min logic
        if (!root)
        {
            cerr << "BST is empty" << endl;
            throw runtime_error("BST is empty");
        }
        Node *minNode = findMinNode(root);
        return minNode->key;
    }

    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override
    {
        // TODO: Implement find_max logic
        if (!root)
        {
            cerr << "BST is empty" << endl;
            throw runtime_error("BST is empty");
        }
        Node *current = root;
        while (current->right)
        {
            current = current->right;
        }
        return current->key;
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override
    {
        // TODO: Implement print logic
        if (traversal_type == 'D')
            printDefault(root);
        else if (traversal_type == 'I')
            printIn(root);
        else if (traversal_type == 'P')
            printPre(root);
        else
            printPost(root);
    }
};

#endif // LISTBST_H