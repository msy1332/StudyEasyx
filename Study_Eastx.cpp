#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <easyx.h>//包含easyx图形库
#include <time.h>
using namespace std;
//清屏
//双缓冲
//帧率的控制
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
    /*
        TRANSPARENT将背景模式设置为透明
        如果你设置背景模式设置为透明
        例：如果绘制完文字没有使用cleardevice()这个函数使用当前背景色清空绘图设备。
            就会下次绘制文字的时候，绘制出来的文字看不清
    */
    int score=0;//创建int类型的变量，用来存储分数
    char str[50]="";//创建char类型的字符串，用来存储分数字符串并输出到我们的图形窗口上
    /*
        FPS一般为60帧或120帧
        如果没有帧数控制，如果是一个游戏，当你移动角色，那就移动的很快，这是就需要帧是控制在60帧或120帧以内
        这里我以60帧为例：
            1秒60帧，就使1秒60个画面
            1秒等于1000毫秒
            也就是说如果我们要把帧数保持到60帧以内
            就是1毫秒要保持在1000/60以内
            也就是说1帧要保持在1000/60毫秒
    */
    int Fps=1000/60;//算出1毫秒要保持在1000/60以内，等于16.6666666...
    while(1)
    {
        int StartTime=clock();//用clock()获取程序开始到调用的时间，也就是获取他的毫秒数
        sprintf(str,"score:%d",score++);//把分数格式化输出到字符串里
        settextcolor(BLACK);//设置文字颜色为黑色
        cleardevice();//用设置的背景颜色清屏
        BeginBatchDraw();//开启双缓存绘图
        /*
            如果程序运行太快，绘制出的页面就会偶尔闪屏
            这时候就需要开启双缓冲
            BeginBatchDraw();//开使双缓存绘图
            所有的绘图都写到这里
            EndBatchDraw();//结束双缓冲绘图
        */
        outtextxy(20,20,str);//输出分数
        EndBatchDraw();//结束双缓冲绘图
        // getchar();//当我每次按下任意键的时候就让分数++
        int StopTime=clock();//用clock()获取程序开始到调用的时间，也就是获取他的毫秒数
        cout<<StartTime<<endl;
        if(StopTime-StartTime<=Fps)//通过作差，算出中间执行时间所消耗的毫秒数，如果没超过Fps,那就暂停程序，时间为作差后没有达到Fps的时间
        {
            Sleep(StopTime-StartTime);//使程序暂停，暂停时间为作差后没有达到Fps的时间
            /*
                例：StopTime为1000ms
                    StartTime为987
                    StopTime-StartTime=1000-987=13毫秒，那也就不能达到16ms绘制一个画面
                    也就就1秒绘制60个画面，也就是1秒60帧
                    所以我们要把剩下的16-13毫秒时间给延长，也就是暂停程序16-13毫秒，来达到达到16ms绘制一个画面
            */
        }
    }
    system("pause");//防止窗口一闪而过,闪退
    closegraph();//关闭绘图窗口
    return 0;
}