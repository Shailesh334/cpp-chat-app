#include<iostream>
#include<string>
#include<winsock2.h>
#include<ws2tcpip.h>


using namespace std;



int main(){

    // =======================  [ 1 ] =================================
    //                 WinSock Intialization
    WSADATA wsaData;
    int wsaerr;
    WORD version = MAKEWORD(2 , 2);

    wsaerr = WSAStartup(version , &wsaData);

    if(wsaerr != 0){
        cout<<"WSA intialization() failed !!"<<endl;
    }
    else{
        cout<<"Wsa intialized !"<<endl;
    }

    // =======================  [ 2 ] =================================
    //                   Socket Creation

     SOCKET clientSocket = socket(AF_INET , SOCK_STREAM , 0);

     if(clientSocket == INVALID_SOCKET){
        cout<<"socket() creation failed !!"<<endl;
     }
     else{
        cout<<"socket() created succesfully!"<<endl;
     }

     
    // =======================  [ 3 ] =================================
    //                   Connect to the serverSocket

    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8080);

    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(clientSocket , (sockaddr*) &servAddr , sizeof(servAddr)) == SOCKET_ERROR){
        cout<<"connect() failed !!"<<endl;
    }
    else{
        cout<<"Connected to the server !"<<endl;
    }

    char buffer[512];
    bool flag = true;

    while(flag){
        string msg;
        cout << "Enter message: ";
        getline(cin, msg);
        if(msg == "exit")flag = false;
        send(clientSocket, msg.c_str(), msg.size() + 1, 0);

        recv(clientSocket, buffer, sizeof(buffer), 0);
        cout << "Client says: " << buffer << endl;
    }

}