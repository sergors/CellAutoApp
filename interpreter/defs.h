#ifndef DEFS_H
#define DEFS_H

#include <string>
using namespace std;

#define MAXTEXT    1000000
#define MAXLEX     1000
#define MAXKEY     11
#define MAX_INT    17
#define MAX_DOUBLE 20
typedef char LEX[MAXLEX];
typedef char TEXT[MAXTEXT];

//иденификатор и ключевые слова
#define t_id           1
#define t_var          2
#define t_int          3
#define t_long         4
#define t_double       5
#define t_bool         6
#define t_neig         9
#define t_class_array  10
#define t_cell_auto    11
#define t_system       12
#define t_const        13
#define t_new          14
#define t_int_const    15
#define t_long_const   16
#define t_double_const 17
#define t_bool_const   18


#define t_op_brace         19   //   {
#define t_cl_brace         20   //   }
#define t_op_round_bkt     21   //   (
#define t_cl_round_bkt     22   //   )
#define t_op_square_bkt    23   //   [
#define t_cl_square_bkt    24   //   ]
#define t_semicolon        25   //   ;
#define t_assignment       26   //   =
#define t_scharp           27   //   #
#define t_colon            28   //   :
#define t_dot              29   //   .
#define t_comma            30   //   ,
#define t_lambda           31   //   ->
#define t_star             32   //   *
#define t_plus             33   //   +
#define t_minus            34   //   -
#define t_div              35   //   /
#define t_more             36   //   >
#define t_more_equal       37   //   >=
#define t_less             38   //   <
#define t_less_equal       39   //   <=
#define t_equal            40   //   ==
#define t_not_equal        41   //   !=
#define t_and              42   //   &&
#define t_or               43   //   ||


#define t_end              50   //   $

#define t_error       200
#define t_undefined   300

static LEX keywords[MAXKEY] = {
    "var", "int", "bool", "neig", "ClassArray", "true", "false", "CellAuto", "System", "const", "new"
};
static int indexkeywords[MAXKEY] = {
  t_var, t_int, t_bool, t_neig, t_class_array, t_bool_const, t_bool_const, t_cell_auto, t_system, t_const, t_new
};

#endif // DEFS_H
