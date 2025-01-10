#include "headers.h"
#include "structs.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// List of prototypes : 

User* createUser(void);

void addUserInf(User* current, char username[MAX_LEN], char password[MAX_LEN]);

User* alreadyexist(User* Userdummy, char username[MAX_LEN]);

int repeatedChatName(User* Userdummy, char chat_name[MAX_LEN], char author[MAX_LEN], char reciever[MAX_LEN]);

Chats* createChat(char chat_name[MAX_LEN], char author[MAX_LEN], char reciever[MAX_LEN]);

Chats* findChat(User* Userdummy, Logged_in* currentloggedin, char chat_name[MAX_LEN]);

Messages* createMessage(Logged_in* currentloggedin, char text[TEXT_LEN]);

void freeUsers(User* Userdummy);

void freechats(User* Userdummy);

void freemessages(User* Userdummy);

int loadFromFile(User* Userdummy, User* current);

int signUp(User* Userdummy, User* current);

int login(User* Userdummy, Logged_in* currentloggedin);

int logout(Logged_in* currentloggedin);

int newChat(User* Userdummy, Logged_in* currentloggedin);

Chats* selectChat(User* Userdummy, Logged_in* currentloggedin);

int sendMessage(User* Userdummy, Chats* currentchat, Logged_in* currentloggedin);

int showChat(Chats* currentchat);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


User* createUser(void){
    
    User* newnode = (User*) malloc(sizeof(User));
    newnode -> next = NULL;
    return newnode;
}


void addUserInf(User* current, char username[MAX_LEN] , char password[MAX_LEN]){

    strcpy(current -> username, username);
    strcpy(current -> password, password);
}

User* alreadyexist(User* Userdummy, char username[MAX_LEN]){

    User* temp = Userdummy->next;

    while ( temp != NULL){

        if ( !strcmp(temp->username, username) ){
            return temp;
        }

        temp = temp -> next ;
    }

    return NULL;
}

Chats* createChat(char chat_name[MAX_LEN], char author[MAX_LEN], char reciever[MAX_LEN]){

    Chats* newchat;
    newchat = (Chats*) calloc(1,sizeof(Chats));
    strcpy(newchat->name, chat_name);
    strcpy(newchat->author, author);
    strcpy(newchat->reciever, reciever);
    newchat -> messages_list = (Messages*) calloc(1,sizeof(Messages));
    newchat -> next = NULL;
    return newchat;
}

int repeatedChatName(User* Userdummy, char chat_name[MAX_LEN], char author[MAX_LEN], char reciever[MAX_LEN]){

    User* temp1 = Userdummy -> next;
    Chats* temp2;

    while ( temp1->next != NULL ){

        temp2 = (temp1 -> user_chats) -> next;

        while ( temp2 != NULL ){

            if ( (!strcmp(temp2->author, author) || !strcmp(temp2->author, reciever))   && !strcmp(temp2->name, chat_name) ){
                return 1;
            }

            temp2 = temp2 -> next;
        }
        temp1 = temp1 -> next;
    }
    return 0;
}

Chats* findChat(User* Userdummy, Logged_in* currentloggedin, char chat_name[MAX_LEN]){

    User* user1 = alreadyexist(Userdummy, currentloggedin->username);

    Chats* temp = (user1 -> user_chats) -> next;

    while ( temp != NULL ){

        if ( !strcmp(temp->name, chat_name) ){
            return temp;
        }

        temp = temp -> next;
    }

    return NULL;
}


Messages* createMessage(Logged_in* currentloggedin, char text[TEXT_LEN]){

    Messages* newmessage = (Messages*) calloc(1,sizeof(Messages));
    strcpy(newmessage->author, currentloggedin->username);
    strcpy(newmessage->text, text);
    newmessage -> next = NULL;
    return newmessage;
}

void freeUsers(User* Userdummy){

    User* temp1 = Userdummy;
    User* temp2;

    while (temp1 != NULL){

        temp2 = temp1 -> next;
        free(temp1);
        temp1 = temp2;
    }
}

void freechats(User* Userdummy){

    User* temp = Userdummy -> next;
    Chats* temp1, *temp2;

    while ( temp != NULL ){

        temp1 = temp -> user_chats;

        while ( temp1 != NULL ){

            temp2 = temp1 -> next;
            free(temp1);
            temp1 = temp2;
        }

        temp = temp -> next;
    }
}

