#include "main.h"


template<class T>
void LinkedList<T>::addNode(T data){        /* add any object in any list */

    if(head == NULL){

        head = new Node<T>;
        head->setData(data);
        head->setNext(NULL);

    }
    else{

        Node<T>* temp = new Node<T>;
        temp = head;

        Node<T> *newNode = new Node<T>;
        newNode->setData(data);
        newNode->setNext(NULL);

        while(temp->nextNode() != NULL){
            temp = temp->nextNode();
        }

        temp->setNext(newNode);

    }

}

template<class T>
bool LinkedList<T>::checkUsername(string username){     /* check username for every class that have getUsername() function */

    Node<T>* temp = new Node<T>;
    temp = head;

    while(temp != NULL){

        if(temp->getData().getUsername().compare(username) == 0)
            return true;
        temp = temp->nextNode();

    }

    return false;
}

template<>          /* use template because syntax */
bool LinkedList<Follow>::checkAlreadyFollow(string followerUsername, string followedUsername){

    Node<Follow>* temp = new Node<Follow>;
    temp = head;

    while(temp != NULL){

        if( ( temp->getData().getFollowerUsername().compare(followerUsername) == 0 ) && ( temp->getData().getFollowedUsername().compare(followedUsername) == 0 ) ){
            return true;
        }
        temp = temp->nextNode();

    }

    return false;
}

template<>          /* use template because syntax */
bool LinkedList<Post>::checkUserPost(string likedUsername, string postId){

    Node<Post>* temp = new Node<Post>;
    temp = head;

    while(temp != NULL){

        if( ( temp->getData().getUsername().compare(likedUsername) == 0 ) && ( temp->getData().getPostId().compare(postId) == 0 ) ){
            return true;
        }
        temp = temp->nextNode();
    }

    return false;
}

template<>          /* use template because syntax */
bool LinkedList<Like>::checkAlreadyLike(string likerUsername, string likedUsername, string postId){

    Node<Like>* temp = new Node<Like>;
    temp = head;

    while(temp != NULL){

        if( ( temp->getData().getLikerUsername().compare(likerUsername) == 0 ) && ( temp->getData().getLikedUsername().compare(likedUsername) == 0 ) && ( temp->getData().getPostId().compare(postId) == 0 ) ){
            return true;
        }
        temp = temp->nextNode();
    }

    return false;
}

template<>          /* use template because syntax */
Post LinkedList<Post>::getPostByIdAndUsername(string reposterUsername, string repostedUsername, string postId){

    Node<Post>* temp = new Node<Post>;
    temp = head;
    Post newPost;

    while(temp != NULL){

        if( (temp->getData().getUsername().compare(repostedUsername) == 0) && (temp->getData().getPostId().compare(postId) == 0) ){
            newPost = temp->getData();
            newPost.setUsername(reposterUsername);
        }

        temp = temp->nextNode();
    }
	return newPost;
}

template<>          /* use template because syntax */
bool LinkedList<Block>::checkBlock(string blockerUsername, string blockedUsername){

    Node<Block>* temp = new Node<Block>;
    temp = head;

    while(temp != NULL){

        if( (temp->getData().getBlockerUsername().compare(blockerUsername) == 0 ) && ( temp->getData().getBlockedUsername().compare(blockedUsername) == 0 ) ){
            return true;
        }
        temp = temp->nextNode();
    }

    return false;
}

template<>          /* use template because syntax */
string LinkedList<User>::getPersonelComment(string username){

    Node<User>* temp = new Node<User>;
    temp = head;
	string comment;

    while(temp != NULL){

        if(temp->getData().getUsername().compare(username) == 0){
            comment = temp->getData().getPersonalComment();
        }

        temp = temp->nextNode();
    }
	return comment;
}

template<>          /* use template because syntax */
int LinkedList<Follow>::getNumberOfFollowing(string username){

    int counter = 0;

    Node<Follow>* temp = new Node<Follow>;
    temp = head;

    while(temp != NULL){

        if(temp->getData().getFollowerUsername().compare(username) == 0){
            counter++;
        }
        temp = temp->nextNode();
    }

    return counter;
}

