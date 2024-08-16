//
// Created by 25230 on 24-8-16.
//
#include "Bsp_rgb.h"
#include "tim.h"
#include "stdlib.h"

/*Some Static Colors------------------------------*/
const RGB_Color_TypeDef RED      = {255,0,0};   //红色
const RGB_Color_TypeDef GREEN    = {0,255,0};   //绿色
const RGB_Color_TypeDef BLUE     = {0,0,255};   //深蓝色
const RGB_Color_TypeDef SKY      = {0,255,255};  //天蓝色
const RGB_Color_TypeDef MAGENTA  = {255,0,220};  //粉色
const RGB_Color_TypeDef YELLOW   = {128,216,0};  //黄色
const RGB_Color_TypeDef OEANGE   = {127,106,0};  //橘色
const RGB_Color_TypeDef BLACK    = {0,0,0};    //无颜色
const RGB_Color_TypeDef WHITE    = {255,255,255}; //白色

//将好看的颜色封装成数组，便于集中管理和访问
RGB_Color_TypeDef table[16] =
{
   {254,67,101},
   {76,0,10},
   {249,15,173},
   {128,0,32},
   {158,46,36},
   {184,206,142},
   {227,23,13},
   {178,34,34},
   {255,99,71},
   {99,38,18},
   {255,97,0},
   {21,161,201},
   {56,94,15},
   {50,205,50},
   {160,32,240},
    {218,60,90}
};
 //这些是好看的颜色
const RGB_Color_TypeDef color1 = {254,67,101};
//const RGB_Color_TypeDef color2 = {76,0,10};
//const RGB_Color_TypeDef color3 = {249,15,173};
//const RGB_Color_TypeDef color4 = {128,0,32};
//const RGB_Color_TypeDef color5 = {158,46,36};
//const RGB_Color_TypeDef color6 = {184,206,142};
//const RGB_Color_TypeDef color7 = {227,23,13};
//const RGB_Color_TypeDef color8 = {178,34,34};
//const RGB_Color_TypeDef color9 = {255,99,71};
//const RGB_Color_TypeDef color10 ={99,38,18};
//const RGB_Color_TypeDef color11= {255,97,0};
//const RGB_Color_TypeDef color12= {21,161,201};
//const RGB_Color_TypeDef color13= {56,94,15};
//const RGB_Color_TypeDef color14= {50,205,50};
//const RGB_Color_TypeDef color15= {160,32,240};
//const RGB_Color_TypeDef color16= {218,60,90};


/*二维数组存放最终PWM输出数组，每一行24个数据代表一个LED，最后一行24个0用于复位*/
uint32_t Pixel_Buf[Pixel_NUM+1][24];

/*
功能：最后一行装在24个0，输出24个周期占空比为0的PWM波，作为最后reset延时，这里总时长为24*1.25=37.5us > 24us(要求大于24us)
//如果出现无法复位的情况，只需要在增加数组Pixel_Buf[Pixel_NUM+1][24]的行数，并改写Reset_Load即可，这里不做演示了，
*/
static void Reset_Load(void)
{
	uint8_t i;
	for(i=0;i<24;i++)
	{
		Pixel_Buf[Pixel_NUM][i] = 0;
	}
}

/*
功能：发送数组Pixel_Buf[Pixel_NUM+1][24]内的数据，发送的数据被存储到定时器1通道1的CCR寄存器，用于控制PWM占空比
参数：(&htim1)定时器1，(TIM_CHANNEL_1)通道1，((uint32_t *)Pixel_Buf)待发送数组，
			(Pixel_NUM+1)*24)发送个数，数组行列相乘
*/
static  void RGB_SendArray(void)
{
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_2, (uint32_t *)Pixel_Buf,(Pixel_NUM+1)*24);
}

/*
功能：设定单个RGB LED的颜色，把结构体中RGB的24BIT转换为0码和1码
参数：LedId为LED序号，Color：定义的颜色结构体
*/
 //刷新WS2812B灯板显示函数
static void RGB_Flush(void)
{
    Reset_Load();     //复位
    RGB_SendArray();  //发送数据
}

void RGB_SetOne_Color(uint8_t LedId,RGB_Color_TypeDef Color)
{
	uint8_t i;
	if(LedId > Pixel_NUM)return; //avoid overflow 防止写入ID大于LED总数
	//这里是对 Pixel_Buf[LedId][i]写入一个周期内高电平的持续时间（或者说时PWM的占空比寄存器CCR1），
	for(i=0;i<8;i++) Pixel_Buf[LedId][i]   = ( ((Color.G/5) & (1 << (7 -i)))? (CODE_1):CODE_0 );//数组某一行0~7转化存放G
	for(i=8;i<16;i++) Pixel_Buf[LedId][i]  = ( ((Color.R/5) & (1 << (15-i)))? (CODE_1):CODE_0 );//数组某一行8~15转化存放R
	for(i=16;i<24;i++) Pixel_Buf[LedId][i] = ( ((Color.B/5) & (1 << (23-i)))? (CODE_1):CODE_0 );//数组某一行16~23转化存放B
}

//调用RGB_SetOne_Color函数，完成对多个LED的颜色设置。
void RGB_SetMore_Color(uint8_t head, uint8_t heal,RGB_Color_TypeDef color)
{
    uint8_t i=0;
    for(i=head;i<=heal;i++)
    {
        RGB_SetOne_Color(i,color) ;
    }
}



//用来显示单个颜色的函数，只能从第一个开始显示，不好用
//void RGB_RED(uint16_t Pixel_Len)
//{
//	uint16_t i;
//	for(i=0;i<Pixel_Len;i++)//给对应个数LED写入红色
//	{
//		RGB_SetOne_Color(i,RED);
//	}
//}
//


//灯管实现函数（完成本期效果的实现）
void RGB_Show_64(void)
{
    RGB_SetMore_Color(0,63,BLACK);  //清空所有的LED数据
    RGB_SetMore_Color(0,rand()%8,table[rand()%16]);  //第一行随机个灯亮随机颜色
    RGB_SetMore_Color(8,rand()%8+8,table[rand()%16]);  //第二行。。。。以此类推
    RGB_SetMore_Color(16,rand()%8+16,table[rand()%16]);
    RGB_SetMore_Color(24,rand()%8+24,table[rand()%16]);
    RGB_SetMore_Color(32,rand()%8+32,table[rand()%16]);
    RGB_SetMore_Color(40,rand()%8+40,table[rand()%16]);
    RGB_SetMore_Color(48,rand()%8+48,table[rand()%16]);
    RGB_SetMore_Color(56,rand()%8+56,table[rand()%16]);
    RGB_Flush();      //刷新WS2812B的显示
}



