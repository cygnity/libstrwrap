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

char *
estrtok(char * str, const char * delim)
{
  static const char empty[] = "\0";
  static char * save_ptr = (char *)empty;

  char *token;

  if (str == NULL) {
    str = save_ptr;
  }
  
  if (str == empty) {
    return NULL;
  }

  token = str;
  str = strpbrk(token, delim);
  if (str == NULL)
    save_ptr = (char *)empty;
  else {
    *str = '\0';
    save_ptr = str + 1;
  }
  return token;
}
