#include <iostream>
#include <string>

#include "SocialNetwork.h"

int main() {
    SocialNetwork snetwork;
    snetwork.addProfile("john", "doe", "john@doe.com");
    snetwork.addPost("Hello world! My name is John Doe.", "john@doe.com");
    snetwork.addProfile("ali", "veysel", "ali@veysel.com");
    snetwork.unlikePost(1, "ali@veysel.com");
    snetwork.print();
    snetwork.getListOfMostRecentPosts("john@doe.com", -10).print();
    /*
    int i, j;
    SocialNetwork snetwork;
    for (i = 1; i <= 11; i++)
    {
        snetwork.addProfile("profil" + std::to_string(i), "soyad" + std::to_string(i), "profil" + std::to_string(i) + "@a.com");
    }
    for (i = 1; i <= 11; i++)
    {
        for (j = 0; j < 4; j++)
        {
            snetwork.addPost("Post number:" + std::to_string(i) + std::to_string(j), "profil" + std::to_string(i) + "@a.com");;
        }
    }
    for (i = 1; i <= 11; i+=3)
    {
        for (j = i; j <= 11; j++)
        {
            if (j != i)
            {
                snetwork.makeFriends("profil" + std::to_string(i) + "@a.com", "profil" + std::to_string(j) + "@a.com");
            }
        }
    }
    for (i = 1; i <= 11; i++)
    {
        for (j = 1; j < 44; j++)
        {
            snetwork.likePost(j, "profil" + std::to_string(i) + "@a.com");
        }
    }
    snetwork.print();
    */
    //snetwork.getMutualFriends("profil7@a.com", "profil4@a.com").print();
    /*
    for (i = 1; i <= 11; i++)
    {
        for (j = 22; j < 44; j++)
        {
            snetwork.unlikePost(j, "profil" + std::to_string(i) + "@a.com");
        }
    }
    */
    //snetwork.deleteProfile("profil11@a.com");
    //snetwork.print();
    
    /*
    SocialNetwork snetwork;
    snetwork.print();
    snetwork.addProfile("john", "doe", "john@doe.com");
    snetwork.addPost("Hello world! My name is John Doe.", "john@doe.com");
    snetwork.addPost("Unutmadınız inş", "john@doe.com");
    snetwork.deleteProfile("john@doe.com");
    snetwork.print();
    */
    /*
    snetwork.print();

    snetwork.print();

    snetwork.addProfile("john", "doe", "john@doe.com");
    snetwork.addProfile("zeynep", "notdoe", "zeynep@notdoe.com");
    snetwork.addProfile("ali", "veysel", "ali@veysel.com");

    snetwork.print();

    snetwork.addPost("Hello world! My name is John Doe.", "john@doe.com");
    snetwork.addPost("Unutmadınız inş", "john@doe.com");
    snetwork.addPost("Unutmadınız inş2", "john@doe.com");
    snetwork.addPost("Hello world! My name is Ali Veysel.", "ali@veysel.com");
    snetwork.addPost("Unutmadınız inş", "ali@veysel.com");
    snetwork.addPost("Unutmadınız inş2", "ali@veysel.com");
    snetwork.addPost("Hello world! My name is Ali Veysel.", "zeynep@notdoe.com");
    snetwork.addPost("Unutmadınız inş", "zeynep@notdoe.com");
    snetwork.addPost("Unutmadınız inş2", "zeynep@notdoe.com");
    snetwork.makeFriends("john@doe.com", "ali@veysel.com");
    snetwork.makeFriends("zeynep@notdoe.com", "ali@veysel.com");
    snetwork.print();
    snetwork.likePost(4, "john@doe.com");
    snetwork.likePost(5, "john@doe.com");
    snetwork.likePost(6, "john@doe.com");
    snetwork.likePost(1, "ali@veysel.com");
    snetwork.likePost(2, "ali@veysel.com");
    snetwork.likePost(3, "ali@veysel.com");
    snetwork.likePost(4, "ali@veysel.com");
    snetwork.likePost(5, "zeynep@notdoe.com");
    snetwork.likePost(1, "zeynep@notdoe.com");
    snetwork.unlikePost(2, "ali@veysel.com");
    snetwork.print();
    */
    //snetwork.deleteProfile("ali@veysel.com");
    //snetwork.deleteProfile("zeynep@notdoe.com");
    //snetwork.print();
    //snetwork.getListOfMostRecentPosts("ali@veysel.com", 3).print();
    //snetwork.getListOfMostRecentPosts("ali@veysel.com", 5).print();
    //snetwork.getListOfMostRecentPosts("ali@veysel.com", 1).print();
    return 0;
}