template<>          /* use template because syntax */
int LinkedList<Block>::getNumberOfBlock(string username){

    int counter = 0;

    Node<Block>* temp = new Node<Block>;
    temp = head;

    while(temp != NULL){

        if(temp->getData().getBlockerUsername().compare(username) == 0){
            counter++;
        }
        temp = temp->nextNode();
    }

    return counter;
}

template<>          /* use template because syntax */
int LinkedList<Post>::getNumberOfPost(string username){

    int counter = 0;

    Node<Post>* temp = new Node<Post>;
    temp = head;

    while(temp != NULL){

        if(temp->getData().getUsername().compare(username) == 0){
            counter++;
        }
        temp = temp->nextNode();
    }

    return counter;
}

template<>          /* use template because syntax */
int LinkedList<Like>::getNumberOfLike(string username, string postId){

    int counter = 0;

    Node<Like>* temp = new Node<Like>;
    temp = head;

    while(temp != NULL){

        if( (temp->getData().getLikedUsername().compare(username) == 0) && (temp->getData().getPostId().compare(postId) == 0) ){

            counter++;
        }
        temp = temp->nextNode();
    }

    return counter;
}

template<>          /* use template because syntax */
void LinkedList<Post>::printPostWithLikes(string username, LinkedList<Like> likeList, ofstream& outputFile){

    Node<Post>* temp = new Node<Post>;
    temp = head;

    while(temp != NULL){

        if(temp->getData().getUsername().compare(username) == 0){
            outputFile << temp->getData().getPostText()+" - ";
            cout << temp->getData().getPostText()+" - ";
            if(temp->getData().getWidth() != 0){
                outputFile << "TotalSize: ["<< (temp->getData().getWidth())*(temp->getData().getHeight()) <<" pixels] - ";
                cout << "TotalSize: ["<< (temp->getData().getWidth())*(temp->getData().getHeight()) <<" pixels] - ";
            }
            outputFile << "Likes: " << likeList.getNumberOfLike(username, temp->getData().getPostId()) << "\n";
            cout << "Likes: " << likeList.getNumberOfLike(username, temp->getData().getPostId()) << "\n";
        }
        temp = temp->nextNode();
    }

}

template<>          /* use template because syntax */
Follow LinkedList<Follow>::RemoveFollowing(string followerUsername, string followedUsername){

    Node<Follow>* temp = new Node<Follow>;
    temp = head;
    Follow newFollow;

    while(temp != NULL){

        if( ( temp->getData().getFollowerUsername().compare(followerUsername) == 0 ) && ( temp->getData().getFollowedUsername().compare(followedUsername) == 0 ) ){
            newFollow.setFollowerUsername(followerUsername+"silindi");
            newFollow.setFollowedUsername(followedUsername+"silindi");
            
        }
        temp = temp->nextNode();

    }
	return newFollow;	
}

