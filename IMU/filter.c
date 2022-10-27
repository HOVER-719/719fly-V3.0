//git测试
/************************************************************************************************
* 程序版本：V2.1
* 程序日期：2021-12-8
* 程序作者：719飞行器实验室：
*                        张润
*                        杨晨阳
************************************************************************************************/
#include "filter.h"
#include <string.h>
#include <stdio.h>

#define N 20          //滤波缓存数组大小

/*******************************************************************************
* 函  数 ：float FindPos(float*a,int low,int high)
* 功  能 ：确定一个元素位序
* 参  数 ：a  数组首地址
*          low数组最小下标
*          high数组最大下标
* 返回值 ：返回元素的位序low
* 备  注 : 无
*******************************************************************************/
float FindPos(float*a,int low,int high)
{
    float val = a[low];                      //选定一个要确定值val确定位置
    while(low<high)
    {
        while(low<high && a[high]>=val)
             high--;                           //如果右边的数大于VAL下标往前移
             a[low] = a[high];                 //当右边的值小于VAL则复值给A[low]

        while(low<high && a[low]<=val)
             low++;                            //如果左边的数小于VAL下标往后移
             a[high] = a[low];                 //当左边的值大于VAL则复值给右边a[high]
    }
    a[low] = val;
    return low;
}

/*******************************************************************************
* 函  数 ：void QuiteSort(float* a,int low,int high)
* 功  能 ：快速排序
* 参  数 ：a  数组首地址
*          low数组最小下标
*          high数组最大下标
* 返回值 ：无
* 备  注 : 无
*******************************************************************************/
void QuiteSort(float* a,int low,int high)
{
    int pos;
    if(low<high)
    {
        pos = FindPos(a,low,high); //排序一个位置
        QuiteSort(a,low,pos-1);    //递归调用
        QuiteSort(a,pos+1,high);
    }
}

/*******************************************************************************
* 函  数 ：float  SortAver_Filter(float value)
* 功  能 ：去最值平均值滤波一组数据
* 参  数 ：value 采样的数据
*           *filter 滤波以后的数据地址
* 返回值 ：无
* 备  注 : 无
*******************************************************************************/
void SortAver_Filter(float value,float *filter,uint8_t n)
{
    static float buf[N] = {0.0};
    static uint8_t cnt =0,flag = 1;
    float temp=0;
    uint8_t i=0;
    buf[cnt++] = value;
    if(cnt<n && flag)
        return;     //数组填不满不计算
    else flag=0;
    QuiteSort(buf,0,n-1);
    for(i=1;i<n-1;i++)
    {
        temp += buf[i];
    }

    if(cnt>=n) cnt = 0;

    *filter = temp/(n-2);
}

/*******************************************************************************
* 函  数 ：float  SortAver_Filter1(float value)
* 功  能 ：去最值平均值滤波一组数据
* 参  数 ：value 采样的数据
*           *filter 滤波以后的数据地址
* 返回值 ：无
* 备  注 : 无
*******************************************************************************/
void SortAver_Filter1(float value,float *filter,uint8_t n)
{
    static float buf[N];
    static uint8_t cnt =0 ,flag = 1;
    float temp=0;
    uint8_t i;
    buf[cnt++] = value;
    if(cnt<n && flag)
        return;                                           //数组填不满不计算
    else
        flag = 0;
    QuiteSort(buf,0,n-1);
    for(i=1;i<n-1;i++)
    {
        temp += buf[i];
    }
    if(cnt>=n) cnt = 0;

    *filter = temp/(n-2);
}

