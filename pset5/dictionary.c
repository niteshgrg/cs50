/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

 unsigned int no_words;

 typedef struct node
 {
 	bool is_word;
 	struct node* children[27];
 }node;


 node* root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
	int i = 0;
	int j;
	node* ptr;
	ptr=root;
    while(word[i]!='\0')
    {
    	if(word[i] >= 'a' && word[i] <= 'z')
    	{
    		j=word[i]-'a';
    	}
    	else if(word[i] >= 'A' && word[i] <= 'Z')
    	{
    		j=word[i] - 'A';
    	}
    	else
    	{
    		j=26;
    	}
    	if(ptr->children[j]!=NULL)
    	{
    		ptr=ptr->children[j];
    		i++;
    	}
    	else
    	{
    		return false;
    	}

    }
    if(ptr->is_word==true)
    {
    	return true;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	
	int j=0;
	node* ptr=NULL;
	no_words=0;
	root=malloc(sizeof(node));
    ptr=root;
    FILE* dict = fopen(dictionary,"r");
   
    for(int i=fgetc(dict); i!=EOF; i=fgetc(dict))
    {
    	
    	if(i>='a' && i<='z')
    	{
    		j=i-'a';
          
    	}
    	else if(i=='\'')
    	{
    		j=26;
    	}
    	else if(i=='\n')
    	{
    		ptr->is_word = true;
    		no_words++;
    		ptr=root;
    		continue;
    	}

    	
        if(ptr->children[j] == NULL)
    	{
    		ptr->children[j] = malloc(sizeof(node));
    		ptr = ptr->children[j];

    	}
    	else
    	{
    		ptr = ptr->children[j];
    	}
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return no_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
void free_node(node* current_node)
{
	for(int i=0;i<27;i++)
    {
        if(current_node->children[i]!=NULL)
        {
            free_node(current_node->children[i]);
        }
    }
    free(current_node);
}

bool unload(void)
{
	
	free_node(root);
   
    return true;
    
}
