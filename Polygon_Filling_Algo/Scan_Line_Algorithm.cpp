/*
    This code is the property of
    Name:Sourav Saha
    Reg: 2017331095
*/
#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>


using namespace std;


///Defines window size
const int win_h=600,win_w=800;

///This function defines the structure of a point variable
struct PT{

    double x,y;
    PT(){}
    PT(double a,double b)
    {
        x=a;
        y=b;
    }

    bool operator < (const PT &p)const
    {
        return x < p.x;
    }

};

///This method converts the coordinate system from a traditional one to a computer recognized one.
PT convert_pixel(PT p)
{
    p.x+=(double)(win_w/2);
    p.y= p.y*(-1.00);
    p.y+=(double)(win_h/2);

    return p;
}

///This method just draws the desired pixel.
void draw_pixel(PT p,int color)
{
    //delay(1);
    p=convert_pixel(p);
    putpixel((int)(p.x+0.5),(int)(p.y+0.5),color);
}

///This method draws the traditional axis lines on the window.
void draw_axis(int x,int y)
{
    //for drawing x axis
    for(int i=0;i<x;i++)
        putpixel(i,(y/2),WHITE);

    //for drawing y axis
    for(int i=0;i<y;i++)
        putpixel((x/2),i,WHITE);

    return ;
}
///For drawing lines DDA line drawing algorithm is used.
void dda_line_draw(PT a,PT b,int color)
{
    if(a.x>b.x)
            swap(a,b);

    if(a.y==b.y)
    {
        for(int x=a.x;x<=b.x;x++)
            draw_pixel(PT(x,a.y),color);
    }
    else if(a.x==b.x)
    {
        if(a.y>b.y)
            swap(a,b);
        for(int y=a.y;y<=b.y;y++)
            draw_pixel(PT(a.x,y),color);
    }
    else
    {
        double dx=(double)b.x-(double)a.x;
        double dy=(double)b.y-(double)a.y;

        double m=dy/dx;
        double m_inv=dx/dy;

        if((fabs(dx)-fabs(dy))>0.0000001)
        {
            if(a.x>b.x)
                swap(a,b);

            double y= (double)a.y;

            for(int x=a.x;x<=b.x;x++)
            {
              draw_pixel(PT(x,round(y)),color);
              y+=m;
              delay(1);
            }
        }
        else
        {
            if(a.y>b.y)
                swap(a,b);

            double x= (double)a.x;

            for(int y=a.y;y<=b.y;y++)
            {
              draw_pixel(PT(round(x),y),color);
              x+=m_inv;
              delay(1);
            }
        }
    }

    return;
}

///This method is used for drawing polygons.
void draw_Polygon(vector<PT> points)
{
    int sz=points.size();

    for(int i=0;i<sz;i++)
        dda_line_draw(points[i],(points[(i+1)%sz]),YELLOW);

    return;
}

///Structure of an edge in the edgelist
struct EDGE
{
    double y_min,y_max,x_of_y_min,m_inv;
    EDGE()
    {

    }

    EDGE(double a, double b, double c, double d)
    {
        y_min=a;
        y_max=b;
        x_of_y_min=c;
        m_inv=d;
    }
    bool operator < (const EDGE &p)const
    {
        return y_min < p.y_min;
    }
};

///Implementation of the scanline algorithm
void scan_Line(vector<PT> polygon ,int color)
{
    ///create edge list
    vector<EDGE> edges;

    int n=polygon.size();

    double start = 1e9;
    double finish = - 1e9;

    map<double,int> mp;

    for(int i=0;i<n;i++)
    {
        PT a = polygon[i];
        PT b = polygon[(i+1)%n];

        if(a.y == b.y)
            continue;
        EDGE temp;
        temp.y_min = min(a.y,b.y);
        temp.y_max = max(a.y,b.y);
        temp.x_of_y_min = a.y < b.y ? a.x : b.x;
        temp.m_inv = (double)(b.x - a.x) / (double)(b.y - a.y);

        start = min(start, temp.y_min);
        finish = max (finish , temp.y_max);

        mp[temp.y_min]=1;

        edges.push_back(temp);
    }
    ///sort edge list based on ymin

    sort(edges.begin() ,  edges.end() );

    for(int i=0; i<n;i++)
    {
        if(mp[edges[i].y_max]==1)
            edges[i].y_max--;
    }
    ///traverse loop on y

    n=edges.size();

    for(double y=start; y<=finish; y++)
    {
        ///intersecting point calculation
        vector<PT> intersecting_points;

        for(int i=0; i < n; i++)
        {
            if(y>=edges[i].y_min && y<= edges[i].y_max)
            {
                PT sect;

                sect.x = edges[i].x_of_y_min;
                sect.y = y;

                edges[i].x_of_y_min += edges[i].m_inv;
                intersecting_points.push_back(sect);

            }
        }


        ///sort intersecting points
        sort(intersecting_points.begin(),intersecting_points.end());
        ///line draw
        for(int i=0;i<intersecting_points.size()-1;i+=2)
        {
            dda_line_draw(intersecting_points[i],intersecting_points[(i+1)%n],RED);
        }

    }
    return;
}

///For drawing lines DDA line drawing algorithm is used.
int main()
{
    initwindow(win_w,win_h);
    //For drawing axis
    draw_axis(win_w,win_h);

    vector<PT> polygon;

    polygon.push_back(PT(40,35));
    polygon.push_back(PT(100,70));
    polygon.push_back(PT(45,140));
    polygon.push_back(PT(50,180));
    polygon.push_back(PT(-60,100));
    polygon.push_back(PT(-30,-100));

    draw_Polygon(polygon);

    scan_Line(polygon, RED);

    getchar();

    return 0;
}

