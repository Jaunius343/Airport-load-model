#include <stdio.h>
#include <stdlib.h>

#include "pq_struct.h"
#include "priority_queue.h"
#include "priority_queue.c"
#include "big_int.h"
#include "big_int.c"

#define COUNT 29
#define TIME_SIZE 32

int main()
{
//    //test
//    print_big_int(div_big_int(new_big_int("1500"), new_big_int("10")));
//    print_big_int(div_big_int(new_big_int("900"), new_big_int("10")));


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
//        printf("%d", rng);
        enque(&airplanes, i, rng);
    }

    int takeoff_count_copy = takeoff_count,
        land_count_copy = land_count;
//
//    printf("\n");
//    print_list(airplanes);
//    printf("\n");

    printf("\ntake off: %d", takeoff_count);
    //land_count = 10;
    printf("\nlanding: %d\n", land_count);

    //reading data from file
    FILE *read, *print;
    read = fopen("duom.txt", "r");
    print = fopen("log.txt", "w");
    char temp_land_time[TIME_SIZE],
         temp_takeoff_time[TIME_SIZE],
         temp_fuel_time[TIME_SIZE];

    fprintf(print, "landing: %d\n", land_count);
    fprintf(print, "take off: %d\n", takeoff_count);

    if(read != NULL){
        fscanf(read, "%s %s %s", &temp_land_time, &temp_takeoff_time, &temp_fuel_time);
        close(read);
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
    big_int *time_passed = new_big_int("0");

    int flag = 0;
    big_int *max_wait_time_landing = new_big_int("0"),
            *max_wait_time_takeoff = new_big_int("0");
    while (planes_left > 0){
        fprintf(print, "\nplanes left: %d", planes_left);
        fprintf(print, "\nland count: %d", land_count);
        fprintf(print, "\ntakeoff count: %d", takeoff_count);

//        printf("\nplanes left: %d", planes_left);
//        printf("\nland count: %d", land_count);
//        printf("\ntakeoff count: %d", takeoff_count);

        rng = 0 + rand()% (100 - 0 + 1);
        fprintf(print, "\nrng: %d", rng);

//        printf("\nrng: %d\n", rng);

        if (rng > 50){
            if (land_count > 0){
                fprintf(print, "\nTotal time now: ");
                print_big_int_file(time_passed, print);

//                printf("\nTotal time now: ");
//                print_big_int(time_passed);

                fprintf(print, "Time to land: ");
                print_big_int_file(land_time, print);
                time_passed = add_big_int(time_passed, land_time);

//                printf("Time to land: ");
//                print_big_int(land_time);

                fprintf(print, "New time: ");
                print_big_int_file(time_passed, print);

//                printf("New time: ");
//                print_big_int(time_passed);

                big_int *temptemp = sub_big_int(fuel_time, time_passed);
                fprintf(print, "%c", temptemp->sign);
                fprintf(print, "\nfuel time - time passed = ");
                print_big_int_file(temptemp, print);

//                printf("%c", temptemp->sign);
//                printf("\nfuel time - time passed = ");
//                print_big_int(temptemp);

                if(temptemp->sign == '-'){
                    flag = 1;
                    break;
                }
                --land_count;

                if (land_count > 0){
                    max_wait_time_landing = add_big_int(max_wait_time_landing, land_time);
                }
                max_wait_time_takeoff = add_big_int(max_wait_time_takeoff, land_time);

            } else {
                time_passed = add_big_int(time_passed, takeoff_time);
                --takeoff_count;
                if (takeoff_count > 0){
                    max_wait_time_takeoff = add_big_int(max_wait_time_takeoff, takeoff_time);
                }
            }
            deque(&airplanes);
            --planes_left;
        } else {
            if(land_count == 1){
                fprintf(print, "\nprevious plane didn't want to land");
                fprintf(print, "\nallowing takeoff");
                fprintf(print, "\nnew rng: ");

//                printf("\nprevious plane didn't want to land");
//                printf("\nallowing takeoff");
//                printf("\nnew rng: ");

                rng = 0 + rand()% (100 - 0 + 1);
                fprintf(print, "%d", rng);
                printf("%d", rng);
                if (rng > 50){
                    time_passed = add_big_int(time_passed, takeoff_time);
                    --takeoff_count;
                    deque(&airplanes);
                    --planes_left;
                    max_wait_time_landing = add_big_int(max_wait_time_landing, takeoff_time);
                    if(takeoff_count > 0){
                        max_wait_time_takeoff = add_big_int(max_wait_time_takeoff, takeoff_time);
                    }
                }
            }
        }
        fprintf(print, "\n");
    }
    printf("\ntotal time passed: ");
    print_big_int(time_passed);
    if(flag == 1){
        printf("\n plane crash\n");
    }

    char temp_string[TIME_SIZE];
    printf("\nmax wait time for landing: ");
    print_big_int(max_wait_time_landing);
//    itoa(land_count_copy-1, temp_string, TIME_SIZE);
    sprintf(temp_string,"%d",land_count_copy);
//
//    printf("\n%d\n", land_count_copy);
//    printf("\nthe string: %s\n", temp_string);

    printf("average landing time = ");
    print_big_int(div_big_int(max_wait_time_landing, new_big_int(temp_string)));

    printf("max wait time for takeoff: ");
    print_big_int(max_wait_time_takeoff);
//    itoa(takeoff_count_copy, temp_string, TIME_SIZE);
    sprintf(temp_string,"%d",takeoff_count_copy);
//    printf("\nthe string: %s\n", temp_string);
    printf("average takeoff time: ");
    print_big_int(div_big_int(max_wait_time_takeoff, new_big_int(temp_string)));

    return 0;
}
