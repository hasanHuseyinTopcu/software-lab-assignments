#include <iostream>

using namespace std;

class User{

    public:
        string getUsername(void){
    return username;
}
        string getPersonalComment(void){
    return personalComment;
}
        void setUsername(string name){
    username = name;
}


        void setPersonalComment(string comment){
    personalComment = comment;
}



    private:
        string username;
        string personalComment;

};
