#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_WORDS 100
#define WORD_SIZE 50
#define PORTNO 10200

typedef struct{
    char word[WORD_SIZE];
    int count;
} WordInfo;

void removeDuplicates(char * text){
    WordInfo words[MAX_WORDS];
    int wordCount=0;

    char *token = strtok(text, " ");
    int existingIndex = -1;
    while(token!=NULL){
    for (int i = 0; i < wordCount ; i++)
    {
        if (strcmp(words[i].word, token)==0)
        {
            existingIndex=i;
            break;
        }
        
    }
    if (existingIndex != -1)
    {
        words[existingIndex].count++;
    }
    else if(wordCount < MAX_WORDS){
        strcpy(words[wordCount].word,token);
        words[wordCount].count = 1;
        wordCount++;
    }
    token = strtok(NULL, " ");
    }
    printf("Word\t\tOccurances\n");
    for (int i = 0; i < wordCount; i++)
    {
        if(words[i].count>1)
        printf("%s\t\t%d\n",words[i].word, words[i].count);

    } 
    text[0] = '\0';
    for (int i = 0; i < wordCount; i++) {
        strcat(text, words[i].word);
        if (i != wordCount - 1) {
            strcat(text, " ");
        }
    }    
}

int main(){
    int sockfd, newsockfd, portno, clilen, n=1;
    struct sockaddr_in seraddr, cliaddr;
    int i, value;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    seraddr.sin_family=AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr*)&seraddr,sizeof(seraddr));

    listen(sockfd,5);
    
    while(1){
        
        char buf[256]="";
        printf("Server Waiting\n");
        clilen = sizeof(clilen);
        newsockfd=accept(sockfd,(struct sockaddr*)&cliaddr, &clilen);
        
        n=read(newsockfd, buf,sizeof(buf));
        printf("Message from client: %s\n",buf);
        buf[strcspn(buf, "\n")] = '\0';
        if ((strcmp(buf,"Stop")==0)) {
            printf("Terminated\n");
            break;
        }
        removeDuplicates(buf);
        write(newsockfd,buf,sizeof(buf));
        close(newsockfd);
        
        }
        
        close(sockfd);
        return 0;
    

}
