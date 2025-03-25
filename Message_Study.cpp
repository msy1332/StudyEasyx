#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <easyx.h>//包含easyx图形库
#include <windows.h>
using namespace std;
struct Circle_Stats
{
    int x;//圆心的x坐标
    int y;//圆心的y坐标
    int r;//圆的半径
};
Circle_Stats Circle_1={50,50,20};
int main()
{
    initgraph(800,800,EX_SHOWCONSOLE | EX_DBLCLKS);//创建一个800*800的窗口,并显示控制台
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
    
    //定义消息结构体变量
    ExMessage msg={0};
    /*
        第一个参数是ExMessage结构体的指针获取指针消息，用于存储获取到的消息。
        第二个参数是filter消息过滤器，用于指定要获取的消息类型。EX_MOUSE 是其中之一，
            WM_MOUSEMOVE：鼠标移动。
            消息过滤器
                WM_LBUTTONDOWN：鼠标左键按下。
                WM_LBUTTONUP：鼠标左键释放。
                WM_RBUTTONDOWN：鼠标右键按下。
                WM_RBUTTONUP：鼠标右键释放。
                WM_MBUTTONDOWN：鼠标中键按下。
                WM_MBUTTONUP：鼠标中键释放。
        第三个参数是bRemoveMessage 
            是否从消息队列中移除消息，默认为 true，表示获取消息后将其从队列中移除
            如果设置为 false，则消息仍保留在队列中。
            返回值：
                如果成功获取到消息，返回 true。
                如果消息队列为空，返回 false。
        如果我们还要获取别的消息我可以使用按位或操作连接起来
        例：peekmessage(&msg,EX_MOUSE| EX_KEY）
    */
    //获取消息,如果他获取到了消息会返回真，否则会返回假
    int Speed=3;//小球的速度，每次移动3个的距离
    int Direction_Circle_X=0;//小球的左右方向
    int Direction_Circle_Y=0;//小球的上下方向
    /*
        如果键盘按下A键或左键则Direction_Circle_X是-1
        如果键盘按下D键或右键则Direction_Circle_X是1
        如果键盘按下W键或上键则Direction_Circle_Y是-1
        如果键盘按下S键或上下键则Direction_Circle_Y是1
    */
    while(1)
    {
        cleardevice();//这个函数使用当前背景色清空绘图设备。
        if(peekmessage(&msg,EX_MOUSE| EX_KEY))
        {
            switch(msg.message)
            {
                //判断鼠标消息
                /*
                    消息标识            消息类别    描述 
                    WM_MOUSEMOVE        EX_MOUSE    鼠标移动消息。 
                    WM_MOUSEWHEEL       EX_MOUSE    鼠标滚轮拨动消息。 
                    WM_LBUTTONDOWN      EX_MOUSE    左键按下消息。 
                    WM_LBUTTONUP        EX_MOUSE    左键弹起消息。 
                    WM_LBUTTONDBLCLK    EX_MOUSE    左键双击消息。 
                    WM_MBUTTONDOWN      EX_MOUSE    中键按下消息。 
                    WM_MBUTTONUP        EX_MOUSE    中键弹起消息。 
                    WM_MBUTTONDBLCLK    EX_MOUSE    中键双击消息。 
                    WM_RBUTTONDOWN      EX_MOUSE    右键按下消息。 
                    WM_RBUTTONUP        EX_MOUSE    右键弹起消息。 
                    WM_RBUTTONDBLCLK    EX_MOUSE    右键双击消息。 
                    WM_KEYDOWN          EX_KEY      按键按下消息。
                    WM_KEYUP            EX_KEY      按键弹起消息。 
                    WM_CHAR             EX_CHAR     字符消息。 
                    WM_ACTIVATE         EX_WINDOW   窗口激活状态改变消息。 
                    WM_MOVE             EX_WINDOW   窗口移动消息。 
                    WM_SIZE             EX_WINDOW   窗口大小改变消息 
                    例：if(msg.message==WM_LBUTTONDOWN)判断鼠标是否按下鼠标左键
                */
                case WM_LBUTTONDOWN://左键按下
                    cout<<"左键按下\n";
                    break;
                case WM_RBUTTONDOWN://右键按下
                    cout<<"右键按下\n";
                    break;
                case WM_MBUTTONDOWN://中键按下
                    cout<<"中键按下\n";
                    break;
                case WM_MOUSEWHEEL://滚轮滚动
                    cout<<"滚轮滚动("<<msg.wheel<<")\n";//msg.wheel获取滚轮滚动的方向，120是朝向屏幕滚动(向上滚动)，-120朝向自己滚动(向下滚动)
                    //wheel鼠标滚轮滚动值，仅当消息所属类别为 EX_MOUSE 时有效
                    break;
                case WM_LBUTTONDBLCLK://左键双击消息,需要在initgraph添加EX_DBLCLKS开启鼠标的双击事件，例：initgraph(800,800,EX_SHOWCONSOLE | EX_DBLCLKS)
                    cout<<"左键双击消息\n";
                    break;
                case WM_RBUTTONDBLCLK://右键双击消息,需要在initgraph添加EX_DBLCLKS开启鼠标的双击事件，例：initgraph(800,800,EX_SHOWCONSOLE | EX_DBLCLKS)
                    cout<<"右键双击消息\n";
                    break;
                //判断按键消息
                case WM_KEYDOWN://按键按下
                /*
                    如果我们要获取他按下了什么键
                    vkcode按键的虚拟键码。仅当消息所属类别为 EX_KEY 时有效。
                    例：if(msg.vkcode)=='W'))获取按键消息，判断是否按下了W键
                    在微软网站上列出有所有的虚拟键码：https://docs.microsoft.com/windows/win32/inputdev/virtual-key-codes
                */
                    switch(msg.vkcode)
                    {
                        case 'W'://按下W键
                            Direction_Circle_Y=-1;//小球向上移动
                            cout<<"W\n";
                            break;
                        case 'S'://按下S键
                            Direction_Circle_Y=1;//小球向下移动   
                            cout<<"S\n";
                            break;
                        case 'A'://按下A键
                            Direction_Circle_X=-1;//小球向左移动       
                            cout<<"A\n";
                            break;
                        case 'D'://按下D键
                            Direction_Circle_X=1;//小球向右移动
                            cout<<"D\n";
                            break;
                        case VK_UP://按下上键
                            Direction_Circle_Y=-1;//小球向上移动
                            cout<<"UP\n";
                            break;
                        case VK_DOWN://按下下键
                            Direction_Circle_Y=1;//小球向下移动
                            cout<<"DOWN\n";
                            break;
                        case VK_LEFT://按下左键
                            Direction_Circle_X=-1;//小球向左移动
                            cout<<"LEFT\n";
                            break;   
                        case VK_RIGHT://按下右键
                            Direction_Circle_X=1;//小球向右移动
                            cout<<"RIGHT\n";
                            break;
                    }
                    break;
                case WM_KEYUP://按键弹起
                /*
                    如果我们要获取他按下了什么键
                    vkcode按键的虚拟键码。仅当消息所属类别为 EX_KEY 时有效。
                    例：if(msg.vkcode)=='W'))获取按键消息，判断是否按下了W键
                    在微软网站上列出有所有的虚拟键码：https://docs.microsoft.com/windows/win32/inputdev/virtual-key-codes
                */
                /*
                    当我们按键弹起时，会发现小球还在动，这时我们就要需要更新小球的状态
                    我们就可以把Direction_Circle_X,Direction_Circle_Y这个赋值为0
                    Circle_1.y+=Speed*Direction_Circle_Y刚好Speed*Direction_Circle_Y等于0,这样就可以实现小球运动状态的改变和更新
                */
                    switch(msg.vkcode)
                    {
                        
                        case 'W'://按下W键
                            Direction_Circle_Y=0;
                            cout<<"W\n";
                            break;
                        case 'S'://按下S键
                            Direction_Circle_Y=0;
                            cout<<"S\n";
                            break;
                        case 'A'://按下A键
                            Direction_Circle_X=0;
                            cout<<"A\n";
                            break;
                        case 'D'://按下D键
                            Direction_Circle_X=0;
                            cout<<"D\n";
                            break;
                        case VK_UP://按下键盘上键
                        Direction_Circle_Y=0;
                            cout<<"UP\n";
                            break;
                        case VK_DOWN://按下键盘下键
                            Direction_Circle_Y=0;
                            cout<<"DOWN\n";
                            break;
                        case VK_LEFT://按下键盘左键
                            Direction_Circle_X=0;
                            cout<<"LEFT\n";
                            break;   
                        case VK_RIGHT://按下键盘右键
                            Direction_Circle_X=0;
                            cout<<"RIGHT\n";
                            break;
                    }
                    break;
            }
        }
        Circle_1.x+=Speed*Direction_Circle_X;
        Circle_1.y+=Speed*Direction_Circle_Y;
        /*
            如果键盘按下A键或左键，或D或右键，就是实际x坐标减去或加去每次移动的距离也就是速度
                如果想要小球向右移动，就要把小球的x坐标加上每次移动的距离也就是速度，也就可以把Direction_Circle_X赋值为1
                如果想要小球向左移动，就要把小球的x坐标减去每次移动的距离也就是速度，也就可以把Direction_Circle_X赋值为-1
                Circle_1.x实际x坐标加上Speed每次移动的距离乘以-1或1
            如果键盘按下W键或上键，或S或下键，就是实际y坐标减去或加去每次移动的距离也就是速度
                如果想要小球向上移动，就要把小球的y坐标减去每次移动的距离也就是速度，也就可以把Direction_Circle_Y赋值为-1
                如果想要小球向下移动，就要把小球的y坐标加上每次移动的距离也就是速度，也就可以把Direction_Circle_Y赋值为1
                Circle_1.y实际y坐标加上Speed每次移动的距离乘以-1或1
        */
        setlinecolor(BLUE);//设置线条颜色
        setfillcolor(RED);//设置填充颜色
        /*
            如果程序运行太快，绘制出的页面就会偶尔闪屏
            这时候就需要开启双缓冲
            BeginBatchDraw();//开使双缓存绘图
            所有的绘图都写到这里
            EndBatchDraw();//结束双缓冲绘图
        */
        BeginBatchDraw();//开使双缓存绘图
        fillcircle(Circle_1.x,Circle_1.y,Circle_1.r);//绘制圆
        fillcircle(msg.x,msg.y,20);//绘制圆
        Sleep(10);//由于计算机太快，使小球移动的很快，使用windows的Sleep()使函数暂停程序的执行一段时间，时间以毫秒为单位
        EndBatchDraw();//结束双缓冲绘图
    }
    system("pause");//防止窗口一闪而过,闪退
    closegraph();//关闭绘图窗口
    return 0;
}