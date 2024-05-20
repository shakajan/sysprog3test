
int main(void) {

  dbg("\ntest 1:: fread(1) -> fseek(1, SEEK_CUR) loop test\n");
  FILE *fp11 = fopen("test11", "r");
  // test11 file is "0123456789" * 3 + EOF, 31 byte file.
  char buf[20];
  memset(buf, 0, sizeof(buf));
  for (int i = 0; i < 30; i += 2) {
    int read_size = fread(buf, 1, 1, fp11);
    fseek(fp11, 1, SEEK_CUR);
    assert(read_size == 1);
    assert((buf[0] - '0') == (i % 10));
  }
  fclose(fp11);

  dbg("\ntest 2:: write string over buffer size.\n");
  FILE *fp21 = fopen("test2", "w+");
  const char *s21 = "HELLO";
  for (int i = 0; i < 30; i++) {
    int write_size = fwrite(s21, 1, 5, fp21);
  }
  fclose(fp21);

  dbg("\ntest 3:: write strings at random position, after then, read that "
      "positions.\n");
  FILE *fp31 = fopen("test2", "r+");

  const char *s31 = "YOON";
  int rand[7] = {0, 72, 36, 64, 150, 23, 132};
  for (int i = 0; i < 7; i++) {
    int fseek_rslt = fseek(fp31, rand[i], SEEK_SET);
    int write_size = fwrite(s31, 1, 4, fp31);
  }

  char b31[6] = {0};
  b31[4] = '\0';
  for (int i = 0; i < 7; i++) {
    int fseek_rslt = fseek(fp31, rand[i], SEEK_SET);
    int read_size = fread(b31, 1, 4, fp31);
    assert(strcmp(b31, s31) == 0);
  }
  fclose(fp31);

  dbg("\ntest 4:: write many different strings to one file and check the "
      "length.\n");
  const char *b4a = "rabbit, ";
  const char *b4b = "elephant, ";
  const char *b4c = "chicken, ";
  const char *b4d = "elegator, dragon, camponotus japonicus, ";
  const char *b4e = "are along with human.\n";
  FILE *fp41 = fopen("test4", "w+");
  int w4a = fwrite(b4a, 1, strlen(b4a), fp41);
  int w4b = fwrite(b4b, 1, strlen(b4b), fp41);
  int w4c = fwrite(b4c, 1, strlen(b4c), fp41);
  int w4d = fwrite(b4d, 1, strlen(b4d), fp41);
  int w4e = fwrite(b4e, 1, strlen(b4e), fp41);
  assert(w4a == strlen(b4a));

  fseek(fp41, 0, SEEK_SET);
  char b41[200] = {0};
  int i4_total = fread(b41, 1, 200, fp41);
  fclose(fp41);
  assert(i4_total ==
         strlen(b4a) + strlen(b4b) + strlen(b4c) + strlen(b4d) + strlen(b4e));

  dbg("\ntest 5:: fseek whence SEEK_CUR.\n");
  char b51[25] = {0};
  int ws51;
  FILE *fp51 = fopen("test4", "r");

  const char *b5a = "rabbit";
  memset(b51, 0, sizeof(b51));
  ws51 = fread(b51, 1, strlen(b5a), fp51);
  fseek(fp51, 2, SEEK_CUR);
  assert(strcmp(b5a, b51) == 0);

  const char *b5b = "elephant";
  memset(b51, 0, sizeof(b51));
  ws51 = fread(b51, 1, strlen(b5b), fp51);
  fseek(fp51, 2, SEEK_CUR);
  assert(strcmp(b5b, b51) == 0);

  const char *b5c = "chicken";
  memset(b51, 0, sizeof(b51));
  ws51 = fread(b51, 1, strlen(b5c), fp51);
  fseek(fp51, 2, SEEK_CUR);
  assert(strcmp(b5c, b51) == 0);

  const char *b5d = "elegator";
  memset(b51, 0, sizeof(b51));
  ws51 = fread(b51, 1, strlen(b5d), fp51);
  fseek(fp51, 2, SEEK_CUR);
  assert(strcmp(b5d, b51) == 0);

  const char *b5e = "dragon";
  memset(b51, 0, sizeof(b51));
  ws51 = fread(b51, 1, strlen(b5e), fp51);
  fseek(fp51, 2, SEEK_CUR);
  assert(strcmp(b5e, b51) == 0);

  const char *b5f = "camponotus japonicus";
  memset(b51, 0, sizeof(b51));
  ws51 = fread(b51, 1, strlen(b5f), fp51);
  assert(strcmp(b5f, b51) == 0);

  // reverse test.
  fseek(fp51, -strlen(b5f) - 2 - strlen(b5e), SEEK_CUR);
  memset(b51, 0, sizeof(b51));
  ws51 = fread(b51, 1, strlen(b5e), fp51);
  assert(strcmp(b5e, b51) == 0);

  fclose(fp51);

  dbg("\ntest 6:: fflush test\n");

  FILE *fp62 = fopen("test61", "w");
  const char *b6a =
      "hot blood java programming, java implementation data structure, hot "
      "blood c++ programming, deep learning started at underground, jump to "
      "python, foundations of algorithms, the elements of computing systems, "
      "learning sql, computer netoking: a top-down approach.\n";
  fwrite(b6a, 1, strlen(b6a), fp62);
  assert(fflush(fp62) == 0);

  FILE *fp63 = fopen("test61", "r");
  char b61[300] = {0};
  int i62 = fread(b61, 1, 300, fp63);
  assert(strcmp(b61, b6a) == 0);
  fclose(fp62);
  fclose(fp63);

  dbg("\ntest 7:: append+ mode test.\n");
  FILE *fp71 = fopen("test61", "a+");
  char b71[20] = {0};
  fseek(fp71, 0, SEEK_SET);
  int i71 = fread(b71, 1, 10, fp71);
  assert(i71 == 10);

  fclose(fp71);

  dbg("\ntest 8: fseek -> (fwrite | fread) loop test by brute force style.\n");
  FILE *fp81 = fopen("test81", "w+");
  char b81[10001] = {0};
  for (int i = 0; i < 10000; i++) {
    char *tmp = itoa(i % 10);
    fwrite(tmp, 1, 1, fp81);
    b81[i] = tmp[0];
    free(tmp);
  }

  const int DISTORTION = 83;
  int base = 1;
  char b82[11] = {0};
  for (int i = 0; i < 10000; i++) {
    memset(b82, 0, sizeof(b82));
    fseek(fp81, base, SEEK_SET);

    if (i % 2) {
      fread(b82, 1, 10, fp81);
      char b83[11] = {0};
      memcpy(b83, &b81[base], 10);
      assert(strcmp(b83, b82) == 0);
    } else {
      fwrite("bsmq", 1, 4, fp81);
      memcpy(&b81[base], "bsmq", 4);
    }
    base *= DISTORTION;
    base %= 9967;
  }
  fclose(fp81);

  dbg("\ntest 9: fseek with SEEK_END & non-positive offset.\n");
  FILE *fp91 = fopen("test91", "w+");
  const char *s91 = "The second test of database by S. H. Lee is next monday..";
  int i91 = fwrite(s91, 1, strlen(s91), fp91);
  char *b91 = (char *)malloc(strlen(s91) + 1);

  for (int i = 1; i < strlen(s91); i++) {
    int neg = -i;
    int fskrslt = fseek(fp91, neg, SEEK_END);
    int i92 = fread(b91, 1, strlen(s91), fp91);
    b91[i92] = '\0';
    assert(strcmp(b91, &s91[strlen(s91) - i]) == 0);
  }
  fclose(fp91);
  free(b91);

  dbg("\ntest 10:: fopen test: try to read non-exist file.\n");
  FILE* fp101 = fopen("non-exist", "r");
  assert(fp101 == NULL);

  dbg("\ntest 11:: fflush test: fwrite -> fflush -> assert\n");
  FILE* fp111 = fopen("test111", "w+");
  const char* s111 = "first write";
  const char* s112 = "second write";

  int i111 = fwrite(s111, 1, strlen(s111), fp111);
  int i112 = fflush(fp111);
  assert(i112 != EOF);

  FILE* fp112 = fopen("test111", "r");
  char b111[30] = {0};
  int i113 = fread(b111, 1, 30, fp112);
  assert(i113 == i111);
  
  int i114 = fwrite(s112, 1, strlen(s112), fp111);
  int i115 = fflush(fp111);
  assert(i115 != EOF);

  fseek(fp112, 0, SEEK_SET);
  char b112[30] = {0};
  int i116 = fread(b112, 1, 30, fp112);
  assert(i111 == strlen(s111));
  assert(i114 == strlen(s112));
  assert(i116 == i114 + i111);

  fclose(fp111);
  fclose(fp112);

  return 0;
}
