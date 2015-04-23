#include<stdio.h>
#include<cs50.h>
#include<math.h>

int main(void)
{
float balance;
int i,b;
printf("O hai! How much change is owed?\n");
balance=GetFloat();
while(balance < 0)
{
printf("HOw much change is owed?");
balance=GetFloat();
}
balance=balance*100;
b=round(balance);
i=b/25+(b%25)/10+((b%25)%10)/5+((b%25)%10%5);
printf("%d\n",i);
}
