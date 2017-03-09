#include <iostream>

using namespace std;

class Post{

    public:
        string getUsername(void){
    return username;
}
        string getPostId(void){
    return postId;
}
        string getPostText(void){
    return postText;
}
        int getWidth(void){
    return width;
}
        int getHeight(void){
    return height;
}
        void setUsername(string name){
    username = name;
}
        void setPostId(string name){
    postId = name;
}
        void setPostText(string name){
    postText = name;
}
        void setWidth(int name){
    width = name;
}
        void setHeight(int name){
    height = name;
}

    private:
        string username;
        string postId;
        string postText;
        int width;
        int height;
};
