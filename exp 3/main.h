#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "LinkedList.cpp"
#include <stdlib.h>

using namespace std;

vector<string> splitLine(string , char );           /* function's prototypes */
void addUserCommand(LinkedList<User>* , string , string , ofstream&);
void addTextPostCommand(LinkedList<User> , LinkedList<Post>* , string , string , string , ofstream&);
void addImagePostCommand(LinkedList<User> , LinkedList<Post>* , string , string , string , string , ofstream&);
int followCommand(LinkedList<User> , LinkedList<Block> , LinkedList<Follow>* , string , string , ofstream&);
int likePostCommand(LinkedList<User> , LinkedList<Block> , LinkedList<Post> , LinkedList<Like>* , string , string , string , ofstream&);
int repostCommand(LinkedList<User> , LinkedList<Block> , LinkedList<Post>* , string , string , string , ofstream&);
int blockUserCommand(LinkedList<User> , LinkedList<Like>* , LinkedList<Block>* , string , string , ofstream&);
void viewUserCommand(LinkedList<User> , LinkedList<Post> , LinkedList<Follow> , LinkedList<Like> , LinkedList<Block> , string , ofstream&);
int unfollowUserCommand(LinkedList<User> , LinkedList<Follow>* , string , string , ofstream&);
