
#include "ll.h"


void List::create(){
   
    head=tail=NULL;
    logicalLength=0;
}

void List::destroy(){
    NodeList *curr;

    while(head!=NULL){
        curr=head;
        head=curr->next;
        delete curr;
    }
}

//adds a node to the head
Result List::prepend( int element){
    NodeList *newNode=new NodeList;
    if(newNode==NULL)   return Fail;

    newNode->data=element;
    newNode->next=head;

    head=newNode;
    
    if(!tail){
        tail=head;
    }

    logicalLength++;
    return Success;
}

//adds a node to the tail
Result List::append(int element){
    NodeList *newNode=new NodeList;
    if(newNode==NULL)   return Fail;

    newNode->data=element;
    newNode->next=NULL;

    if(logicalLength==0){
        head=tail =newNode;
    }
    else{
        tail->next=newNode;
        tail=newNode;
    }

    logicalLength++;
    return Success;
}

int List::size(){
    return logicalLength;
}

Result List::findElementIndex(int data,int& index){
    NodeList *curr=head;
    int cnt=1;

    while(curr!=NULL && curr->data!=data){
        curr=curr->next;
        cnt++;
    }
    if(curr==NULL){
        index=-1;
        return Fail;
    }
    index=cnt;
    return Success;
}
Result List::removeElement(int data){
    NodeList *curr,*prev;
    curr=prev=head;
    if(head!=NULL &&curr->data==data){
        head=curr->next;
        delete curr;
        logicalLength--;
        return Success;
    }
    while(curr!=NULL && curr->data!=data){
        prev=curr;
        curr=curr->next;
    }
    if(curr==NULL)  return Fail;
    
    prev->next=curr->next;
    delete curr;
    logicalLength--;
    return Success;
}

