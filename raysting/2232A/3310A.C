//�˿�˵����
//*****
//P1��Ϊ���̿�
//P1.0Ϊ�Զ���
//P1.1Ϊ�ֶ���
//P1.2Ϊ��λһ
//P1.3Ϊ��λ��
//P1.4Ϊ��λ��
//P1.5Ϊ��λ��
//P1.6Ϊ��λ��
//P1.6Ϊ��λ��
//******
//P2.1Ϊ�������ź�
//P2.0Ϊ���Ƿ�����ź�
//*****
//P0.2Ϊ164�����ź�
//P0.1Ϊ164�����ź�
//P0.0Ϊ164�����ź�

    #include <reg52.h>
	#include <stdio.h>
	#include <intrins.h>
	#define uchar unsigned char
	#define uint unsigned int
	#define ulong unsigned long
	sbit dat= P0^0;   //����������
    sbit clk= P0^1;   //����ʱ�Ӷ�
	sbit clr= P0^2;   //�����
    sbit J0= P1^0;   
    sbit J1= P1^1;   
	sbit J3= P1^2;   
    sbit J4= P1^3;   
    sbit J5= P1^4;   
	sbit J6= P1^5;   
    sbit J7= P1^6;   
    sbit J8= P1^7;   
	sbit YC= P2^1;  
    sbit QL= P2^0;

    uchar  anjianbaochi;//�������ּ���  
    uchar  daout;//�������
    uchar  outjiance;//������
    uchar  zdbz;//�Զ�����־λ
    uchar  zdbaochi;
    uchar  anjianbz;
    uchar  aj;
    uint  ys;
//    uchar code jdq[]={0x60,0x50,0x48,0x44,0x42,0x41,0x01,0x00}; // 0x20,0x10,0x08,0x04,0x02,0x01,0x41,0x00
//    uchar code xsdw[]={0x48,0x88,0x24,0x44,0x84,0x22,0x42,0x00};// 0xb8,0x78,0xd4,0xb4,0x74,0xd2,0xb2,0x00
    //outformat b4,b3,b2,b1,a4,a3,a2,a1  point position is (b4,b3,b2,b1)(a4,a3,a2,a1)
	//array is from 0.1mA to 10A
//    uchar code xsdw[]={0x88,0x28,0x48,0x84,0x24,0x44,0x82,0x00};// 0xb8,0x78,0xd4,0xb4,0x74,0xd2,0xb2,0x00

    uchar code xsdw[]={0x88,0x24,0x44,0x84,0x22,0x42,0x82,0x00};// 0xb8,0x78,0xd4,0xb4,0x74,0xd2,0xb2,0x00
uchar code jdq[]={0x60,0x50,0x48,0x44,0x42,0x02,0x01,0x00}; // 0x20,0x10,0x08,0x04,0x02,0x01,0x41,0x00
void wait(uint j)
  {
   uint i;
   for(i=0;i<j;i++)
      ;
   }
void d164()   //74164������λһ����
   {
         uchar i=0,ajbc,c;
         ajbc=anjianbaochi;
         c=jdq[ajbc];
         
         do{  
             if(c&0x01)     
                   	dat=1;
                    else
					dat=0;
		     c>>=1;        //����tabel�еĵ�N���������ƶ�һλ
             clk=0;            //�½��ؽ�����д��164������ʱ�Ӷ�ֹͣ�������͵ȴ���һ��д��
             clk=1;
             clk=0;
             i++;
            }
        while(i<8);
               i=0;
               c=xsdw[ajbc];
           if(zdbz==0xff)
             c=c|0x01; 
             
        do{  
             if(c&0x01)     
                   	dat=1;
                    else
					dat=0;
		     c>>=1;        //����tabel�еĵ�N���������ƶ�һλ
             clk=0;            //�½��ؽ�����д��164������ʱ�Ӷ�ֹͣ�������͵ȴ���һ��д��
             clk=1;
             clk=0;
             i++;
            }
        while(i<8);
        }
   
void keydsp()
  {
   uchar aj;
   anjianbaochi=~anjianbaochi;
   aj=anjianbaochi;
   if(anjianbaochi==1)
     { zdbz=0xff;
       anjianbaochi=0;
       d164();}
    else
     { 
     zdbz=0;
      if(anjianbaochi==2)
        {  anjianbaochi=0;
           d164();}
      else if(anjianbaochi==4)
        {  anjianbaochi=1;
           d164();} 
      else if(anjianbaochi==8)
        {  anjianbaochi=2;
           d164(); }
      else if(anjianbaochi==16)
        {  anjianbaochi=3;
           d164(); }
      else if(anjianbaochi==32)
        {  anjianbaochi=4;
           d164(); }
      else if(anjianbaochi==64)
        {  anjianbaochi=5;
           d164(); }
      else if(anjianbaochi==128)
        {  anjianbaochi=6;
           d164(); }
       else
         ;
      
   
      }
   } 
void key(void)
   {
 
    if(anjianbz!=0)
      {
       if(P1==0xff)
         keydsp();
         anjianbz=0;
       }
     if(P1!=0xff)
       {
       wait(2);
       if(P1!=0xff)
          anjianbaochi=P1;
          anjianbz=0xff;
       }
     
   }
void jiance(void)
   {
    ys=0;
    if(zdbz==0xff)
     {
    
      if(YC==1)
        {if(anjianbaochi!=0)
         { anjianbaochi=anjianbaochi-1; 
          d164();
		  return;}
          }
      if(QL==1)
         {if(anjianbaochi!=6)
          {anjianbaochi=anjianbaochi+1;  
          d164();} 
          }
       
      }
    }
void main()
   {

 zdbz=0xff;
    while(1)
    {
    key();
    if(ys>0x2ff0)
      {jiance();}
     ys++;
    }
   }
    
    