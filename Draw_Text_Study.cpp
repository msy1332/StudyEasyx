#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <easyx.h>//包含easyx图形库
using namespace std;
void Draw_Text()
{
    //在控制台绘制文字
    cout<<"hello easyx";
    printf("!\n");
    //在图形窗口输出文字
    //设置文字样式及大小
    settextstyle(48,0,"Tahoma");
    /*
        第一个参数是设置文字的高度
        第二个参数是设置文字的宽度，如果填0则宽度自适应
        第三个参数是设置文字的字体
    */

    //设置文字颜色
    settextcolor(GREEN);
    //设置文字背景模式
    setbkmode(TRANSPARENT);
    //TRANSPARENT将背景模式设置为透明
    //这个标志告诉系统不要填充文本、阴影画刷或非实线画笔样式的背景

    //绘制文字
    outtextxy(50,50,"hello easyx!");
    /*
        第一个参数是绘制文字的x的坐标
        第二个参数是绘制文字的y的坐标
        第三个参数是绘制的字符串
    */
    //如何将数字输出在图形窗口上
    int score=66;//创建一个score分数
    char score_text[10];//创建一个score_text字符串
    sprintf(score_text,"score:%d",score);//将分数score格式化输入到字符串中
    outtextxy(500,0,score_text);//在坐标为(500,0)位置输出分数
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
    Draw_Text();//绘制图形
    system("pause");//防止窗口一闪而过,闪退
    closegraph();//关闭绘图窗口
    return 0;
}