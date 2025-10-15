#include<iostream>
#include<string>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<vector>
#include<map>
#include<thread>




using namespace std;

vector<SOCKET> chatroom;
map<SOCKET , string> mp;
SOCKET acceptClient(){
     //  ====================================================================   
    //       1] Initializing the Winsock DLL  -- WSAStartup()


            WSADATA wsaData; // contains info about windows sockets implementation 

            
            int wsaerr; // To collect output of WSAStartup

            WORD version = MAKEWORD(2 , 2); // version of winsock you want to use in WORD 
        
            
            wsaerr = WSAStartup(version , &wsaData); // Takes version and data 

            if(wsaerr != 0){ // != 0 if fails
                cout<<"WSA dll not found !"<<endl;
                WSACleanup(); 
            }
            else{ // == 0 if success
                cout<<"WSA intialized !!"<<endl;
            }

    
   //  ===============================================================   
  //       2] Create a socket  -- socket()

  /*
            AF_INET      → Address family (IPv4)
            SOCK_STREAM  → Type of socket (stream-based, i.e., reliable, connection-oriented)
            0            → Protocol (default for the chosen socket type)

            When you use SOCK_STREAM with AF_INET, the default protocol is TCP.
            When you use SOCK_DGRAM with AF_INET, the default protocol is UDP.

            So by passing 0, you’re basically saying:

                “Use the default protocol for this socket type.”

            And Winsock automatically maps:

                SOCK_STREAM → IPPROTO_TCP
                SOCK_DGRAM → IPPROTO_UDP
  
  */
    SOCKET serverSocket = socket(AF_INET , SOCK_STREAM , 0);
    // OR SOCKET serverSocket = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    
    if(serverSocket == INVALID_SOCKET){
        cout<<"Socket creation failed !!"<<endl;
        WSACleanup();
    }
    else{
        cout<<"Socket() is OK!"<<endl;
    }

    //  ===============================================================   
   //       3] Bind the socket  -- bind()

        sockaddr_in servAddr;
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = INADDR_ANY;
        servAddr.sin_port = htons(8080);

        if(bind(serverSocket , (sockaddr *)&servAddr , sizeof(servAddr)) == SOCKET_ERROR ){
                cout<<"bind() failed !"<<endl;
                closesocket(serverSocket);
                WSACleanup();
        }else{
                cout<<"bind() successful !"<<endl;
        }

    
    //  ===============================================================   
   //       4] Listen on the soket  -- listen()

        if(listen(serverSocket , 1) == SOCKET_ERROR){
            cout<<"listen(): Error listening on socket "<<endl;
        }
        else{
            cout<<"listen() is OK! , Im waiting for connections "<<endl;
        }

      
    //  ===============================================================   
   //       5] Accept the client  -- accept()  

   SOCKET clientSocket = accept(serverSocket , nullptr , nullptr);
      
   return clientSocket;
}

void broadcast(string msg ,SOCKET sender){

    for(auto i : chatroom){
        if(msg == "exit"){
            string m = mp[sender] + "left the chatroom..";
            send(i )

        }
        if( i != sender){
            send(i, msg.c_str(), msg.size() + 1, 0);
        }
    }
}

void handleClient(SOCKET clientSocket){

    chatroom.push_back(clientSocket);
    string name;
    cout<<"Enter your username : ";
    getline(cin , name);
    mp[clientSocket] = name;
    
    string m = name + "joined !";
   

    char buffer[512];
    bool flag = true;
    while(flag){

         recv(clientSocket, buffer, sizeof(buffer), 0);
         cout <<name <<":"<< buffer << endl;

            string msg;
            cout << name << ':';
            getline(cin, msg);

            broadcast(msg , clientSocket)
            


    }
   

}


int main(){


    SOCKET clientSocket = acceptClient();

       if(clientSocket == INVALID_SOCKET){
                cout<<"Connect() failed !"<<endl;
        }
        else{
                cout<<"Client connected !"<<endl;
        }

        thread(handleClient , clientSocket).detach();

   

    
}   