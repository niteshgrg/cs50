#include<stdio.h>
#include<cs50.h>
int main(void)
{

int height,i,j;
printf("height: ");
height=GetInt();
while((height<0)||(height>23))
{
printf("height: ");
height=GetInt();
}
for(i=2;i<=height+1;i++)
{
for(j=height;j>=i;j--)
{
printf(" ");
}
for(j=1;j<=i;j++)
{
printf("#");
}
printf("\n");
}
}
