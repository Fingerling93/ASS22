#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

enum {STORY_MAX = 12, TITLE_MAX = 1024};

typedef struct 
{

	char title[TITLE_MAX];
	char file_a[PATH_MAX];
	char file_b[PATH_MAX];
	// story *right;
	// story *left;
	char *text;

} story;

int read_files(story *chapters, char *filename);

int main(int argc, char **argv)
{
	int num = 0;
	int story_count = 0;
	story stories[STORY_MAX] = {{.title = ""}};
	char *filename = argv[1];
	//
	/* read all file_a filenames */
	while(num < STORY_MAX && read_files(&stories[num], filename))
	{
		filename = stories[num].file_a;
		num++;	
	}
	story_count = num;  /* current story count of all file_a */
	
	for(int count = 0; count < STORY_MAX-story_count; count++) /* find all file_b files */
  {
    while(num < STORY_MAX && read_files(&stories[num], stories[count].file_b))
    {
      filename = stories[count++].file_b;
      num++;
    }
  }



	for(int count = 0; count < num; count++) /* output stories content */
	{
		printf ("%s\n%s\n%s\n%s\n", 
                stories[count].title, stories[count].file_a, 
                stories[count].file_b, stories[count].text);
		free(stories[count].text);
	}

	return 0;

}


/* read values into struct story 'chapters' from 'filename' */
int read_files(story *chapters, char *filename)
{
	size_t length = 0;  								/* strlen */
	size_t text_size = 0;								/* total text_size*/
	size_t nul_char = 0;								/* flag for +1 on first allocation */
	char buffer[TITLE_MAX] = "";				/* read buffer for 'text' */
	FILE *fp = fopen(filename, "r");  	/* file pointer */

	if(!fp)
	{	
	
		return 0;		/* validate file open for reading or return 0 (silent, no file a or b)*/
	}

	if(fgets(chapters->title, TITLE_MAX, fp) == 0) /* read title */
	{
  	printf ("error: failed to read title from '%s'.\n",filename);
  	return 0;
	}
	length = strlen(chapters->title);   /* get title length */

	if(length && chapters->title[length - 1] == '\n')  /* check last char is '\n' */
	{
		chapters->title[--length] = 0;	 /* overwrite with nul-character */
	}
	else  		/* handle error if line too long */
	{
     printf ("error: title too long, filename '%s'.\n", filename);
     return 0;
	}

	if(fgets(chapters->file_a, PATH_MAX, fp) == 0) /* same for file_a */
	{
  	printf ("error: failed to read file_a from '%s'.\n", filename);
    return 0;
	}
	length = strlen(chapters->file_a);

	if(length && chapters->file_a[length - 1] == '\n')
	{
  	chapters->file_a[--length] = 0;
	}
	else
	{
    printf("error: file_a too long, filename '%s'.\n",filename);
    return 0;		
	}

	if(fgets(chapters->file_b, PATH_MAX, fp) == 0) /* same for file_b */
	{
    printf ("error: failed to read file_y from '%s'.\n", filename);
    return 0;
	}
	length = strlen(chapters->file_b);

	if(length && chapters->file_b[length - 1] == '\n')
	{
		chapters->file_b[--length] = 0;
	}
	else
	{
    printf ("error: file_y too long, filename '%s'.\n",filename);
    return 1;		
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

		void *tmp = realloc (chapters->text, text_size + length + nul_char);

		if(!tmp)
		{
			printf("realloc failed\n");
			break;
		}

		chapters->text = tmp;

		if(nul_char)
		{
			*(chapters)->text = 0;
		}
		strcat(chapters->text, buffer);
		text_size += (length + 1);
	}

	fclose(fp);
	return 1;
}