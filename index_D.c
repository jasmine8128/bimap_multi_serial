#include"stdio.h"
#include"math.h"
#include"stdlib.h"
//二进制改为十进制进行数据处理
#define attrs 10
#define datas 100
int bit[attrs][datas];
int key[attrs][datas];
int offset[attrs][datas];
int attr_size;
int bin31=2147483648;
FILE *fp;

void get_attr_size()//get the size of attribute
{
    fp=fopen("outputm.txt","r");
    char c;
    attr_size=0;
    while((c=fgetc(fp))!=EOF)
    {
        if(c=='[')
            attr_size++;
    }
    attr_size=attr_size/2;
    fclose(fp);
}

void get_bitmap()//put the bitmap into bitmap[][][]
{
    fp=fopen("outputm.txt","r");
    int i,j,k,offs;
    char s[32];
    char init;
    i=0;j=0;k=0;
    fscanf(fp,"%d",&bit[i][j]);j++;
    while((init=fgetc(fp))!=EOF)
    {
        if(init=='[')//key and offset
        {

            fscanf(fp,"%d",&offs);
            while(fgetc(fp)!=']')
            {
                key[i][k]=offs;
                k++;
                fscanf(fp,"%d",&offs);
            }
            key[i][k]=offs;
            fgetc(fp);
            fgetc(fp);
            k=0;

            fscanf(fp,"%d",&offs);
            while(fgetc(fp)!=']')
            {
                offset[i][k]=offs;
                k++;
                fscanf(fp,"%d",&offs);
            }
            offset[i][k]=offs;
            i++;j=0;k=0;
        }
        else
        {
            fscanf(fp,"%d",&bit[i][j]);
            j++;
        }
    }
}

void index_bitmap()//index attribute from bitmap
{
    int attr;
    int size[attrs];
    int lie[attrs];
    int loca,total;
    int bits[3];
    char s[32];
    for(int i=0;i<3;i++)//bits stores the results of attributes '&'
    {
        bits[i]=4294967295;
    }
    for(int i=0;i<attr_size;i++)
    {
        printf("Please input the attribute you choose(if not,input -1):\n");
        scanf("%d",&attr);
        if(attr==-1)
        {
            size[i]=0;
            lie[i]=0;
        }
        else{
            size[i]=key[i][attr];
            lie[i]=offset[i][attr];
        }
    }
    for(int i=0;i<attr_size;i++)
    {
        loca=-1;
        for(int i1=0;i1<size[i];i1++)
        {
            loca+=1;
            if(bit[i][lie[i]+i1]>bin31)//not 0-Fill,do '&'
            {
                itoa(bit[i][lie[i]+i1],s,2);
                printf("%s\n",s);
                bits[loca]=bits[loca]&bit[i][lie[i]+i1];
            }
            else{
                total=bit[i][lie[i]+i1];//compute the lies of 0-Fill
                for(int i2=0;i2<total;i2++)
                {
                    bits[loca+i2]=0;
                }
                loca=loca+total-1;
            }
        }
    }
    for(int i=0;i<3;i++)//the results of index_bitmap
    {
        itoa(bits[i],s,2);
        printf("%s\n",s);
    }
    for(int i=0;i<3;i++)//address of the attribute
    {
        itoa(bits[i],s,2);
        for(int j=1;j<32;j++)
        {
            if(s[j]=='1')
            {
                printf("%d;",i*31+j);
            }
        }
    }
}
int main()
{
    get_attr_size();
    get_bitmap();
    index_bitmap();
    return 0;

}
