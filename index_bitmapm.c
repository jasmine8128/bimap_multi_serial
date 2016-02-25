#include"stdio.h"
#include"math.h"

char bit[10][100][33];
int key[10][100];
int offset[10][100];

void get_bitmap()
{
    FILE *fp;
    char init;
    int i,j,k,offs;
    fp=fopen("outputs.txt","r");
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
    }*/

}

/*void index_bitmap()
{

    printf("Please input the attribute you choose:\n");
    int attr;
    scanf("%d",&attr);
    int size,lie,loca,total;
    size=key[attr];
    lie=offset[attr];
    loca=-1;

    for(int i=0;i<size;i++)
    {
        loca+=1;
        if(bit[lie+i][31]=='1')
        {
            for(int j=0;j<31;j++)
            {
                if(bit[lie+i][j]=='1')
                {
                    printf("lie+i:%d j:%d  ",lie+i,j);
                    printf("%d\n",1+j+loca*31);
                }

            }
        }
        else
        {
            total=0;
            for(int j=30;j>=0;j--)
            {
                if(bit[lie+i][j]=='1')
                {
                    total+=pow(2,30-j);
                }
            }
            loca=loca+total-1;
        }
    }
}*/

int main()
{

    //get_bitmap();
    //index_bitmap();

    return 0;

}
