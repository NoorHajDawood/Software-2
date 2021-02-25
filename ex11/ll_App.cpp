#include <iostream>
#include "ll.h"

using namespace std;

int main(){
    int data;
    List list;
    int index;
    list.create();

    while(1){
        cout<<"Add node as First: ";
        cin>>data;
        if(cin.eof())   break;
        list.prepend(data);

        cout<<"Add node as last: ";
        cin>>data;
        if(cin.eof())   break;
        list.append(data);       
    }
    cout<<"The size of the list (num of nodes) is: "<<list.size()<<endl;
    if (list.findElementIndex(2,index)==Success){    
        cout<<"The index of element with data 2 is: "<<index<<endl;
        if(list.removeElement(2)==Success){
            cout<<"The size of the list (num of nodes) is: "<<list.size()<<endl;
        }
    }
    list.destroy();

}