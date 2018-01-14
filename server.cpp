#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<cstring>
#include<ctime>
#include "tHeader.h"

using namespace std;
int main(int argc, char * argv[])
{
	struct sockaddr_in srvr, client;
	socklen_t sSize=sizeof(struct sockaddr_in);
	int mySOCK, newSOCK;
	const char *mesg;
	string buff;
	char rply[1000];
	char ip[50];
	time_t clk=time(NULL);
	
	mySOCK = socket(AF_INET, SOCK_DGRAM, 0);
	if (mySOCK == -1)
	{
		cout<<("socket fail\n");
	}
	
	srvr.sin_family= AF_INET;
	srvr.sin_addr.s_addr=htonl(INADDR_ANY);
	srvr.sin_port = htons(3000);
	
	tHeader r1(1);
	cout<<r1.body <<"\n";//print out server table
	
	if (bind(mySOCK, (struct sockaddr *)&srvr, sizeof(srvr))<0)//use mySOCK as a door
	{
		cout<<"failed to bind\n";
		return 1;
	}
	cout<<("bind ok\n");
	//struct sockaddr_in;
	while(1)
	{

		cout<<("Server waiting...\n\n");
		
		
		if(recvfrom(mySOCK, rply, 1000, 0,(struct sockaddr *)&srvr, &sSize) <0)
		{
			cout<<("failed to get reply.\n");
			return 1;
		}
		tHeader r0(0);
		r0.id =atoi(strtok(rply,","));
		r0.ver=strtok(NULL,",");
		r0.type=strtok(NULL,",");
		r0.body=strtok(NULL,",");
		
		if(r0.id == 1)//manipulate reply based on messg
		{
			r1.id=2;
			r1.type="REPLY";
			
			char name[50];
			cout<<"Recived OP Code ("<<r0.id<<") from IP address: "<<inet_ntoa(srvr.sin_addr)<<" Port#: " <<(int) ntohs(srvr.sin_port)<<"\n"<< asctime(localtime(&clk))<<"\n";
			
			buff=to_string(static_cast<long long>(r1.id)) +"," + r1.ver+"," + r1.type+"," + r1.body;
			
			mesg= buff.c_str();
			if (sendto(mySOCK, mesg, 1000, 0,(struct sockaddr *)&srvr, sSize) <0)
			{
				cout<<"send fail";
				break;
			}
			cout<<"Sending Reply\n\n";
		}
		else
		{
			cout<<"Recived OP Code ("<<r0.id<<")\n"<<asctime(localtime(&clk))<<"\n";
			cout<<r0.body<<"\n";
		}
	}
	return 0;
}
