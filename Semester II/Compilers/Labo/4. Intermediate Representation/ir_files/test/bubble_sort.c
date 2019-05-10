// sort an array using the bubble sort algorithm

int iterations = 1024;

// FIXME: variable-size arrays
// FIXME: larger arrays (requires a bump in stack size, or proper malloc)
int n = 512;
int numbers[512];

int seed = 1;

int i; int j;
int a; int b;
int switches;
int rand;

for (i = 0; i < iterations; i = i + 1) {
    // pseudo-randon number generation
    for (j = 0; j < n; j = j+1) {
        // Get random number
        seed = seed * 1103515245 + 12345;
        rand = (seed/65536) % 32768;

        numbers[j] = rand;
    }

    // bubble sort
    switches = 1;
    while (switches > 0) {
        switches = 0;

        for (j = 0; j < n-1; j = j+1) {
            a = numbers[j];
            b = numbers[j+1];
            if (b < a) {
                switches = switches + 1;
                numbers[j] = b;
                numbers[j+1] = a;
            }
        }
    }
}

// check if sorted
int sorted = 1;
for (j = 0; j < n-1; j = j+1) {
    if (numbers[j] > numbers[j+1]) {
        sorted = 0;
    }
}
echo(sorted);
