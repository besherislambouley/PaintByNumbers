    #define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
    #include <bits/stdc++.h>
    using namespace std;
    #define sqr 200
    #define mid (l+r)/2
    #define pb push_back
    #define ppb pop_back
    #define fi first
    #define se second
    #define lb lower_bound
    #define ub upper_bound
    #define ins insert
    #define era erase
    #define C continue
    #define mem(dp,i) memset(dp,i,sizeof(dp))
    #define mset multiset
    typedef long long ll;
    typedef short int si;
    typedef long double ld;
    typedef pair<int,int> pi;
    typedef pair<ll,ll> pll;
    typedef vector<int> vi;
    typedef vector<ll> vll;
    typedef vector<pi> vpi;
    typedef vector<pll> vpll;
    const ll mod=1e9+7;
    const ll inf= 4e18;
    const ld pai=acos(-1);
    #include "paint.h"
    #include <cstdlib>
    int n ,k ;
    string s;
    int a[200009];
    int bs[200009];
    int yes[200009][2];
    int dp[200009][109];
    void upd(int l,int r,int t){
            yes[l][t]++;
            yes[r+1][t]--;
    }
    int sum(int l,int r){
            if ( l>r || r>=n )return -1;
            int x=bs[r];
            if(l)x-=bs[l-1];
            return x;
    }
    int bt(int id,int crnt){
            if(id==n)return (crnt==k);
            int &ret=dp[id][crnt];
            if(ret!=-1) return ret;
            ret=0;
            if(s[id]=='_'){
                    ret=bt(id+1,crnt);
            }
            if(s[id]=='.'){
                    ret=bt(id+1,crnt);
                    if(ret>0)upd(id,id,0);
                    int z=1;
                    if(crnt<k){
                            int l=id,r=id+a[crnt]-1;
                            int Sum=sum(l,r);
                            if(Sum!=a[crnt]) z=0;
                            if(r+1<n && s[r+1]=='X') z=0;
                            if(z){
                                    z=bt(min(r+2,n),crnt+1);
                                    if(z){
                                            upd(l,r,1);
                                            upd(r+1,r+1,0);
                                    }
                            }
                            ret=max(ret,z);
                    }
            }
            if(s[id]=='X' && crnt<k){
                    int l=id,r=id+a[crnt]-1;
                    int Sum=sum(l,r);
                    if(Sum!=a[crnt])return ret=0;
                    if(r+1<n && s[r+1]=='X') return ret=0;
                    ret=bt( min(r+2,n) ,crnt+1);
                    if(ret){
                            upd(l,r,1);
                            upd(r+1,r+1,0);
                    }
            }
            else if(s[id]=='X')return ret=0;
            return ret;
    }
    string solve_puzzle(string S , vector<int> c) {
            mem(dp,-1);
            s=S;
            n=S.size();
            k=c.size();
            for(int i=0;i<n;i++){
                    bs[i]=(s[i]!='_');
                    if(i)bs[i]+=bs[i-1];
            }
            for(int i=0;i<k;i++)a[i]=c[i];
            bt(0,0);
            for(int i=1;i<n;i++){
                    for(int j=0;j<2;j++){
                            yes[i][j]+=yes[i-1][j];
                    }
            }
            string ans="";
            for(int i=0;i<n;i++){
                    if(s[i]!='.'){
                            ans+=s[i];
                            C;
                    }
                    if(yes[i][0] && yes[i][1])ans+='?';
                    else if(yes[i][0])ans+='_';
                    else ans+='X';
            }
            return ans;
    }
