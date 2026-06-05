#include <stdio.h>

int main() {
    int pages[50], frames[10];
    int n, f, i, j, k, pos, farthest;
    int pageFaults = 0, found;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++)
        frames[i] = -1;

    for(i = 0; i < n; i++) {
        found = 0;

        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            pageFaults++;

            for(j = 0; j < f; j++) {
                if(frames[j] == -1) {
                    frames[j] = pages[i];
                    found = 1;
                    break;
                }
            }

            if(!found) {
                farthest = -1;
                pos = -1;

                for(j = 0; j < f; j++) {
                    int nextUse = 1000;

                    for(k = i + 1; k < n; k++) {
                        if(frames[j] == pages[k]) {
                            nextUse = k;
                            break;
                        }
                    }

                    if(nextUse > farthest) {
                        farthest = nextUse;
                        pos = j;
                    }
                }

                frames[pos] = pages[i];
            }
        }
    }

    printf("Total Page Faults = %d\n", pageFaults);

    return 0;
}
