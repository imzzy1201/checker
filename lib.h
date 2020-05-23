#define OS "WIN"
/**************
 * "WIN"	: Windows all
 * "LINUX"	: Linux all
 * "MACOS"	: Mac OS*(uncompleted)
 */

#include<bits.stdc++.h>
using namespace std;

string PATH;

namespace OSwindows
{
	#include<windows.h>
	
	const int CRED    =FOREGROUND_INTENSITY|FOREGROUND_RED;
	const int CGREEN  =FOREGROUND_INTENSITY|FOREGROUND_GREEN;
	const int CBLUE   =FOREGROUND_INTENSITY|FOREGROUND_BLUE;
	const int CYELLOW =FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN;
	const int CWHITE  =FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;
	
	inline void SetFontColor(int c) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);}
	inline void title(string t) {system(("title "+t).c_str());}
	inline void mkdir(string t) {system(("mkdir \""+t+'\"').c_str());}
	inline void mkfile(string t) {system(("cd.>\""+t+'\"').c_str());}
	inline int run(string t) {return system(t.c_str());}
	inline string getpath()
	{
		string res=_pgmptr;
		for(rgi i=res.length()-1;i>0;--i)
			if(res[i]!='\\') res.pop_back();
			else {res.pop_back(); break;}
		return res;
	}
}


namespace random
{
	inline void RandomInit()
	{
		fostream iofile;
		try
		{
			iofile.open("random.seed");
			unsigned seed=1201;
			iofile>>seed;
			srand(seed);
			iofile<<(seed*rand())%1201201;
		}
		catch(...)
		{
			exit("3315");
		}
	}
}

using namespace OSwindows;
using namespace random;

inline void INIT()
{
	PATH=;
	
}