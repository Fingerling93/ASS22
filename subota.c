#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

enum {STORY_MAX = 12, TITLE_MAX = 1024};

typedef struct story
{

	char title[TITLE_MAX];
	//char file_a[PATH_MAX];
	//char file_b[PATH_MAX];
	struct story *right;
	struct story *left;
	char *text;

} story;

story *read_files(char *filename);

int main(int argc, char **argv)
{
	int num = 0;
	int story_count = 0;
	//story stories[STORY_MAX] = {{.title = ""}};
	
	char *filename = argv[1];
	read_files(filename);
	
	/*	while(num < STORY_MAX && read_files(&stories[num], filename))
	{
		filename = stories[num].file_a;
		num++;	
	}
	story_count = num;  
	
	for(int count = 0; count < STORY_MAX-story_count; count++) 
  {
    while(num < STORY_MAX && read_files(&stories[num], stories[count].file_b))
    {
      filename = stories[count++].file_b;
      num++;
    }
  }
*/


	/*for(int count = 0; count < num; count++) 
	{
		printf ("%s\n%s\n%s\n%s\n", 
                stories[count].title, stories[count].file_a, 
                stories[count].file_b, stories[count].text);
		free(stories[count].text);
	}*/

	return 0;

}


/* read values into struct story 'chapters' from 'filename' */
story *read_files(char *filename)
{
	size_t length = 0;  								/* strlen */
	size_t text_size = 0;								/* total text_size*/
	size_t nul_char = 0;								/* flag for +1 on first allocation */
	char buffer[TITLE_MAX] = "";				/* read buffer for 'text' */
	
	FILE *fp = fopen(filename, "r");  	/* file pointer */

	if(!fp)
	{		
		return NULL;		/* validate file open for reading or return 0 (silent, no file a or b)*/
	}

	char temp[TITLE_MAX] = "";
	struct story *rc = (struct story*) malloc(sizeof(struct story)); 

	if(fgets(rc->title, TITLE_MAX, fp) == 0) /* read title */
	{
  	printf ("error: failed to read title from '%s'.\n",filename);
  	return 0;
	}
	length = strlen(rc->title);   /* get title length */

	if(length && rc->title[length - 1] == '\n')  /* check last char is '\n' */
	{
		rc->title[--length] = 0;	 /* overwrite with nul-character */
	}
	/*else  		
	{
     printf ("error: title too long, filename '%s'.\n", filename);
     return 0;
	}*/

	if(fgets(temp, PATH_MAX, fp) == 0) 
	{
  	printf ("error: failed to read file_a from '%s'.\n", filename);
    return 0;
	}
	length = strlen(temp);

	if(length && temp[length - 1] == '\n')
	{
  	temp[--length] = 0;
	}
	// TEMP now contains option a's filename


	story *make_a = read_files(temp);

	if( make_a != NULL)
	{
		rc->left = make_a;
	}
	// temp = fread(fp)
	fgets(temp, PATH_MAX, fp);


	if(fgets(temp, PATH_MAX, fp) == 0) 
	{
    printf ("error: failed to read file_y from '%s'.\n", filename);
    return 0;
	}
	length = strlen(temp);

	if(length && temp[length - 1] == '\n')
	{
		temp[--length] = 0;
	}
	/*else
	{
    printf ("error: file_y too long, filename '%s'.\n",filename);
    return 1;		
	}*/
	story *make_b = read_files(temp);

	if( make_b != NULL)
	{
		rc->right = make_b;
	}

	/* Read text in TITLE_MAX chunks*/
	while(fgets(buffer, TITLE_MAX, fp))
	{
		length = strlen(buffer);

		//if(length && buffer[length - 1] == '\n')  /* check for '\n' */
		//{
			//buffer[length - 1] = ' '; /* overwrite with ' ' for concat */
		//}
		if(text_size == 0)		/* account for space for '\0' when empty, and  */
		{											/* and use flag to set new block to empty-string*/
			nul_char = 1;				
		}
		else
		{
			nul_char = 0;
		}

		void *tmp = realloc (rc->text, text_size + length + nul_char);

		if(!tmp)
		{
			printf("realloc failed\n");
			break;
		}

		rc->text = tmp;

		if(nul_char)
		{
			*(rc)->text = 0;
		}
		strcat(rc->text, buffer);
		text_size += (length + 1);
	}

	printf("RC:\n%s\n%s\n",rc->title,rc->text );
	free(rc); // not sure if ok here
	fclose(fp);
	return rc;
}