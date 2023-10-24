#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int nb;
    int rating;
    int delta_rating;
    char *tmp;
    char *secondInput;
    char **f;
    char **s;
    char *rating_c;
    int var;

    rating_c = calloc(100,1);
    secondInput = calloc(100000,5);
    // read first input from default input then write it to output
    scanf("%d %d", &nb, &rating);
    read(1, secondInput, 10000 * 5 - 1);
    // printf("%s", secondInput);
    tmp = rating_c;
    while (*secondInput)
    {
        // printf("%s\n", rating_c);
        if (*secondInput == ' ' || *(secondInput + 1) == '\0')
        {
            delta_rating = atoi(rating_c);
            
            // printf("%d\n", delta_rating);
            var = (rating - delta_rating) / 2;
            if (var < 0)
                var *= -1;
            rating = rating + var;
            rating_c = tmp;
        }
        *tmp = *secondInput;
        tmp++;
        secondInput++;
    }
    printf("%d\n", rating);



}