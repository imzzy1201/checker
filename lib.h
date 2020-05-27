#include<bits/stdc++.h>
#define Int32 int
#define Int64 long long
#define uInt32 unsigned int
#define uInt64 unsigned long long
using namespace std;
string PATH, FNAME;
void exit_all(int);


namespace SYS
{
#define OS_WIN 1
#define MAX_PATH 10004

#ifdef OS_WIN
#include<windows.h>
#include<conio.h>
	const int CRED    = FOREGROUND_INTENSITY | FOREGROUND_RED;
	const int CGREEN  = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
	const int CBLUE   = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
	const int CYELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
	const int CWHITE  = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	void SetColor(int c) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);}
	void title(string t) {system(("title " + t).c_str());}
	void mkdir(string t) {system(("mkdir \"" + t + '\"').c_str());}
	void mkfile(string t) {system(("cd.>\"" + t + '\"').c_str());}
	int run(string t) {return system(t.c_str());}
	void pause() {system("pause");}
	pair<string, string> getpath()
	{
		TCHAR *szFilePath = new TCHAR[MAX_PATH];
		szFilePath[0] = '\0';
		GetModuleFileName(NULL, szFilePath, MAX_PATH - 2);
		string res1 = szFilePath, res2 = "";
		delete[] szFilePath;
		for(int i = 0; i < res1.length(); ++i) if(res1[i] == '\\') res1[i] = '/';
		for(int i = res1.length() - 1; i > 0; --i)
			if(res1[i] != '/') res2 = res1[i] + res2, res1.pop_back();
			else {res1.pop_back(); break;}
		return make_pair(res1, res2);
	}
#endif

#ifdef OS_LINUX
#include<unistd.h>
#include<termio.h>
	const char *CRED    = "\033[1;31m";
	const char *CGREEN  = "\033[1;32m";
	const char *CYELLOW = "\033[1;33m";
	const char *CBLUE   = "\033[1;34m";
	const char *CWHITE  = "\033[1;37m";
	void SetColor(const char *c) {printf("%s", c);}
	void title(string t) {cout << "\033]0;" << t << "\007";}
	void mkdir(string t) {system(("mkdir \"" + t + '\"').c_str());}
	void mkfile(string t) {system(("touch\"" + t + '\"').c_str());}
	int run(string t) {return system(("\"./" + t + "\"").c_str());}
	int getch()
	{
		struct termios tm, tm_old;
		int fd = 0, ch;
		if (tcgetattr(fd, &tm) < 0) return -1;
		tm_old = tm;
		cfmakeraw(&tm);
		if (tcsetattr(fd, TCSANOW, &tm) < 0) return -1;
		ch = getchar();
		if (tcsetattr(fd, TCSANOW, &tm_old) < 0) return -1;
		return ch;
	}
	void pause() {cout << "Press any key to continue . . .", getch(), cout << endl;}
	pair<string, string> getpath()
	{
		char *tmp = new char[MAX_PATH];
		tmp[0] = '\0';
		readlink("/proc/self/exe", tmp, MAX_PATH - 2);
		string res1 = tmp, res2 = "";
		delete[] tmp;
		for(int i = 0; i < res1.length(); ++i) if(res1[i] == '\\') res1[i] = '/';
		for(int i = res1.length() - 1; i > 0; --i)
			if(res1[i] != '/') res2 = res1[i] + res2, res1.pop_back();
			else {res1.pop_back(); break;}
		return make_pair(res1, res2);
	}
#endif
} using namespace SYS;


namespace RANDOM
{
	default_random_engine random_root;
	void init()
	{
		std::mt19937 tmproot(std::chrono::steady_clock::now().time_since_epoch().count());
		random_root.seed(tmproot() + 1201);
	}
	template<typename T> T random(T l, T r)
	{
		if(r < l) exit_all(3325);
		uniform_int_distribution<T> u(l, r);
		return u(random_root);
	}
} using namespace RANDOM;


namespace LOGTIME
{
#include<sys/time.h>
	char szTime[30];
	string logTime()
	{
		struct tm *ptm;
		struct timeb stTimeb;
		szTime[0] = '\0';
		ftime(&stTimeb);
		ptm = localtime(&stTimeb.time);
		sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d.%03d\0",
				ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, stTimeb.millitm);
		return string(szTime);
	}
} using namespace LOGTIME;


namespace LOG
{
	ofstream logF;
	void init()
	{
		logF.open(PATH + "/temp/" + FNAME + ".log", ios::app);
		if(!logF) exit_all(1345);
		logF << "[o] " << logTime() << ' ' << "STARTED_SECCESSFULLY: " << PATH << ' ' << FNAME << endl;
	}
	void stop() {logF.close();}
} using namespace LOG;


void exit_all(int exitVal)
{
	if(exitVal == 0)
	{
		logF << "[o] " << logTime() << ' ' << "EXITED_NORMALLY: " << exitVal << endl << endl;
		LOG::stop();
		SetColor(CWHITE);
		exit(0);
	}
	SetColor(CRED);
	cout << "Program received an error, ERRCODE: " << exitVal << endl;
	cout << "Please read ERRCODE.md to find out what's wrong. ";
	cout << "You can also upload \'temp/*.log\' to us at GitHub to find more information about this." << endl;
	if(logF) logF << "[x] " << logTime() << ' ' << "ABORTED: " << exitVal << endl << endl;
	LOG::stop();
	SetColor(CWHITE);
	pause();
	exit(exitVal);
}


void INIT()
{
	pair<string, string> p = getpath();
	PATH = p.first, FNAME = p.second;
	RANDOM::init();
	LOG::init();
}