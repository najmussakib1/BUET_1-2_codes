 #include <iostream>
#include <fstream>
#include "listBST.hpp"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file)
    {
        cerr << "Unable to open file\n";
        return 2;
    }
    char c, str[5];
    int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst)
    {
        cerr << "Memory allocation failed\n";
        return 3;
    }
    while (in_file >> c)
    {
        // TODO: Implement the logic to read commands from the file and output accordingly
        // After every insertion and removal, print the BST in nested parentheses format
        // Handle exceptions where necessary and print appropriate error messages

        // Start your code here
        if (c == 'F')
        {
            in_file >> val;
            if (!bst->find(val))
                cout << "Key " << val << " not found in BST." << endl;
            else
                cout << "Key " << val << " found in BST." << endl;
        }
        else if (c == 'E')
        {
            if (bst->empty())
                cout << "Empty" << endl;
            else
                cout << "BST is not Empty" << endl;
        }
        else if (c == 'I')
        {
            in_file >> val;
            if (bst->insert(val, val))
            {
                cout << "Key " << val << " inserted into BST, ";
                bst->print('D');
                cout << endl;
            }
            else
            {
                cout << "Insertion failed! Key " << val << " already exists in BST, ";
                bst->print('D');
                cout << endl;
            }
        }
        else if (c == 'M')
        {
            in_file >> str;
            if (str[0] == 'M' && str[1] == 'i')
            {
                if (bst->find_min())
                    cout << "Minimum value: " << bst->find_min() << endl;
                else
                    cout << "Minimum find failed !" << endl;
            }
            else if (str[0] == 'M' && str[1] == 'a')
            {
                if (bst->find_max())
                    cout << "Maximum value: " << bst->find_max() << endl;
                else
                    cout << "Maximum find failed !" << endl;
            }
            else
                cout << "Invalid Command !" << endl;
        }
        else if (c == 'D')
        {
            in_file >> val;
            if (bst->remove(val))
                cout << "Key " << val << " removed from BST, ";
            else
                cout << "Removal failed! Key " << val << " not found in BST, ";
            bst->print('D');
            cout << endl;
        }
        else if (c == 'T')
        {
            in_file >> str;
            if (str[0] == 'P' && str[1] == 'r')
            {
                bst->print('P');
            }
            else if (str[0] == 'P' && str[1] == 'o')
            {
                bst->print('S');
            }
            else if (str[0] == 'I')
            {
                bst->print('I');
            }
            else
            {
                bst->print('D');
            }
        }
        else if (c == 'S')
            cout << "Size: " << bst->size() << endl;
        else
            cout << "Invalid Command !" << endl;

        // End your code here
    }
    in_file.close();
    delete bst;
    return 0;
}