#include <iostream>
#include <string>
#include "Post.cpp"
#include "Follow.cpp"
#include "Like.cpp"
#include "Block.cpp"
#include "User.cpp"

using namespace std;

template<class T> class Node{       /* template Node Class to hide all class type */

    T data;                         /* T may User or Post or Block or Like or Follow   */
    Node<T> *next;

    public:
        void setData(T newData){        /* get set functions */
            data = newData;
        };
        void setNext(Node *nextNode){
            next = nextNode;
        };
        T getData(){
            return data;
        };
        Node* nextNode(){
            return next;
        };

};

template<class T> class LinkedList{

    Node<T> *head;

    public:
        LinkedList(){head = NULL;}; /* constructor function */
        void addNode(T data);                       /* functions' prototypes */
        bool checkUsername(string);
        bool checkAlreadyFollow(string , string);
        bool checkUserPost(string , string);
        bool checkAlreadyLike(string , string , string);
        Post getPostByIdAndUsername(string , string , string);
        bool checkBlock(string , string);
        string getPersonelComment(string);
        int getNumberOfFollowing(string);
        int getNumberOfBlock(string);
        int getNumberOfPost(string);
        void printPostWithLikes(string , LinkedList<Like>, ofstream&);
        int getNumberOfLike(string, string);
        Follow RemoveFollowing(string , string);
};

