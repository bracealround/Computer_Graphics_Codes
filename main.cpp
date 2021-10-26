#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>


using namespace std;

const int win_h=600,win_w=800;
struct PT{

    int x,y;
    PT(){}
    PT(double a,double b)
    {
        x=a;
        y=b;
    }

};

//This method converts the coordinate system from a traditional one to a computer recognized one.
PT convert_pixel(PT p)
{
    p.x+=(double)(win_w/2);
    p.y= p.y*(-1.00);
    p.y+=(double)(win_h/2);

    return p;
}

//This method just draws the desired pixel.
void draw_pixel(PT p,int color)
{
    //for drawing pixel
    //delay(1);
    p=convert_pixel(p);
    putpixel((int)(p.x+0.5),(int)(p.y+0.5),color);
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
    if(a.y == b.y)
    {
        if(a.x>b.x)
            swap(a,b);
        for(int x=a.x;x<=b.x;x++)
            draw_pixel(PT(x,a.y),YELLOW);
    }
    else if(a.x == b.x)
    {
        if(a.y>b.y)
            swap(a,b);
        for(int y=a.y;y<=b.y;y++)
            draw_pixel(PT(a.x,y),YELLOW);
    }
    else
    {
        double m = b.y-a.y;
        m=m/(b.x-a.x);
        double m_inv=1.0/m;
        if(fabs(m)<=1.0)
        {
            if(a.x > b.x)
                swap(a,b);
            while(a.x<=b.x)
            {
                draw_pixel(a,YELLOW);
                a.x+=1;
                a.y+=m;
            }
        }
        else
        {
            if(a.y > b.y)
                swap(a,b);
            while(a.y <= b.y)
            {
                draw_pixel(a,YELLOW);
                a.x+=m_inv;
                a.y+=1;
            }

        }
    }
    return ;
}

void bressenham_line_draw(PT a , PT b)
{
    int dx,dy;

    dx=b.x-a.x;
    dy=b.y-a.y;

    double m = (double)dy/(double)dx;

    if(a.x>b.x)
        swap(a,b);
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
    else if((m-1.00)>0.0000001)
    {
        if(a.y>b.y)
            swap(a,b);

        int d=2*abs(dx)-abs(dy);

        int x,y;
        x=a.x;


        for(int y=a.y;y<=a.y+abs(dy);y++)
        {
            draw_pixel(PT(x,y),RED);
            delay(20);
            if(d>=0)
            {
                x+=1;
                d+=2*(abs(dy)+abs(dx));
            }
            else
            {
                d+=2*abs(dx);
            }
        }
        draw_pixel(PT(b.x,y),RED);
    }
    else
    {
        if(a.x>b.x)
            swap(a,b);

        int d=2*(dy)-dx;

        int y=a.y;

        for(int x=a.x;x<=b.x;x++)
        {
            draw_pixel(PT(x,y),RED);
            delay(20);
            if(d>=0)
            {
                y+=1;
                d+=2*(dy-dx);
            }
            else
            {
                d+=2*dy;
            }
        }
        draw_pixel(PT(b.x,y),RED);
    }


}

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
void draw_Polygon(vector<PT> points)
{
    int sz=points.size();

    for(int i=0;i<sz;i++)
        dda_line_draw(points[i],(points[(i+1)%sz]),YELLOW);

    return;

}

void draw_PolygonF(vector<PT> points)
{
    int sz=points.size();

    for(int i=0;i<sz;i++)
    {
        int color;
        if(i%4 == 0) color = CYAN;
        else if(i%4 == 1) color = GREEN;
        else if(i%4 == 2) color = BLUE;
        else color = YELLOW;
        dda_line_draw(points[i],(points[(i+1)%sz]),color);
    }

    return;

}

void Boundary_Fill(PT currentpixel,int boundarycolor,int fillcolor)
{
    PT pixel=convert_pixel(currentpixel);
    int currentpixelcolor=getpixel(pixel.x,pixel.y);
    if(currentpixelcolor==boundarycolor || currentpixelcolor==fillcolor)
        return;

    draw_pixel(currentpixel,fillcolor);

    Boundary_Fill(PT(currentpixel.x,currentpixel.y+1),boundarycolor,fillcolor);
    Boundary_Fill(PT(currentpixel.x,currentpixel.y-1),boundarycolor,fillcolor);
    Boundary_Fill(PT(currentpixel.x+1,currentpixel.y),boundarycolor,fillcolor);
    Boundary_Fill(PT(currentpixel.x-1,currentpixel.y),boundarycolor,fillcolor);

    return;
}


void Flood_Fill(PT currentpixel,int boundarycolor,int fillcolor,int oldcolor)
{
    PT pixel=convert_pixel(currentpixel);
    int currentpixelcolor=getpixel(pixel.x,pixel.y);
    if(currentpixelcolor!=oldcolor && currentpixelcolor!=WHITE)
        return;

    draw_pixel(currentpixel,fillcolor);

    Flood_Fill(PT(currentpixel.x,currentpixel.y+1),boundarycolor,fillcolor,oldcolor);
    Flood_Fill(PT(currentpixel.x,currentpixel.y-1),boundarycolor,fillcolor,oldcolor);
    Flood_Fill(PT(currentpixel.x+1,currentpixel.y),boundarycolor,fillcolor,oldcolor);
    Flood_Fill(PT(currentpixel.x-1,currentpixel.y),boundarycolor,fillcolor,oldcolor);

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

    polygon.push_back(PT(40,35));
    polygon.push_back(PT(100,70));
    polygon.push_back(PT(45,140));
    polygon.push_back(PT(50,180));
    polygon.push_back(PT(-60,100));
    polygon.push_back(PT(-30,-100));


    /*polygon.push_back(PT(0,0));
    polygon.push_back(PT(100,0));
    polygon.push_back(PT(100,100));
    polygon.push_back(PT(0,100));*/

    //draw_Polygon(polygon);
    draw_PolygonF(polygon);

    //Boundary_Fill(PT(10,10),YELLOW,RED);
    Flood_Fill(PT(10,10),YELLOW,RED,BLACK);

    //dda_line_draw(PT(100,70),PT(45,140));

    //draw_line(PT(150,-100),PT(0,200));

    //bressenham_line_draw(PT(50,180),PT(45,140));
    getchar();

    return 0;
}
