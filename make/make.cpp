#include<bits/stdc++.h>

namespace RAND
{
#define ll long long
	ll seed,res;
	inline ll init() {return seed=time(NULL)+1201LL;}
	inline ll random()
	{
		try
		{
			res=time(NULL)+seed;
			res*=seed;
			res+=time(NULL)*1201201LL;
			seed=res%1201201201LL+201LL;
		}
		catch(...)
		{
			std::cout<<"Err: runtime error in \'random\'"<<endl;
			exit(-1201);
		}
		return res;
	}
	inline ll random(const ll mx) {return random()%mx+1LL;}
	inline ll random(const ll mn,const ll mx) {return random(mx-mn+1LL)+mn-1LL;}
#undef ll
}

namespace MAKE
{
	string script,testFile;
	FILE *fp;
	int init(const char f[])
	{
		script=a,testFile=b;
		
	}
}

int init(const char f[])
{
	if(RAND::init()<0) return -2;
	return MAKE::init(f);
}

int t;
signed main(int argc,char* argv[])
{
	if(argc<2)
	{
		std::cout<<"Err: File name missing"<<endl;
		return -1;
	}
	t=init(argv[1])
	if(t)
	{
		switch(t)
		{
			case -2: std::cout<<"Err: random seed error"<<endl; break;
			case -3: std::cout<<"Err: cannot open the script"<<endl; break;
			case -4: std::cout<<"Err: cannot write into the test file"<<endl; break;
			default: std::cout<<"Err: Unknown error while initialization with exit code "<<t<<endl;
		}
		return t;
	}
	
	return 0;
}
// ----------------------------
// by imzzy