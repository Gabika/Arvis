/* 
   IGraph library.
   Copyright (C) 2007  Gabor Csardi <csardi@rmki.kfki.hu>
   MTA RMKI, Konkoly-Thege Miklos st. 29-33, Budapest 1121, Hungary
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#ifndef REST_GML_TREE_H
#define REST_GML_TREE_H

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

__BEGIN_DECLS

#include "types.h"

typedef enum { IGRAPH_I_GML_TREE_TREE=0, 
	       IGRAPH_I_GML_TREE_INTEGER,
	       IGRAPH_I_GML_TREE_REAL,
	       IGRAPH_I_GML_TREE_STRING,
	       IGRAPH_I_GML_TREE_DELETED } igraph_i_gml_tree_type_t;

typedef struct igraph_gml_tree_t {
  igraph_vector_ptr_t names;
  igraph_vector_char_t types;
  igraph_vector_ptr_t children;
} igraph_gml_tree_t;

int igraph_gml_tree_init_integer(igraph_gml_tree_t *t, 
				 const char *name, int namelen,
				 igraph_integer_t value);
int igraph_gml_tree_init_real(igraph_gml_tree_t *t, 
			      const char *name, int namelen,
			      igraph_real_t value);
int igraph_gml_tree_init_string(igraph_gml_tree_t *t,
				const char *name, int namelen,
				const char *value, int valuelen);
int igraph_gml_tree_init_tree(igraph_gml_tree_t *t,
			      const char *name, int namelen,
			      igraph_gml_tree_t *value);
void igraph_gml_tree_destroy(igraph_gml_tree_t *t);

void igraph_gml_tree_delete(igraph_gml_tree_t *t, long int pos);
int igraph_gml_tree_mergedest(igraph_gml_tree_t *t1, igraph_gml_tree_t *t2);

long int igraph_gml_tree_length(const igraph_gml_tree_t *t);
long int igraph_gml_tree_find(const igraph_gml_tree_t *t,
			      const char *name, long int from);
long int igraph_gml_tree_findback(const igraph_gml_tree_t *t,
				  const char *name, long int from);
int igraph_gml_tree_type(const igraph_gml_tree_t *t, long int pos);
const char *igraph_gml_tree_name(const igraph_gml_tree_t *t, long int pos);
igraph_integer_t igraph_gml_tree_get_integer(const igraph_gml_tree_t *t,
					     long int pos);
igraph_real_t igraph_gml_tree_get_real(const igraph_gml_tree_t *t,
				       long int pos);
const char *igraph_gml_tree_get_string(const igraph_gml_tree_t *t,
				       long int pos);

igraph_gml_tree_t *igraph_gml_tree_get_tree(const igraph_gml_tree_t *t,
					    long int pos);
#endif