int main(){

    string line;                        /* definitions */
    vector<string> lineArray;
    ifstream inputFile("input.txt");
    ofstream outputFile("out.txt");
    LinkedList<User> userList;
    LinkedList<Post> postList;
    LinkedList<Follow> followList;
    LinkedList<Like> likesList;
    LinkedList<Block> blockList;

    if (inputFile.is_open() && outputFile.is_open()){

        while(getline(inputFile, line)){

            lineArray = splitLine(line, ' ');   /* parse line by space character for each line */

            if(lineArray[0].compare("AddUser") == 0){   /* addUser command */
                addUserCommand(&userList, lineArray[1], lineArray[2], outputFile);
            }

            else if(lineArray[0].compare("FollowUser") == 0){   /* followUser command */
                followCommand(userList, blockList, &followList, lineArray[1], lineArray[2], outputFile);
            }

            else if(lineArray[0].compare("AddPost") == 0){  /* addPost command */

                if(lineArray.size() == 4){ /* Text Post */
                    addTextPostCommand(userList, &postList, lineArray[1], lineArray[2], lineArray[3], outputFile);
                }
                else if(lineArray.size() == 5){ /* Image Post */
                    addImagePostCommand(userList, &postList, lineArray[1], lineArray[2], lineArray[3], lineArray[4], outputFile);
                }

            }

            else if(lineArray[0].compare("LikePost") == 0){     /* likePost Command */
                likePostCommand(userList, blockList, postList, &likesList, lineArray[1], lineArray[2], lineArray[3], outputFile);
            }

            else if(lineArray[0].compare("ViewUser") == 0){     /* viewUser command */
                viewUserCommand(userList, postList, followList, likesList, blockList, lineArray[1], outputFile);
            }

            else if(lineArray[0].compare("Repost") == 0){       /* repost command */
                repostCommand(userList, blockList, &postList, lineArray[1], lineArray[2], lineArray[3], outputFile);
            }

            else if(lineArray[0].compare("BlockUser") == 0){    /* blockUser command */
                blockUserCommand(userList, &likesList, &blockList, lineArray[1], lineArray[2], outputFile);
            }

            else if(lineArray[0].compare("UnfollowUser") == 0){ /* unfollowUser command */
                unfollowUserCommand(userList, &followList, lineArray[1], lineArray[2], outputFile);
            }

        }/* end while */

    }/* end if */

    inputFile.close();      /* close input and output files */
    outputFile.close();

    cin.get();      /*  to don't close screen */

    return 0;
}/* end main */

vector<string> splitLine(string line, char delimiter){

    vector<string> temp;            /* split line by delimiter */
    stringstream ss(line);          /* use line and image post's width and height */
    string token;

    while(getline(ss, token, delimiter)) {
        temp.push_back(token);
    }

    return temp;
}/* end splitLine function */

void addUserCommand(LinkedList<User>* userList, string username, string personalComment, ofstream &outputFile){

    if(userList->checkUsername(username) == true){      /* if username has already been created, print error message */
        outputFile << "Err: The user username has already been created.\n";
        cout << "Err: The user username has already been created.\n";
    }
    else{
        User newUser;                                   /* create User object and set username, personal comment */
        newUser.setUsername(username);
        newUser.setPersonalComment(personalComment);
        userList->addNode(newUser);                     /* add newUser object in userList */
        outputFile << "User '"+username+"' has been created\n";
        cout << "User '"+username+"' has been created\n";
    }
}/* end addUserCommand function */

void addTextPostCommand(LinkedList<User> userList, LinkedList<Post>* postList, string username, string postId, string postText, ofstream &outputFile){

    if(userList.checkUsername(username) == false){      /* if username does not exist, print error message */
        outputFile << "Err: the user '" + username + "' could not be found!\n";
        cout << "Err: the user '" + username + "' could not be found!\n";
    }
    else{
        Post newTextPost;                       /* create Post object and set post's variables */
        newTextPost.setUsername(username);
        newTextPost.setPostId(postId);
        newTextPost.setPostText(postText);
        newTextPost.setWidth(0);                /* define zero image post's variables */
        newTextPost.setHeight(0);

        postList->addNode(newTextPost);         /* add newTextPost object in postList */
    }

}/* end addTextPostCommand function */

void addImagePostCommand(LinkedList<User> userList, LinkedList<Post>* postList, string username, string postId, string postText, string ImageWidthAndHeight, ofstream &outputFile){

    if(userList.checkUsername(username) == false){      /* if username does not exist, print error message */
        outputFile << "Err: the user '" + username + "' could not be found!\n";
        cout << "Err: the user '" + username + "' could not be found!\n";
    }
    else{
        Post newImagePost;                      /* create Post object and set post's variables */
        newImagePost.setUsername(username);
        newImagePost.setPostId(postId);
        newImagePost.setPostText(postText);

        vector<string> widthAndHeight = splitLine(ImageWidthAndHeight,'x');        /* split widthxheigth by 'x' */

        newImagePost.setWidth(atoi(widthAndHeight[0].c_str()));         /* set width and height variables */
        newImagePost.setHeight(atoi(widthAndHeight[1].c_str()));

        postList->addNode(newImagePost);        /* add newImagePost object in postList */
    }
}/* end addImagePostCommand function */

