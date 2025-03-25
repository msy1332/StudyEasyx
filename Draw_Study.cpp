#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <easyx.h>//包含easyx图形库
using namespace std;
void Draw_Shape()//绘制图形
{
    //绘制一个点,也就是绘制一个像素点
    putpixel(50,50,RED);//在50*50的位置绘制一个红色的点
    //第一个参数是绘制点的x坐标,第二个参数是绘制点的y坐标，第三个参数设置点的颜色

    //设置线条的颜色
    setlinecolor(BLUE);
    //设置线条的样式
    setlinestyle(PS_SOLID,3);
    //第一个参数是线条的样式
    /*
        PS_SOLID 线形为实线。 
        PS_DASH 线形为：------------ 
        PS_DOT 线形为：············ 
        PS_DASHDOT 线形为：-·-·-·-·-·-· 
        PS_DASHDOTDOT 线形为：-··-··-··-·· 
        PS_NULL 线形为不可见。 
        PS_USERSTYLE 线形样式为用户自定义，由参数 puserstyle 和 userstylecount 指定 
    */
    //第二个是线条的宽度
    //绘制一条线
    line(0,0,getwidth(),getheight());//在起始坐标为(0.0)到结束坐标为(getwidth(),getheight())
    //getwidth()获取窗口的宽度，getheight()获取窗口的高度
    //第一个参数是绘制线的起始坐标,第二个参数是绘制线的结束坐标，第三个参数设置点的颜色
    
    //绘制一个无填充矩形
    rectangle(50,0,50+50,0+50);
    //第一，二个参数是矩形的左上角坐标,第三，四个参数是矩形的右下角坐标
    //设置填充颜色
    setfillcolor(YELLOW);
    //绘制一个有边框的填充矩形
    fillrectangle(50,50,50+50,50+50);//和这个rectangle()参数一样
    //绘制一个无边框的填充矩形
    solidrectangle(50,100,50+50,100+50);
    /*
        第一个参数到第四个参数和这个rectangle()参数一样。
        第五个参数是构成圆角矩形的圆角的椭圆的宽度。
        第六个参数是构成圆角矩形的圆角的椭圆的高度。
    */

    //绘制有边框的圆角矩形
    roundrect(100,0,100+50,0+50,20,20);//前四个和这个rectangle()参数一样
    //绘制有边框的填充的圆角矩形
    fillroundrect(100,50,100+50,50+50,20,20);//和这个roundrect()参数一样
    //绘制无边框的填充的圆角矩形
    solidroundrect(100,100,100+50,100+50,20,20);//和这个roundrect()参数一样
    //绘制有边框的圆形
    circle(175,25,25);//第一，二个参数圆心的坐标，第三个参数是圆的半径
    //绘制有边框的填充圆
    fillcircle(175,75,25);//和circle()参数一样
    //绘制无边框的填充圆
    solidcircle(175,125,25);//和circle()参数一样
    //绘制有边框的椭圆
    ellipse(200,0,200+100,0+50);
    /*
        第一，二个参数是外接矩形的左上角的坐标
        第三，四个参数是外接矩形的右上角的坐标
    */
   //绘制有边框的填充椭圆
    fillellipse(200,50,200+100,50+50);//和这个ellipse参数一样
    //绘制无边框的填充椭圆
    solidellipse(200,100,200+100,100+50);//和这个ellipse参数一样
}
int main()
{
    initgraph(800,800,EX_SHOWCONSOLE);//创建一个800*800的窗口,并显示控制台
    /*
        EX_DBLCLKS 在绘图窗口中支持鼠标双击事件。 
        EX_NOCLOSE 禁用绘图窗口的关闭按钮。 
        EX_NOMINIMIZE 禁用绘图窗口的最小化按钮。 
        EX_SHOWCONSOLE 显示控制台窗口。 
    */
    /*
        如果三个都需要设置，可以使用按位或操作连接起来
        EX_NOMINIMIZE | EX_NOCLOSE | EX_SHOWCONSOLE
    */
    setbkcolor(WHITE);//设置窗口的背景颜色，
    /*
        我们的颜色是由RGB组成的，也就是三原色
        如果没有你喜欢的颜色，我可以使用带参宏来实现
        setbkcolor(RGB(41, 29, 55))
    */
    cleardevice();//这个函数使用当前背景色清空绘图设备。
    //窗口的坐标体系，左上角坐标原点，x轴向增大，y轴向下增大
    Draw_Shape();//绘制图形
    system("pause");//防止窗口一闪而过,闪退
    closegraph();//关闭绘图窗口
    return 0;
}