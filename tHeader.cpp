#include<iostream>
#include "tHeader.h"

	tHeader::tHeader(int m)
	{//The type names should only be present when you declare a variable, not when you make a function call
	
	int i;
	string ver, tab, typ, b;
	
		if(m==0)
		{
			b="Router 0 routing table\nPath to R1: 1\nPath to R2: 3\nPath to R3: 7\n"; 
			tHeader::set(i, ver,tab,typ,b);
		}	
		else if(m==1)
		{
			b="Router 1 routing table\nPath to R0: 1\nPath to R2: 1\nPath to R3: UNKWN\n"; 
			tHeader::set(i, ver,tab,typ,b);
		}	
		else if(m==2)
		{
			b="Router 2 routing table\nPath to R1: 1\nPath to R0: 3\nPath to R3: 2\n"; 
			tHeader::set(i, ver,tab,typ,b);
		}
		else
		{
			b="Router 3 routing table\nPath to R0: 7\nPath to R2: 2\nPath to R1: UNKWN\n"; 
			tHeader::set(i, ver,tab,typ,b);
		}
	}
	
	void tHeader::set(int i, string t, string tab, string typ,string b)
	{
		id=1;
		ver="IPv4";
		table=t;
		type="REQUEST";
		body=b;
	}
