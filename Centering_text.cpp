#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <cstdio>
#include <string>
#include <easyx.h>//包含easyx图形库
#include<mmsystem.h>
//Windows多媒体API的头文件，包含了播放音频、视频等多媒体功能的函数和结构体的声明。
#pragma comment(lib,"Winmm.lib")
//这是一个编译器指令，告诉链接器在链接时将Winmm.lib库文件包含进来。Winmm.lib是Windows多媒体API的库文件，包含了实现多媒体功能的函数。
using namespace std;
void Text_Is_Centered_In_A_Rectangle(int Rectangle_Width,int Rectangle_Height,int Rectangle_Left_X,int Rectangle_Left_Y,string Text_Str)//计算文字居中在指定区域的输出坐标
{
    /*
        函数原型
            int textwidth(LPCTSTR str);  // 获取字符串的宽度
            int textheight(LPCTSTR str);  // 获取字符串的高度
            LPCTSTR 是一个指向常量字符串的指针（通常是 const char* 或 const wchar_t*）
            如果你需要获取整个字符串的高度，应该将 std::string 转换为 const char*
            调用str.c_str()转发为const char* str是指字符串  获取字符串 "hello" 的高度
    */
    int Text_Width=textwidth(Text_Str.c_str());//获取文字的宽度,可以用textwidth()来获取文字的宽度
    int Text_Height=textheight(Text_Str.c_str());//获取文字的高度，可以用textheight()来获取文字的高度
    int Text_X=Rectangle_Left_X+(Rectangle_Width-Text_Width)/2;//计算文字居中的时候，文字矩形的左上角的x坐标
    int Text_Y=Rectangle_Left_Y+(Rectangle_Height-Text_Height)/2;//计算文字居中的时候，文字矩形的左上角的y坐标
    settextcolor(BLACK);//设置文字颜色
    // settextstyle(Text_Height,Text_Width,"微软雅黑");//设置文字样式
    outtextxy(Text_X,Text_Y,Text_Str.c_str());//绘制文字
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
    setbkmode(TRANSPARENT);
    //TRANSPARENT将背景模式设置为透明
    //这个标志告诉系统不要填充文本、阴影画刷或非实线画笔样式的背景
    setlinecolor(BLUE);
    setfillcolor(RGB(249, 153, 191));
    fillrectangle(50,50,150,100);    
    Text_Is_Centered_In_A_Rectangle(100,50,50,50,"hello world!");  
    system("pause");//防止窗口一闪而过,闪退
    closegraph();//关闭绘图窗口
    return 0;
}