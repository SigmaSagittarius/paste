namespace NTT {
   int a[131073],b[131073],r[131073],limit;
   long long power(long long b,long long n) {
	   long long s=1;
	   while(n) {
		   if(n%2==1)
		      s=s*b%998244353;
		   b=b*b%998244353;
		   n/=2;
	   }
	   return s;
   }
   void NTT(int *a,int type) {
      for(int i=0;i<limit;++i)
         if(i<r[i]) swap(a[i],a[r[i]]);
      for(int mid=1;mid<limit;mid<<=1) {
         int wn=power(type==1?3:332748118,998244352/(mid<<1));
         for(int j=0;j<limit;j+=mid<<1) {
            long long w=1;
            for(int k=0;k<mid;++k) {
               int x=a[j+k],y=w*a[j+k+mid]%998244353;
               a[j+k]=x+y>=998244353?x+y-998244353:x+y;
               a[j+k+mid]=x<y?x-y+998244353:x-y;
               w=w*wn%998244353;
            }
         }
      }
   }
   void mul(int n,int m) {
      for(int i=0;i<limit;++i) a[i]=b[i]=r[i]=0;
      limit=1;int l=0;
      while(limit<=n+m) {
         limit<<=1;
         ++l;
      }
      for(int i=0;i<limit;++i)
         r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
      NTT(a,1);NTT(b,1);
      for(int i=0;i<limit;++i) a[i]=(long long)a[i]*b[i]%998244353;
      NTT(a,-1);
      long long inv=power(limit,998244351);
      for(int i=0;i<=n+m;++i)
         a[i]=inv*a[i]%998244353;
   }
};
namespace PollardsRho {
   long long gcd(long long a,long long b) {
      if(b==0) return a;
      return gcd(b,a%b);
   }
   long long power(long long x,long long p,long long mod) {
      long long answer=1;
      while(p) {
         if(p&1) answer=(__int128)answer*x%mod;
         x=(__int128)x*x%mod;
         p>>=1;
      }
      return answer;
   }
   long long MillerRabin(long long x,long long b) {
      long long k=x-1;
      while(k) {
         long long cur=power(b,k,x);
         if(cur!=1&&cur!=x-1) return false;
         if((k&1)==1||cur==x-1) return true;
         k>>=1;
      }
      return true;
   }
   bool Prime(long long x) {
      if(x==46856248255981ll||x<2) return false;
      if(x==2||x==3||x==7||x==61||x==24251) return true;
      return MillerRabin(x,2)&&MillerRabin(x,61);
   }
   long long PR(long long x) {
      long long y=1ll*rand()*rand()%x+1,v0=1ll*rand()*rand()%(x-1)+1,v=v0,d,s=1;
      int t=0,k=1;
      while(1) {
         v=((__int128)v*v+y)%x;
         s=(__int128)s*(max(v,v0)-min(v,v0))%x;
         if(v==v0||!s) return x;
         if(++t==k) {
            if((d=gcd(s,x))^1)return d;
            v0=v,k<<=1;
         }
      }
   }
   long long NonTrivialFact(long long x) {
      if(Prime(x)) return -1;
      long long answer=1;
      while(answer==1||answer==x) answer=PR(x);
      return answer;
   }
   vector<long long> Temp;
   void dfs(long long x) {
      if(Prime(x)) {
         Temp.push_back(x);
         return;
      }
      long long t=NonTrivialFact(x);
      dfs(t);dfs(x/t);
   }
   vector<long long> PrimeFacList(long long x) {
      Temp.clear();
      dfs(x);
      return Temp;
   }
};
class STT {
   public:
   vector<int> MX[22];
   void init(vector<int> x) {
      for(int i=0;i<=21;++i) MX[i].resize(x.size()+1);
      for(int i=0;i<(int)x.size();++i) MX[0][i+1]=x[i];
      for(int j=1;j<=21;++j)
         for(int i=1;i+(1<<j)-1<=(int)x.size();++i)
            MX[j][i]=max(MX[j-1][i],MX[j-1][i+(1<<(j-1))]);
   }
   int Query(int l,int r) {
      int k=log2(r-l+1); 
      return max(MX[k][l],MX[k][r-(1<<k)+1]);
   }
};
class dsu {
   public:
   vector<int> d;
   void init(int n) {d.resize(n+1);for(int i=1;i<=n;++i) d[i]=i;}
   int getfa(int x) {return d[x]=getfa(d[x]);}
   void merge(int x,int y) {d[getfa(x)]=getfa(y);}
};
long long power(long long b,long long n) {
	long long s=1;
	while(n) {
		if(n%2==1)s=s*b%MOD;
		b=b*b%MOD;
		n/=2;
	}
	return s;
}
namespace Fact {
   vector<char> isPrime;
	vector<int> Prime,OneFac;
	void GetPrime(int n) {
	   for(int i=0;i<n;++i) isPrime[i]=1;
		isPrime[1]=1;
		for(int i=2;i<=n;i++) {
			if(isPrime[i])Prime.push_back(i);
			for(int j:Prime) {
			   if(i*j>n) break;
				isPrime[i*j]=0;
				OneFac[i*j]=j;
				if(i%j==0)break;
			}
		}
	}
	vector<int>dfs_out;
	vector<pair<int,int>>dfs_in;
	void Fac_dfs(int x,int y) {
		if(x==(long long)(dfs_in.size())) {
			dfs_out.push_back(y);
			return;
		}
		int k=1;
		for(int i=0; i<=dfs_in[x].second; ++i) {
			Fac_dfs(x+1,y*k);
			k*=dfs_in[x].first;
		}
	}
	vector<pair<int,int>>Get_Prime_Fac(int a) {
		vector<pair<int,int>>answer;
		if(isPrime[a])return(vector<pair<int,int>> {pair<int,int>{a,1}});
		answer.push_back({OneFac[a],1});
		a/=OneFac[a];
		while(!isPrime[a]) {
			if(OneFac[a]==answer.back().first)answer.back().second++;
			else answer.push_back({OneFac[a],1});
			a/=OneFac[a];
		}
		if(a==answer.back().first)answer.back().second++;
		else answer.push_back({a,1});
		return(answer);
	}
	vector<int>Get_Fac_List(int a) {
		dfs_out.clear();
		dfs_in=Get_Prime_Fac(a);
		Fac_dfs(0,1);
		return(dfs_out);
	}
	void init(int n) {
	   isPrime.resize(n+2);
	   OneFac.resize(n+2);
		GetPrime(n);
	}
	void init() {
	   init(10000005);
	}
};
int isqrt(int x) {
   int a=x,b=(x+1)/2;
   while(a>b) {
      a=b;
      b=(b+x/b)/2;
   }
   return a;
}
namespace combi {
	long long MOD;
	vector<long long> fac,inv,finv;
	int C(long long x,long long y) {
		if(x<0||y>x)return(0);
		return(fac[x]*finv[y]%MOD*finv[x-y]%MOD);
	}
	long long power(long long b,long long n) {
		long long s=1;
		while(n) {
			if(n%2==1)s=s*b%MOD;
			b=b*b%MOD;
			n/=2;
		}
		return s;
	}
	void init(int n,long long mod) {
	  fac.resize(n+1);inv.resize(n+1);finv.resize(n+1);
	  MOD=mod;
		fac[0]=inv[0]=inv[1]=finv[0]=finv[1]=1;
		for(long long i=1;i<=n;++i)fac[i]=fac[i-1]*i%MOD;
		for(long long i=2;i<=n;++i)inv[i]=MOD-MOD/i*inv[MOD%i]%MOD;
		for(long long i=2;i<=n;++i)finv[i]=finv[i-1]*inv[i]%MOD;
	}
	void init(long long mod) {init(1000010,mod);}
	long long gcd(long long a,long long b) {if(b==0) return a;return gcd(b,a%b);}
	long long lcm(long long a,long long b) {return a/gcd(a,b)*b;}
	long long Inv(int x) {return power(x,MOD-2);}
};
