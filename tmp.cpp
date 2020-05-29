// #include<bits/stdc++.h>
#include"lib.h"
// #include<sys/time.h>
using namespace std;

signed main()
{
	// system("@echo off");
	initialize("HELLO");
	cout<<PATH<<' '<<FNAME<<endl;
	cout<<random(-100,-1)<<endl;
	SetColor(CYELLOW);
	title("aaa");
	logF<<LOUT<<"hey"<<endl;
	logF<<LERR<<"hey"<<endl;
	logF<<LWARN<<"hey"<<endl;
	cout<<LogTime()<<endl;
	Sleep(100);
	cout<<LogTime()<<endl;
	pause();
	SetColor(CBLUE);
	cout<<random(100000000000ll,1000000000000ll)<<endl;
	SetColor(CWHITE);
	exit_all(33);
	return 0;
}