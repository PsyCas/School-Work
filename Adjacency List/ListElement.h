/* 
    * ListElement.h
    * This header file contains the definition and implementation of the class ListElement
    * ListElement implements a vertex that contains a name, list of adjacent vertices and the size of the lists. 
 */

#ifndef LIST_ELEMENT_H
#define LIST_ELEMENT_H

#include <vector>
#include <iostream>  

using namespace std;

// class that stores individual element and their adjacent vertices
template <typename ElementType> 
class ListElement{

    public:
        // constructors
        ListElement() = default;

        // parameterized constructor that initializes name and listsize
        ListElement(const ElementType &name): elementName_(name), listSize_(0){}

        //Accessor functions

        /*
         * Returns the name of the vertex
         */
        ElementType getElementName(){
            return elementName_; 
        }

        /*
         * Returns the size of the adjacency list
         */
        size_t getListSize(){
            return listSize_;
        }

        /*
         * Displays the name of the vertex and all the nodes that it is connected with
         */
        void displayList(){

            cout << elementName_ << " is connected to: " << endl;
            for(ElementNode node: adjacencyList_){
                cout << "\t" << node.nodeName_ << " with weight " << node.nodeWeight_ << endl;
            }
        }

        /*
         * Returns the distance from the current vertex to the node that is passed as a parameter
         * @param: ElementType nodeName
         * @return: double: distance is found and -1 if not found  
         */
        double getWeight(ElementType nodeName){

            for(ElementNode checkNode: adjacencyList_){
                if(checkNode.nodeName_ == nodeName) return checkNode.nodeWeight_;
            }
            return -1;
        }

        // Mutator functions

        /*
         * Function that sets the name of the vertex and returns true
         * @return: bool
         */
        bool setName(ElementType name){
            elementName_ = name;
            return true;
        }

        /*
         * Function that adds an element to the adjacency vector by calling an internal private method.
         * @param: nodeName (ElementType): Vertex to add, weight(double): distance of the vertex to current vertex
         * @return: bool: true if succesful and false if not
         */
        bool addElement(ElementType nodeName, double weight){

            return addNewElement(nodeName, weight)? true: false;
        }

        /*
         * Function that checks the connection (an edge) between the current vertex and the parameter vertex
         * @param: nodeName (ElementType): vertex to check connection with
         * @return: bool: True if connected and false if not
         */
        bool checkConnection(ElementType nodeName){

            for(ElementNode checkNode: adjacencyList_){
                if(checkNode.nodeName_ == nodeName) return true;
            }

            return false;
        }

    // private data members and functions
    private:

        // ElementNode stores the type of elements stored in the vector "adjacencyList_"
        struct ElementNode{
            ElementType nodeName_;
            double nodeWeight_;
        };

        // private data members
        ElementType elementName_;
        std::vector<ElementNode> adjacencyList_;
        size_t listSize_;                               // stores the size of the adjacency list for elementName_

        // private function

        /*
         * Internal function for "addElement"
         * Takes in an element and its weight and adds it to the adjacency list for current vertex.
         * @param: nodeName, weight
         * @return: bool
         */
        bool addNewElement(ElementType nodeName, double weight){
            ElementNode newNode = {nodeName, weight};
            adjacencyList_.push_back(newNode);
            listSize_++;
            return true;
        }
};

#endif  // LIST_ELEMENT_H