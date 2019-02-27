int fib(int n) {
  int first = 0;
  int second = 1;
  int next;

  for (int c = 0; c < n; c = c + 1) {
    if (c <= 1) {
      next = c;
    } else {
      next = first + second;
      first = second;
      second = next;
    }
  }

  return next;
}

int limit = read();

