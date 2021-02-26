#include "SocialNetwork.h"

#include <iostream>

SocialNetwork::SocialNetwork() {

}

void SocialNetwork::addProfile(const std::string &firstname, const std::string &lastname, const std::string &email) {
    profiles.insertSorted(Profile(firstname, lastname, email));
}

void SocialNetwork::addPost(const std::string &message, const std::string &email) {
    Post postToAdd(message);
    Node<Profile> *profilePtr = profiles.getFirstNode();
    posts.insertAtTheTail(postToAdd);
    while (profilePtr)
    {
        if (((profilePtr->data).getEmail()) == email)
        {
            break;
        }
        profilePtr = profilePtr->next;
    }
    //Assuming that the email is already registered
    //currPtr currently points to the post owner's profile
    ((profilePtr->data).getPosts()).insertAtTheTail(&(posts.getLastNode()->data));
}

void SocialNetwork::deleteProfile(const std::string &email) {
    /* 
    Free from friends' friends list
    Free from others' liked posts
    Free friends
    Free likes
    Free posts
    Free the object itself
    Free the posts from the posts linkedlist of the social network object
     */
    Node<Profile> *nodeToDeletePtr = profiles.getFirstNode(), *iteratedNodeProfilePtr;
    Profile *friendPtr, *profileToDeletePtr;
    Node<Profile *> *ptrOfFriendList;
    Node<Post *> *likedPostNodePtr, *tempPostPtrNodePtr, *postNodePtrOfTheDeletedProfile;
    Node<Post> *iteratedPostsNodePtr, *tempPostNodePtr;
    std::string firstname;
    std::string lastname;
    //Assuming that the email is already registered
    //We don't need to check whether nodeToDeletePtr is null or not.
    while ((nodeToDeletePtr->data).getEmail() != email)
    { //We find the profile to delete
        nodeToDeletePtr = nodeToDeletePtr->next;
    }
    profileToDeletePtr = &(nodeToDeletePtr->data);
    //profilePtr points to the profile to be deleted
    ptrOfFriendList = ((nodeToDeletePtr->data).getFriends()).getFirstNode();
    while (ptrOfFriendList)
    { //We clear all friends from the other side
        friendPtr = (ptrOfFriendList->data);
        friendPtr->dropFriend(profileToDeletePtr);
        ptrOfFriendList = ptrOfFriendList->next;
    }
    //We clear all friends from the profile's side
    ((nodeToDeletePtr->data).getFriends()).removeAllNodes();
    //We clear all likes which belong to the posts of the profile to be deleted 
    iteratedNodeProfilePtr = profiles.getFirstNode();
    
    while (iteratedNodeProfilePtr)
    {
        if (iteratedNodeProfilePtr->data == *profileToDeletePtr)
        {
            iteratedNodeProfilePtr = iteratedNodeProfilePtr->next;
        }
        else
        {
            likedPostNodePtr = ((iteratedNodeProfilePtr->data).getLikes()).getFirstNode();
            while (likedPostNodePtr)
            {
                postNodePtrOfTheDeletedProfile = profileToDeletePtr->getPosts().getFirstNode();
                while (likedPostNodePtr && postNodePtrOfTheDeletedProfile)
                {
                    if (likedPostNodePtr->data == postNodePtrOfTheDeletedProfile->data)
                    {
                        tempPostPtrNodePtr = likedPostNodePtr->next;
                        iteratedNodeProfilePtr->data.getLikes().removeNode(likedPostNodePtr);
                        likedPostNodePtr = tempPostPtrNodePtr;
                        postNodePtrOfTheDeletedProfile = profileToDeletePtr->getPosts().getFirstNode();

                    }
                    else
                    {
                        postNodePtrOfTheDeletedProfile = postNodePtrOfTheDeletedProfile->next;
                    }
                }
                if (likedPostNodePtr)
                {
                    likedPostNodePtr = likedPostNodePtr->next;
                }
            }
            iteratedNodeProfilePtr = iteratedNodeProfilePtr->next;
        }
    }
    iteratedPostsNodePtr = posts.getFirstNode();
    while (iteratedPostsNodePtr)
    {
        postNodePtrOfTheDeletedProfile = profileToDeletePtr->getPosts().getFirstNode();
        while (iteratedPostsNodePtr && postNodePtrOfTheDeletedProfile)
        {
            if (iteratedPostsNodePtr->data.getPostId() == postNodePtrOfTheDeletedProfile->data->getPostId())
            {
                tempPostNodePtr = iteratedPostsNodePtr->next;
                posts.removeNode(iteratedPostsNodePtr);
                iteratedPostsNodePtr = tempPostNodePtr;
                profileToDeletePtr->getPosts().removeNode(postNodePtrOfTheDeletedProfile);
                postNodePtrOfTheDeletedProfile = profileToDeletePtr->getPosts().getFirstNode();
            }
            else
            {
                postNodePtrOfTheDeletedProfile = postNodePtrOfTheDeletedProfile->next;
            }
        }
        if (iteratedPostsNodePtr)
        {
            iteratedPostsNodePtr = iteratedPostsNodePtr->next;
        }
    }
    profileToDeletePtr->getFriends().removeAllNodes();
    profileToDeletePtr->getLikes().removeAllNodes();
    profileToDeletePtr->getPosts().removeAllNodes();
    profiles.removeNode(nodeToDeletePtr);
}

