#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ERR_FILE "[ERR] Could not read file %s.\n"
#define ERR_USER "[ERR] Please enter A or B.\n"
#define ERR_MEM "[ERR] Out of memory.\n"
#define ERR_RUN "Usage: ./ass2 [file-name]\n"
#define LINE "------------------------------\n"

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
int print_story(struct Story *strt);
int check_input(void);
void flushScanf(void);

int main(int argc, char **argv)
{
	int num = 0;
	int story_count = 0;

	if(argc != 2)
	{
		printf(ERR_RUN);
		return 1;

	}
	char *filename = argv[1];
	
	struct Story *start = read_files(filename);
	
	//printf("Right:\n %s\n%s\n%s\n%s\n",new_r->title, new_r->file_a, new_r->file_b, new_r->text );
	//printf("LEFT\n %s\n%s\n%s\n%s\n", new_l->title, new_l->file_a, new_l->file_b, new_l->text);

	//start = new_r;
	//new_r = start->right;

	//printf("Right2:\n %s\n%s\n%s\n%s\n",new_r->title, new_r->file_a, new_r->file_b, new_r->text );	

	int check = print_story(start);
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
		//printf ("[ERR] Could not read file %s. \n",filename);
		return NULL;		/* validate file open for reading or return 0 (silent, no file a or b)*/
	}

	char temp[TITLE_MAX] = "";
	struct Story *rc = malloc(sizeof(struct Story)); // does not need a cast (struct Story*)

	if(fgets(rc->title, TITLE_MAX, fp) == 0)				 /* read title */
	{
  	printf ("[ERR] Could not read file %s.\n", filename);
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

	//printf("%s\n%s\n%s\n%s\n",rc->title,rc->file_a,rc->file_b,rc->text );
	fclose(fp);
	return rc;
}

int print_story(struct Story *start)
{	
	int choice = 0;
	int end = 1;

	struct Story *new_r = malloc(sizeof(struct Story*));
	struct Story *new_l = malloc(sizeof(struct Story*));
	
		do
		{		
			printf(LINE);
			if((start->right == NULL) && (start->left) == NULL)
			{
				printf("%s\n\n%s\n\nENDE\n", start->title, start->text);
				return end; // uhvati ga u main i if 1, return 0
			}
			printf("%s\n\n%s\n\nDeine Wahl (A/B)?", start->title, start->text);
			choice = check_input();
			
			if (choice == EOF)
			{
				return end;
			}
			if(choice == 2)
			{
				new_r = start->right;
				start = new_r;
			}
			else
			{
				new_l = start->left;
				start = new_l;
			}
		}
		while( end == 1);
	}


int check_input(void)
{	
  char check = 0;
  int return_value = 0;
  int num = 0;
  int correct_input = 0;
  int choice = 0;
  
  do 
  {
    return_value = scanf(" %c",&check);
    
    if (return_value == EOF)
    {
      return EOF;
    }
    else if (return_value == 1)
    {    	
    	if(check == 'A')
    	{
    		choice = 1;
    		correct_input = 1;
    	}
    	else if(check == 'B')
    	{
    		choice = 2;
    		correct_input = 1;
    	}
    	else
    	{
    		printf(ERR_USER);

    	}	
    }
  } while (correct_input == 0);

  return choice;
}
/*
void flushScanf(void)
{
  char c = 0;

  while (c != '\n')
  {
    scanf("%c", &c);
  }
}
*/