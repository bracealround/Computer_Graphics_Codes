/*
    This code is the property of:
    Name: Sourav Saha
    Reg: 2017331095
*/

#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>


using namespace std;

const int win_h=600,win_w=800;

///Structure of a point
struct PT{

    double x,y;
    PT(){}
    PT(double a,double b)
    {
        x=a;
        y=b;
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
    //for drawing pixel
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
///This method implements bressenhams line drawing algorithm
void bressenham_line_draw(PT a , PT b, int color)
{
    if(a.x>b.x)
        swap(a,b);

    double m= (b.y-a.y)/(b.x-a.x);
    double dy = b.y-a.y;
    double dx = b.x-a.x;
    if(a.x==b.x)
    {
        if(a.y>b.y)
            swap(a,b);
        for(int y=a.y;y<=b.y;y++)
            draw_pixel(PT(a.x,y),color);
    }
    else if(a.y==b.y)
    {
        for(int x=a.x;x<=b.x;x++)
            draw_pixel(PT(x,a.y),color);
    }
    else if(m>0 && m<1)
    {
        double decision_parameter = 2 * dy -dx;
        int y= a.y;
        for(int x=a.x;x<=b.x;x++)
        {
            if(decision_parameter>0)
            {
                y++;
                decision_parameter = decision_parameter + 2*(dy-dx);
            }
            else
            {
                decision_parameter = decision_parameter + 2*dy;
            }
            draw_pixel(PT(x,y),color);
        }
    }
    else if(m>1)
    {
        if(a.y>b.y)
            swap(a,b);
        double decision_parameter = 2 * dx -dy;
        int x= a.x;
        for(int y=a.y;y<=b.y;y++)
        {
            if(decision_parameter>0)
            {
                x++;
                decision_parameter = decision_parameter + 2*(dx-dy);
            }
            else
            {
                decision_parameter = decision_parameter + 2*dx;
            }
            draw_pixel(PT(x,y),color);
        }
    }
    else if(m > -1.00)
    {
        double decision_parameter = 2 * dy + dx;
        int y= a.y;
        for(int x=a.x;x<=b.x;x++)
        {
            if(decision_parameter>0)
            {
                decision_parameter = decision_parameter + 2*dy;
            }
            else
            {
                y--;
                decision_parameter = decision_parameter + 2*(dy+dx);
            }
            draw_pixel(PT(x,y),YELLOW);

        }
    }
    else
    {
        if(a.y>b.y)
            swap(a,b);
        double decision_parameter = 2 * dx +dy;
        int x= a.x;
        for(int y=a.y;y<=b.y;y++)
        {
            if(decision_parameter>0)
            {

                x--;
                decision_parameter = decision_parameter + 2*dx;
            }
            else
            {

                decision_parameter = decision_parameter + 2*(dx+dy);
            }
            draw_pixel(PT(x,y),YELLOW);
        }
    }
    return;
}
///This method DDA line drawing algorithm
void dda_line_draw(PT a, PT b,int color)
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
              delay(10);
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
              delay(10);
            }
        }
    }

    return;
}

///This method draws the polygon
void draw_Polygon(vector<PT> points)
{
    int sz=points.size();

    for(int i=0;i<sz;i++)
        bressenham_line_draw(points[i],(points[(i+1)%sz]),YELLOW);

    return;

}

///This is where it all begins. Let the show begin.
int main()
{
    initwindow(win_w,win_h);
    //For drawing axis
    draw_axis(win_w,win_h);
    PT a,b;
    a.x=50;
    a.y=75;
    b.x=-130;
    b.y=255;

    bressenham_line_draw(PT(a),PT(b),YELLOW);

    ///Draw the polygon to check all the states of m.
    /*vector<PT> polygon;

    polygon.push_back(PT(0,0));
    polygon.push_back(PT(100,0));
    polygon.push_back(PT(150,150));
    polygon.push_back(PT(100,200));
    polygon.push_back(PT(0,200));
    polygon.push_back(PT(-150,150));

    draw_Polygon(polygon);*/
    getchar();

    return 0;
}
