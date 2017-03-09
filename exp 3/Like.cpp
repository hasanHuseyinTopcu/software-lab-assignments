#include <iostream>

using namespace std;

class Like{

    public:
        string getLikerUsername(void){
    return likerUsername;
}
        string getLikedUsername(void){
    return likedUsername;
}
        string getPostId(void){
    return postId;
}

        void setLikerUsername(string liker){
    likerUsername = liker;
}
        void setLikedUsername(string liker){
    likedUsername = liker;
}
        void setPostId(string liker){
    postId = liker;
}

    private:
        string likerUsername;
        string likedUsername;
        string postId;
};
