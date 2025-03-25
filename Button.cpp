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
bool Music_playing_state=0;//播放音乐的状态
//如果等于0，音乐还没开始播放，如果等于1音乐已经开始播放
using namespace std;
struct RGB//定义了一个三原色，用来存储按钮的三个状态的颜色
{
    int R;
    int G;
    int B;
};
RGB Normal_State={249, 153, 191};
RGB Hover_State={244, 83, 148};
RGB Pressed_State={240, 19, 107};
RGB Button_1_Current_Status;
RGB Button_2_Current_Status;
/*
    按钮的状态颜色
    普通状态（Normal_State）
    悬停状态（Hover_State）
    点击状态（Pressed_State）
*/


/*
    Rectangle_Width矩形的宽度
    Rectangle_Height矩形的高度
    Rectangle_Left_X矩形的左上角的x坐标
    Rectangle_Left_Y矩形的左上角的y坐标
    Text_Str[20]要输出文字
*/
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
    //如果写这行 settextstyle(Text_Height,Text_Width,"微软雅黑");//设置文字样式
    //因为有些字体不支持这样的宽高比就会导致渲染问题
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

    ExMessage msg;//定义消息结构体变量
    mciSendString("open Music/j57gx-hru1n.mp3", NULL, 0, NULL);//打开音乐
    while(1)
    {
        //获取消息
        /*
            消息标识            消息类别    描述 
            WM_MOUSEMOVE        EX_MOUSE 鼠标移动消息。 
            WM_MOUSEWHEEL       EX_MOUSE 鼠标滚轮拨动消息。 
            WM_LBUTTONDOWN      EX_MOUSE 左键按下消息。 
            WM_LBUTTONUP        EX_MOUSE 左键弹起消息。 
            WM_LBUTTONDBLCLK    EX_MOUSE 左键双击消息。 
            WM_MBUTTONDOWN      EX_MOUSE 中键按下消息。 
            WM_MBUTTONUP        EX_MOUSE 中键弹起消息。 
            WM_MBUTTONDBLCLK    EX_MOUSE 中键双击消息。  
            WM_RBUTTONDOWN      EX_MOUSE 右键按下消息。 
            WM_RBUTTONUP        EX_MOUSE 右键弹起消息。 
            WM_RBUTTONDBLCLK    EX_MOUSE 右键双击消息。 
            WM_KEYDOWN          EX_KEY 按键按下消息 
            WM_KEYUP            EX_KEY 按键弹起消息。 
            WM_CHAR             EX_CHAR 字符消息。 
            WM_ACTIVATE         EX_WINDOW 窗口激活状态改变消息。 
            WM_MOVE             EX_WINDOW 窗口移动消息。 
            WM_SIZE             EX_WINDOW 窗口大小改变消息。 
        */
        if(peekmessage(&msg,EX_MOUSE))//获取鼠标消息
        {
            if(msg.message==WM_LBUTTONDOWN&&msg.x>=50&&msg.x<=200&&msg.y>=50&&msg.y<=100)//判断消息是否是左键按下并且在按钮内
            {
                //设置左键按下的填充颜色
                Button_1_Current_Status=Pressed_State;
                //setfillcolor(RGB(Pressed_State.R,Pressed_State.G,Pressed_State.B));
                if(Music_playing_state==0)//按下左键，判断音乐是否在播放，如果不在播放，那就开始播放音乐
                {
                    mciSendString("play Music/j57gx-hru1n.mp3", NULL, 0, NULL);//播放音乐
                    /*
                        第一个参数是
                            lpszCommand: 要发送的 MCI 命令字符串
                            类型: LPCTSTR（指向常量字符串的指针）
                            作用: 这是一个字符串参数，用于指定要发送给 MCI 设备的命令。
                            内容: 命令字符串由命令和参数组成，格式为 "命令 参数1 参数2 ..."
                            例如：
                                "open mysong.mp3 alias myaudio"：打开文件 mysong.mp3 并为其分配别名 myaudio。
                                "play myaudio"：播放别名为 myaudio 的设备。
                                "status myaudio mode"：查询别名为 myaudio 的设备的状态。
                            注意事项:
                            命令字符串中的文件名路径需要使用双反斜杠 \\ 或单斜杠 /，以避免转义字符问题。
                            命令字符串是区分大小写的。
                        第二个参数是
                            lpszReturnString: 用于接收返回信息的缓冲区
                            类型: LPTSTR（指向字符串缓冲区的指针）
                            作用: 这是一个输出参数，用于接收 MCI 命令执行后的返回信息。
                            使用场景:
                                当你发送的命令需要返回信息时（例如查询设备状态），可以将返回信息存储在这个缓冲区中。
                                如果不需要返回信息，可以设置为 NULL
                        第三个参数
                            3. cchReturn: 返回信息缓冲区的大小
                            类型: UINT（无符号整数）
                            作用: 指定 lpszReturnString 缓冲区的大小（以字符为位）。
                            使用场景:
                                当 lpszReturnString 不为 NULL 时，需要指定缓冲区的大小，以防止缓冲区溢出。
                                如果 lpszReturnString 为 NULL，则此参数应设为 
                            注意事项:
                                缓冲区大小应足够大，以容纳返回的信息。
                                如果缓冲区太小，可能会导致信息截断或缓冲区溢出。
                        第四个参数
                            hwndCallback: 回调窗口的句柄
                            类型: HANDLE（窗口句柄）
                            作用: 指定一个窗口句柄，用于接收 MCI 设备的通知消息（例如播放完成的通知）。
                                使用场景:
                                当你希望 MCI 设备在特定事件（如播放完成）发生时通知你的程序时，可以指定一个窗口句柄。
                                如果不需要回调通知，可以设置为 NULL。
                    */
                    Music_playing_state=1;//更新音乐播放的状态为1，正在播放音乐
                }
                // else//按下左键，判断音乐是否在播放，如果在播放，那就暂停播放音乐
                // {
                //     mciSendString("stop Music/lavjb-3ixdw.mp3", NULL, 0, NULL);//暂停音乐
                //     Music_playing_state=0;//更新音乐播放的状态为0，正在暂停播放音乐
                // }
            }
            else if(msg.x>=50&&msg.x<=200&&msg.y>=50&&msg.y<=100)
            {
                //设置在按钮内的填充颜色
                Button_1_Current_Status=Hover_State;
                //setfillcolor(RGB(Hover_State.R,Hover_State.G,Hover_State.B));
            }
            else
            {
                //设置不在按钮内的填充颜色
                Button_1_Current_Status=Normal_State;
                //setfillcolor(RGB(Normal_State.R,Normal_State.G,Normal_State.B));
            }


            if(msg.message==WM_LBUTTONDOWN&&msg.x>=300&&msg.x<=450&&msg.y>=50&&msg.y<=100)
            {
                //设置左键按下的填充颜色
                Button_2_Current_Status=Pressed_State;
                if(Music_playing_state==1)//按下左键，判断音乐是否在播放，如果在播放，那就暂停播放音乐
                {
                    mciSendString("stop Music/j57gx-hru1n.mp3", NULL, 0, NULL);//暂停音乐
                    Music_playing_state=0;//更新音乐播放的状态为0，正在暂停播放音乐
                }
            }
            else if(msg.x>=300&&msg.x<=450&&msg.y>=50&&msg.y<=100)
            {
                //设置在按钮内的填充颜色
                Button_2_Current_Status=Hover_State;
            }
            else
            {
                //设置不在按钮内的填充颜色
                Button_2_Current_Status=Normal_State;
            }
        }
        setlinecolor(BLUE);//设置线条颜色为蓝色
        
        //设置按钮一的填充颜色
        setfillcolor(RGB(Button_1_Current_Status.R,Button_1_Current_Status.G,Button_1_Current_Status.B));
        fillrectangle(50,50,200,100);//绘制矩形按钮
        //绘制文字并居中在按钮内
        Text_Is_Centered_In_A_Rectangle(150,50,50,50,"play");
        //设置按钮二的填充颜色
        setfillcolor(RGB(Button_2_Current_Status.R,Button_2_Current_Status.G,Button_2_Current_Status.B));
        fillrectangle(300,50,450,100);//绘制矩形按钮
        //绘制文字并居中在按钮内
        Text_Is_Centered_In_A_Rectangle(150,50,300,50,"stop");
    }
    system("pause");//防止窗口一闪而过,闪退
    closegraph();//关闭绘图窗口
    return 0;
}