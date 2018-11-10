#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

#include "external/mpc.h"


int main(int argc, char** argv) {
  
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
  while(1) {
    
    /* Output the prompt and get input */
    char* input = readline("lispy> ");

    /* Add input to history */
    add_history(input);

    /* Attempt to parse the user Input */
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r )) {
      /* On success Print the AST */
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
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

