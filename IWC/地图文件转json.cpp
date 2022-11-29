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
