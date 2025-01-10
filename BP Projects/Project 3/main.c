#include "functions.h"

int main(){

    System* TotalSystem = (System*) calloc(1,sizeof(System));

    User* Userdummy = createUser();
    User* current = createUser();
    Userdummy -> next = current;

    Logged_in* currentloggedin = (Logged_in*) calloc(1,sizeof(Logged_in));
    strcpy(currentloggedin->username,"");  // initialize loggedin username with ""

    while (TRUE){

        char com[COM_MAX_LEN];

        printf("Enter Command: ");
        scanf("%s",com);

        if ( !strcmp(com,EXIT) ){   // if input is "exit"
            break;
        }

        else if ( !strcmp(com,LOADUSERS) ){

            loadFromFile(Userdummy,current);
        }

        else if ( !strcmp(com,SIGNUP) ){ // if input is "signup"

            if( signUp(Userdummy,current) ){

                current -> user_chats = (Chats*) calloc(1,sizeof(Chats));  // make chatdummy for each signedup users

                current -> next = createUser();
                current = current -> next;
            }
        }

        else if ( !strcmp(com,LOGIN) ){ // if input is "login"

            login(Userdummy, currentloggedin);
            TotalSystem -> logged_in_user = currentloggedin;
        }

        else if ( !strcmp(com,LOGOUT) ){ // if input is "logout"
            
            logout(currentloggedin);
            TotalSystem -> logged_in_user = NULL;
            TotalSystem -> current_chat = NULL;
        }

        else if ( !strcmp(com,NEWCHAT) ){ // if input is "newChat"

            newChat(Userdummy, currentloggedin);
        }

        else if ( !strcmp(com,SELECTCHAT) ){

            Chats* selectedChat = selectChat(Userdummy, currentloggedin);
            TotalSystem -> current_chat = selectedChat;
        }

        else if ( !strcmp(com,SENDMESSAGE) ){

            sendMessage(Userdummy, TotalSystem->current_chat, currentloggedin);
        }

        else if ( !strcmp(com,SHOWCHAT) ){

            showChat(TotalSystem->current_chat);
        }

        else{
            printf("Error: Unknown command.\n");
        }
    }
    freemessages(Userdummy);
    freechats(Userdummy);
    freeUsers(Userdummy);
    free(currentloggedin);
    free(TotalSystem);
    return 0;
}