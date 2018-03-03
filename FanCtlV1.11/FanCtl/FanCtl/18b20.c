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
* Description    : ��ȡһ���ֽڵ�����read a byte date
* Input          : None
* Output         : None
* Return         : None
*******************************************/
unsigned char Read_One_Byte()   //������ʱ,�������ֽڵ������Чλ�ȴ������Ƴ�
{
	uchar i   = 0;
	uchar dat = 0;
	for(i=8;i>0;i--)
	{
		DQ = 0;                  //���������ͣ�Ҫ��1us֮���ͷ�����
		                       //��Ƭ��Ҫ�ڴ��½��غ��15us�ڶ����ݲŻ���Ч��
		_nop_();                 //����ά����1us,��ʾ��ʱ��ʼ
		dat >>= 1;               //�ô������϶�����λ���ݣ����δӸ�λ�ƶ�����λ��
		DQ = 1;                  //�ͷ����ߣ��˺�DS18B20���������,�����ݴ��䵽������
		Delay(1,1,1);        //��ʱ10us,�˴������Ƽ��Ķ�ʱ��ͼ�������ѿ���������ʱ��ŵ���ʱ����15us�ڵ���󲿷�
		if(DQ)                   //���������в���
		{
			dat |= 0x80;            //������Ϊ1,��DQΪ1,�ǾͰ�dat�����λ��1;��Ϊ0,�򲻽��д���,����Ϊ0
		}        
	Delay(1,1,8);       //20us        //����ʱ�����٣�ȷ����ʱ��ĳ���60us��
	}
	return (dat);
}

/******************************************
* Function Name  : Write_One_Byte
* Description    : д��һ���ֽڵ�����
* Input          : uchar dat
* Output         : None
* Return         : None
*******************************************/
void Write_One_Byte(uchar dat)
{
	uchar i = 0;
	for(i=8;i>0;i--)
	{
	   DQ = 0;                        //��������
	   _nop_();                       //����ά����1us,��ʾдʱ��(����д0ʱ���д1ʱ��)��ʼ
	   DQ = dat&0x01;                 //���ֽڵ����λ��ʼ����
	                                 //ָ��dat�����λ���������,�������������ߺ��15us��,
	                                 //��Ϊ15us��DS18B20������߲�����
	   Delay(1,1,15);               //������дʱ���������60us

	   DQ = 1;                        //д���,�����ͷ�����,
	   dat >>= 1;
	  Delay(1,1,1);
	}
}

/******************************************
* Function Name  : Init_Ds18b20
* Description    : DS18B20��ʼ��send reset and initialization command
* Input          : None
* Output         : None
* Return         : None
*******************************************/
void Init_Ds18b20(void)     
{
	DQ = 1;                    //DQ��λ,��ҪҲ���С�
	Delay(1,1,1);              //������ʱ  10us
	DQ = 0;                    //��Ƭ����������
	Delay(6,1,63); //600  us   //��ȷ��ʱ��ά������480us
	DQ = 1;                    //�ͷ����ߣ�������������
	Delay(5,1,63); //500us     //�˴���ʱ���㹻,ȷ������DS18B20�����������塣
}

/******************************************
* Function Name  : ReadTemperature
* Description    : ��ȡ�¶�get the wenduerature
* Input          : None
* Output         : None
* Return         :�¶�ֵ ��-550~1250��
*******************************************/
float ReadTemperature()                   //
{
	u8 TL=0,TH=0;
	u16 tem=0;
	u8 temp;
	float t=0;
	
	Init_Ds18b20();                //��ʼ��
	Write_One_Byte(0xcc);          //����ROMָ��
	Write_One_Byte(0x44);          //�¶�ת��ָ��
	Init_Ds18b20();                 //��ʼ��
	Write_One_Byte(0xcc);          //����ROMָ��
	Write_One_Byte(0xbe);          //���ݴ���ָ��
	TL = Read_One_Byte();           //��ȡ���ĵ�һ���ֽ�Ϊ�¶�LSB
	TH = Read_One_Byte();           //��ȡ���ĵ�һ���ֽ�Ϊ�¶�MSB
	if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;//�¶�Ϊ��  
    }else temp=1;//�¶�Ϊ��	  	  
    tem=TH; //��ø߰�λ
    tem<<=8;    
    tem+=TL;//��õװ�λ
    t=(float)tem*0.0625-3;//ת��     
		if(temp)
			return t; //�����¶�ֵ
		else 
			return -t; 

}