void freemessages(User* Userdummy){

    User* temp = Userdummy -> next;
    Chats* temp1;
    Messages* temp2 , *temp3;

    while ( temp != NULL ){

        temp1 = temp -> user_chats;

        while ( temp1 != NULL ){

            temp2 = temp1 -> messages_list;

            while ( temp2 != NULL ){

                temp3 = temp2 -> next;
                free(temp2);
                temp2 = temp3;
            }

            temp1 = temp1 -> next;
        }

        temp = temp -> next;
    }
}

int signUp(User* Userdummy, User* current){

    char username[MAX_LEN], password[MAX_LEN];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    if ( alreadyexist(Userdummy, username) == NULL ){

        addUserInf(current, username, password);

        printf("User %s successfully registered!\n",current->username);

        return 1;

    }

    else{

        printf("Error: Username %s already exists.\n",username);
        return 0;
    }
}

int login(User* Userdummy, Logged_in* currentloggedin){

    char username[MAX_LEN], password[MAX_LEN];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    User* ifTrue = alreadyexist(Userdummy, username);

    if ( strcmp(currentloggedin->username, "") ){

        printf("Error: There is an open session, please logout first.\n");
        return 0;
    }

    if ( ifTrue != NULL && !strcmp(ifTrue->password, password) ){

        printf("User %s logged in successfully!\n", username);
        strcpy(currentloggedin->username, username);
        return 1;
    }

    else{
        printf("Error: Invalid username or password.\n");
        return 0;
    }
}

int logout(Logged_in* currentloggedin){

    if ( !strcmp(currentloggedin->username, "") ){

        printf("Error: No user is currently logged in.\n");
        return 0;
    }

    else{
        
        printf("User %s logged out successfully!\n",currentloggedin->username);
        strcpy(currentloggedin->username, "");
        return 1;
    }
}

int newChat(User* Userdummy, Logged_in* currentloggedin){

    char chat_name[MAX_LEN];
    char reciever[MAX_LEN];

    printf("Enter chat name: ");
    scanf("%s",chat_name);

    printf("Enter selected username: ");
    scanf("%s",reciever);

    if ( !strcmp(currentloggedin->username, "") ){

        printf("Error: No user is currently logged in.\n");
        return 0;
    }

    User* sender = alreadyexist(Userdummy, currentloggedin->username);
    User* destination = alreadyexist(Userdummy, reciever);

    if ( destination == NULL ){

        printf("Error: User %s not found.\n",reciever);
        return 0;
    }

    else if ( !strcmp(sender->username, reciever) ){

        printf("Error: You cannot create a chat with yourself.\n");
        return 0;
    }

    else if ( repeatedChatName(Userdummy, chat_name, currentloggedin->username, reciever) ){

        printf("Error: Chat with name %s already exists.\n", chat_name);
        return 0;
    }

    else{
        
        // adding newchat to sender's chatslist
        Chats* temp_sender = sender -> user_chats;
        while (temp_sender->next != NULL){
            temp_sender = temp_sender -> next;
        }
        temp_sender -> next = createChat(chat_name, sender->username, reciever);

        // adding newchat to sender's chatslist
        Chats* temp_destination = destination -> user_chats;
        while (temp_destination->next != NULL) {
            temp_destination = temp_destination -> next;
        }
        temp_destination -> next = createChat(chat_name, sender->username, reciever); 


        printf("Chat with the name %s created between %s and %s.\n", chat_name, reciever, currentloggedin->username);
        return 1;
    }
}

Chats* selectChat(User* Userdummy, Logged_in* currentloggedin){

    char chat_name[MAX_LEN];

    printf("Enter chat name: ");
    scanf("%s",chat_name);

    if ( !strcmp(currentloggedin->username, "") ){
        
        printf("Error: No user is currently logged in.\n");
        return NULL;
    }

    Chats* ifexist = findChat(Userdummy, currentloggedin, chat_name); 

    if ( ifexist == NULL ){

        printf("Error: Chat %s not found for user %s.\n",chat_name, currentloggedin->username);
        return NULL;
    }

    else{
        printf("Chat %s has been selected as the current chat\n",chat_name);
        return ifexist;
    }
}

