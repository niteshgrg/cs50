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
    int len_key;
    len_key=strlen(argv[1]);
    for(int i=0; i<len_key; i++)
    {
        if(!(((argv[1][i]>='a')&&(argv[1][i]<='z'))||((argv[1][i]>='A')&&(argv[1][i]<='Z'))))
        {
            printf("enter alphabatecial key");
            return 1;
        }
    }
    
    
    int len_in,key;
    string in;
    in = GetString();
    len_in=strlen(in);
    
    
    for(int i = 0,j=0;i<len_in;i++)
    {   
        if((argv[1][j]>='a')&&(argv[1][j]<='z'))
        {
            key=argv[1][j]-'a';
        }
        else if((argv[1][j]>='A')&&(argv[1][j]<='Z'))
        {
            key=argv[1][j]-'A';
        }
        
        
        if((in[i]>='a')&&(in[i]<='z'))
        {
            in[i]='a'+(in[i]-'a'+key)%26;
            if(j<len_key-1)
            {
                j++;
            }
            else
            {
                j=0;
            }
        }
        else if((in[i]>='A')&&(in[i]<='Z'))
        {
            in[i]='A'+(in[i]-'A'+key)%26;
            if(j<len_key-1)
            {
                j++;
            }
            else
            {
                j=0;
            }
        }
        else
        {
            in[i]=in[i];
        }

    }
    printf("%s\n",in);
        
    return 0;

}
