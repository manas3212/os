#include <stdio.h>
#include <stdbool.h>

// FIFO Page Replacement Algorithm
int fifo_page_faults(int reference_string[], int n, int frame_size) {
    int page_table[frame_size];
    int page_faults = 0;
    int front = 0;

    for (int i = 0; i < frame_size; i++) {
        page_table[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        bool page_found = false;
        int page = reference_string[i];

        for (int j = 0; j < frame_size; j++) {
            if (page_table[j] == page) {
                page_found = true;
                break;
            }
        }

        if (!page_found) {
            page_table[front] = page;
            front = (front + 1) % frame_size;
            page_faults++;
        }
    }

    return page_faults;
}

// LRU Page Replacement Algorithm
int lru_page_faults(int reference_string[], int n, int frame_size) {
    int page_table[frame_size];
    int page_faults = 0;

    for (int i = 0; i < frame_size; i++) {
        page_table[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        bool page_found = false;
        int page = reference_string[i];

        for (int j = 0; j < frame_size; j++) {
            if (page_table[j] == page) {
                page_found = true;
                // Move the accessed page to the end of the table (most recently used)
                for (int k = j; k < frame_size - 1; k++) {
                    page_table[k] = page_table[k + 1];
                }
                page_table[frame_size - 1] = page;
                break;
            }
        }

        if (!page_found) {
            // If a page fault occurs, replace the first page (least recently used)
            for (int j = 0; j < frame_size - 1; j++) {
                page_table[j] = page_table[j + 1];
            }
            page_table[frame_size - 1] = page;
            page_faults++;
        }
    }

    return page_faults;
}

// Optimal Page Replacement Algorithm
int optimal_page_faults(int reference_string[], int n, int frame_size) {
    int page_table[frame_size];
    int page_faults = 0;

    for (int i = 0; i < frame_size; i++) {
        page_table[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        bool page_found = false;
        int page = reference_string[i];

        for (int j = 0; j < frame_size; j++) {
            if (page_table[j] == page) {
                page_found = true;
                break;
            }
        }

        if (!page_found) {
            int replace_index = -1;
            int furthest_used = -1;

            for (int j = 0; j < frame_size; j++) {
                int page_in_memory = page_table[j];
                int next_use = n;  // Default to the last occurrence

                for (int k = i + 1; k < n; k++) {
                    if (reference_string[k] == page_in_memory) {
                        next_use = k;
                        break;
                    }
                }

                if (next_use > furthest_used) {
                    furthest_used = next_use;
                    replace_index = j;
                }
            }

            page_table[replace_index] = page;
            page_faults++;
        }
    }

    return page_faults;
}

int main() {
    int reference_string[] = {5, 7, 1, 3, 4, 1, 6, 2, 3, 5};
    int n = sizeof(reference_string) / sizeof(reference_string[0]);
    int frame_size = 3;

    int fifo_faults = fifo_page_faults(reference_string, n, frame_size);
    int lru_faults = lru_page_faults(reference_string, n, frame_size);
    int optimal_faults = optimal_page_faults(reference_string, n, frame_size);

    printf("FIFO Page Faults: %d\n", fifo_faults);
    printf("LRU Page Faults: %d\n", lru_faults);
    printf("Optimal Page Faults: %d\n", optimal_faults);

    return 0;
}
