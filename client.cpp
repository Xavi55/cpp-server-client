#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<cstring>
#include<cstdlib>
#include<unistd.h>
#include<ctime>
#include "tHeader.h"

//using namespace std;
int main(int argc, char **argv)
{
	struct sockaddr_in dest;//destination ip address
	
	socklen_t sSize=sizeof(struct sockaddr_in);
	int SOCK;
	char rply[1000];
	const char *mesg;
	string buffer;
	time_t clk=time(NULL);
	
	SOCK = socket(AF_INET, SOCK_DGRAM, 0);//make UDP socket
	if(SOCK == -1)
	{
		cout<<("socket fail\n");
		return 1;
	}
	
	dest.sin_addr.s_addr = inet_addr("128.235.208.201"); //command 'hostname -i' to reveal number ip addr
	dest.sin_family = AF_INET;
	dest.sin_port = htons(3000);//3000
	
	tHeader r0(0);//create client mesg
	cout<<r0.body;//print table client side
	
	buffer = to_string(static_cast<long long>(r0.id)) +"," + r0.ver+"," + r0.type+"," + r0.body; //serialize data to bits
	mesg=buffer.c_str();
	if( sendto(SOCK , mesg , strlen(mesg),0,(struct sockaddr *)&dest,sSize ) <0)
	{
		cout<<("fail to send\n");
		return 1;
	}
	cout<<"\nSending OP code ("<<r0.id<< ") to IP address: " <<inet_ntoa(dest.sin_addr) <<" Port# "<< (int) ntohs(dest.sin_port)<<"\n"<<asctime(localtime(&clk))<< "\n\n";
	if( recvfrom (SOCK, rply, 500, 0,(struct sockaddr *)&dest,&sSize )<0)
	{
		cout<<("reply fail\n");
		return 1;
	}
	//deserialize data
	tHeader r1(1);
	r1.id =atoi(strtok(rply,","));
	r1.ver=strtok(NULL,",");
	r1.type=strtok(NULL,",");
	r1.body=strtok(NULL,",");
	cout<<"Recieved OP code ("<< r1.id<< ") from IP address: "<<inet_ntoa(dest.sin_addr) <<" on Port#: "<< (int) ntohs(dest.sin_port)<<"\n"<<asctime(localtime(&clk))<<"\n";
	cout<<r1.body<<"\n\n";
	//
	/////
	///////
	//////////
	
	r0.id=3;
	buffer = to_string(static_cast<long long>(r0.id)) +"," + r0.ver+"," + r0.type+"," + r0.body; //serialize data to bits
	mesg=buffer.c_str();
	if( sendto(SOCK , mesg , strlen(mesg),0,(struct sockaddr *)&dest,sSize ) <0)
	{
		cout<<("fail to send\n");
		return 1;
	}
	cout<<"Sending OP code ("<<r0.id<< ") to IP address: " <<inet_ntoa(dest.sin_addr) <<" Port# "<< (int) ntohs(dest.sin_port)<<"\n"<<asctime(localtime(&clk))<< "\n\n";

	close(SOCK);

	return 0;
}
