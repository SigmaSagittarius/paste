namespace iw {
   struct Frac {int a,b;};
   struct Kid  {Frac Speed,Pos;};
   int sign(Frac a){return a.a==0?0:a.a*a.b<0?-1:1;}
   Frac operator +(Frac a,Frac b) {Frac c={a.a*b.b+b.a*a.b,a.b*b.b};return {c.a/__gcd(c.a,c.b),c.b/__gcd(c.a,c.b)};}
   Frac operator -(Frac a,Frac b) {Frac c={a.a*b.b-b.a*a.b,a.b*b.b};return {c.a/__gcd(c.a,c.b),c.b/__gcd(c.a,c.b)};}
   Frac operator *(Frac a,Frac b) {Frac c={a.a*b.a,a.b*b.b};return {c.a/__gcd(c.a,c.b),c.b/__gcd(c.a,c.b)};}
   bool operator >(Frac a,Frac b) {if(sign(a)^sign(b))return sign(a)>sign(b);return (sign(a)==-1)^(a.a*b.b>b.a*a.b);}
   double Double(Frac a) {return double(a.a)/a.b;}
   void show(Kid x) {cerr << fixed << setprecision(10) << "Pos:" << Double(x.Pos) << " Speed:" << Double(x.Speed) << endl;}
   Kid next(Kid x) {
      Kid y={x.Speed+Frac{2,5},x.Pos+x.Speed+Frac{2,5}};
      return ((Frac{1,2}>y.Pos)?y:Kid{Frac{0,1},x.Pos-Frac{(x.Pos-Frac{1,2}).a/(x.Pos-Frac{1,2}).b,1}});
   }
   Kid cancle(Kid x) {
      if(x.Speed>Frac{0,1})return next(x);
      Kid y={x.Speed*Frac{9,20}+Frac{2,5},x.Pos+x.Speed*Frac{9,20}+Frac{2,5}};
      return ((Frac{1,2}>y.Pos)?y:Kid{Frac{0,1},x.Pos-Frac{(x.Pos-Frac{1,2}).a/(x.Pos-Frac{1,2}).b,1}});
   }
}
/*
使用了两个 int 拼出来的实数，比较平庸，但是计算速度应该会比用 double 和 eps 1e-9 的快一点。
可以考虑计算出可能的最大 gcd，随后使用类似定点数的东西。
*/
