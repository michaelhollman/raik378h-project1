#include "tables.h"

void print_message(message_t *message)
{
    /* message cannot be NULL */
    if (message == NULL) {
        fprintf(stderr, "The message is NULL\n");
        exit(0);
    }

    /* print message text */
    printf("Text: %s\n", message->text);
}

void print_time(timestamp_t *time)
{
    printf("Time: %02d/%02d/%04d %02d:%02d\n", timestamp_t->month, timestamp_t->day,
           timestamp_t->year, timestamp_t->hour, timestamp_t->minute);
}

void read_message(message_t *message, FILE *fp)
{
    /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }

    /* message cannot be NULL */
    if (message == NULL) {
        fprintf(stderr, "The message is NULL\n");
        exit(0);
    }

    fread(&(message->messageId), sizeof(int), 1, fp);
    fread(&(message->userId), sizeof(int), 1, fp);
    fread(&(message->timestampId), sizeof(int), 1, fp);
    fread(&(message->text[0]), sizeof(char), TEXT_LONG, fp);
}


user_t *read_user(FILE *fp)
{
    /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }

    /* allocate memory for the user */
    user_t *user = (user_t *)malloc(sizeof(user_t));

    /* memory error */
    if (user == NULL) {
        fprintf(stderr, "Cannot allocate memory for user.\n");
        exit(0);
    }

    /* read user id */
    fread(&(user->userId), sizeof(int), 1, fp);

    /* read user name */
    fread(&(record->name[0]), sizeof(char), TEXT_SHORT, fp);

    /* read cityId */
    fread(&(record->cityId), sizeof(int), 1, fp);

    /* read stateId */
    fread(&(record->stateId), sizeof(int), 1, fp);

    /* return the user */
    return user;
}

timestamp_t *read_timestamp(FILE *fp)
{
    /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }

    /* allocate memory for the record */
    timestamp_t *timestamp = (timestamp_t *)malloc(sizeof(timestamp_t));

    /* memory error */
    if (timestamp == NULL) {
        fprintf(stderr, "Cannot allocate memory for city.\n");
        exit(0);
    }

    fread(&(timestamp->timestampId), sizeof(int), 1, fp);

    fread(&(timestamp->year), sizeof(int), 1, fp);

    fread(&(timestamp->month), sizeof(int), 1, fp);
    fread(&(timestamp->day), sizeof(int), 1, fp);
    fread(&(timestamp->hour), sizeof(int), 1, fp);
    fread(&(timestamp->minute), sizeof(int), 1, fp);

    return timestamp;
}

// read city from a file
city_t *read_city(FILE *fp)
{
    /* Assume file has been opened */
    if (fp == NULL) {
        fprintf(stderr, "The file stream is NULL\n");
        exit(0);
    }

    /* allocate memory for the record */
    city_t *city = (city_t *)malloc(sizeof(city_t));

    /* memory error */
    if (city == NULL) {
        fprintf(stderr, "Cannot allocate memory for city.\n");
        exit(0);
    }

    /* read city id */
    fread(&(city->cityId), sizeof(int), 1, fp);

    /* read city name */
    fread(&(city->cityName[0]), sizeof(char), TEXT_SHORT, fp);

    /* read cityId */
    fread(&(record->cityId), sizeof(int), 1, fp);

    /* read stateId */
    fread(&(record->stateId), sizeof(int), 1, fp);

    fread(&(city->stateName[0]), sizeof(char), TEXT_SHORT, fp);

    return city;
}

