/*
 Copyright 2018 Aaron Liu <dexin@informedia.net.cn>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "strwrap.h"

#undef  strtok_r
#undef estrtok_r

extern char * strtok_r(char *s, const char *delim, char **save_ptr);
extern char * estrtok_r(char *s, const char *delim, char **save_ptr);
static char *(*FUNC_STRTOK_R)(char *, const char *, char **);

/**
 * Make argv array (*arvp) for tokens in s which are separated by
 * delimiters. Return -1 on error or the number of tokens otherwise.
 */
int 
makeargv(char ***argvp, const char *s, const char *delimiters, int flag)
{
  int argc;
  char *t, *next;
  int i;

  if (flag == NOTOKENS) {
    FUNC_STRTOK_R = &strtok_r;
    s += strspn(s, delimiters);
  }
  else {
    FUNC_STRTOK_R = &estrtok_r;
  }

  // STEP1: calculate value of argc

  if ((t = (char *) calloc(strlen(s) + 1, sizeof(char))) == NULL) {
    *argvp = NULL;
    return -1;
  }

  strcpy(t, s);

  if ((*FUNC_STRTOK_R)(t, delimiters, &next) == NULL) {
    argc = 0;
  }
  else {
    for (argc = 1; (*FUNC_STRTOK_R)(NULL, delimiters, &next) != NULL; argc++)
      ;
  }

  free(t);

  // STEP2: make argv

  if ((t = (char *) calloc(strlen(s) + 1, sizeof(char))) == NULL) {
    *argvp = NULL;
    return -1;
  }

  strcpy(t, s);

  if ((*argvp = (char **) calloc(argc + 1, sizeof(char *))) == NULL) {
    free(t);
    *argvp = NULL;
    return -1;
  }

  if (argc == 0) {
    free(t);
    **argvp = NULL;
    return 0;
  }

  **argvp = (*FUNC_STRTOK_R)(t, delimiters, &next);
  for (i = 1; i <= argc; i++) {
    *((*argvp) + i) = (*FUNC_STRTOK_R)(NULL, delimiters, &next);
  }

  return argc;
}

void
freeargv(char ***argvp)
{
  char     *t = **argvp;
  char **argv = *argvp;

  if (t != NULL) {
    free(t);
  }

  if (argv != NULL) {
    free(argv);
  }

  *argvp = NULL;
}
