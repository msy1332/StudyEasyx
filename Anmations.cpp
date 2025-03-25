#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <easyx.h>//包含easyx图形库
#include <time.h>
using namespace std;
void Transparency_Image(int x,int y,IMAGE *img)//透明贴图
{
    //获取窗口的图片缓冲区数组指针（他是个一维数组）
    DWORD *Before_conversion_Buffer=GetImageBuffer();//使用GetImageBuffer获取图片缓冲区数组指针,如果没有参数就是获取窗口缓冲区指针
    //获取img的图片的缓冲区数组指针（他是个一维数组）
    DWORD *After_conversion_Buffer=GetImageBuffer(img);//使用GetImageBuffer获取图片缓冲区数组指针
    int win_w=getwidth();//获取窗口的宽度
    int win_h=getheight();//获取窗口的高度
    int img_w=img->getwidth();//获取图片宽度
    int img_h=img->getheight();//获取图片的高度
    int real_w=img_w;//将图片的宽度赋值给图片的实际宽度
    int real_h=img_h;//将图片的高度赋值给图片的实际高度
    if(x+img_w>win_w&&x>0)//判断是否超过右边界
    {
        real_w=win_w-x;//实际的宽度等于窗口的宽度减去贴图的x坐标
    }
    if(y+img_h>win_h&&y>0)//判断是否超过下边界
    {
        real_h=win_h-y;//实际的高度等于窗口的高度减去贴图的Y坐标
    }
    if(x<0)//判断是否超过左边界
    {
        After_conversion_Buffer+=abs(x)-1;//让指针偏移向后偏移
        real_w-=abs(x);//改变图片的实际的宽度
        x=0;//把x赋值为0
    }
    if(y<0)//判断是否超过上边界
    {
        After_conversion_Buffer+=abs(y)*img_w;//让指针向后偏移
        real_h-=abs(y);//改变他的高度
        y=0;//把y赋值为0
    }
    //遍历这个一维数组
    for(int i=0;i<real_w;i++)
    {
        for(int j=0;j<real_h;j++)
        {
            UCHAR alpha=After_conversion_Buffer[j*img_w+i]>>24;
            if(alpha>100)
            {
                Before_conversion_Buffer[(y+j)*win_w+(x+i)]=After_conversion_Buffer[j*img_w+i];
            }
        }
    }
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
    IMAGE Place_Blow_Up_Image[4];
    char Place_Path[100]={0};
    for(int i=0;i<4;i++)
    {
        sprintf(Place_Path,"Image/enemy2_down%d.png",i);
        loadimage(Place_Blow_Up_Image+i,Place_Path);//加载图片，并存储在IMAGE类型图片变量里
    }
    int index=0;//定义int的类型，用来存储下标
    int Fps=1000/60;//算出1毫秒要保持在1000/60以内，等于16.6666666...
    int speed=500;//让图片动画每隔500毫秒切换一次画面
    int i=0;
    while(1)
    {
        int StartTime=clock();//用clock()获取程序开始到调用的时间，也就是获取他的毫秒数
        BeginBatchDraw();//开启双缓存绘图
        /*
            如果程序运行太快，绘制出的页面就会偶尔闪屏
            这时候就需要开启双缓冲
            BeginBatchDraw();//开使双缓存绘图
            所有的绘图都写到这里
            EndBatchDraw();//结束双缓冲绘图
        */
        cleardevice();//这个函数使用当前背景色清空绘图设备。
        Transparency_Image(0,0,Place_Blow_Up_Image+index);//使用透明贴图，(index++)%4控制他的范围在0到3之间，为什么可以控制呢？，因为当是4的倍数的时候，用模运算求余数刚好等于0，这样就可以控制他的范围了
        EndBatchDraw();//结束双缓冲绘图
        index=(clock()/speed)%4;//用clock()获取程序开始到调用的时间，也就是获取他的毫秒数，除以500，也就是计算clock()有多少个speed间隔数，有多少个间隔数就是贴到了第几张图片，例：当满1000/500等于1时，就是已经满1个500毫秒了可以切换下一张图片，1000/500等于1，其实就可以来当作图片的下标来使用,就可以然每隔500毫秒切换一张图片，为了防止越界，还要模4，这样就可以把他控制在0到3之间，防止越界
        int StopTime=clock();//用clock()获取程序开始到调用的时间，也就是获取他的毫秒数
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
    /*
        这个时实现了在不同图片上绘制出来的动画
    */
    system("pause");//防止窗口一闪而过,闪退
    closegraph();//关闭绘图窗口
    return 0;
}