void SocialNetwork::makeFriends(const std::string &email1, const std::string &email2) {
    //Assuming that email1 and email2 are registered and are not friends
    Node<Profile> *profile1Ptr = nullptr, *profile2Ptr = nullptr, *currProfilePtr = profiles.getFirstNode();
    while (currProfilePtr)
    {
        if (currProfilePtr->data.getEmail() == email1)
        {
            profile1Ptr = currProfilePtr;
            if (profile2Ptr)
            {
                break;
            }
        }
        else if (currProfilePtr->data.getEmail() == email2)
        {
            profile2Ptr = currProfilePtr;
            if (profile1Ptr)
            {
                break;
            }
        }
        currProfilePtr = currProfilePtr->next;
    }
    profile1Ptr->data.getFriends().insertAtTheTail(&(profile2Ptr->data));
    profile2Ptr->data.getFriends().insertAtTheTail(&(profile1Ptr->data));
}

void SocialNetwork::likePost(int postId, const std::string &email) {
    Node<Profile> *currProfilePtr = profiles.getFirstNode(), *profileLikedNodePtr;
    Node<Post> *currPostPtr = posts.getFirstNode(), *likedPostNodePtr;
    while (currProfilePtr->data.getEmail() != email)
    {
        currProfilePtr = currProfilePtr->next;
    }
    profileLikedNodePtr = currProfilePtr;
    while (currPostPtr->data.getPostId() != postId)
    {
        currPostPtr = currPostPtr->next;
    }
    likedPostNodePtr = currPostPtr;
    (profileLikedNodePtr->data.getLikes()).insertAtTheTail(&(likedPostNodePtr->data));
}

void SocialNetwork::unlikePost(int postId, const std::string &email) {
    Node<Profile> *currProfilePtr = profiles.getFirstNode(), *profileLikedNodePtr;
    Node<Post *> *currPostNodePtr, *likedPostNodePtr = nullptr;
    while (currProfilePtr)
    {
        if (currProfilePtr->data.getEmail() == email)
        {
            profileLikedNodePtr = currProfilePtr;
            break;
        }
        else
        {
            currProfilePtr = currProfilePtr->next;
        }   
    }
    currPostNodePtr = currProfilePtr->data.getLikes().getFirstNode();
    while (currPostNodePtr)
    {
        if (currPostNodePtr->data->getPostId() == postId)
        {
            likedPostNodePtr = currPostNodePtr;
            break;
        }
        else
        {
            currPostNodePtr = currPostNodePtr->next;
        }
    }
    if (likedPostNodePtr)
    {
        profileLikedNodePtr->data.getLikes().removeNode(likedPostNodePtr);
    }
}

LinkedList<Profile *> SocialNetwork::getMutualFriends(const std::string &email1, const std::string &email2) {
    Node<Profile *> *iteratedFriendNodePtr1, *iteratedFriendNodePtr2;
    Node<Profile> *currProfilePtr = profiles.getFirstNode(), *NodeProfilePtr1 = nullptr, *NodeProfilePtr2 = nullptr;
    LinkedList<Profile *> listOfMutualFriends;
    while (currProfilePtr)
    {
        if (currProfilePtr->data.getEmail() == email1)
        {
            NodeProfilePtr1 = currProfilePtr;
            if (NodeProfilePtr2)
            {
                break;
            }
        }
        else if (currProfilePtr->data.getEmail() == email2)
        {
            NodeProfilePtr2 = currProfilePtr;
            if (NodeProfilePtr1)
            {
                break;
            }
        }
        currProfilePtr = currProfilePtr->next;
    }
    iteratedFriendNodePtr1 = NodeProfilePtr1->data.getFriends().getFirstNode();
    while (iteratedFriendNodePtr1)
    {
        iteratedFriendNodePtr2 = NodeProfilePtr2->data.getFriends().getFirstNode();
        while (iteratedFriendNodePtr2)
        {
            if (iteratedFriendNodePtr1->data == iteratedFriendNodePtr2->data)
            {
                listOfMutualFriends.insertAtTheTail((iteratedFriendNodePtr2->data));
            }
            iteratedFriendNodePtr2 = iteratedFriendNodePtr2->next;
        }
        iteratedFriendNodePtr1 = iteratedFriendNodePtr1->next;
    }
    return listOfMutualFriends;
}

LinkedList<Post *> SocialNetwork::getListOfMostRecentPosts(const std::string &email, int k) {
    Node<Profile> *currProfilePtr = profiles.getFirstNode(), *userNodeProfilePtr;
    Node<Post *> *currPostNodePtr;
    LinkedList<Post *> recentPosts;
    int i = 0;
    while (currProfilePtr)
    {
        if (currProfilePtr->data.getEmail() == email)
        {
            userNodeProfilePtr = currProfilePtr;
            break;
        }
        else
        {
            currProfilePtr = currProfilePtr->next;
        }
    }
    userNodeProfilePtr = currProfilePtr;
    currPostNodePtr = userNodeProfilePtr->data.getPosts().getLastNode();
    while (currPostNodePtr && i < k)
    {
        recentPosts.insertAtTheTail(currPostNodePtr->data);
        currPostNodePtr = currPostNodePtr->prev;
        i++;
    }
    return recentPosts;
}

void SocialNetwork::print() const {
    std::cout << "# Printing the social network ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getNumberOfNodes() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of posts is " << posts.getNumberOfNodes() << ":" << std::endl;
    posts.print();

    std::cout << "# Printing is done." << std::endl;
}
