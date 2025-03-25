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
        After_conversion_Buffer+=abs(x);//让指针偏移向后偏移
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
void Transparency_Image(int dstX, int dstY, int dstWidth, int dstHeight,IMAGE *pSrcImg, int srcX, int srcY)//透明贴图
{
    //获取窗口的图片缓冲区数组指针（他是个一维数组）
    DWORD *Before_conversion_Buffer=GetImageBuffer();//使用GetImageBuffer获取图片缓冲区数组指针,如果没有参数就是获取窗口缓冲区指针
    //获取img的图片的缓冲区数组指针（他是个一维数组）
    DWORD *After_conversion_Buffer=GetImageBuffer(pSrcImg);//使用GetImageBuffer获取图片缓冲区数组指针
    int win_w=getwidth();//获取窗口的宽度
    int win_h=getheight();//获取窗口的高度
    int img_w=pSrcImg->getwidth();//获取图片宽度
    int img_h=pSrcImg->getheight();//获取图片的高度
    int real_w=dstWidth;//将图片的宽度赋值给图片的实际宽度
    int real_h=dstHeight;//将图片的高度赋值给图片的实际高度
    After_conversion_Buffer+=srcY*img_w+srcX;
    if(dstX+img_w>win_w&&dstX>0)//判断是否超过右边界
    {
        real_w=win_w-dstX;//实际的宽度等于窗口的宽度减去贴图的x坐标
    }
    if(dstY+img_h>win_h&&dstY>0)//判断是否超过下边界
    {
        real_h=win_h-dstY;//实际的高度等于窗口的高度减去贴图的Y坐标
    }
    if(dstX<0)//判断是否超过左边界
    {
        After_conversion_Buffer+=abs(dstX);//让指针偏移向后偏移
        real_w-=abs(dstX);//改变图片的实际的宽度
        dstX=0;//把x赋值为0
    }
    if(dstY<0)//判断是否超过上边界
    {
        After_conversion_Buffer+=abs(dstY)*img_w;//让指针向后偏移
        real_h-=abs(dstY);//改变他的高度
        dstY=0;//把y赋值为0
    }
    //遍历这个一维数组
    for(int i=0;i<real_w;i++)
    {
        for(int j=0;j<real_h;j++)
        {
            UCHAR alpha=After_conversion_Buffer[j*img_w+i]>>24;
            if(alpha>100)
            {
                Before_conversion_Buffer[(dstY+j)*win_w+(dstX+i)]=After_conversion_Buffer[j*img_w+i];
            
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
    int Fps=1000/60;//算出1毫秒要保持在1000/60以内，等于16.6666666...
    int Img_Width=69;//每一帧的宽度
    int Img_Height=95;//每一帧的高度
    int Number_of_pictures=3;//总共有多少帧
    int speed=500;//每个多少间隔切换一张图片
    int index=0;//贴的是哪一张图
    IMAGE Place;
    loadimage(&Place,"Image/Sprite_table_Img.png");
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
        Transparency_Image(-50,50,Img_Width,Img_Height,&Place,index*Img_Width,0);
        /*
            第一，二个参数是你要输出图片的左上角坐标坐标
            第三，四个参数是图片的宽度和图片的高度
            第五个参数是IMAGE类型图片的指针
            第六，七个是动画的每一帧相对于图片的坐标
        */
        EndBatchDraw();//结束双缓冲绘图
        index=(clock()/speed)%Number_of_pictures;
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
        这个时实现了在同一张图片实现的动画，我们称这个图片是精灵表动画图片
    */
    system("pause");//防止窗口一闪而过,闪退
    closegraph();//关闭绘图窗口
    return 0;
}