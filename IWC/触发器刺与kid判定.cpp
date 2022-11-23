#include<bits/stdc++.h>
using namespace std;
struct Circle{double x,y,r;};
struct Line{double x1,y1,x2,y2;};
struct Kid{double x,y,speed;};
struct Needle{double x,y;char v;};
vector<Needle> needle;
double sqr(double x){return x*x;}

bool Circle_Line(Circle a,Line b) {
   double d1=(b.x2-b.x1)*(a.x-b.x1)+(b.y2-b.y1)*(a.y-b.y1);
   if(d1<=0) return sqrt(sqr(a.x-b.x1)+sqr(a.y-b.y1))<=a.r;
   double d2 =sqr(b.x2-b.x1)+sqr(b.y2-b.y1);
   if(d1>=d2) return sqrt(sqr(a.x-b.x2)+sqr(a.y-b.y2))<=a.r;
   double x=b.x1+(b.x2-b.x1)*d1/d2;
   double y=b.y1+(b.y2-b.y1)*d1/d2;
   return sqrt(sqr(a.x-x)+sqr(y-a.y))<=a.r;
}
bool Circle_Circle(Circle a,Circle b) {
   return sqr(a.x-b.x)+sqr(a.y-b.y)<=sqr(a.r+b.r);
}
bool Line_Line(Line a,Line b) {
   return 
   max(a.x1,a.x2)>=min(b.x1,b.x2)&&
   min(a.x1,a.x2)<=max(b.x1,b.x2)&&
   max(a.y1,a.y2)>=min(b.y1,b.y2)&&
   min(a.y1,a.y2)<=max(b.y1,b.y2)&&
   ((b.x1-a.x1)*(a.y2-a.y1)-(b.y1-a.y1)*(a.x2-a.x1))*((b.x2-a.x1)*(a.y2-a.y1)-(b.y2-a.y1)*(a.x2-a.x1))<=0&&
   ((a.x1-b.x1)*(b.y2-b.y1)-(a.y1-b.y1)*(b.x2-b.x1))*((a.x2-b.x1)*(b.y2-b.y1)-(a.y2-b.y1)*(b.x2-b.x1))<=0;
}
bool Kid_Line(Kid a,Line b) {
   bool flag=false;
   flag|=Circle_Line({a.x+0.04375,a.y-0.245,0.045},b);
   flag|=Circle_Line({a.x-0.04375,a.y-0.245,0.045},b);
   flag|=Circle_Line({a.x+0.04375,a.y-0.08,0.045},b);
   flag|=Circle_Line({a.x-0.04375,a.y-0.08,0.045},b);
   flag|=Line_Line({a.x-0.08875,a.y-0.245,a.x-0.08875,a.y+0.08},b);
   flag|=Line_Line({a.x+0.08875,a.y-0.245,a.x+0.08875,a.y+0.08},b);
   flag|=Line_Line({a.x-0.04375,a.y+0.125,a.x+0.04375,a.y+0.125},b);
   flag|=Line_Line({a.x-0.04375,a.y-0.29,a.x+0.04375,a.y-0.29},b);
   return flag;
}
bool Kid_Circle(Kid a,Circle b) {
   bool flag=false;
   flag|=Circle_Circle({a.x+0.04375,a.y-0.245,0.045},b);
   flag|=Circle_Circle({a.x-0.04375,a.y-0.245,0.045},b);
   flag|=Circle_Circle({a.x+0.04375,a.y-0.08,0.045},b);
   flag|=Circle_Circle({a.x-0.04375,a.y-0.08,0.045},b);
   flag|=Circle_Line(b,{a.x-0.08875,a.y-0.245,a.x-0.08875,a.y+0.08});
   flag|=Circle_Line(b,{a.x+0.08875,a.y-0.245,a.x+0.08875,a.y+0.08});
   flag|=Circle_Line(b,{a.x-0.04375,a.y+0.125,a.x+0.04375,a.y+0.125});
   flag|=Circle_Line(b,{a.x-0.04375,a.y-0.29,a.x+0.04375,a.y-0.29});
   return flag;
}
bool Kid_Needle(Kid a,Needle b) {
   if(b.v=='U') {
      if(Kid_Circle(a,{b.x-0.3,b.y-0.3,0.005})) return true;
      if(Kid_Circle(a,{b.x    ,b.y+0.3,0.005})) return true;
      if(Kid_Circle(a,{b.x+0.3,b.y-0.3,0.005})) return true;
      if(Kid_Line(a,{b.x-0.3-sqrt(5)/500,b.y-0.3+sqrt(5)/1000,b.x-sqrt(5)/500,b.y+0.3+sqrt(5)/1000}))  return true;
      if(Kid_Line(a,{b.x+sqrt(5)/500,b.y+0.3+sqrt(5)/10003,b.x+0.3+sqrt(5)/500,b.y-0.3+sqrt(5)/1000})) return true;
      if(Kid_Line(a,{b.x-0.3,b.y-0.305,b.x+0.3,b.y-0.305})) return true;
   }
   if(b.v=='D') {
      if(Kid_Circle(a,{b.x-0.3,b.y+0.3,0.005})) return true;
      if(Kid_Circle(a,{b.x    ,b.y-0.3,0.005})) return true;
      if(Kid_Circle(a,{b.x+0.3,b.y+0.3,0.005})) return true;
      if(Kid_Line(a,{b.x-0.3-sqrt(5)/500,b.y-0.3-sqrt(5)/1000,b.x-sqrt(5)/500,b.y-0.3-sqrt(5)/1000}))  return true;
      if(Kid_Line(a,{b.x+sqrt(5)/500,b.y-0.3-sqrt(5)/10003,b.x+0.3+sqrt(5)/500,b.y+0.3-sqrt(5)/1000})) return true;
      if(Kid_Line(a,{b.x-0.3,b.y+0.305,b.x+0.3,b.y+0.305})) return true;
   }
   
   return false;
}
signed main() {
   cout << Kid_Needle({0.265,-0.007},{0.64,0,'U'}) << endl;
}
