using namespace std;

class tHeader
{
	//int map;
	public:
	int id;
	string ver, table, type,body;
	
	
	public:
		tHeader(int m);//different int = different routing table
		void set(int i, string v, string tab, string typ,string b);
		string print();
		
		
		//tHeader(int v,int c,int i,string m,string typ);
};
