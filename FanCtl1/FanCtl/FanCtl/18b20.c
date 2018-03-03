#include "18b20.h"
#include "delay.h"

/******************************************
* Function Name  : Delay
* Description    : None
* Input          : unsigned char a1,b1,c1
* Output         : None
* Return         : None
*******************************************/
void Delay(unsigned char a1,b1,c1)
{
	unsigned char a,b,c;
	for(a=0;a<a1;a++)
	for(b=0;b<b1;b++)
	for(c=0;c<c1;c++);
}



/******************************************
* Function Name  : Read_One_Byte()
* Description    : 读取一个字节的数据read a byte date
* Input          : None
* Output         : None
* Return         : None
*******************************************/
unsigned char Read_One_Byte()   //读数据时,数据以字节的最低有效位先从总线移出
{
	uchar i   = 0;
	uchar dat = 0;
	for(i=8;i>0;i--)
	{
		DQ = 0;                  //将总线拉低，要在1us之后释放总线
		                       //单片机要在此下降沿后的15us内读数据才会有效。
		_nop_();                 //至少维持了1us,表示读时序开始
		dat >>= 1;               //让从总线上读到的位数据，依次从高位移动到低位。
		DQ = 1;                  //释放总线，此后DS18B20会控制总线,把数据传输到总线上
		Delay(1,1,1);        //延时10us,此处参照推荐的读时序图，尽量把控制器采样时间放到读时序后的15us内的最后部分
		if(DQ)                   //控制器进行采样
		{
			dat |= 0x80;            //若总线为1,即DQ为1,那就把dat的最高位置1;若为0,则不进行处理,保持为0
		}        
	Delay(1,1,8);       //20us        //此延时不能少，确保读时序的长度60us。
	}
	return (dat);
}

/******************************************
* Function Name  : Write_One_Byte
* Description    : 写入一个字节的数据
* Input          : uchar dat
* Output         : None
* Return         : None
*******************************************/
void Write_One_Byte(uchar dat)
{
	uchar i = 0;
	for(i=8;i>0;i--)
	{
	   DQ = 0;                        //拉低总线
	   _nop_();                       //至少维持了1us,表示写时序(包括写0时序或写1时序)开始
	   DQ = dat&0x01;                 //从字节的最低位开始传输
	                                 //指令dat的最低位赋予给总线,必须在拉低总线后的15us内,
	                                 //因为15us后DS18B20会对总线采样。
	   Delay(1,1,15);               //必须让写时序持续至少60us

	   DQ = 1;                        //写完后,必须释放总线,
	   dat >>= 1;
	  Delay(1,1,1);
	}
}

/******************************************
* Function Name  : Init_Ds18b20
* Description    : DS18B20初始化send reset and initialization command
* Input          : None
* Output         : None
* Return         : None
*******************************************/
void Init_Ds18b20(void)     
{
	DQ = 1;                    //DQ复位,不要也可行。
	Delay(1,1,1);              //稍做延时  10us
	DQ = 0;                    //单片机拉低总线
	Delay(6,1,63); //600  us   //精确延时，维持至少480us
	DQ = 1;                    //释放总线，即拉高了总线
	Delay(5,1,63); //500us     //此处延时有足够,确保能让DS18B20发出存在脉冲。
}

/******************************************
* Function Name  : ReadTemperature
* Description    : 获取温度get the wenduerature
* Input          : None
* Output         : None
* Return         :温度值 （-550~1250）
*******************************************/
float ReadTemperature()                   //
{
	u8 TL=0,TH=0;
	u16 tem=0;
	u8 temp;
	float t=0;
	
	Init_Ds18b20();                //初始化
	Write_One_Byte(0xcc);          //忽略ROM指令
	Write_One_Byte(0x44);          //温度转换指令
	Init_Ds18b20();                 //初始化
	Write_One_Byte(0xcc);          //忽略ROM指令
	Write_One_Byte(0xbe);          //读暂存器指令
	TL = Read_One_Byte();           //读取到的第一个字节为温度LSB
	TH = Read_One_Byte();           //读取到的第一个字节为温度MSB
	if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;//温度为负  
    }else temp=1;//温度为正	  	  
    tem=TH; //获得高八位
    tem<<=8;    
    tem+=TL;//获得底八位
    t=(float)tem*0.0625-3;//转换     
		if(temp)
			return t; //返回温度值
		else 
			return -t; 

}