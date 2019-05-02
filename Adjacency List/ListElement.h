#ifndef LIST_ELEMENT_H
#define LIST_ELEMENT_H

#include <vector>
#include <iostream>  

using namespace std;

// class that stores individual element and their adjacent elements
template <typename ElementType> 
class ListElement{

    public:
        // constructors
        ListElement() = default;
        ListElement(const ElementType &name): elementName_(name), listSize_(0){}

        //accessors
        ElementType getElementName(){
            return elementName_; 
        }

        size_t getListSize(){
            return listSize_;
        }

        void displayList(){

            cout << elementName_ << " is connected to: " << endl;
            for(ElementNode node: adjacencyList_){
                cout << "\t" << node.nodeName_ << " with weight " << node.nodeWeight_ << endl;
            }
        }

        double getWeight(ElementType nodeName){

            for(ElementNode checkNode: adjacencyList_){
                if(checkNode.nodeName_ == nodeName) return checkNode.nodeWeight_;
            }
            return -1;
        }

        //mutators
        bool setName(ElementType name){
            elementName_ = name;
            return true;
        }

        bool addElement(ElementType nodeName, double weight){

            return addNewElement(nodeName, weight)? true: false;
        }

        bool checkConnection(ElementType nodeName){

            for(ElementNode checkNode: adjacencyList_){
                if(checkNode.nodeName_ == nodeName) return true;
            }

            return false;
        }


    private:

        struct ElementNode{
            ElementType nodeName_;
            double nodeWeight_;
        };

        ElementType elementName_;
        std::vector<ElementNode> adjacencyList_;
        size_t listSize_;                               // stores the size of the adjacency list for elementName_

        // private functions
        bool addNewElement(ElementType nodeName, double weight){
            ElementNode newNode = {nodeName, weight};
            adjacencyList_.push_back(newNode);
            listSize_++;
            return true;
        }
};

#endif  // LIST_ELEMENT_H