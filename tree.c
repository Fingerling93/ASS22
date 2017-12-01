#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

enum{TITLE_MAX = 1024};

typedef struct Story
{

	char title[TITLE_MAX];
	char file_a[PATH_MAX];
	char file_b[PATH_MAX];
	struct Story *right;
	struct Story *left;
	char *text;

}Story;



struct Story * initTree(char*,char*,char*,char*);
struct Story * addRight(struct Story * root,char*,char*,char*,char*);
struct Story * addLeft(struct Story * root,char*,char*,char*,char*);


int main()
{

		struct Story *root = initTree("Chapter 1", "Chapter 2", "Chapter 3", "text");
		struct Story **head = (struct Story **) malloc(sizeof( struct Story *));
		
		if(head == NULL)
		{
			printf("memory not allocated\n");
		}
		head = &root;
		struct Story *current = *head;

		current = addRight(current, "Chapter 2", "Chapter 4", "Chapter 5", "text");
		current = addLeft(current, "Chapter 3", "Chapter 6", "Chapter 7", "text");

		current = *head->right; //(  ERROR: head is a pointer...)

		current = addRight(current, "Chapter 4", "Chapter 8", "Chapter 9", "text");
		current = addLeft(current, "Chapter 5", "Chapter 10", "Chapter 11", "text");

		current = *head->left;  // ima error

		current = addRight(current, "Chapter 6", "Chapter 12", "Chapter 13", "text");
		current = addLeft(current, "Chapter 7", "Chapter 14", "Chapter 15", "text");

		//free(story);
		free(head);
		//free(right);
		//for(left);

}

struct Story * addLeft(struct Story * current, char t[TITLE_MAX], char fa[PATH_MAX], char fb[PATH_MAX], char *text)
{
	if(current == NULL)
		return NULL;
	
	struct Story * left = (struct Story*) malloc(sizeof(struct Story));
	if(left == NULL)
	{
		printf("memory not allocated(addLeft)\n");
		return NULL;
	}
	strcpy(left->title,t); // bilo : left->title = t; ERROR 
	left->text = text;
	left->right = NULL;
	left->left = NULL;
	strcpy(left->file_a,fa);
	strcpy(left->file_b,fb);

	current->left = left;
	return current;
}

struct Story * initTree(char t[TITLE_MAX], char f_a[PATH_MAX], char f_b[PATH_MAX], char *text)
{
	struct Story* story = (struct Story*) malloc(sizeof(struct Story));
	if(story == NULL )
	{
		printf("memory not allocted (initTree)\n");
		return NULL;
	}
	strcpy(story->title, t);//story->title = t; ERROR
	story->text = text;
	story->right = story;
	story->left = story;
	strcpy(story->file_a,f_a); // bilo : story->file_a = f_a; ERROR
	strcpy(story->file_b,f_b);

	return story;
}


struct Story * addRight(struct Story *current, char t[TITLE_MAX], char fa[PATH_MAX], char fb[PATH_MAX], char *text)
{
	if(current == NULL)
	{
		printf("memory not allocated (addRight)\n");
		return NULL;
	}
	
	struct Story * right = (struct Story*) malloc(sizeof(struct Story));

	strcpy(right->title, t);
	right->text = text;
	right->right = NULL;
	right->left = NULL;
	strcpy(right->file_a,fa);
	strcpy(right->file_b,fb);

	current->right = right;

	return current;


}


