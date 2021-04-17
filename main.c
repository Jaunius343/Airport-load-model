#include <stdio.h>
#include <stdlib.h>

#include "pq_struct.h"
#include "priority_queue.h"
#include "priority_queue.c"
#include "big_int.h"
#include "big_int.c"

#define COUNT 11
#define TIME_SIZE 32

int main()
{
    //generating airplane priority queue
    srand(0);
    int rng = 0 + rand()% (1 - 0 + 1);
//    printf("%d", rng);

    int takeoff_count = 0,
        land_count = 0;
    Node* airplanes = new_node(1, rng);
    if (rng == 0){
        ++land_count;
    } else {
        ++takeoff_count;
    }
    for (int i = 2; i <= COUNT; ++i){
        rng = 0 + rand()% (1 - 0 + 1);

        if (rng == 0){
            ++land_count;
        } else {
            ++takeoff_count;
        }
        printf("%d", rng);
        enque(&airplanes, i, rng);
    }

    printf("\n");
    print_list(airplanes);
    printf("\n");
//    Node* temp = airplanes;
//    while (temp != NULL)
//    for(int i = 0; i < COUNT - 1; ++i){
//        printf("%d ", airplanes[i].data);
//    }
    printf("\ntake off: %d", takeoff_count);
    printf("\nlanding: %d", land_count);

    //reading data from file
    FILE *read;
    read = fopen("duom.txt", "r");
    char temp_land_time[TIME_SIZE],
         temp_takeoff_time[TIME_SIZE],
         temp_fuel_time[TIME_SIZE];

    if(read != NULL){
        fscanf(read, "%s %s %s", &temp_land_time, &temp_takeoff_time, &temp_fuel_time);
    } else {
        printf("\nCouldn't open file\n" );
    }

    big_int *land_time,
            *takeoff_time,
            *fuel_time;
    land_time = new_big_int(temp_land_time);
//    printf("\n");
//    print_big_int(land_time);
    takeoff_time = new_big_int(temp_takeoff_time);
    fuel_time = new_big_int(temp_fuel_time);

    int planes_left = COUNT;
    big_int *time_passed = new_big_int("000");

    int flag = 0;
    while (planes_left > 0){
        printf("\nplanes left: %d", planes_left);
        rng = 0 + rand()% (100 - 0 + 1);
        printf("\nrng: %d", rng);
        if (rng > 50){
            printf("\nland count: %d", land_count);
            if (land_count > 0){
                printf("\n");
                print_big_int(time_passed);
                print_big_int(land_time);
                time_passed = add_big_int(time_passed, land_time);
                big_int *temptemp = sub_big_int(fuel_time, time_passed);
                printf("%c", temptemp->sign);
                printf("\nfuel time - time passed = ");
                print_big_int(temptemp);
                if(temptemp->sign == '-'){
                    flag = 1;
                    break;
                }
                print_big_int(time_passed);
                --land_count;
            } else {
                time_passed = add_big_int(time_passed, takeoff_time);
                --takeoff_count;
            }
            deque(&airplanes);
            --planes_left;
        } else {

        }
        printf("\n");
    }
    printf("\ntotale time passed: ");
    print_big_int(time_passed);
    if(flag == 1){
        printf("\n plane crash\n");
    }
//    printf("\n%s %s %s\n", land_time, takeoff_time, fuel_time);

//    Node* pq = new_node(9, 0);
//    printf("is it empty: ");
//    if (is_empty(pq)){
//        printf("yes\n");
//    } else {
//        printf("no\n");
//    }
//    print_list(pq);
//
//    enque(&pq, 8, 0);
//    enque(&pq, 5, 2);
//    enque(&pq, 10, 1);
//    enque(&pq, 7, 0);
//    print_list(pq);
//    printf("top: %d\n", top(&pq));
//    printf("queue size: %d\n", queue_size(pq));
//    printf("is it full: ");
//    if (is_full(pq) == 1){
//        printf("yes\n");
//    } else {
//        printf("no\n");
//    }
//    print_list(pq);
//
//    printf("\n\n%d\n\n", deque(&pq));
//    print_list(pq);
//    printf("top: %d\n", top(&pq));
//
////    while (!is_empty(&pq)) {
////        printf("%d ", top(&pq));
////        deque(&pq);
////    }
//    printf("queue size: %d\n", queue_size(pq));
//    destroy_list(&pq);
//    print_list(pq);
    return 0;
}
