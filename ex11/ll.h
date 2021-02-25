#include <iostream>
enum Result {Success, Fail} ;


class NodeList{
    public:
        int data;
        NodeList *next;
    };
class List{
    private:
    
        int logicalLength;
        NodeList *head;
        NodeList *tail;
    public:
        void create();
        void destroy();
        Result prepend(int element);//adds a node to the head
        Result append( int element); //adds a node to the tail
        Result findElementIndex(int data,int& index);
        Result removeElement(int data);
        int size();
};