int followCommand(LinkedList<User> userList, LinkedList<Block> blockList, LinkedList<Follow>* followList, string followerUsername, string followedUsername, ofstream &outputFile){

    /* return type is int because if input provide any if blocks conditions( error blocks ) then print error message and return 1 ( so end method ) */

    if( userList.checkUsername(followerUsername) == false ){        /* if followerUsername does not exist, print error message */
        outputFile << "Err: the user '"+followerUsername+"' could not be found!\n";
        cout << "Err: the user '"+followerUsername+"' could not be found!\n";
        return 1;
    }
    if( userList.checkUsername(followedUsername) == false ){        /* if followedUsername does not exist, print error message */
        outputFile << "Err: the user '"+followedUsername+"' could not be found!\n";
        cout << "Err: the user '"+followedUsername+"' could not be found!\n";
        return 1;
    }
    if(followerUsername.compare(followedUsername) == 0){            /* if followerUsername is equal followerUsername , print error message */
        outputFile << "Err: "+followerUsername+" cannot follow itself\n";
        cout << "Err: "+followerUsername+" cannot follow itself\n";
        return 1;
    }
    if( followList->checkAlreadyFollow(followerUsername, followedUsername) == true ){   /* if follower has already block followed , print error message */
        outputFile << "Err: "+followerUsername+" has already followed "+followedUsername+"\n";
        cout << "Err: "+followerUsername+" has already followed "+followedUsername+"\n";
        return 1;
    }
    if( blockList.checkBlock(followedUsername, followerUsername) == true ){         /* if followed block follower , print error message */
        outputFile << "Err: the user '"+followedUsername+"' had blocked '"+followerUsername+"'.\n";
        cout << "Err: the user '"+followedUsername+"' had blocked '"+followerUsername+"'.\n";
        return 1;
    }

    Follow newFollow;                    /* create Follow object and set newFollow's variables */
    newFollow.setFollowerUsername(followerUsername);
    newFollow.setFollowedUsername(followedUsername);

    followList->addNode(newFollow);      /* add newFollow object in followList */

    outputFile << followerUsername+" followed "+followedUsername+"\n";
    cout << followerUsername+" followed "+followedUsername+"\n";

    return 1;
}/* end followCommand function */

int likePostCommand(LinkedList<User> userList , LinkedList<Block> blockList, LinkedList<Post> postList, LinkedList<Like>* likesList, string likerUsername, string likedUsername, string postId, ofstream& outputFile){

    /* return type is int because if input provide any if blocks conditions( error blocks ) then print error message and return 1 ( so end method ) */

    if( userList.checkUsername(likerUsername) == false ){               /* if likerUsername does not exist, print error message */
        outputFile << "Err: the user '"+likerUsername+"' could not be found!\n";
        cout << "Err: the user '"+likerUsername+"' could not be found!\n";
        return 1;
    }
    if( userList.checkUsername(likedUsername) == false ){               /* if likedUsername does not exist, print error message */
        outputFile << "Err: the user '"+likedUsername+"' could not be found!\n";
        cout << "Err: the user '"+likedUsername+"' could not be found!\n";
        return 1;
    }
    if( postList.checkUserPost(likedUsername, postId) == false ){       /* if liked's post does not exist */
        outputFile << "Err: "+likedUsername+"'s post could not be found!\n";
        cout << "Err: "+likedUsername+"'s post could not be found!\n";
        return 1;
    }
    if( blockList.checkBlock(likedUsername, likerUsername) == true ){   /* if liked block liker */
        outputFile << "Err: the user '"+likedUsername+"' had blocked '"+likerUsername+"'. You cannot like a post of '"+likedUsername+"'!\n";
        cout << "Err: the user '"+likedUsername+"' had blocked '"+likerUsername+"'. You cannot like a post of '"+likedUsername+"'!\n";
        return 1;
    }
    if(likesList->checkAlreadyLike(likerUsername, likedUsername, postId) == true ){     /* if liker has already been liked  */
        outputFile << "Err: "+likedUsername+"'s post had already been liked!\n";
        cout << "Err: "+likedUsername+"'s post had already been liked!\n";
        return 1;
    }

    Like newLike;                       /* create Like object and set newLike's variables */
    newLike.setLikerUsername(likerUsername);
    newLike.setLikedUsername(likedUsername);
    newLike.setPostId(postId);

    likesList->addNode(newLike);        /* add newLike object in likeList */

    outputFile << likerUsername+" has liked "+likedUsername+"'s post\n";
    cout << likerUsername+" has liked "+likedUsername+"'s post\n";

    return 1;
}/* end likePostCommand function */

