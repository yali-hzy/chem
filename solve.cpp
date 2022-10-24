#include<bits/stdc++.h>
using namespace std;
map<string,int>ma,mana;
string name[200],mat[200],ans[200];
vector<string>vec[200],lim[200],exi[200];
int n,m,k,c,edge[200][200][5],edg[200][200][5],e[200][200],vis[200],cnt[200],now;
inline int count(string x)
{
	int len=x.length(),sum=0;
	for(register int i=0;i<len;i++)
		if(x[i]>='A' && x[i]<='Z')
			sum++;
	return sum;
}
inline bool exist(string x,string y)
{
	int xlen=x.length(),ylen=y.length();
	for(register int i=0;i<=xlen-ylen;i++)
	{
		bool flag=0;
		for(register int j=0;j<ylen;j++)
			if(x[i+j]!=y[j])
			{
				flag=1;
				break;
			}
		if(!flag)
			return 1;
	}
	return 0;
}
inline bool pd_sig(string x)
{
	int len=x.length(),sum=0;
	for(register int i=0;i<len;i++)
		if(x[i]>='A' && x[i]<='Z')
			sum++;
	if(sum==1)
		return 1;
	return 0;
}
inline bool pd_O(string x)
{
	int len=x.length(),sum=0,f=0;
	for(register int i=0;i<len;i++)
	{
		if(x[i]>='A' && x[i]<='Z')
			sum++;
		if(x[i]=='O')
			f=1;
	}
	if(sum==2 && f)
		return 1;
	return 0;
}
inline bool pd_H(string x)
{
	if(x=="H2CO3" || x=="HCl" || x=="H2SO4" || x=="H2SO3" || x=="HNO3")
		return 1;
	return 0;
}
inline bool pd_OH(string x)
{
	int len=x.length();
	for(register int i=0;i<len-1;i++)
		if(x[i]=='O' && x[i+1]=='H')
			return 1;
	return 0;
}
inline bool pd_bio(string x)
{
	if(x=="CH4" || x=="C2H5OH" || x=="C6H12O6")
		return 1;
	return 0;
}
inline bool pd_salt(string x)
{
	if(!pd_O(x) && !pd_sig(x) && !pd_H(x) && !pd_OH(x) && !pd_bio(x))
		return 1;
	return 0;
}
inline int pd(string x)
{
	if(pd_sig(x))
		return 1;
	if(pd_O(x))
		return 2;
	if(pd_H(x))
		return 3;
	if(pd_OH(x))
		return 4;
	if(pd_bio(x))
		return 6;
	return 5;
}
inline bool check(int x,string y)
{
	if(cnt[x] && cnt[x]!=count(y))
		return 0;
	if(exi[x].size())
	{
		bool flag=0;
		for(register int i=0;i<(int)exi[x].size();i++)
			if(exist(y,exi[x][i]))
			{
				flag=1;
				break;
			}
		if(!flag)
			return 0;
	}
	for(register int i=1;i<x;i++)
		for(register int j=1;j<=2;j++)
			if(edg[i][x][j] && edg[i][x][j]!=edge[ma[ans[i]]][ma[y]][j] || edg[x][i][j] && edg[x][i][j]!=edge[ma[y]][ma[ans[i]]][j] || e[i][x]==1 && pd(ans[i])!=pd(y) || e[i][x]==-1 && pd(ans[i])==pd(y))
				return 0;
	return 1;
}
inline bool ok()
{
	for(register int i=1;i<=now;i++)
	{
		map<string,int>a;
		for(register int j=1;j<lim[i].size();j++)
		{
			string s="";
			for(register int k=0;k<ans[mana[lim[i][j]]].length();k++)
			{
				if(ans[mana[lim[i][j]]][k]>='A' && ans[mana[lim[i][j]]][k]<='Z')
				{
					if(s!="")
						a[s]++;
					s="";
					s+=ans[mana[lim[i][j]]][k];
				}
				if(ans[mana[lim[i][j]]][k]>='a' && ans[mana[lim[i][j]]][k]<='z')
					s+=ans[mana[lim[i][j]]][k];
			}
			if(s!="")
				a[s]++;
		}
		string s="";
		bool flag=0;
		for(register int j=0;j<ans[mana[lim[i][0]]].length();j++)
		{
			if(ans[mana[lim[i][0]]][j]>='A' && ans[mana[lim[i][0]]][j]<='Z')
			{
				if(s!="" && a[s]==lim[i].size()-1)
					flag=1;
				s="";
				s+=ans[mana[lim[i][0]]][j];
			}
			if(ans[mana[lim[i][0]]][j]>='a' && ans[mana[lim[i][0]]][j]<='z')
				s+=ans[mana[lim[i][0]]][j];
		}
		if(s!="" && a[s]==lim[i].size()-1)
			flag=1;
		if(!flag)
			return 0;
	}
	return 1;
}
void dfs(int x)
{
	if(x>n)
	{
		if(!ok())
			return; 
		for(register int i=1;i<=n;i++)
			cout<<name[i]<<"="<<ans[i]<<endl;
		puts("");
		return;
	}
	if(vec[x].size())
		for(register int i=0;i<vec[x].size();i++)
		{
			if(!vis[ma[vec[x][i]]] && check(x,vec[x][i]))
			{
				vis[ma[vec[x][i]]]=1;
				ans[x]=vec[x][i];
				dfs(x+1);
				vis[ma[vec[x][i]]]=0;
			}
		}
	else
		for(register int i=1;i<=104;i++)
			if(!vis[i] && check(x,mat[i]))
			{
				vis[i]=1;
				ans[x]=mat[i];
				dfs(x+1);
				vis[i]=0;
			}
}
int main()
{
	freopen("material.txt","r",stdin);
	for(int i=1;;i++)
	{
		string s;
		if(feof(stdin))
			break;
		cin>>s;
		ma[s]=i;
		mat[i]=s;
	}
	fclose(stdin);
	cin.clear();
	freopen("equation.txt","r",stdin);
	for(;;)
	{
		string s;
		getline(cin,s);
		if(feof(stdin))
			break;
		vector<string>vec,vec1;
		int len=s.length();
		bool flag=0;
		string s1="";
		for(register int i=0;i<len;i++)
		{
			if(s[i]!=' ' && s[i]!='+' && s[i]!='-' && s[i]!='>')
				s1+=s[i];
			if(s[i]==' ' && s1!="")
			{
				if(!flag)
					vec.push_back(s1);
				else
					vec1.push_back(s1);
				s1="";
			}
			if(s[i]=='-' || s[i]=='>')
				flag=1;
		}
		vec1.push_back(s1);
		for(register int i=0;i<vec.size();i++)
			for(register int j=0;j<vec.size();j++)
				edge[ma[vec[i]]][ma[vec[j]]][2]=1;
		for(register int i=0;i<vec.size();i++)
			for(register int j=0;j<vec1.size();j++)
				edge[ma[vec[i]]][ma[vec1[j]]][1]=1;
	}
	fclose(stdin);
	cin.clear();
	freopen("prob.txt","r",stdin);
	freopen("solution.txt","w",stdout);
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++)
	{
		cin>>name[i];
		mana[name[i]]=i;
	}
	for(register int i=1;i<=m;i++)
	{
		string x,y;
		int t,z;
		cin>>t;
		if(t==1)
		{
			cin>>x>>y>>z;
			edg[mana[x]][mana[y]][z]=1;
		}
		if(t==2)
		{
			cin>>x>>y;
			vec[mana[x]].push_back(y);
		}
		if(t==3)
		{
			cin>>x>>y>>z;
			e[mana[x]][mana[y]]=z;
			e[mana[y]][mana[x]]=z;
		}
		if(t==4)
		{
			cin>>x>>z;
			cnt[mana[x]]=z;
		}
		if(t==5)
		{
			cin>>z;
			++now;
			for(register int j=1;j<=z;j++)
			{
				string s;
				cin>>s;
				lim[now].push_back(s);
			}
		}
		if(t==6)
		{
			cin>>x>>y;
			exi[mana[x]].push_back(y);
		}
	}
	dfs(1);
	return 0;
}
