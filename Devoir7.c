#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
    if (argc < 2) {
        printf("Usage: %s <adresse_ip>\n", argv[0]);
        return 1;
    }
    struct sockaddr_in addrServer;

    //initialiser la structure a 0
    memset(&addrServer,0,sizeof(addrServer));
    addrServer.sin_family=AF_INET;
    addrServer.sin_addr.s_addr=inet_addr(argv[1]);

    int socketTCP;
    for(int port=0;port<3000;port++)
    {
        socketTCP=socket(AF_INET,SOCK_STREAM,0);
        if(socketTCP==-1)
        {
            printf("Erreur de creation de la socket TCP au port %d\n",port);
            return 0;
        }
        addrServer.sin_port=htons(port);

        // tenter de se connecter au port
        if(connect(socketTCP,(struct sockaddr*)&addrServer,sizeof(addrServer))==0)
        {
            printf("Connecxion TCP reussie au port %d\n",port);
        }
        close(socketTCP);
    }

    return 0;
}