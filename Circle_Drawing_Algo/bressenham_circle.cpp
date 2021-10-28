#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>


using namespace std;

const int win_h=600,win_w=800;

///Structure of a point
struct PT{

    int x,y;
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
    delay(1);
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

///This function draws all the mirror points to form a circle
void mirror_point_draw(PT center, PT a)
{
    draw_pixel(PT(a.x + center.x, a.y + center.y),YELLOW);
    draw_pixel(PT(-a.x + center.x, a.y + center.y),YELLOW);
    draw_pixel(PT(a.x + center.x, -a.y + center.y),YELLOW);
    draw_pixel(PT(-a.x + center.x, -a.y + center.y),YELLOW);
    draw_pixel(PT(a.y + center.x, a.x + center.y),YELLOW);
    draw_pixel(PT(-a.y + center.x, a.x + center.y),YELLOW);
    draw_pixel(PT(a.y + center.x, -a.x + center.y),YELLOW);
    draw_pixel(PT(-a.y + center.x, -a.x + center.y),YELLOW);

}

/// Bressenhams Circle Drawing Algorithm
void bressenham_circle(PT center, int radious)
{
    PT a;
    a.x = 0;
    a.y = radious;

    int decision_parameter = 3- 2*radious;

    while(a.x<=a.y)
    {
        mirror_point_draw(center, a);

        a.x++;

        if(decision_parameter<0)
            decision_parameter = decision_parameter + (4 * a.x) + 6;
        else
        {
            a.y--;
            decision_parameter = decision_parameter + (4 * a.x) - (4 * a.y) + 10;
        }

    }
}

int main()
{
    initwindow(win_w,win_h);
    //For drawing axis
    draw_axis(win_w,win_h);


    bressenham_circle(PT(0,0),100);
    getchar();

    return 0;
}
