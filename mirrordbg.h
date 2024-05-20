#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void dbg(const char *str) { printf("%s", str); }

char *itoa(int _n) {
  int absn = _n < 0 ? -_n : _n;
  char *buf = (char *)malloc(20);
  int pos = 1;
  int i;
  if (_n == 0) {
    buf[0] = '0';
    buf[1] = '\0';
    return buf;
  }

  for (i = 0; i < 20; i++) {
    if (pos > absn) {
      break;
    }
    buf[i] = (absn % (pos * 10)) / pos + '0';
    pos *= 10;
  }

  for (int x = 0; x < i / 2; x++) {
    char tmp = buf[x];
    buf[x] = buf[i - x - 1];
    buf[i - x - 1] = tmp;
  }
  if (_n < 0) {
    for (int x = i - 1; x >= 0; x--) {
      buf[x + 1] = buf[x];
    }
    buf[0] = '-';
    i++;
  }
  buf[i] = '\0';
  return buf;
}
