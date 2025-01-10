typedef struct messages
{
    char text[TEXT_LEN];
    char author[MAX_LEN];
    struct messages* next;

}Messages;

typedef struct chats
{
    char name[MAX_LEN];
    char author[MAX_LEN];
    char reciever[MAX_LEN];
    Messages* messages_list;
    struct chats* next;

}Chats;

typedef struct user
{
    char username[MAX_LEN];
    char password[MAX_LEN];
    Chats* user_chats;
    struct user* next;
    
}User;

typedef struct logged_in
{
    char username[MAX_LEN];

}Logged_in;


typedef struct system
{

    User* users_list;
    Logged_in* logged_in_user;
    Chats* current_chat;

}System;

