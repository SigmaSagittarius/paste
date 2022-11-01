namespace iwbtc {
   struct Frac {long long a,b;};
   struct Kid  {Frac speed,pos;};
   int sign(Frac a){return a.a==0?0:a.a*a.b<0?-1:1;}
   Frac operator +(Frac a,Frac b) {Frac c={a.a*b.b+b.a*a.b,a.b*b.b};return {c.a/__gcd(c.a,c.b),c.b/__gcd(c.a,c.b)};}
   Frac operator -(Frac a,Frac b) {Frac c={a.a*b.b-b.a*a.b,a.b*b.b};return {c.a/__gcd(c.a,c.b),c.b/__gcd(c.a,c.b)};}
   Frac operator *(Frac a,Frac b) {Frac c={a.a*b.a,a.b*b.b};return {c.a/__gcd(c.a,c.b),c.b/__gcd(c.a,c.b)};}
   bool operator >(Frac a,Frac b) {if(sign(a)^sign(b))return sign(a)>sign(b);return (sign(a)==-1)^(abs(a.a*b.b)>abs(b.a*a.b));}
   double Double(Frac a) {return double(a.a)/a.b;}
   void show(Kid x)  {cerr << fixed << setprecision(10) << "pos:" << Double(x.pos) << " speed:" << Double(x.speed) << endl;}
   Kid next(Kid x)   {x.speed=x.speed-Frac{29,100};if(Frac{-829,100}>x.speed)x.speed=Frac{-829,100};x.pos=x.pos+(x.speed*Frac{1,50});return x;}
   Kid cancle(Kid x) {if(x.speed>Frac{0,1}) x.speed=x.speed*Frac{9,20};return x;}
}