/********************************************************************************
* 函  数 ：void  SortAver_FilterXYZ(INT16_XYZ *acc,FLOAT_XYZ *Acc_filt,uint8_t n)
* 功  能 ：去最值平均值滤波三组数据
* 参  数 ：*acc 要滤波数据地址
*          *Acc_filt 滤波后数据地址
* 返回值 ：无
* 备  注 : 无
********************************************************************************/
void SortAver_FilterXYZ(INT16_XYZ *acc,FLOAT_XYZ *Acc_filt,uint8_t n)
{
    static float bufx[N],bufy[N],bufz[N];
    static uint8_t cnt =0,flag = 1;
    float temp1=0,temp2=0,temp3=0;
    uint8_t i;
    bufx[cnt] = acc->X;
    bufy[cnt] = acc->Y;
    bufz[cnt] = acc->Z;
    cnt++;      //这个的位置必须在赋值语句后，否则bufx[0]不会被赋值
    if(cnt<n && flag)
        return;   //数组填不满不计算
    else
        flag = 0;

    QuiteSort(bufx,0,n-1);
    QuiteSort(bufy,0,n-1);
    QuiteSort(bufz,0,n-1);
    for(i=1;i<n-1;i++)
    {
        temp1 += bufx[i];
        temp2 += bufy[i];
        temp3 += bufz[i];
    }

    if(cnt>=n) cnt = 0;
    Acc_filt->X  = temp1/(n-2);
    Acc_filt->Y  = temp2/(n-2);
    Acc_filt->Z  = temp3/(n-2);
}
/************************************************************************************************
* 函  数：void Aver_FilterXYZ6(INT16_XYZ *acc,INT16_XYZ *gry,FLOAT_XYZ *Acc_filt,FLOAT_XYZ *Gry_filt,uint8_t n)
* 功  能：滑动窗口滤波六组数据
* 参  数：*acc ,*gry 要滤波数据地址
*         *Acc_filt,*Gry_filt 滤波后数据地址
* 返回值：无
* 备  注：本程序为STM32飞控新生比赛精简版
************************************************************************************************/
void Aver_FilterXYZ6(INT16_XYZ *acc,INT16_XYZ *gry,FLOAT_XYZ *Acc_filt,FLOAT_XYZ *Gry_filt,uint8_t n)
{
    static float bufax[N],bufay[N],bufaz[N],bufgx[N],bufgy[N],bufgz[N];
    static uint8_t cnt =0,flag = 1;
    float temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0;
    uint8_t i;
    bufax[cnt] = acc->X;
    bufay[cnt] = acc->Y;
    bufaz[cnt] = acc->Z;
    bufgx[cnt] = gry->X;
    bufgy[cnt] = gry->Y;
    bufgz[cnt] = gry->Z;
    cnt++;                                   //这个的位置必须在赋值语句后，否则bufax[0]不会被赋值
    if(cnt<n && flag)
        return;                                //数组填不满不计算
    else
        flag = 0;
    for(i=0;i<n;i++)
    {
        temp1 += bufax[i];
        temp2 += bufay[i];
        temp3 += bufaz[i];

        temp4 += bufgx[i];
        temp5 += bufgy[i];
        temp6 += bufgz[i];
    }
    if(cnt>=n) cnt = 0;
    Acc_filt->X  = temp1/n;
    Acc_filt->Y  = temp2/n;
    Acc_filt->Z  = temp3/n;

    Gry_filt->X  = temp4/n;
    Gry_filt->Y  = temp5/n;
    Gry_filt->Z  = temp6/n;
}


/*********************** 滑动窗口滤波函数 **********************************/
/* 参  数：*acc  要滤波数据地址
 *         *Acc_filt 滤波后数据地址 */
void sliding_average_filter(INT16_XYZ *acc, FLOAT_XYZ *Acc_filt, uint8_t n)
{
    static int data_num = 0;
    static float bufx[N],bufy[N],bufz[N];
    float output1 = 0, output2 = 0, output3 = 0;

    if (data_num < n) //不满窗口，先填充
    {
        bufx[data_num++] = acc->X;
        bufy[data_num++] = acc->Y;
        bufz[data_num++] = acc->Z;
        output1 = acc->X;
        output2 = acc->Y;
        output3 = acc->Z;
    }
    else
    {
        int i = 0;
        float sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;
        memcpy(&bufx[0], &bufx[1], (n - 1) * 4); //将1之后的数据移到0之后，即移除头部
        memcpy(&bufy[0], &bufy[1], (n - 1) * 4);
        memcpy(&bufz[0], &bufz[1], (n - 1) * 4);
        bufx[n-1] = acc->X;   //即添加尾部
        bufy[n-1] = acc->Y;
        bufz[n-1] = acc->Z;
        for (i = 0; i < n; i++)
        {
            sum1 += bufx[i];
            sum2 += bufy[i];
            sum3 += bufz[i];
        }
        output1 = sum1 / n;
        output2 = sum2 / n;
        output3 = sum3 / n;
    }

    Acc_filt->X  = output1;
    Acc_filt->Y  = output2;
    Acc_filt->Z  = output3;
}

