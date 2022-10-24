#include<bits/stdc++.h>
using namespace std;
map<string,int>ma;
string mel[15]={"K","Ca","Na","Mg","Al","Zn","Fe","Cu","Ag","Ba","NH4"},H[6]={"CO3","SO4","Cl","NO3","HCO3","SO3"};
vector<int>ji[1000];
int n,m;
inline void jia()
{
	ji[ma["SO3"]].push_back(-2);
	ji[ma["H"]].push_back(1);
	ji[ma["HCO3"]].push_back(-1);
	ji[ma["K"]].push_back(1);
	ji[ma["Ca"]].push_back(2);
	ji[ma["Na"]].push_back(1);
	ji[ma["Mg"]].push_back(2);
	ji[ma["Al"]].push_back(3);
	ji[ma["Zn"]].push_back(2);
	ji[ma["Fe"]].push_back(2);
	ji[ma["Fe"]].push_back(3);
	ji[ma["H"]].push_back(1);
	ji[ma["Cu"]].push_back(2);
	ji[ma["Ag"]].push_back(1);
	ji[ma["CO3"]].push_back(-2);
	ji[ma["SO4"]].push_back(-2);
	ji[ma["Cl"]].push_back(-1);
	ji[ma["NO3"]].push_back(-1);
	ji[ma["OH"]].push_back(-1);
	ji[ma["NH4"]].push_back(1);
	ji[ma["Ba"]].push_back(2);
	ji[ma["O"]].push_back(-2);
}
inline int gcd(int x,int y)
{
	if(x%y==0)
		return y;
	return gcd(y,x%y);
}
inline string sauce(string x)
{
	string ans="H";
	if(ji[ma[x]][0]!=-1)
		ans+=(abs(ji[ma[x]][0])+48);
	ans+=x;
	return ans;
}
inline string jian(string x,int xx)
{
	if(x=="NH4")
		return "NH3.H2O";
	string ans=x;
	if(xx==1)
	{
		ans+="OH";
		return ans;
	}
	else
	{
		ans+="(OH)";
		ans+=(xx+48);
		return ans;
	}
}
inline string salt(string x,string y,int xx,int yy)
{
	string ans="";
	int g=gcd(xx,yy);
	xx/=g;
	yy/=g;
	if(yy>1)
	{
		if(x!="NH4")
			ans+=x;
		else
			ans+="(NH4)";
		ans+=yy+48;
	}
	else
		ans+=x;
	if(xx>1)
	{
		if(y=="Cl")
			ans+="Cl";
		else
		{
			ans+='(';
			ans+=y;
			ans+=')';
		}
		ans+=xx+48;
	}
	else
		ans+=y;
	return ans;
}
inline bool possible(string x,string y,int xx)
{
	if(x=="Al" && y=="CO3" || x=="Fe" && y=="CO3" && xx==3 || x=="Cu" && y=="CO3" || x=="Ag" && y=="OH")
		return 0;
	return 1;
}
inline bool float_jian(string x)
{
	if(x=="Mg" || x=="Al" || x=="Fe" || x=="Cu" || x=="Zn")
		return 0;
	return 1;
}
inline bool float_salt(string x,string y)
{
	if(x=="K" || x=="Na" || x=="NH4")
		return 1;
	if(y=="NO3" || y=="HCO3")
		return 1;
	if(x=="Ba" && y=="SO4")
		return 0;
	if(x=="Ag" && y=="Cl")
		return 0;
	if(y=="CO3")
		return 0;
	return 1;
}
int main()
{
	freopen("element.txt","r",stdin);
	for(int i=0;;i++)
	{
		string s;
		if(feof(stdin))
			break;
		cin>>s;
		ma[s]=i;
	}
	fclose(stdin);
	jia();
	freopen("cache.txt","w",stdout);
	for(register int i=3;i<8;i++)
		for(register int j=i+1;j<=8;j++)
			for(register int k=1;k<4;k++)
				if(possible(mel[j],H[k],ji[ma[mel[j]]][0]) && float_salt(mel[j],H[k]))
				{
					string ans="";
					ans+=mel[i];
					ans+=" + ";
					ans+=salt(mel[j],H[k],ji[ma[mel[j]]][0],-ji[ma[H[k]]][0]);
					ans+=" -> ";
					ans+=salt(mel[i],H[k],ji[ma[mel[i]]][0],-ji[ma[H[k]]][0]);
					ans+=" + ";
					ans+=mel[j];
					cout<<ans<<endl;
				}
	return 0;
}
