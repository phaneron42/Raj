#include <stdio.h>

#include <stdlib.h>



#define MAX_CYLINDERS 200



void sstf(int requests[], int n, int head) {

    int completed[MAX_CYLINDERS] = {0};

    int seek_count = 0;

    int current_position = head;



    printf("SSTF Disk Scheduling:\n");

    for (int i = 0; i < n; i++) {

        int min_distance = 9999;

        int index = -1;

        for (int j = 0; j < n; j++) {

            if (!completed[j]) {

                int distance = abs(requests[j] - current_position);

                if (distance < min_distance) {

                    min_distance = distance;

                    index = j;

                }

            }

        }

        completed[index] = 1;

        seek_count += min_distance;

        current_position = requests[index];



        printf("Head moved to: %d\n", current_position);

    }

    printf("Total seek time (SSTF): %d\n\n", seek_count);

}



void scan(int requests[], int n, int head, int total_cylinders) {

    int seek_count = 0;

    int current_position = head;

    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            if (requests[i] > requests[j]) {

                int temp = requests[i];

                requests[i] = requests[j];

                requests[j] = temp;

            }

        }

    }



    printf("SCAN Disk Scheduling:\n");

    for (int i = 0; i < n; i++) {

        if (requests[i] >= current_position) {

            seek_count += abs(current_position - requests[i]);

            current_position = requests[i];

            printf("Head moved to: %d\n", current_position);

        }

    }

    if (current_position < total_cylinders - 1) {

        seek_count += abs(current_position - (total_cylinders - 1));

        current_position = total_cylinders - 1;

        printf("Head moved to: %d\n", current_position);

    }

    for (int i = 0; i < n; i++) {

        if (requests[i] < current_position) {

            seek_count += abs(current_position - requests[i]);

            current_position = requests[i];

            printf("Head moved to: %d\n", current_position);

        }

    }



    printf("Total seek time (SCAN): %d\n\n", seek_count);

}



void clook(int requests[], int n, int head) {

    int seek_count = 0;

    int current_position = head;



    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            if (requests[i] > requests[j]) {

                int temp = requests[i];

                requests[i] = requests[j];

                requests[j] = temp;

            }

        }

    }



    printf("C-Look Disk Scheduling:\n");

    for (int i = 0; i < n; i++) {

        if (requests[i] >= current_position) {

            seek_count += abs(current_position - requests[i]);

            current_position = requests[i];

            printf("Head moved to: %d\n", current_position);

        }

    }



    if (current_position != requests[n - 1]) {

        seek_count += abs(current_position - requests[0]);

        current_position = requests[0];

        printf("Head moved to: %d\n", current_position);

    }

    for (int i = 1; i < n; i++) {

        seek_count += abs(current_position - requests[i]);

        current_position = requests[i];

        printf("Head moved to: %d\n", current_position);

    }



    printf("Total seek time (C-Look): %d\n\n", seek_count);

}



int main() {

    int requests[] = { 98, 183, 37, 122, 14, 124, 65, 67 };

    int n = sizeof(requests) / sizeof(requests[0]);

    int initial_head = 50; 

    int total_cylinders = MAX_CYLINDERS; 

    sstf(requests, n, initial_head);



    int requests_scan[n];

    for (int i = 0; i < n; i++) {

        requests_scan[i] = requests[i];

    }

    scan(requests_scan, n, initial_head, total_cylinders);

    int requests_clook[n];

    for (int i = 0; i < n; i++) {

        requests_clook[i] = requests[i];

    }

    clook(requests_clook, n, initial_head);



    return 0;

}

