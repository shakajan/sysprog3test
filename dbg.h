#include "mystdio.h"
#include <assert.h>

void dbg(const char *_buf) {
  if (write(stdout, _buf, strlen(_buf)) < 0) {
    exit(1);
  }
}

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

void PrintInt(int a) {
  char *ptr = itoa(a);
  dbg(ptr);
  free(ptr);
}
/*
void dbgstream(FILE *file) {
  dbg("\n::stream dbg start::\n");
  dbg("file descriptor:: ");
  PrintInt(file->fd);
  dbg("\nfile descriptor offset:: ");
  PrintInt(lseek(file->fd, 0, SEEK_CUR));
  dbg("\neof: ");
  PrintInt(file->eof);
  dbg("\nlastop: ");
  switch (file->lastop) {
  case 'o':
    dbg("open");
    break;
  case 'w':
    dbg("write");
    break;
  case 'r':
    dbg("read");
    break;
  case 'f':
    dbg("flush");
    break;
  case 's':
    dbg("seek");
    break;
  default:
    dbg("unknown");
    break;
  }
  dbg("\npos: ");
  PrintInt(file->pos);
  dbg("\nsize: ");
  PrintInt(file->size);
  dbg("\nbuffer: ");
  dbg(file->buffer);
  dbg("\nbuffer position: ");
  PrintInt(file->buf_pos);
  dbg("\nbuffer len: ");
  PrintInt(file->buf_len);
  dbg("\n\n::stream dbg end::\n\n");
}
*/
