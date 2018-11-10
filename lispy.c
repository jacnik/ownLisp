#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

#include "external/mpc.h"


long eval_op(long x, char* op, long y)
{
  if (strcmp(op, "+") == 0) {return x + y;}
  if (strcmp(op, "-") == 0) {return x - y;}
  if (strcmp(op, "*") == 0) {return x * y;}
  if (strcmp(op, "/") == 0) {return x / y;}
  return 0;
}

long eval(mpc_ast_t* t) 
{
  /* If tagged as number return it directly  */
  if(strstr(t->tag, "number"))
  {
    return atoi(t->contents);
  }

  /* The operator is always second child */
  char* op = t->children[1]->contents;

  /* Store the third child in 'x' */
  long x = eval(t->children[2]);

  /* Iterate the remaining children and combine */
  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) 
  {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}

void test(mpc_ast_t* t) 
{
/*
typedef struct mpc_ast_t {
	  char* tag;
	  char* contents;
	  mpc_state_t state;
	  int children_num;
	  struct mpc_ast_t** children;
} mpc_ast_t;
*/

  printf("Tag: %s\n", t->tag);
  printf("Contents: %s\n", t->contents);
  printf("Number of children: %i\n", t->children_num);

  for (int i = 0; i < t->children_num; i++)
  {
    printf("\n Child at %i:\n", i);
    mpc_ast_t* child = t->children[i];
    printf("Tag: %s\n", child->tag);
    printf("Contents: %s\n", child->contents);
    printf("Number of children: %i\n", child->children_num);
  }
}

int main(int argc, char** argv) 
{
  /* Create parser */
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  /* Define parsers with the following lanuage */
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                   \
      number  : /-?[0-9]+/ ;                            \
      operator: '+' | '-' | '*' | '/' | '%'             \
      		| \"add\" | \"sub\" | \"mul\"           \
		| \"div\" | \"mod\" ;                   \
      expr    : <number> | '(' <operator> <expr>+ ')' ; \
      lispy   : /^/ <operator> <expr>+ /$/ ;            \
    ",
    Number, Operator, Expr, Lispy);

  /* print Version and Exit information */
  puts("Lispy Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  /* in a never ending loop */
  while(1) 
  {  
    /* Output the prompt and get input */
    char* input = readline("lispy> ");

    /* Add input to history */
    add_history(input);

    /* Attempt to parse the user Input */
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r )) 
    {
	test(r.output); // todo remove

      /* If parsed correctly evaluate and print */
      long result = eval(r.output);
      printf("%li\n", result);
      mpc_ast_delete(r.output);
    } 
    else 
    {
      /* Otherwise Print the Error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    } 

    /* Free retrieved input */
    free(input);
  }

  /* Udefine and Delete the Parsers */
  mpc_cleanup(4, Number, Operator, Expr, Lispy);

  return 0;
}

