////
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

/*
   TEMPLATE TREE CLASS
   Multiple parents may point to the same child.
   Students must manage storage, pointers, and dynamic allocation.

   Requirements:
   1. Templated Tree class.
   2. Nodes stored dynamically.
   3. Each node has:
      - id
      - data
      - vector of children pointers
   4. Students must prevent memory leaks.
   5. Students must create createRoot, addNode, findNode, print functions, etc.

   DO NOT IMPLEMENT ANYTHING HERE.
   Only placeholders and TODO comments.
*/


template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;

    // TODO: Write constructor
    Node(const string &nodeID, const U &value): id(nodeID), data(value) {}

};

template <typename T>
class Tree {
private:
    Node<T>* root;
    vector<Node<T>*> allNodes;

public:
    Tree(): root(nullptr) {}
    // TODO: Initialize root pointer to nullptr



    void createRoot(const string &id, const T &value){
    // TODO: Allocate memory, assign id, assign data, set as root
        if (root != nullptr) {
            return;
        }
        Node<T>* node = new Node<T>(id, value);
        root = node;
        allNodes.push_back(node);
    }
    Node<T>* findNode(const string &id){
        // TODO: Use DFS or BFS to search tree
        for (auto* n : allNodes){
            if (n->id == id){
                return n;
            }
        }
        return nullptr;
    }

    void addNode(const string &parentID, const string &childID, const T &value){
    // TODO: Find parent, create child, link parent to child
    // TODO: Support repeated children under multiple parents
        Node<T>* parent = findNode(parentID);
        if (parent == nullptr){
            return;
        }
        Node<T>* child = findNode(childID);
        if (child == nullptr){
            child = new Node<T>(childID, value);
            allNodes.push_back(child);
        }
        for (auto* c : child->children){
            if(c == child) {
                return;
            }
        }
        parent->children.push_back(child);
    }


    void printAll() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        for (auto* n : allNodes) {
            cout << "Node " << n->id << ": " << n->data << endl;
            if (n->children.empty()) {
                cout << "  Child -> (none)" << endl;
            } else {
                for (auto* c : n->children) {
                    cout << "  Child -> " << c->id << endl;
                }
            }
            cout << endl;
        }
    }

    void playGame(){
        if (root == nullptr){
            cout << "Tree is empty." << endl;
            return;
        }
        cout <<"===== Begin Adventure =====" << endl << endl;
        Node<T> *current = root;
        while (current != nullptr){

            //displays current nodes text
            cout << current->data << endl;

            //if no children, end the game
            if (current->children.empty()){
                cout << "There are no further paths." << endl;
                cout << "Your journey ends here." << endl << endl;
                break;
            }

            //show choices
            cout<< "Choose your next action:" << endl;
            for (size_t i = 0; i < current->children.size(); i++){
                cout << (i+1) << ". " << current->children[i]->data << endl;
            }
            cout <<"Selection: ";


            //get user input and validate
            int choice;
            while (true){
                if(!(cin >> choice)){
                    cin.clear();
                    string x;
                    getline(cin, x);
                    cout << "Please enter a number between 1 and " << current->children.size() << ": ";
                    continue;
                }
                if (choice<1 || static_cast<size_t>(choice) > current->children.size()){
                    cout <<"Invalid choice. Enter a number between 1 and "<< current->children.size() << ": ";
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
               }
           }
           current = current -> children[choice-1];
           cout << endl;
        }
        cout <<"===== Adventure Complete =====" << endl << endl;
    }



    ~Tree(){
    // TODO: Free all allocated memory
        for (auto* c : allNodes){
            delete c;
        }
        allNodes.clear();
        root = nullptr;
    }
};

#endif //FA25EC3_TREE_H

