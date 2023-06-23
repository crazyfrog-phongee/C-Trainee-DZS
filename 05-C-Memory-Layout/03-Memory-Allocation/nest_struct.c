#include <stdio.h>
#include <stdlib.h>

struct address
{
    int code;
};

struct student
{
    struct address *ads;
};

int main()
{
    struct student *person;

    /* You should check that malloc succeeded otherwise undefined behavior would happen */
    person = (struct student *)malloc(sizeof(struct student));
    if (person == NULL)
    {
        printf("Cannot allocate memory\n");
        exit(EXIT_FAILURE);
    }

    person->ads = (struct address *)malloc(sizeof(struct address));
    if (person->ads == NULL)
    {
        printf("Cannot allocate memory\n");
        /* On failure free successfuly allocated person */
        free(person);
        exit(EXIT_FAILURE);
    }

    person->ads->code = 123;
    printf("Code: %d\n", person->ads->code);

    /* De-allocate memory */
    // free(person->ads);
    free(person);

    return 0;
}