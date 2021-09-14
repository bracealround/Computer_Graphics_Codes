#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>


using namespace std;

const int win_h=600,win_w=800;
struct PT{
    int x,y;
    PT(){}
    PT(int a,int b)
    {
        x=a;
        y=b;
    }

};

//This method converts the coordinate system from a traditional one to a computer recognized one.
PT convert_pixel(PT p)
{
    p.x+=(win_w/2);
    p.y= p.y*(-1);
    p.y+=(win_h/2);

    return p;
}

//This method just draws the desired pixel.
void draw_pixel(PT p,int color)
{
    //for drawing pixel
    delay(7);
    p=convert_pixel(p);
    putpixel(p.x,p.y,color);
}

//This method draws the traditional axis lines on the window.
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

void draw_line(PT a, PT b)
{
    if(a.x>b.x)
    {
        swap(a,b);
    }
    if(a.y==b.y)
    {
        for(int x=a.x;x<=b.x;x++)
            draw_pixel(PT(x,a.y),YELLOW);
    }
    else if(a.x==b.x)
    {
        if(a.y>b.y)
            swap(a,b);
        for(int y=a.y;y<=b.y;y++)
            draw_pixel(PT(a.x,y),YELLOW);
    }
    else
    {
        double m= (double)(b.y-a.y)/(double)(b.x-a.x);
        double c=(double)a.y-m*(double)a.x;
        for(int x=a.x;x<=b.x;x++)
        {
            int tmp=m*(double)x+c;
            int y=(int)(tmp+0.5);

            draw_pixel(PT(x,y),YELLOW);
        }
    }
    return ;
}

void draw_Polygon(vector<PT> points)
{
    int sz=points.size();
    for(int i=0;i<sz;i++)
    {
        draw_line(points[i],(points[(i+1)%sz]));
    }
    return;

}

int main()
{
    initwindow(win_w,win_h);
    //For drawing axis
    draw_axis(win_w,win_h);

    /*for(int i=0;i<100;i++)
    {
        delay(30);
        draw_pixel(PT(i,i),YELLOW);
    }*/


    /*PT a = PT(150,-100);
    PT b = PT(0,200);

    draw_line(a,b);*/

    vector<PT> polygon;

    polygon.push_back(PT(0,0));
    polygon.push_back(PT(100,0));
    polygon.push_back(PT(150,150));
    polygon.push_back(PT(100,200));
    polygon.push_back(PT(0,200));
    polygon.push_back(PT(-150,150));

    draw_Polygon(polygon);

    getchar();

    return 0;
}