int repostCommand(LinkedList<User> userList, LinkedList<Block> blockList, LinkedList<Post>* postList, string reposterUsername, string repostedUsername, string postIdRepostedItem, ofstream& outputFile){

    /* return type is int because if input provide any if blocks conditions( error blocks ) then print error message and return 1 ( so end method ) */

    if( userList.checkUsername(reposterUsername) == false ){                        /* if reposterUsername does not exist, print error message */
        outputFile << "Err: the user '"+reposterUsername+"' could not be found!\n";
        cout << "Err: the user '"+reposterUsername+"' could not be found!\n";
        return 1;
    }
    if( userList.checkUsername(repostedUsername) == false ){                        /* if repostedUsername does not exist, print error message */
        outputFile << "Err: the user '"+repostedUsername+"' could not be found!\n";
        cout << "Err: the user '"+repostedUsername+"' could not be found!\n";
        return 1;
    }
    if(postList->checkUserPost(repostedUsername, postIdRepostedItem) == false){     /* if reposted's post does not exist , print error message */
        outputFile << "Err: "+repostedUsername+"'s post could not be found!\n";
        cout << "Err: "+repostedUsername+"'s post could not be found!\n";
        return 1;
    }
    if(postList->checkUserPost(reposterUsername, postIdRepostedItem) == true){      /* if the post has already been reposted , print error message */
        outputFile << "Err: this post had already been reposted by "+reposterUsername+"!\n";
        cout << "Err: this post had already been reposted by "+reposterUsername+"!\n";
        return 1;
    }
    if( blockList.checkBlock(repostedUsername, reposterUsername) == true ){         /* if reposted block reposter , print error message */
        outputFile << "Err: the user '"+repostedUsername+"' had blocked '"+reposterUsername+"'. You cannot repost a post of '"+repostedUsername+"'!\n";
        cout << "Err: the user '"+repostedUsername+"' had blocked '"+reposterUsername+"'. You cannot repost a post of '"+repostedUsername+"'!\n";
        return 1;
    }

    /* get post object and add post object in postList */
    postList->addNode(postList->getPostByIdAndUsername(reposterUsername, repostedUsername, postIdRepostedItem));

    outputFile << reposterUsername+" has reposted "+repostedUsername+"'s post\n";
    cout << reposterUsername+" has reposted "+repostedUsername+"'s post\n";

    return 1;
}/* end repostCommand function */

