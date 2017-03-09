#include <iostream>

using namespace std;

class Follow{

    public:
        string getFollowerUsername(void){
    return followerUsername;
}
        string getFollowedUsername(void){
    return followedUsername;
}
        void setFollowerUsername(string username1){
    followerUsername = username1;
}
        void setFollowedUsername(string username2){
    followedUsername = username2;
}

    private:
        string followerUsername;
        string followedUsername;

};
