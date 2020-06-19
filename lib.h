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

	pair<string, string> FPath(string full)
	{
		string fname = "";
		for(uInt32 i = 0; i < full.length(); ++i) if(full[i] == '\\') full[i] = '/';
		for(uInt32 i = full.length() - 1; i > 0; --i)
			if(full[i] != '/') fname = full[i] + fname, full.pop_back();
			else {full.pop_back(); break;}
		return make_pair(full, fname);
	}

#ifdef OS_WIN
#include<windows.h>
#include<conio.h>
	const int CRED    = FOREGROUND_INTENSITY | FOREGROUND_RED;
	const int CGREEN  = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
	const int CBLUE   = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
	const int CYELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
	const int CWHITE  = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	void SetColor(int c) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);}
	void title(string t) {system(("title " + t + " 2>nul >nul").c_str());}
	void mkdir(string t) {system(("mkdir \"" + t + "\" 2>nul >nul").c_str());}
	void mkfile(string t) {system(("cd.>\"" + t + "\" 2>nul >nul").c_str());}
	int run(string t) {return system(t.c_str());}
	void pause() {system("pause");}
	pair<string, string> GetPath()
	{
		TCHAR *szFilePath = new TCHAR[MAX_PATH];
		szFilePath[0] = '\0';
		GetModuleFileName(NULL, szFilePath, MAX_PATH - 2);
		pair<string, string> res = FPath(string(szFilePath));
		delete[] szFilePath;
		return res;
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
	pair<string, string> GetPath()
	{
		char *szFilePath = new char[MAX_PATH];
		szFilePath[0] = '\0';
		readlink("/proc/self/exe", szFilePath, MAX_PATH - 2);
		pair<string, string> res = FPath(string(szFilePath));
		delete[] szFilePath;
		return res;
	}
#endif
} using namespace SYS;


namespace RANDOM
{
	default_random_engine random_root;
	void init()
	{
		std::mt19937 rSeed(std::chrono::steady_clock::now().time_since_epoch().count());
		random_root.seed(rSeed() + 1201);
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
	string LogTime()
	{
		struct tm *ptm;
		struct timeb stTimeb;
		szTime[0] = '\0';
		ftime(&stTimeb);
		ptm = localtime(&stTimeb.time);
		sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
				ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, stTimeb.millitm);
		return string(szTime);
	}
} using namespace LOGTIME;


namespace LOG
{
#define LOUT  "[o] "<<LogTime()<<' '
#define LERR  "[x] "<<LogTime()<<' '
#define LWARN "[!] "<<LogTime()<<' '
	ofstream logF;
	void init(string id)
	{
		mkdir(PATH + "/temp/" + FNAME);
		logF.open(PATH + "/temp/" + FNAME + '/' + id + ".log", ios::app);
		if(!logF) exit_all(1345);
		logF << "------------------------------------------------" << endl;
		logF << LOUT << "STARTED_SECCESSFULLY: " << PATH << ' ' << FNAME << ' ' << id << endl;
	}
	void stop() {logF.close();}
} using namespace LOG;


void exit_all(int exitVal = 0)
{
	if(exitVal == 0)
	{
		logF << LOUT << "EXITED_NORMALLY: " << exitVal << endl;
		LOG::stop();
		SetColor(CWHITE);
		exit(0);
	}
	SetColor(CRED);
	cout << "Program received an error, ERRCODE: " << exitVal << endl;
	cout << "Please read ERRCODE.md to find out what's wrong. ";
	cout << "You can also send \'temp/*.log\' to us at GitHub to find more information about this." << endl;
	if(logF)
	{
		try {logF << LERR << "ABORTED: " << exitVal << endl;}
		catch(...) {cout << "[We cannot record this error into log file.]" << endl;}
	}
	LOG::stop();
	SetColor(CWHITE);
	pause();
	exit(exitVal);
}


string initialize(string id = "RANDOM_VAL")
{
	pair<string, string> p = GetPath();
	PATH = p.first, FNAME = p.second;
	RANDOM::init();
	if(id == "RANDOM_VAL")
	{
		char *tmp = new char[50];
		tmp[0] = '\0';
		sprintf(tmp, "%09d", random(1, 999999999));
		id = tmp;
		delete[] tmp;
	}
	LOG::init(id);
	return id;
}