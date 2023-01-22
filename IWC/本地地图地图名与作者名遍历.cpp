#include<bits/stdc++.h>
#include<io.h>
#include<direct.h>
using namespace std;
#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
vector<string> FindAllFileOnCurFolder(string path) {
   _finddata_t file_info;
   int handle=_findfirst((path+"/*.*").c_str(),&file_info); //*/
   if(-1==handle) return {};
   vector<string> Q;
   do {
      string attribute=file_info.name;
      if(!set<string>{".",".."}.count(attribute))
         Q.push_back(file_info.name);
   } while(!_findnext(handle,&file_info));
   _findclose(handle);
   return Q;
}
string Decode(string s) {
   vector<int> Q;string P;
   for(int i=0;i<(int)s.size();++i) {
      Q.push_back(i);
      if(s[i]>>7) i+=2;
   }
   int D=Q.size();
   for(int i=1;i<D/2;i+=2) swap(Q[D-i-1],Q[i]);
   for(int i=0;i<D-2;i+=3) swap(Q[i+2],Q[i]);
   for(int i=0;i<D/2;i+=1) swap(Q[D-i-1],Q[i]);
   for(auto i:Q) {P+=s[i];if(s[i]>>7){P+=s[i+1];P+=s[i+2];}}
   return P;
}
string GetName(string T) {
   string answer;
   for(int i=0;i+7<(int)T.size();++i)
      if(T[i+0]=='\\'&&T[i+1]=='\"'&&T[i+2]=='n'&&T[i+3]=='a'&&T[i+4]=='m'&&T[i+5]=='e'&&T[i+6]=='\\'&&T[i+7]=='\"'&&T[i+8]==':'&&T[i+9]=='\\'&&T[i+10]=='\"') {
            for(int j=i+11;T[j]!='\\'&&T[j]!='\"';++j)
               answer.push_back(T[j]);
            break;
         }
   return answer;
}
string GetAuthor(string T) {
   string answer;
   for(int i=0;i+7<(int)T.size();++i)
      if(T[i+0]=='\\'&&T[i+1]=='\"'&&T[i+2]=='a'&&T[i+3]=='u'&&T[i+4]=='t'&&T[i+5]=='h'&&T[i+6]=='o'&&T[i+7]=='r'&&T[i+8]=='\\'&&T[i+9]=='\"'&&T[i+10]==':'&&T[i+11]=='\\'&&T[i+12]=='\"') {
            for(int j=i+13;T[j]!='\\'&&T[j]!='\"';++j)
               answer.push_back(T[j]);
            break;
         }
   return answer;
}
string GetFromFile(string X) {
   string answer;
   freopen(X.c_str(),"r",stdin);
   getline(cin,answer);
   fclose(stdin);
   return answer;
}
char X[300];
string T;
int main() {
   freopen("output.txt","w",stdout);
   getcwd(X,300);
   for(char i:string(X)) {
      if(i=='\\') T.push_back('/');
      else T.push_back(i);
      if(i==':') T.push_back('/');
   }
   auto Temp=FindAllFileOnCurFolder(T);
   for(auto i:Temp) {
      for(auto Name:FindAllFileOnCurFolder(T+"/"+i)) {
         string Text=Decode(GetFromFile(T+"/"+i+"/"+Name+"/GameInfoData.gid"));
         
         if(Text.size()!=0)
            cout << GetName(Text) << ' ' << GetAuthor(Text) << endl;
      }
   }
   fclose(stdout);
}
