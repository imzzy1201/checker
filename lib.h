#define OS_WIN
/**************
 * "WIN"	: Windows all
 * "LINUX"	: Linux all
 * "MACOS"	: Mac OS*(uncompleted)
 */

#include<bits.stdc++.h>
using namespace std;

string PATH;

#ifdef OS_WIN
namespace SYS
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
#endif

void exit_all(int exitVal)
{
	if(exitval==0) exit(0);
	SYS::SetFontColor(CRED);
	cout<<"checker received an error, ERRCODE: "<<exitVal<<endl;
	cout<<"Please read ERRCODE.md to solve it"<<endl;
	cout<<"You can also upload \'temp/ERR.log\' to us"<<endl
}

namespace random
{
#define int32 int
#define int64 long long
#define uint32 unsigned int
#define uint64 unsigned long long
	std::mt19937 root1(std::chrono::steady_clock::now().time_since_epoch().count());
	std::mt19937_64 root2(std::chrono::steady_clock::now().time_since_epoch().count());
	uint32 ruint32(uint32 l, uint32 r) {
		assert(r >= l);
		return root1() % (r - l + 1) + l;
	}
	uint64 ruint64(uint32 l, uint32 r) {
		assert(r >= l);
		return root2() % (r - l + 1) + l;
	}
	int32 rint32(int l, int r) {
		assert(r >= l);
		return (int32)ruint32(l, r);
	}
	int64 rint64(int64 l, int64 r) {
		assert(r >= l);
		return (int64)ruint64(l, r);
	}
#undef int32
#undef int64
#undef uint32
#undef uint64
}

using namespace random;

inline void INIT()
{
	PATH=;
	
}