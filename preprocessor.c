/************************************************************
 * File name: processor.c
 * Author: sky    Version: 0.1    Date: 2018-01-06
 * Description:
 * Others:
 * Function List:
 * History:
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MACRO_NAME_SIZE 64
#define MACRO_VALUE_SIZE 32
#define MACRO_TABLE_SIZE 16
#define WORD_BUFFER_SIZE 128

/* macro item with macro name and it's value */
typedef struct MacroItem
{
	char* name;	// to record macro name 
	char* value;	// to record marco value
} macroitem;

/* macro table bulid with macro item and top.
 * when input the table, it likes a link table. */
typedef struct MacroTable
{
	macroitem item[MACRO_TABLE_SIZE];	// a array to get marco
	int top;				// top is to record the top of table
} macrotable;

/* function prototype declaration */
void buildTable(FILE* input, macrotable* table);

int main (int argc, char* argv[])
{
	FILE* psrc_file;	// source file pointer
	FILE* ptrgt_file;	// target file pointer
	macrotable temp_macro_table;	// a temporary macro table
	macrotable* ptemp_macro_table;	// pointer to the temporary macro table

	ptemp_macro_table = &temp_macro_table;

	/* Open file with file pointer */
	if(!(psrc_file = fopen(argv[1], "r")))
	{
		printf("Can't open source file\n");
	}

	if(!(ptrgt_file = fopen("trgt.c", "w+")))
	{
		printf("Can't make target file\n");

	}// end of if(!(lfpv_trgtFile = fopen("trgt.c", "w+")))

	buildTable(psrc_file, ptemp_macro_table);

	/* other code for main function */
	
	return 0;
}

/*****************************************************************
 * Function: bulidTable()
 * Description: To macro in the source file and store them in 
 * 	a table. All macro value is the final value. That mean
 * 	they are not formula. 
 * Calls: 
 * Called By: main()
 * Input: 
 * 	FILE* input -- pointer to the source file.
 * 	macrotable* table -- pointer to the new macro table.
 * Output:
 * Return:
 * Others:
 *****************************************************************/
void buildTable(FILE* input, macrotable* table)
{
	table->top = 0; // initiate the macro table 
	
	const char def_sign[] = "#define"; 	// a const char variable
	char word_buffer[WORD_BUFFER_SIZE];	// a buffer to get the each word	

	while (!feof(input))
	{
		/* match the string "#define" */
		fscanf(input, "%s", word_buffer);
		int hit_flg = strcmp(def_sign, word_buffer); 

		if (hit_flg == 0)
		{
			/* get name from source file */
			fscanf(input, "%s", word_buffer);
			table->item[table->top].name 
				= (char*)malloc(sizeof(char) * MACRO_NAME_SIZE);
			strcpy(table->item[table->top].name, word_buffer);

			/* get value from source file */
			fscanf(input, "%s", word_buffer);
			table->item[table->top].value
				= (char*)malloc(sizeof(char) * MACRO_VALUE_SIZE);
			strcpy(table->item[table->top].value, word_buffer);

			/* check if overstep the boundary */
			if (table->top < MACRO_TABLE_SIZE)
			{
				table->top++;
			} // end of if (table->top < MACRO_TABLE_SIZE)
			else
			{
				printf("Too much defines! Overstep the boundary!\n");
			} // end of else of if (table->top < MACRO_TABLE_SIZE)
		} // end of if(hit_flg == 0)
	} // end of while(!(feof(input)) 
}
