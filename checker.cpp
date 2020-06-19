#include"lib.h"

namespace CHECK
{
	string tmpDir,ansOut,myOut,logFile,testFile;
	int exit_val,num,errcode;
	clock_t startTime,endTime;
	ofstream tmpF;
	int check(string id,int times,string make,string ans,string my,string compare)
	{
		try
		{
			logF<<LOUT<<"CHECK::check("<<id<<','<<times<<','<<make<<','<<ans<<','<<my<<','<<compare<<')'<<endl;
			
			title(string("checking: ")+my+" with "+ans);
						
			tmpDir=PATH+"/temp/"+FNAME+'/'+id;
			ansOut=tmpDir+"/ans.out";
			myOut=tmpDir+"/my.out";
			logFile=tmpDir+"/"+id+".log";
			testFile=tmpDir+"/test.in";
			
			tmpF.open(logFile,ios::out);
			if(!tmpF)
			{
				tmpF.close();
				SetColor(CRED);
				cout<<"Err while creating files: File "<<logFile<<" already exists";
				SetColor(CWHITE);
				return -1;
			}
			mkdir(tmpDir);
			mkfile(ansOut);
			mkfile(myOut);
			mkfile(logFile);
			
			SetColor(CYELLOW);
			logF<<LOUT<<"CHECK::check() "<<"start tests"<<endl;
			cout<<"-------- start tests --------"<<endl<<endl;
			
			errcode=0;
			if(num>999999999||num<1) num=999999999;
			for(num=1;num!=times;++num)
			{
				SetColor(CWHITE);
				printf("\n----- test %09d -----\n",num);
				logF<<LOUT<<"CHECK::check() test "<<num<<endl;
				
				startTime=clock();
					exit_val=run(make+" >\""+testFile+"\"");
				endTime=clock();
				if(exit_val) {errcode=1; break;}
				SetColor(CWHITE);  cout<<"\'make\'    ";
				SetColor(CGREEN);  cout<<"exited normally";
				SetColor(CWHITE);  cout<<" with time used: ";
				SetColor(CYELLOW); printf("%.4lfs\n",(double)(endTime-startTime)/CLOCKS_PER_SEC);
				logF<<LOUT<<"CHECK::check() test "<<num<<" make exited normally.  Start: "<<startTime<<" End: "<<endTime<<" CLOCK: "<<CLOCKS_PER_SEC<<endl;
				
				startTime=clock();
					exit_val=run(ans+" <\""+testFile+"\" >\""+ansOut+"\"");
				endTime=clock();
				if(exit_val) {errcode=2; break;}
				SetColor(CWHITE);  cout<<"\'ans\'     ";
				SetColor(CGREEN);  cout<<"exited normally";
				SetColor(CWHITE);  cout<<" with time used: ";
				SetColor(CYELLOW); printf("%.4lfs\n",(double)(endTime-startTime)/CLOCKS_PER_SEC);
				logF<<LOUT<<"CHECK::check() test "<<num<<" ans exited normally.  Start: "<<startTime<<" End: "<<endTime<<" CLOCK: "<<CLOCKS_PER_SEC<<endl;
				
				startTime=clock();
					exit_val=run(my+" <\""+testFile+"\" >\""+myOut+"\"");
				endTime=clock();
				if(exit_val) {errcode=3; break;}
				SetColor(CWHITE);  cout<<"\'my\'      ";
				SetColor(CGREEN);  cout<<"exited normally";
				SetColor(CWHITE);  cout<<" with time used: ";
				SetColor(CYELLOW); printf("%.4lfs\n",(double)(endTime-startTime)/CLOCKS_PER_SEC);
				logF<<LOUT<<"CHECK::check() test "<<num<<" my exited normally.  Start: "<<startTime<<" End: "<<endTime<<" CLOCK: "<<CLOCKS_PER_SEC<<endl;
				
				startTime=clock();
					exit_val=run(compare+" \""+ansOut+"\" \""+myOut+"\" >\""+logFile+"\"");
				endTime=clock();
				if(exit_val) {errcode=4; break;}
				SetColor(CWHITE);  cout<<"\'compare\' ";
				SetColor(CGREEN);  cout<<"exited normally";
				SetColor(CWHITE);  cout<<" with time used: ";
				SetColor(CYELLOW); printf("%.4lfs\n",(double)(endTime-startTime)/CLOCKS_PER_SEC);
				logF<<LOUT<<"CHECK::check() test "<<num<<" compare exited normally.  Start: "<<startTime<<" End: "<<endTime<<" CLOCK: "<<CLOCKS_PER_SEC<<endl;
			}
			SetColor(CYELLOW);
			cout<<endl<<endl<<"-------- tests over --------"<<endl;
			logF<<LOUT<<"CHECK:check() tests over"<<endl;
			if(!errcode)
			{
				SetColor(CGREEN);
				cout<<"All tests passed!"<<endl;
				logF<<LOUT<<"CHECK:check() All tests passed."<<endl;
			}
			else
			{
				SetColor(CRED);
				cout<<"Failed on test "<<num<<" :"<<endl;
				logF<<LOUT<<"CHECK:check() Failed on test "<<num<<", errcode: "<<errcode<<endl;
			}
			if(errcode==1) cout<<"Err while running \'make\' with exit val: "<<exit_val<<endl;
			if(errcode==2) cout<<"Err while running \'ans\' with exit val: "<<exit_val<<endl;
			if(errcode==3) cout<<"Err while running \'my\' with exit val: "<<exit_val<<endl;
			if(errcode==4) cout<<"Err while running \'compare\' with exit val: "<<exit_val<<endl<<"LOG file: \""<<logFile<<"\""<<endl;
			cout<<endl;
		}
		catch(...)
		{
			SetColor(CRED);
			cout<<"Unknown Error!"<<endl;
			errcode=-1201;
		}
		SetColor(CWHITE);
		return errcode;
	}
}

signed main()
{
	string id=initialize();
	// CHECK::check(4321,1234,"a.exe","b.exe");
	// cout<<"Press any key to exit"<<endl;
	// getch();
	exit_all(0);
}
// ----------------------------
// by imzzy