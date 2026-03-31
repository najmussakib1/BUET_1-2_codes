#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
using namespace std;


int TOTAL_BIDS = 0;
int TOTAL_SUCCESS = 0;
int TOTAL_REJECT = 0;

void printauction(BST<string, int> *items)
{
    cout<<"BST (In-order): ";
    items->print('I');
    cout << endl;
}

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
        return 1;
    }

    // TODO: Declare data structures to track bid statistics for each item
    // You need to track: total bids, successful bids, rejected bids for each item
    // Hint: You may use additional BSTs or other data structures
    // Start your code here
    typedef struct Stats
{
    int total_bids;
    int successful_bids;
    int rejected_bids;
    Stats() : total_bids(0), successful_bids(0), rejected_bids(0) {}
} Stats;

    BST<string, int> *items = new ListBST<string, int>();
    BST<string, Stats *> *stats = new ListBST<string, Stats *>();
    // End your code here

    int n;
    in_file >> n;
    for (int i = 0; i < n; ++i)
    {
        // TODO: Implement the logic to read initial items and their starting bids
        // Initialize statistics tracking for each item
        // Start your code here
        string id;
        int bid;
        in_file >> id >> bid;

        if (!items->find(id))
        {
            items->insert(id, bid);
            stats->insert(id, new Stats());
        }
        else
        {
            int cur = items->get(id);
            if (bid > cur) items->update(id, bid);
        }
        // End your code here
    }

    // TODO: Implement the logic to print the initial auction state
    // Start your code here
    cout << "Initial auction items:\n";
    printauction(items);
    // End your code here
    cout << "\nAuction starts!\n\n";
    cout << "==============================\n";

    string operation;
    while (in_file >> operation)
    {
        // TODO: Implement the logic to process operations (ADD, BID, CHECK, STATS, REPORT) and print auction state after each operation
        // For BID operations: update statistics (total bids, successful/rejected counts)
        // For STATS operations: display statistics for the specified item
        // For REPORT operations: display comprehensive auction statistics
        // For other operations: print auction state using in-order traversal
        // Start your code here
        if (operation == "ADD")
        {
            string id;
            int bid;
            in_file >> id >> bid;

            if (!items->find(id))
            {
                items->insert(id, bid);
                stats->insert(id, new Stats());
                cout << "Item " << id << " added with starting bid " << bid << endl;
            }
            else
            {
                int cur = items->get(id);
                if (bid > cur)
                {
                    items->update(id, bid);
                    cout << "Item " << id << " updated to new starting bid " << bid << endl;
                }
                else
                {
                    cout << "Item " << id << " already exists. Bid unchanged.\n";
                }
            }
            printauction(items);
        }
        else if (operation == "BID")
        {
            string id;
            int bid;
            in_file >> id >> bid;

            if (!items->find(id))
            {
                cout << "Item " << id << " does not exist.\n";
            }
            else
            {
                Stats *s = stats->get(id);
                s->total_bids++;
                TOTAL_BIDS++;
                int cur = items->get(id);
                if (bid > cur)
                {
                    items->update(id, bid);
                    s->successful_bids++;
                    TOTAL_SUCCESS++;
                    cout << "Bid of " << bid << " on " << id << " accepted. Current bid: " << bid << endl;
                }
                else
                {
                    s->rejected_bids++;
                    TOTAL_REJECT++;
                    cout << "Bid of " << bid << " on " << id << " rejected. Current bid: " << cur << endl;
                }
            }

            printauction(items);
        }
        else if (operation == "CHECK")
        {
            string id;
            in_file >> id;

            if (!items->find(id))
                cout << "Item " << id << " does not exist.\n";
            else
                cout << "Current bid for " << id << ": " << items->get(id) << endl;

            printauction(items);
        }
        else if (operation == "STATS")
        {
            string id;
            in_file >> id;

            if (!stats->find(id))
            {
                cout << "Item " << id << " does not exist.\n";
            }
            else
            {
                Stats *s = stats->get(id);
                cout << "Statistics for " << id << ":\n";
                cout << "  Current highest bid: " << items->get(id) << endl;
                cout << "  Total bids placed: " << s->total_bids << endl;
                cout << "  Successful bids: " << s->successful_bids << endl;
                cout << "  Rejected bids: " << s->rejected_bids << endl;
            }
        }
        else if (operation == "REPORT")
        {
            cout << "Auction Report:\n";
            cout << "Total items: " << items->size() << endl;
            cout << "Total bids placed: " << TOTAL_BIDS << endl;
            cout << "Total successful bids: " << TOTAL_SUCCESS << endl;
            cout << "Total rejected bids: " << TOTAL_REJECT << endl;
            cout << endl;
            cout << "Item Statistics:\n";
            BST<string, Stats*> *temp = new ListBST<string, Stats*>();

            while (!stats->empty())
            {
                string id = stats->find_min();
                Stats *s = stats->get(id);

                int curBid = items->get(id);

                cout << "  " << id
                     << ": Current bid: " << curBid
                     << ", Total bids: " << s->total_bids
                     << ", Successful: " << s->successful_bids
                     << ", Rejected: " << s->rejected_bids;

                temp->insert(id, s);
                stats->remove(id);
                if(!stats->empty()) cout << endl;
            }

            while (!temp->empty())
            {
                string id = temp->find_min();
                stats->insert(id, temp->get(id));
                temp->remove(id);
            }

            delete temp;
            cout << endl;
        }

        // End your code here
        cout << "==============================\n";
    }

    in_file.close();
    // TODO: Delete data structures you created
    // Start your code here
    delete items;
    delete stats;
    in_file.close();
    // End your code here
    return 0;
}
