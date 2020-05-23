#include<bits/stdc++.h>
using namespace std;

string f1,f2;
signed main(int argc, char* argv[])
{
	if(argc<3)
	{
		std::cout<<"Err: File name missing"<<std::endl;
		return -1;
	}
	string f1=argv[1],f2=argv[2];
	int comp=0;
	//--------------------------
	
	string tmp="fc "+f1+" "+f2;
	comp=system(tmp.c_str());
	
	//--------------------------
	return comp;
}
// ----------------------------
// by imzzy