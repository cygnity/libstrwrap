/*
 Copyright 2018-2019 Aaron Liu <dexin@informedia.net.cn>

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
#include <ctype.h>

char *
strtrim(char * str)
{

  if (str == NULL)
    return NULL;

  if (*str == '\0')
    return str;

  char *s = str + 0;
  char *e = str + (strlen(str) - 1);

  while (s != e && isspace(*s))
    *s++ = '\0';

  while (e != s && isspace(*e))
    *e-- = '\0';

  if (s == e && isspace(*s))
    *s = '\0';

  if (str != s)
    memmove(str, s, strlen(s) + 1);

  return str;
}