int blockUserCommand(LinkedList<User> userList, LinkedList<Like>* likeList, LinkedList<Block>* blockList, string blockerUsername , string blockedUsername , ofstream& outputFile){

    /* return type is int because if input provide any if blocks conditions( error blocks ) then print error message and return 1 ( so end method ) */

    if( userList.checkUsername(blockerUsername) == false ){                     /* if blockerUsername does not exist, print error message */
        outputFile << "Err: the user '"+blockerUsername+"' could not be found!\n";
        cout << "Err: the user '"+blockerUsername+"' could not be found!\n";
        return 1;
    }
    if( userList.checkUsername(blockedUsername) == false ){                     /* if blockedUsername does not exist, print error message */
        outputFile << "Err: the user '"+blockedUsername+"' could not be found!\n";
        cout << "Err: the user '"+blockedUsername+"' could not be found!\n";
        return 1;
    }
    if(blockList->checkBlock(blockerUsername,blockedUsername) == true){         /* if blocker has already been block blocked , print error message */
        outputFile << "Err: "+blockerUsername+" has already blocked "+blockedUsername+"!\n";
        cout << "Err: "+blockerUsername+" has already blocked "+blockedUsername+"!\n";
        return 1;
    }

    Block newBlock;                                 /* create block object and set newBlock's variables */
    newBlock.setBlockerUsername(blockerUsername);
    newBlock.setBlockedUsername(blockedUsername);
    blockList->addNode(newBlock);                   /* add newBlock object in blockList */

    outputFile << blockerUsername+" has blocked "+blockedUsername+"\n";
    cout << blockerUsername+" has blocked "+blockedUsername+"\n";

    return 1;
}/* end blockUserCommand function */

void viewUserCommand(LinkedList<User> userList, LinkedList<Post> postList, LinkedList<Follow> followList, LinkedList<Like> likeList, LinkedList<Block> blockList, string username, ofstream& outputFile){

    if( userList.checkUsername(username) == false ){                     /* if username does not exist, print error message */
        outputFile << "Err: the user '"+username+"' could not be found!\n";
        cout << "Err: the user '"+username+"' could not be found!\n";
    }
    else{
        outputFile << "------------------------------------------------\n";         /* print number of followings, blocks, posts */
        cout << "------------------------------------------------\n";
        outputFile << username+" following [" << followList.getNumberOfFollowing(username) << "] - blocked [" << blockList.getNumberOfBlock(username) << "] users - [" << postList.getNumberOfPost(username) << "] posts.\n";
        cout << username+" following [" << followList.getNumberOfFollowing(username) << "] - blocked [" << blockList.getNumberOfBlock(username) << "] users - [" << postList.getNumberOfPost(username) << "] posts.\n";
        outputFile << userList.getPersonelComment(username)+"\n";
        cout << userList.getPersonelComment(username)+"\n";
        outputFile << "---------------------Tweets---------------------\n";
        cout << "---------------------Tweets---------------------\n";
        postList.printPostWithLikes(username, likeList, outputFile);
        outputFile << "------------------------------------------------\n";
        cout << "------------------------------------------------\n";
    }

}/* end viewUserCommand function */

int unfollowUserCommand(LinkedList<User> userList, LinkedList<Follow>* followList, string unfollowerUsername, string unfollowedUsername, ofstream& outputFile){

    if( userList.checkUsername(unfollowerUsername) == false ){                     /* if unfollowerUsername does not exist, print error message */
        outputFile << "Err: the user '"+unfollowerUsername+"' could not be found!\n";
        cout << "Err: the user '"+unfollowerUsername+"' could not be found!\n";
        return 1;
    }
    if( userList.checkUsername(unfollowedUsername) == false ){                     /* if unfollowedUsername does not exist, print error message */
        outputFile << "Err: the user '"+unfollowedUsername+"' could not be found!\n";
        cout << "Err: the user '"+unfollowedUsername+"' could not be found!\n";
        return 1;
    }
    if( followList->checkAlreadyFollow(unfollowerUsername+"silindi", unfollowedUsername+"silindi") == true ){           /* if unfollower has already been unfollow by you , print error message */
        outputFile << "Err: "+unfollowedUsername+" has already been unfollowed by you! You cannot unfollow again.\n";
        cout << "Err: "+unfollowedUsername+" has already been unfollowed by you! You cannot unfollow again.\n";
        return 1;
    }

    followList->addNode(followList->RemoveFollowing(unfollowerUsername, unfollowedUsername));  /* add follow object in followList */
    outputFile << unfollowedUsername+" has been unfollowed by "+unfollowerUsername+"\n";
    cout << unfollowedUsername+" has been unfollowed by "+unfollowerUsername+"\n";

    return 1;
}/* end unfollowUserCommand function */
