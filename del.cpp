#include<bits/stdc++.h>
using namespace std;
map<string,bool>p;
string s;
int main()
{
    for(;;)
    {
        getline(cin,s);
        if(feof(stdin))
            return 0;
        if(!p[s])
        {
            cout<<s<<endl;
            p[s]=1;
        }
    }
    return 0;
}
