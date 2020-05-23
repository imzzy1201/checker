#include"lib.h"

namespace CHECK
{
	string tmpDir,ansOut,myOut,logFile,testFile;
	int exit_val,num,errcode;
	clock_t startTime,endTime;
	ifstream tmpF;
	int check(string cur,int id,int times,string make,string ans,string my,string compare)
	{
		try
		{
			title(string("checking: ")+my+" with "+ans);
						
			char *tmpC=new char[34];
			sprintf(tmpC,"%010d",id);
			tmpDir=cur+"\\temp\\"+tmpC;
			ansOut=tmpDir+"\\ans.out";
			myOut=tmpDir+"\\my.out";
			logFile=tmpDir+"\\"+tmpC+".log";
			testFile=tmpDir+"\\test.in";
			delete[] tmpC;
			
			tmpF.open(logFile,ios::in);
			if(tmpF)
			{
				tmpF.close();
				SetFontColor(CRED);
				cout<<"Err while creating files: File "<<logFile<<" already exists";
				SetFontColor(CWHITE);
				return -1;
			}
			mkdir(tmpDir);
			mkfile(ansOut);
			mkfile(myOut);
			mkfile(logFile);
			
			SetFontColor(CYELLOW);
			cout<<"-------- start tests --------"<<endl<<endl;
			
			errcode=0;
			for(num=1;num<=times;++num)
			{
				SetFontColor(CWHITE);
				printf("\n----- test %010d -----\n",num);
				
				startTime=clock();
					exit_val=run(make+" >\""+testFile+"\"");
				endTime=clock();
				if(exit_val) {errcode=1; break;}
				SetFontColor(CWHITE); cout<<"\'make\'    ";
				SetFontColor(CGREEN); cout<<"exited normally";
				SetFontColor(CWHITE); cout<<" with time used: ";
				SetFontColor(CYELLOW); printf("%.4lfs\n",(double)(endTime-startTime)/CLOCKS_PER_SEC);
				
				startTime=clock();
					exit_val=run(ans+" <\""+testFile+"\" >\""+ansOut+"\"");
				endTime=clock();
				if(exit_val) {errcode=2; break;}
				SetFontColor(CWHITE); cout<<"\'ans\'     ";
				SetFontColor(CGREEN); cout<<"exited normally";
				SetFontColor(CWHITE); cout<<" with time used: ";
				SetFontColor(CYELLOW); printf("%.4lfs\n",(double)(endTime-startTime)/CLOCKS_PER_SEC);
				
				startTime=clock();
					exit_val=run(my+" <\""+testFile+"\" >\""+myOut+"\"");
				endTime=clock();
				if(exit_val) {errcode=3; break;}
				SetFontColor(CWHITE); cout<<"\'my\'      ";
				SetFontColor(CGREEN); cout<<"exited normally";
				SetFontColor(CWHITE); cout<<" with time used: ";
				SetFontColor(CYELLOW); printf("%.4lfs\n",(double)(endTime-startTime)/CLOCKS_PER_SEC);
				
				startTime=clock();
					exit_val=run(compare+" \""+ansOut+"\" \""+myOut+"\" >\""+logFile+"\"");
				endTime=clock();
				if(exit_val) {errcode=4; break;}
				SetFontColor(CWHITE); cout<<"\'compare\' ";
				SetFontColor(CGREEN); cout<<"exited normally";
				SetFontColor(CWHITE); cout<<" with time used: ";
				SetFontColor(CYELLOW); printf("%.4lfs\n",(double)(endTime-startTime)/CLOCKS_PER_SEC);
			}
			SetFontColor(CYELLOW);
			cout<<endl<<endl<<"-------- tests over --------"<<endl;
			if(!errcode)
			{
				SetFontColor(CGREEN);
				cout<<"All tests passed!"<<endl;
			}
			else
			{
				SetFontColor(CRED);
				cout<<"Failed on test "<<num<<" :"<<endl;
			}
			if(errcode==1) cout<<"Err while running \'make\' with exit val: "<<exit_val<<endl;
			if(errcode==2) cout<<"Err while running \'ans\' with exit val: "<<exit_val<<endl;
			if(errcode==3) cout<<"Err while running \'my\' with exit val: "<<exit_val<<endl;
			if(errcode==4) cout<<"Err while running \'compare\' with exit val: "<<exit_val<<endl<<"LOG file: \""<<logFile<<"\""<<endl;
			cout<<endl;
		}
		catch(...)
		{
			SetFontColor(CRED);
			cout<<"Unknown Error!"<<endl;
			errcode=-1201;
		}
		SetFontColor(CWHITE);
		return errcode;
	}
}

signed main()
{
	CHECK::check(4321,1234,"a.exe","b.exe");
	// cout<<"Press any key to exit"<<endl;
	// getch();
	return 0;
}
// ----------------------------
// by imzzy