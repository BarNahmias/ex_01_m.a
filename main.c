#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>




// #include <sys/types.h> 




char* input() {
    printf("%s","enter input: ");
    int count = 0;
    char c;
    char* str = (char*)malloc((count+1)*sizeof(char));
    char* cpy = str;
    while(scanf("%c",&c) && c != '\n'){
    count++;
    str = realloc(str, (count+1)*sizeof(char));
    if(!str){
    printf("Too long input");
    free(cpy);
    return NULL;
    }
    cpy = str;
    str[count-1] = c;
    }
    str[count] = '\0';
    return str;
}


int main(){

    int tcpOrLocal = 0;
    int sock = 0;
    // /* part 1 */
    char* str = "";
    while (strcmp(str, "EXIT"))
    {
        str = input();
        

        /* part 3*/
        char subbuff[10];
        memcpy( subbuff, &str[0], 4);
        subbuff[4] = '\0';
    
        if(!strcmp(subbuff, "ECHO")){
            if (tcpOrLocal == 0){
            printf("%s\n", &str[5]);
            }
            else{
                int messageLen = strlen(&str[5]) + 1;

                int bytesSent = send(sock, &str[5], messageLen, 0);
                if (bytesSent == -1)
                {
                    perror("failed to sending File\n");
                    exit(0);
                }
            }
        }

        /^^ part 3 ^^/

        /part 4/
        
       
        if(!strcmp(str, "TCP PORT")){
            tcpOrLocal = 1;

            /* open socket */
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if(sock == -1)
            {
                printf("Could not create socket");
            }

            struct sockaddr_in serverAddress;
            memset(&serverAddress, 0, sizeof(serverAddress));

            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(5000);
            serverAddress.sin_addr.s_addr = INADDR_ANY;

            if (connect(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1)
            {
                printf("connect() failed with error code");
                exit(0);
            }


        
        }
    }
    free(str);

    /* part 2 */

    char cwd[256];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }


    return 0;
}