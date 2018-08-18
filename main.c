#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MODE 2

int random(int min, int max) {
    return (int)(rand()%(max-min)+min);
}
void generation(int min, int max, int number, int *buffer) {
    for (int counter = 0; counter < number; counter++) {
        buffer[counter] = random(min, max);
    }
}
void selection(int number, int *buffer) {
    for (int counterFirst = 0; counterFirst < number; counterFirst++) {
        for (int counterSecond = counterFirst; counterSecond < number; counterSecond++) {
            if (buffer[counterFirst] > buffer[counterSecond]) {
                int temp = buffer[counterSecond];
                buffer[counterSecond] = buffer[counterFirst];
                buffer[counterFirst] = temp;
            }
        }
    }
}
void bubble(int number, int *buffer) {
    for (int counterFirst = 0; counterFirst < number; counterFirst++) {
        for (int counterSecond = 0; counterSecond < number; counterSecond++) {
            if (buffer[counterSecond] > buffer [counterSecond + 1]) {
                int temp = buffer[counterSecond];
                buffer[counterSecond] = buffer[counterSecond + 1];
                buffer[counterSecond + 1] = temp;
            }
        }
    }
}
void insertion(int number, int *buffer) {
    for (int counterFirst = 0; counterFirst < number; counterFirst++) {
        for (int counterSecond = counterFirst; counterSecond > 0; counterSecond--) {
            if (buffer[counterSecond] < buffer[counterSecond-1]) {
                int tmp = buffer[counterSecond];
                buffer[counterSecond] = buffer[counterSecond-1];
                buffer[counterSecond-1] = tmp;
            }
        }
    }
}

int *resize(int *bufferFirst, unsigned int size) {
    int *bufferSecond = (int*)malloc(size * sizeof(int));

    for(unsigned int counter = 0; counter < size-1; counter++) {
       bufferSecond[counter] = bufferFirst[counter];
    }
    free(bufferFirst);
    return bufferSecond;
}

int main()
{
    FILE *in;
    unsigned int counterFirst = 1;
    int *buffer = (int*) malloc(counterFirst * sizeof (int));

#if MODE == 1
    int min, max;
    unsigned int size;
    in = fopen("in.txt", "w");
    srand(time(NULL));
    printf("Enter number of items generated: ");
    scanf("%d", &size);
    printf("Enter min range for generation: ");
    scanf("%d", &min);
    printf("Enter max range for generation: ");
    scanf("%d", &max);
    buffer = malloc(size * sizeof (int));
    generation(min, max, size, buffer);

    for (int counter = 0; counter < size; counter++) {
        fprintf(in, "%d ", buffer[counter]);
    }
    printf("Enter for closed");
#else
    int type;
    FILE *out;
    clock_t start, stop;
    unsigned int counterMax = 2;

    in = fopen("in.txt", "r");
    out = fopen("out.txt", "w");

    while (fscanf(in, "%d", &buffer[counterFirst-1]) != -1 ) {
        printf("%d %d\n", counterFirst, buffer[counterFirst-1]);
        counterFirst++;
        if (counterFirst == counterMax) {
            counterMax *= 2;
            buffer = resize(buffer, counterMax);
        }
    }

    printf("Enter type sorting(1 - bubble, 2 - selection or 3 - insertion):");
    scanf("%d", &type);

    start = clock();
    if (type == 1) {
        bubble((int) counterFirst, buffer);
    } else if (type == 2) {
        selection((int) counterFirst, buffer);
    } else if (type == 3) {
        insertion((int) counterFirst, buffer);
    }
    stop = clock();

    for (int counterSecond = 0; counterSecond < counterFirst; counterSecond++) {
        if (counterSecond != 0 && counterSecond % 5 == 0)
            fprintf(out, "\n");
        fprintf(out, "%d ", buffer[counterSecond]);
    }

    if (type == 1) {
        printf("Type sort: bubble\nWas sorted %d elements\nTime == %ld", counterFirst-1, (stop-start));
    } else if (type == 2) {
        printf("Type sort: selection\nWas sorted %d elements\nTime == %ld", counterFirst-1, (stop-start));
    } else if (type == 3) {
        printf("Type sort: insertion\nWas sorted %d elements\nTime == %ld",counterFirst-1, (stop-start));
    }
    fclose(out);
    printf("\nEnter for closed");
#endif
    fclose(in);
    return 0;
}