/************************************************************************************************
* 函  数：void Aver_FilterXYZ(INT16_XYZ *acc,FLOAT_XYZ *Acc_filt,uint8_t n)
* 功  能：滑动窗口滤波三组数据
* 参  数：*acc  要滤波数据地址
*         *Acc_filt 滤波后数据地址
* 返回值：无
* 备  注：本程序为STM32飞控新生比赛精简版
************************************************************************************************/
void Aver_FilterXYZ(INT16_XYZ *acc, FLOAT_XYZ *Acc_filt, uint8_t n)
{
    static int32_t bufax[N],bufay[N],bufaz[N];
    static uint8_t cnt =0,flag = 1;
    int32_t temp1=0, temp2=0, temp3=0,i;
    bufax[cnt] = acc->X;
    bufay[cnt] = acc->Y;
    bufaz[cnt] = acc->Z;
    cnt++;                                                                  //这个的位置必须在赋值语句后，否则bufax[0]不会被赋值
    if(cnt<n && flag)
        return;                                                            //数组填不满不计算
    else
        flag = 0;
    for(i=0;i<n;i++)
    {
        temp1 += bufax[i];
        temp2 += bufay[i];
        temp3 += bufaz[i];
    }
    if(cnt>=n)  cnt = 0;
    Acc_filt->X  = temp1/n;
    Acc_filt->Y  = temp2/n;
    Acc_filt->Z  = temp3/n;
}
/************************************************************************************************
* 函  数：void Aver_Filter(float data,float *filt_data,uint8_t n
* 功  能：滑动窗口滤波一组数据
* 参  数：data  要滤波数据
*          *filt_data 滤波后数据地址
* 返回值：返回滤波后的数据
* 备  注：本程序为STM32飞控新生比赛精简版
************************************************************************************************/
void Aver_Filter(float data,float *filt_data,uint8_t n)
{
    static float buf[N];
    static uint8_t cnt =0,flag = 1;
    float temp=0;
    uint8_t i;
    buf[cnt] = data;
    cnt++;
    if(cnt<n && flag)
        return;                                                           //数组填不满不计算
    else
        flag = 0;

    for(i=0;i<n;i++)
    {
        temp += buf[i];
    }
    if(cnt>=n) cnt = 0;
    *filt_data = temp/n;
}
/************************************************************************************************
* 函  数：void Aver_Filter1(float data,float *filt_data,uint8_t n
* 功  能：滑动窗口滤波一组数据
* 参  数：*acc ,*gry 要滤波数据地址
*         *Acc_filt,*Gry_filt 滤波后数据地址
* 返回值：返回滤波后的数据
* 备  注：本程序为STM32飞控新生比赛精简版
************************************************************************************************/
void Aver_Filter1(float data,float *filt_data,uint8_t n)
{
    static float buf[N];
    static uint8_t cnt =0,flag = 1;
    float temp=0;
    uint8_t i;
    buf[cnt++] = data;
    if(cnt<n && flag)
        return;                                                               //数组填不满不计算
    else
        flag = 0;
    for(i=0;i<n;i++)
    {
        temp += buf[i];
    }
    if(cnt>=n) cnt = 0;
     *filt_data = temp/n;
}

typedef struct
{
    float lpf_1;

    float out;
}_lf_t;

#define ABS(x) ( (x)>0?(x):-(x) )
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )

void LPF_1(float hz,float time,float in,float *out)
{
    *out += ( 1 / ( 1 + 1 / ( hz *6.28f *time ) ) ) *( in - *out );
}

void limit_filter(float T,float hz,_lf_t *data,float in)
{
    float abs_t;
    LPF_1(hz,T,     in,&(data->lpf_1));
    abs_t = ABS(data->lpf_1);
    data->out = LIMIT(in,-abs_t,abs_t);
}

