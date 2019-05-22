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
#define t_id          1
#define t_var         2
#define t_int         3
#define t_long        4
#define t_double      5
#define t_bool        6
#define t_true        7
#define t_false       8
#define t_neig        9
#define t_class_array 10
#define t_cell_auto   11
#define t_system      12
#define t_const       13
#define t_new         14

#define t_op_brace         15   //   {
#define t_cl_brace         16   //   }
#define t_op_round_bkt     17   //   (
#define t_cl_round_bkt     18   //   )
#define t_op_square_bkt    19   //   [
#define t_cl_square_bkt    20   //   ]
#define t_semicolon        21   //   ;
#define t_assignment       22   //   =
#define t_scharp           23   //   #
#define t_colon            24   //   :
#define t_dot              25   //   .
#define t_comma            26   //   ,
#define t_lambda           27   //   ->
#define t_star             28   //   *
#define t_end              29   //   $

#define t_error       200
#define t_undefined   300

#endif // DEFS_H
