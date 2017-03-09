#include <iostream>

using namespace std;

class Block{

    public:
        string getBlockerUsername(void){
    return blockerUsername;
}
        string getBlockedUsername(void){
    return blockedUsername;
}
        void setBlockerUsername(string blocker){
    blockerUsername = blocker;
}
        void setBlockedUsername(string blocker){
    blockedUsername = blocker;
}
    private:
        string blockerUsername;
        string blockedUsername;

};
