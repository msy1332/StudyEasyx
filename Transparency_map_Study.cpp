#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <easyx.h> //包含easyx图形库
#include <ctime>
#include <cmath>
using namespace std;
void Transparency_Image(int x,int y,IMAGE *img)
{
    //获取窗口的图片缓冲区数组指针（他是个一维数组）
    DWORD *Before_conversion_Buffer=GetImageBuffer();//使用GetImageBuffer获取图片缓冲区数组指针,如果没有参数就是获取窗口缓冲区指针
    //获取img的图片的缓冲区数组指针（他是个一维数组）
    DWORD *After_conversion_Buffer=GetImageBuffer(img);//使用GetImageBuffer获取图片缓冲区数组指针
    int win_w=getwidth();//获取窗口的宽度
    int win_h=getheight();//获取窗口的高度
    int img_w=img->getwidth();//获取图片的宽度
    int img_h=img->getheight();//获取图片的高度
    //遍历这个一维数组
    for(int i=0;i<img_w;i++)
    {
        for(int j=0;j<img_h;j++)
        {
            UCHAR alpha=After_conversion_Buffer[j*img_w+i]>>24;//通过按位或操作来获取了alpha也就是透明度
            if(alpha>200)//如果透明度大于200，也就是半透明
            {
                Before_conversion_Buffer[(y+j)*win_w+(x+i)]=After_conversion_Buffer[j*img_w+i];
            }
        }
    }
}
void Transparency_Image_S(int x,int y,IMAGE *img)
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
            if(alpha>200)
            {
                Before_conversion_Buffer[(y+j)*win_w+(x+i)]=After_conversion_Buffer[j*img_w+i];
            }
        }
    }
}
void Image_turn_Black_and_white(IMAGE* After_conversion,IMAGE* Before_conversion)//将图片转化成黑白图片
{
    //After_conversion转化为黑白图后的图片,Before_conversion转化为黑白图前的图片
    After_conversion->Resize(Before_conversion->getwidth(),Before_conversion->getheight());//After_conversion把转化后的图片大小设置跟Before_conversion转化前的大小一样
    //通过Resize()函数可以设置图片的大小，第一个参数是你要设置图片的宽度，第二个参数是你要设置图片的高度
    
    //获取Before_conversion转化为黑白图前的图片的缓冲区数组指针（他是个一维数组）
    DWORD *Before_conversion_Buffer=GetImageBuffer(Before_conversion);//使用GetImageBuffer获取图片缓冲区数组指针
    //获取Before_conversion转化为黑白图前的图片的缓冲区数组指针（他是个一维数组）
    DWORD *After_conversion_Buffer=GetImageBuffer(After_conversion);//使用GetImageBuffer获取图片缓冲区数组指针
    //遍历这个一维数组
    for(int i=0;i<(Before_conversion->getwidth()*Before_conversion->getheight());i++)
    {
        //After_conversion_Buffer[i]=Before_conversion_Buffer[i];//Before_conversion_Buffer[i]中的地址的值复制到After_conversion_Buffer[i]中地址的里,他是通过指针访问数组元素时，p[i] 和 *(p + i) 是等价的
        /*
            那我们如何给他转化成黑白图呢？
                黑白图的特点
                定义：黑白图（灰度图）是一种单通道图像，每个像素的值表示亮度，取值范围通常是 0（黑色）到 255（白色）。
                颜色信息：黑白图没有颜色信息，只有亮度信息。
                存储方式：在计算机中，黑白图通常以单通道形式存储，但在某些情况下（如显示或处理时），会将其扩展为三通道（R、G、B）形式。
                为什么会将其扩展为三通道（R、G、B），因为白色（255，255，255）黑色（0，0，0）
                黑白图是单通道图像，但为了兼容彩色图像的显示和处理方式，通常将其扩展为三通道（R、G、B）形式。
                因为每个像素的值表示亮度，取值范围通常是 0（黑色）到 255（白色），因为显示图片时是以RGB形式输出颜色的，所以RGB取值范围在 黑色(0,0,0)到白色(255,255,255)
                那如何将RGB颜色值转化为亮度值，在图像处理中通常被称为灰度值，颜色越亮那就更接近（255，255，255）
                亮度值的定义（Luminance）
                    亮度值是颜色的一个属性，表示颜色的明暗程度。
                    在 RGB 颜色模型中，亮度值是通过对 R、G、B 三个分量进行加权计算得到的。
                    亮度值的范围通常是 0（最暗）到 255（最亮）。
                灰度值的定义（Gray Value）
                    灰度值是黑白图（灰度图）中每个像素的值，表示该像素的明暗程度。
                    灰度值的范围也是 0（黑色）到 255（白色）。
                    灰度值是通过将彩色图像的 R、G、B 分量合并为一个值得到的。 
                亮度值和灰度值都表示像素的明暗程度，只是名称不同  
                计算方法：亮度值通常通过加权平均法计算，而灰度值是通过将亮度值应用于黑白图得到的
                人眼对颜色的感知特性
                    人眼对不同颜色的敏感度不同：
                    对 绿色 的敏感度最高。
                    对 红色 的敏感度次之。
                    对 蓝色 的敏感度最低。
                    因此，在计算亮度时，通常会对 R、G、B 分量赋予不同的权重，以反映人眼的感知特性。
                    权重的定义
                        权重 是一个数值，表示某个因素在计算中的重要性或者是影响力。
                        权重越大，表示该因素对结果的影响越大；权重越小，表示该因素的影响越小。
                亮度计算公式
                    亮度计算公式是 加权平均法，其公式为：Gray=0.299×R+0.587×G+0.114×B
                    权重来源
                        绿色G）的权重最高（0.587），人眼对绿色的敏感度最高，因此绿色通道的权重最大。。
                        红色（R）权重次之（0.299），人眼对红色的敏感度次之，因此红色通道的权重中等。。
                        蓝色（B）的权重最低（0.114），人眼对蓝色的敏感度最低，因此蓝色通道的权重最小。。
                权重的作用：通过为 R、G、B 通道赋予不同的权重，可以生成更符合人眼感知特性的灰度图也就是黑白图
        */   
        //Before_conversion_Buffer指向图片的缓冲区数组指针，每一个数组元素都就是图片的RGB颜色值
        //首先要分解每个元素的RGB颜色值
        DWORD rgb=Before_conversion_Buffer[i];
        UCHAR r=UCHAR(rgb);
        UCHAR g=UCHAR(rgb>>8);
        UCHAR b=UCHAR(rgb>>16);
        //使用加权平均法来计算亮度值也就是灰度值
        int Gray=0.299*r+0.587*g+0.114*b;
        //为了兼容彩色图像的显示和处理方式我要转化为三通道，并赋值给After_conversion_Buffer[i]
        After_conversion_Buffer[i]=RGB(Gray,Gray,Gray);
    }
}
int main()
{
    initgraph(800, 800, EX_SHOWCONSOLE); // 创建一个800*800的窗口,并显示控制台
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
    setbkcolor(WHITE); // 设置窗口的背景颜色，
    /*
        我们的颜色是由RGB组成的，也就是三原色
        如果没有你喜欢的颜色，我可以使用带参宏来实现
        setbkcolor(RGB(41, 29, 55))
    */
    cleardevice(); // 这个函数使用当前背景色清空绘图设备。
    // 窗口的坐标体系，左上角坐标原点，x轴向增大，y轴向下增大
    
    //绘制像素点用putpixel()来绘制
    /*
        以（400，400）为中心的九宫格画一个由像素点构成的矩形
        我们可以像二维数组一样遍历九宫格的每一个坐标
        九宫格的左上角坐标是（400-1，400-1）
        右上角的坐标是（400+1，400+1）
        我可以先从左向有遍历或从上到下遍历
    */
    int x=400;//绘制九宫格的中心像素点的x坐标
    int y=400;//绘制九宫格的中心像素点的y坐标
    int cut=0;
    for(int i=x-100;i<=x+100;i++)
    {
        /*
            方法一：
                上面的代码也可以写成这样
                int RGB_Color=255-cut;
                cut++;
                if(cut>255)
                {
                    cut=0;
                }
            方法二：
                int RGB_Color=255-(cut++)%256
                当满255时包括255，将cut赋值为0
                也就是控制它的范围在255~0之间，包括255
                如果超过的话，那就在初始化为0
            例如：  255-0%256=255-0=255
                    255-255%256=255-255=0
            通过这样实现颜色的渐变效果
        */
        // int RGB_Color=255-cut;
        // cut++;
        // if(cut>255)//包括255，当满255，初始化为0，控制他的范围0到255
        // {
        //     cut=0;
        // }
        int RGB_Color=255-(cut++)%256;//这个是上面的简化，也可以实现一样的效果
        cout<<RGB_Color<<endl;
        for(int j=y-100;j<=y+100;j++)
        {
            putpixel(j,i,((25<<8)|255)|(30<<16));      
        }
        /*
            在 RGB 颜色编码中，每种颜色分量（红、绿、蓝）通常用 两位十六进制数 表示，范围是 00 到 FF（对应十进制的 0 到 255）。
            如果时0~F那就是0~15无法满足0~255RGB的颜色范围所以是00~FF
            如何分解0x0000FF的RGB颜色值
            我们都知道一个十六进制数可以用4位的二进制表示，比如说A的十进制是10，10的二进制是1010
            因为1字节是由8位二进制组成的，所以AA才代表1个字节
            前面的0x是代表这个数是十六进制，后面的就是十六进制数0000FF
            因为AA代表一个字节，拆解出来00 00 AA 就是三个字节，刚好对应三原色，也就是RGB，但是他的最后一个是R，倒数第二个是G,倒数第三个是B
            如何把0x0000FF分解成RGB
            首先分解R,int r=0x0000FF我们可以这样写，因为int 变量会自动将十六进制、八进制或二进制值转换为十进制存储
            0x0000FF 可以简化为 0xFF，因为前面的 0000 都是 0，不影响最终值
            然后分解G，因为RGB是由3个字节组成，那我们就可以向右移动8位，在通过int自动转化成十进制
            为什么移动8位呢，一个十六进制数可以用4位的二进制，那两个十六进制数就是一个字节也就是8位，所以我们可以移动8位就可以得到第二个字节
        */
    }
    /*
        DWORD的变量原型unsigned long 是一个无符号的长整型，通常占用 4 字节（32 位）
        无符号整数的定义：
        无符号的长整数（unsigned long）它是无符号的，因此只能表示非负数。
        一个 unsigned long 是 32 位的数据类型，可以存储 ARGB 颜色值
        那我们如何分别分解出来
        我们都知道1个字节是8位,因为ABGR各占一个字节,为什么是ABGR，但是最右边才是R,倒数第二个是G,倒数第三个是B，倒数第四个是A，
        为什么是ABGR
            字节序（Endianness）的影响：
            字节序是指数据在内存中的存储顺序，分为两种：
            大端序（Big Endian）：高位字节存储在低地址。
            小端序（Little Endian）：低位字节存储在低地址。
            
            大多数现代计算机（如 64位 的 x86 架构）使用 小端序
            在小端序系统中，数据的低位字节存储在低地址，高位字节存储在高地址。
            如果你将一个 32 位的颜色值（如 0xAABBGGRR）存储到内存中，小端序会将其存储为 RR GG BB AA。
            因此，当你从内存中读取时，顺序会变成 ABGR
        那我们如何分解出R呢
            因为ARGB,都是1字节存储的
            那么我们可以使用 UCHAR 原型unsigned char无符号整数
            无符号整数的定义
                无符号整数（unsigned integer）是指没有符号位（即不表示正负）的整数。
                对于 unsigned char，所有 8 位都用于表示数值，没有符号位。
            取值范围：
                由于 unsigned char 是 8 位的，它可以表示 2的8次方等于256
                取值范围是：0 ≤unsigned char ≤255
                最小值：0
                最大值：255
            那为什么取值范围是：0 ≤unsigned char ≤255，为什么最小值：0，最大值：255
            取值范围的计算：
                对于一个 8 位的无符号整数：
                    最小的值是所有位都为 0，即：00000000    
                    对应的十进制值是 0。
                最大的值是所有位都为 1，即：11111111
                对应的十进制值是：1*2的7次方+1*2的6次方+1*2的5次方+1*2的4次方+1*2的3次方+1*2的2次方+1*2的1次方+1*2的0次方
                计算结果是：
                    128+64+32+16+8+4+2+1=255
                计算机如何存储数据：
                    计算机以二进制形式存储数据。
                    对于 unsigned char，它只能存储 8 位二进制数据（1 字节）。
                    如果赋值的数据超出了 8 位，计算机会只保留最低的 8 位，而丢弃高位。
                    当数据超出范围时，计算机会从最低位开始保留数据，因为：
                        最低位对值的影响最小。
                        丢弃高位对值的影响较大，但这是为了适应存储空间的限制。
                        示例分析
                            示例代码：   unsigned char x = 300;
                                        printf("%u\n", x); // 输出: 44
                        分析过程：
                                将 300 转换为二进制：100101100
                                保留最低的 8 位：,因为最低位对值的影响最小，所以丢弃高位。
                                从右往左数，保留最低的 8 位：00101100
                              把00101100转化为十进制：44
            例如：0x0000FF
            那我们就可以把0x0000FF强制转化为UCHAR那他就会从右到左保存8位，也就是FF
        然后我们就分解G
            因为ARGB都是由1字节组成
            所以我们就可以把0x0000FF向右移动8为，然后把他强制转化为UCHAR那他就会从右到左保存8位，这样也就分解出了G
        然后分解B和A也是一样，只是向右的字节数不同，分解B移动16位，分解A移动24位
    */
    DWORD RGBA=RGB(255,25,30);
    int R=UCHAR(RGBA);
    int G=UCHAR(RGBA>>8);
    int B=UCHAR(RGBA>>16);
    int A=UCHAR(RGBA>>24);
    cout<<"RGBA "<<RGBA<<endl;
    cout<<"R: "<<R<<endl;
    cout<<"G: "<<G<<endl;
    cout<<"B: "<<B<<endl;
    cout<<"A: \n"<<A<<endl;
    /*
        如何将RGB(255,25,30)合成一个颜色，转化位十六进制颜色值
        RGB颜色由三个分量组成：红（R）、绿（G）、蓝（B）。
        每个分量的取值范围是 0到255。
        在十六进制表示中，每个分量用 两位十六进制数 表示。
        十六进制颜色的标准格式是 #RRGGBB，其中：
        RR 表示红色分量。
        GG 表示绿色分量。
        BB 表示蓝色分量。
        例如：  RGB(255, 25, 30) 的十六进制表示
                对于RGB颜色 (255, 25, 30)：
                红色分量（R = 255）的十六进制是 FF。
                绿色分量（G = 25）的十六进制是 19。
                蓝色分量（B = 30）的十六进制是 1E。
                按照标准格式 #RRGGBB，组合起来就是 #1E19FF
                注意：  putpixel(int x, int y, COLORREF color)
                        COLORREF的原型是DWORD，DWORD在64位 的 x86 架构使用的是小端序
                        所以计算机#RRGGBB应使用小端序，也就是#BBGGRR,所以这个#1E19FF应该是#FF191E
        还有一种方法
            ((G<<8)| R) |(B<<16)
            ((25<<8)|255)|(30<<16)
            使用按位或把RGB和成一个32位整数，把每一个字节都转化成十六进制数，在按照标准格式 #RRGGBB组合起来就也可以实现一样的效果
    */
    //将图片存储在IMAGE的变量中
    IMAGE Tree;//定义IMAGE类型的图片变量
    loadimage(&Tree,"./Image/Original drawing.png",218,167);//加载图片,并对图片进行等比的缩放
    putimage(0,0,&Tree);//贴图
    IMAGE Tree1;//定义IMAGE类型的图片变量
    Image_turn_Black_and_white(&Tree1,&Tree);//把彩图转化成黑白图
    putimage(218,0,&Tree1);//贴图
    Transparency_Image_S(-50,-50,&Tree); 
    //使用getpixel()函数获取某一个像素点的颜色值
    DWORD Image_pixel=getpixel(0,0);
    int R1=UCHAR(Image_pixel);
    int G1=UCHAR(Image_pixel>>8);
    int B1=UCHAR(Image_pixel>>16);
    int A1=UCHAR(Image_pixel>>24);
    cout<<"RGBA "<<RGBA<<endl;
    cout<<"R1: "<<R1<<endl;
    cout<<"G1: "<<G1<<endl;
    cout<<"B1: "<<B1<<endl;
    cout<<"A1: "<<A1<<endl;
    system("pause");   // 防止窗口一闪而过,闪退
    closegraph();      // 关闭绘图窗口
    return 0;
}