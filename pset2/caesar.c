#include<stdio.h>
#include<cs50.h>
#include<string.h>

int main(int argc, string argv[])
{
    if(argc !=2)
    {
        printf("Usage: /home/cs50/pset2/caesar <key>");
        return 1;
    }
    int i, key,len;
    string in;
    key = atoi(argv[1]);
    in = GetString();
    len=strlen(in);
    for(i = 0;i<len;i++)
    {   
        if((in[i]>='a')&&(in[i]<='z'))
        {
            in[i]='a'+(in[i]-'a'+key)%26;
        }
        else if((in[i]>='A')&&(in[i]<='Z'))
        {
            in[i]='A'+(in[i]-'A'+key)%26;
        }
        else
        {
            in[i]=in[i];
        }
        
    }
    printf("%s\n",in);
        
    return 0;

}
