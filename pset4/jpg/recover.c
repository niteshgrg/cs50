/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 #include<stdio.h>
 #include<stdlib.h>
 #include<stdint.h>
 
 typedef uint8_t BYTE;
 typedef uint32_t DWORD;
 
 typedef struct
 {
    BYTE Start[4];
    BYTE Body[508];
 }JPG;
 
    
    
 

int main(int argc, char* argv[])
{
    BYTE C1_Start[4] = {0xff, 0xd8, 0xff, 0xe0};
    BYTE C2_Start[4] = {0xff, 0xd8, 0xff, 0xe1};
    FILE* inptr = fopen("card.raw", "r");
   
    JPG block;
    char title[8];
    int jpgindex=0,firststart=0;
    while(fread(&block, sizeof(JPG), 1, inptr)==1)
    {
        int newstart=0;
        for(int k=0; k<4; k++)
        {
            if((block.Start[k] == C1_Start[k]) || (block.Start[k] == C2_Start[k]))
            {
                newstart++;
                firststart++;    
            }
        }
        if(firststart>=4)
    
        {   
            if(newstart==4)
            {
                sprintf(title, "%03d.jpg", jpgindex);
                FILE* outr = fopen(title, "w");
                fwrite(&block, sizeof(JPG), 1, outr);
                jpgindex++;
                fclose(outr);
            }   
            else
            {
                FILE* outr = fopen(title, "a");
                fwrite(&block, sizeof(JPG), 1, outr);
                fclose(outr);
            }
        }
    }
    fclose(inptr); 
       

}
