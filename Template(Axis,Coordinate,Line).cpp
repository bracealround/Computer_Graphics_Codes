#include<graphics.h>
#include<windows.h>
#include<iostream>
#include<stdio.h>


const int win_h=600,win_w=800;
struct pii{
    int x,y;
};

//This method converts the coordinate system from a traditional one to a computer recognized one.
pii convert_pixel(int x,int y)
{
    x+=(win_w/2);
    y= y*(-1);
    y+=(win_h/2);
    //printf("%d %d\n",x,y);


    pii p;
    p.x=x;
    p.y=y;

    return p;
}

//This method just draws the desired pixel.
void draw_pixel(int x,int y)
{
    //for drawing pixel
    pii p=convert_pixel(x,y);
    putpixel(p.x,p.y,WHITE);
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



int main()
{
    initwindow(win_w,win_h);
    //For drawing axis
    draw_axis(win_w,win_h);

    for(int i=0;i<100;i++)
    {

        draw_pixel(i,i);

    }
    getchar();

    return 0;
}
