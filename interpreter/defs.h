#ifndef DEFS_H
#define DEFS_H

#include <string>
using namespace std;

#define MAXTEXT 1000000
#define MAXLEX 1000
#define MAXKEY 7
typedef char LEX[MAXLEX];
typedef char TEXT[MAXTEXT];

#define t_id          1
#define t_var         2
#define t_int         3
#define t_bool        4
#define t_neig        5

#define t_class_array 10
#define t_cell_auto   11
#define t_system      12
#define t_error       200

#endif // DEFS_H
