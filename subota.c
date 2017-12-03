#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
//**//
enum {STORY_MAX = 12, TITLE_MAX = 1024};

typedef struct Story
{

	char title[TITLE_MAX];
	char file_a[PATH_MAX];
	char file_b[PATH_MAX];
	struct Story *right;
	struct Story *left;
	char *text;

} Story;

struct Story *read_files(char *filename);
//int newline()
void read_text();
int main(int argc, char **argv)
{
	int num = 0;
	int story_count = 0;
	char *filename = argv[1];
	
	struct Story *start = read_files(filename);

	return 0;

}


/* read values into struct story 'chapters' from 'filename' */
struct Story *read_files(char *filename)
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
	struct Story *rc = malloc(sizeof(struct Story)); // does not need a cast (struct Story*)

	if(fgets(rc->title, TITLE_MAX, fp) == 0)				 /* read title */
	{
  	printf ("error: failed to read title from '%s'.\n",filename);
  	return 0;
	}
	length = strlen(rc->title) - 1; 								  /* get title length */

	if(rc->title[length] == '\n')  										/* check last char is '\n' */
	{
		rc->title[length] = 0;													 /* overwrite with nul-character */
	}
	/*else /too long can be added */ 		

	if(fgets(temp, PATH_MAX, fp) == 0) 
	{
  	printf ("error: failed to read file_a from '%s'.\n", filename);
    return 0;
	}
	length = strlen(temp) - 1;

	if(temp[length] == '\n')
	{
  	temp[length] = 0;
	}
	strcpy(rc->file_a, temp);
	// TEMP now contains option a's filename

	Story *make_a = read_files(temp);

	if( make_a != NULL)
	{
		rc->left = make_a;
	}

	if(fgets(temp, PATH_MAX, fp) == 0) 
	{
    printf ("error: failed to read file_y from '%s'.\n", filename);
    return 0;
	}
	length = strlen(temp) - 1;
	
	if(temp[length] == '\n')
	{
		temp[length] = 0;
	}
	strcpy(rc->file_b, temp);
	
	Story *make_b = read_files(temp);

	if( make_b != NULL)
	{
		rc->right = make_b;
	}

	rc->text = read_text();
	/* Read text in TITLE_MAX chunks*/
	while(fgets(buffer, TITLE_MAX, fp))
	{
		length = strlen(buffer);

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

	printf("%s\n%s\n%s\n%s\n",rc->title,rc->file_a,rc->file_b,rc->text );
	fclose(fp);
	return rc;
}

void read_text()
{

}