int sendMessage(User* Userdummy, Chats* currentchat, Logged_in* currentloggedin){

    if ( currentchat == NULL ){
        printf("Error: No chat selected. Please select a chat first.\n");
        return 0;
    }

    else {

        if ( !strcmp(currentloggedin->username, currentchat->reciever) )
            printf("Receiver: %s\n", currentchat->author);
        
        else 
            printf("Receiver: %s\n", currentchat->reciever);

        char text[TEXT_LEN];
        printf("Enter message: ");
        while (getchar() != '\n');
        fgets(text, sizeof(text), stdin);
        text[strcspn(text,"\n")] = '\0';

        User* sender = alreadyexist(Userdummy, currentchat->author);
        User* destination = alreadyexist(Userdummy, currentchat->reciever);

        // uptading sender's chat
        Chats* temp1 = sender -> user_chats -> next;
        while ( temp1 != NULL ){
            if ( !strcmp(currentchat->name, temp1->name) ){
                break;
            }
            temp1 = temp1 -> next ;
        }
        Messages* temp1_messages = temp1 -> messages_list;
        while ( temp1_messages->next != NULL ){
            temp1_messages = temp1_messages -> next;
        }
        temp1_messages -> next = createMessage(currentloggedin, text);


        // updating reciever's chat
        Chats* temp2 = destination -> user_chats -> next;
        while ( temp2 != NULL ){
            if ( !strcmp(currentchat->name, temp2->name) ){
                break;
            }
            temp2 = temp2 -> next ;
        }
        Messages* temp2_messages = temp2 -> messages_list;
        while ( temp2_messages->next != NULL ){
            temp2_messages = temp2_messages -> next;
        }
        temp2_messages -> next = createMessage(currentloggedin, text);

        return 1;
    }
}

int showChat(Chats* currentchat){

    if ( currentchat == NULL ){
        printf("Error: No chat selected. Please select a chat first.\n");
        return 0;
    }

    else{

        printf("Messages in Chat '%s':\n", currentchat->name);

        Messages* temp = (currentchat -> messages_list) -> next;

        while ( temp != NULL ){
            printf("%s: %s\n",temp->author, temp->text);
            temp = temp -> next;
        }
        
        return 1;
    }
}

int loadFromFile(User* Userdummy, User* current){

    char file_name[MAX_LEN];
    printf("Enter filename: ");
    while ( getchar() != '\n' );
    scanf("%s",file_name);

    FILE* input = fopen(file_name, "r");
    if ( input == NULL ){
        printf("Error: Unable to open file %s.\n",file_name);
        return 0;
    }

    char each_line[256];
    char username[MAX_LEN],password[MAX_LEN];
    int i,j;
    int line = 1;
    int test = 0 , signedup_users = 0;

    while ( fgets(each_line, sizeof(each_line), input) ){  // reads line by line 

        for ( i=0 ; i < MAX_LEN ; i++ ){
            username[i] = '\0';  // initializing by null
            password[i] = '\0';
        }

        for (i=0 ; i < MAX_LEN+2 ; i++){

            if ( each_line[i] && each_line[i+1] == ' '){

                test = 1;

                for (j=0 ; j < i+1 ; j++){

                    username[j] = each_line[j];  // make username
                }
                break;
            } 
        }

        if ( test == 0 ){

            printf("Warning: Invalid format in line %d. Skipping.\n",line);
            line++;
            continue;
        }

        else{

            test = 0;
            for ( j=0, i = i + 2 ; each_line[i] != '\n' ; j++, i++){

                password[j] = each_line[i]; // make password
            }

            if ( password[0] == '\0' ){
                printf("Warning: Invalid format in line %d. Skipping.\n",line);
                line++;
                continue;
            }

            // signing up users
            addUserInf(current, username, password);
            current -> user_chats = (Chats*) calloc(1,sizeof(Chats));  // make chatdummy for each signedup users
            current -> next = createUser();
            current = current -> next;
            signedup_users++;       
        }
        line++;
    }

    printf("Users successfully loaded from %s , %d user(s) added.\n",file_name,signedup_users);
    fclose(input);
    return 1;
}



