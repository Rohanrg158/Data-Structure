#include <stdio.h>
int main() {
    int frames, pages, i, j, k, flag, faults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &pages);
    int ref[pages], frame[frames];
    printf("Enter page reference string:\n");
    for(i = 0; i < pages; i++) {
        scanf("%d", &ref[i]);
    }
    for(i = 0; i < frames; i++) {
        frame[i] = -1;
    }
    int index = 0; 
    for(i = 0; i < pages; i++) {
        flag = 0;
        for(j = 0; j < frames; j++) {
            if(frame[j] == ref[i]) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) { 
            frame[index] = ref[i];
            index = (index + 1) % frames;
            faults++;
        }
        printf("\nFrames: ");
        for(k = 0; k < frames; k++) {
            if(frame[k] != -1)
                printf("%d ", frame[k]);
            else
                printf("- ");
        }
    }
    printf("\n\nTotal Page Faults = %d\n", faults);
    return 0;
}
