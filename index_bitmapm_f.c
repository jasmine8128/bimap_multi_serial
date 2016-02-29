#include"stdio.h"
#include"math.h"

char bit[10][100][33];
int key[10][100];
int offset[10][100];
int attr_size;
FILE *fp;


void get_attr_size()//get the size of attribute
{
    fp=fopen("outputs.txt","r");
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
    fp=fopen("outputs.txt","r");
    char init;
    int i,j,k,offs;

    i=0;j=0;k=0;
    while((init=fgetc(fp))!=EOF)
    {
        if(init=='1')//'1'-literal
        {

            fgets(bit[i][j],32,fp);
            bit[i][j][31]='1';bit[i][j][32]='\0';
            printf("%s\n",bit[i][j]);
            j++;
            fgetc(fp);
        }
        else if(init=='0')//'0'-Fill
        {

            fgets(bit[i][j],32,fp);
            bit[i][j][31]='0';bit[i][j][32]='\0';
            printf("%s\n",bit[i][j]);
            j++;
            fgetc(fp);
        }
        else if(init=='[')//key and offset
        {

            fscanf(fp,"%d",&offs);
            while(fgetc(fp)!=']')
            {
                key[i][k]=offs;
                printf("%d,",key[i][k]);
                k++;
                fscanf(fp,"%d",&offs);
            }
            key[i][k]=offs;
            printf("%d\n",key[i][k]);
            fgetc(fp);
            fgetc(fp);
            k=0;

            fscanf(fp,"%d",&offs);
            while(fgetc(fp)!=']')
            {
                offset[i][k]=offs;
                printf("%d,",offset[i][k]);
                k++;
                fscanf(fp,"%d",&offs);
            }
            offset[i][k]=offs;
            printf("%d\n",offset[i][k]);
            i++;j=0;k=0;
        }
    }
    /*for( i=0;i<4;i++)
    {
        for( j=0;j<20;j++)
        {
            printf("%s\n",bit[i][j]);
        }

        for( j=0;j<20;j++)
        {
            printf("%d,",key[i][j]);
        }
        printf("\n");
        for( j=0;j<20;j++)
        {
            printf("%d,",offset[i][j]);
        }
        printf("\n");
    }*///用于检验程序

}

void index_bitmap()//index attribute from bitmap
{
    int attr;
    int size[10];
    int lie[10];
    int loca,total;
    char bits[3][33];
    for(int i=0;i<3;i++)//bits stores the results of attributes '&'
    {
        for(int j=0;j<32;j++)
            bits[i][j]='1';
        bits[i][32]='\0';
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
    /*for(int i=0;i<attr_size;i++)
        printf("%d,",size[i]);
    printf("\n");
    for(int i=0;i<attr_size;i++)
        printf("%d,",lie[i]);
    printf("\n");*///用于检验程序
    for(int i=0;i<attr_size;i++)
    {
        loca=-1;
        for(int i1=0;i1<size[i];i1++)
        {
            loca+=1;
            if(bit[i][lie[i]+i1][31]=='1')//not 0-Fill,for every bit do '&'
            {
                for(int i2=0;i2<31;i2++)
                {
                    bits[loca][i2]=bits[loca][i2]&bit[i][lie[i]+i1][i2];
                }
                bits[loca][31]='0';
            }
            else{
                total=0;
                for(int i3=30;i3>=0;i3--)    //compute the lies of 0-Fill
                {
                    if(bit[i][lie[i]+i1][i3]=='1')
                    {
                        total+=pow(2,30-i3);
                    }
                }
                for(int i4=0;i4<total;i4++)
                {
                    for(int i5=0;i5<32;i5++)
                    {
                        bits[loca+i4][i5]='0';
                    }
                }
                loca=loca+total-1;
            }
        }
    }
    for(int i=0;i<3;i++)//the results of index_bitmap
    {
        printf("%s\n",bits[i]);
    }
    for(int i=0;i<3;i++)//address of the attribute
    {
        for(int j=0;j<32;j++)
        {
            if(bits[i][j]=='1')
            {
                printf("%d;",i*31+j+1);
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