/*************************************巴特沃斯滤波************************************************/
Butter_Parameter Butter_80HZ_Parameter_Acce,Butter_60HZ_Parameter_Acce,Butter_51HZ_Parameter_Acce,
                 Butter_30HZ_Parameter_Acce,Butter_20HZ_Parameter_Acce,Butter_15HZ_Parameter_Acce,
                 Butter_10HZ_Parameter_Acce,Butter_5HZ_Parameter_Acce,Butter_2HZ_Parameter_Acce,
				 Butter_1HZ_Parameter_Acce;

/****************************************
Butterworth低通滤波器参数初始化：http://blog.csdn.net/u011992534/article/details/73743955
***************************************/
void Butterworth_Parameter_Init(void)
{
  Set_Cutoff_Frequency(200, 80,&Butter_80HZ_Parameter_Acce);
  Set_Cutoff_Frequency(200, 60,&Butter_60HZ_Parameter_Acce);
  Set_Cutoff_Frequency(200, 51,&Butter_51HZ_Parameter_Acce);
  Set_Cutoff_Frequency(200, 30,&Butter_30HZ_Parameter_Acce);
  Set_Cutoff_Frequency(200, 20,&Butter_20HZ_Parameter_Acce);
  Set_Cutoff_Frequency(200, 15,&Butter_15HZ_Parameter_Acce);
  Set_Cutoff_Frequency(200, 10,&Butter_10HZ_Parameter_Acce);
  Set_Cutoff_Frequency(200, 5 ,&Butter_5HZ_Parameter_Acce);
  Set_Cutoff_Frequency(200, 2 ,&Butter_2HZ_Parameter_Acce);
  Set_Cutoff_Frequency(200, 1 ,&Butter_1HZ_Parameter_Acce);

}

/*************************************************
函数名:    float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter)
说明:    加速度计低通滤波器
入口:    float curr_input 当前输入加速度计,滤波器参数，滤波器缓存
出口:    无
备注:    2阶Butterworth低通滤波器
*************************************************/
float LPButterworth(float curr_input, Butter_BufferData *Buffer, Butter_Parameter *Parameter)
{
  /* 加速度计Butterworth滤波 */
    /* 获取最新x(n) */
        static int LPF_Cnt=0;
        Buffer->Input_Butter[2] = curr_input;
        if(LPF_Cnt >= 100)
        {
            /* Butterworth滤波 */
            Buffer->Output_Butter[2]=
             Parameter->b[0] * Buffer->Input_Butter[2]
            +Parameter->b[1] * Buffer->Input_Butter[1]
            +Parameter->b[2] * Buffer->Input_Butter[0]
            -Parameter->a[1] * Buffer->Output_Butter[1]
            -Parameter->a[2] * Buffer->Output_Butter[0];
        }
        else
        {
            Buffer->Output_Butter[2] = Buffer->Input_Butter[2];
            LPF_Cnt++;
        }
    /* x(n) 序列保存 */
        Buffer->Input_Butter[0]=Buffer->Input_Butter[1];
        Buffer->Input_Butter[1]=Buffer->Input_Butter[2];
    /* y(n) 序列保存 */
        Buffer->Output_Butter[0]=Buffer->Output_Butter[1];
        Buffer->Output_Butter[1]=Buffer->Output_Butter[2];
        return Buffer->Output_Butter[2];
}

void Set_Cutoff_Frequency(float sample_frequent, float cutoff_frequent, Butter_Parameter *LPF)
{
    float fr = sample_frequent / cutoff_frequent;
    float ohm = tanf(M_PI_F / fr);
    float c = 1.0f + 2.0f * cosf(M_PI_F / 4.0f) * ohm + ohm * ohm;

    if (cutoff_frequent <= 0.0f)
    {
        return;
    }

    LPF->b[0] = ohm * ohm / c;
    LPF->b[1] = 2.0f * LPF->b[0];
    LPF->b[2] = LPF->b[0];
    LPF->a[0] = 1.0f;
    LPF->a[1] = 2.0f * (ohm * ohm - 1.0f) / c;
    LPF->a[2] = (1.0f - 2.0f * cosf(M_PI_F / 4.0f) * ohm + ohm * ohm) / c;
}


