#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Track
{
    int id;
    char track_name[50];
    char composer[50];
    char media_type[5];
    char album[50];
    int duration; // Duration in seconds
    struct Track *next;
} Track;

typedef struct List
{
    Track *head;
} List;

List *create_list()
{
    List *list = malloc(sizeof(List));
    list->head = NULL;
    return list;
}

Track *create_track(int id, char track_name[50], char composer[50], char media_type[5], char album[50], int duration)
{
    Track *track = malloc(sizeof(Track));
    track->id = id;
    strcpy(track->track_name, track_name);
    strcpy(track->composer, composer);
    strcpy(track->media_type, media_type);
    strcpy(track->album, album);
    track->duration = duration;
    track->next = NULL;
    return track;
}

void sort_list_by_id(List *list)
{
    if (list->head == NULL || list->head->next == NULL) // empty list || sorted
        return;

    int swapped;
    Track *ptr1;
    Track *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = list->head;

        while (ptr1->next != lptr)
        {
            if (ptr1->id > ptr1->next->id)
            {
                int temp = ptr1->id;
                ptr1->id = ptr1->next->id;
                ptr1->next->id = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void push_front(List *list, Track *new_track)
{
    new_track->next = list->head;
    list->head = new_track;
}

void push_back(List *list, Track *new_track)
{
    if (list->head == NULL)
    {
        list->head = new_track;
        return;
    }

    Track *current_track = list->head;
    while (current_track->next != NULL)
    {
        current_track = current_track->next;
    }
    current_track->next = new_track;
}

void print_list(List *list)
{
    printf("List elements:\n");
    if (list->head == NULL)
    {
        printf("\nList is NULL\n");
        return;
    }
    for (Track *current_track = list->head; current_track; current_track = current_track->next)
    {
        printf("\nTrack ID: %-10d\n", current_track->id);
        printf("Track Name: %-10s\n", current_track->track_name);
        printf("Composer Name: %-10s\n", current_track->composer);
        printf("Media Type: %-10s\n", current_track->media_type);
        printf("Album: %-10s\n", current_track->album);
        printf("Duration: %-10d\n", current_track->duration);
    }
    printf("\n");
}

int compare(const void *a, const void *b)
{
    Track *trackA = (Track *)a;
    Track *trackB = (Track *)b;
    return (trackB->id - trackA->id);
}

int search_list(List *list, int id)
{
    int counter = 0;
    for (Track *current_track = list->head; current_track; current_track = current_track->next)
    {
        if (current_track->id == id)
        {
            printf("Position: %d", counter);
            return counter;
        }
        counter++;
    }
    return -1;
}

void insert_at_specified_id(List *list, int id, char track_name[50], char composer[50], char media_type[5], char album[50], int duration, int specified_id)
{
    Track *new_track = create_track(id, track_name, composer, media_type, album, duration);

    printf("Insert at ID: %d\n", specified_id);

    for (Track *current_track = list->head; current_track; current_track = current_track->next)
    {
        printf("current_track->id = %d\n", current_track->id);
        if ((current_track->id) == specified_id)
        {
            printf("\nID FOUND\n");
            new_track->next = current_track->next;
            current_track->next = new_track;

            break;
        }
    }
    printf("ID %d not found in the list\n", specified_id);
};

void delete_specified_id(List *list, int specified_id)
{
    Track *current_track = list->head;
    Track *previous_track = NULL;

    printf("id to delete = %d\n", specified_id);
    while (current_track != NULL)
    {
        printf("current_track->id = %d\n", current_track->id);
        if (current_track->id == specified_id)
        {
            printf("\nID FOUND\nDeleting...\n");
            if (previous_track == NULL)
            {
                list->head = current_track->next;
            }
            else
            {
                previous_track->next = current_track->next;
            }
            free(current_track);
            printf("ID %d deleted.\n", specified_id);
            return;
        }
        previous_track = current_track;
        current_track = current_track->next;
    }
    printf("ID %d not found in the list\n", specified_id);
}

void print_reverse(List *list)
{
    struct Track *prev = NULL;
    struct Track *current_track = list->head;
    struct Track *next = NULL;
    while (current_track != NULL)
    {
        next = current_track->next; // store `next`
        current_track->next = prev; // current node -> back
        prev = current_track;       // move pointer 1 position ahead
        current_track = next;
    }
    list->head = prev;
    printf("List reversed!");
}

void clear_list(List *list)
{
    Track *current_track = list->head, *back_node = NULL;
    while (current_track)
    {
        back_node = current_track;
        current_track = current_track->next;
        free(back_node);
    }
    list->head = NULL;
    printf("List cleared!");
}

Track *input_track()
{
    int id, duration;
    char track_name[50];
    char composer[50];
    char media_type[5];
    char album[50];

    printf("Insert id: ");
    scanf("%d", &id);
    printf("Insert track name: ");
    scanf("%s", track_name);
    printf("Insert composer: ");
    scanf("%s", composer);
    printf("Insert media type: ");
    scanf("%s", media_type);
    printf("Insert album: ");
    scanf("%s", album);
    printf("Insert duration: ");
    scanf("%d", &duration);

    return create_track(id, track_name, composer, media_type, album, duration);
}

void input_multiple_tracks(List *list, int num_objects)
{
    for (int i = 0; i < num_objects; i++)
    {
        printf("\ni = %d, object_numer = %d\n", i, num_objects);
        Track *new_track = input_track();
        push_front(list, new_track);
    }
}

int main()
{
    int obj_number, searched_id, specified_id = 0;
    List *list1 = create_list();

    int track_id;
    char track_name[50];
    char composer[50];
    char media_type[5];
    char album[50];
    int duration;

    printf("Object number: ");
    scanf("%d", &obj_number);

    input_multiple_tracks(list1, obj_number);

    int n;
    do
    {
        printf("\nMenu:\n");
        printf("  1| Print tracks\n");
        printf("  2| Search tracks\n");
        printf("  3| Sort tracks by ID\n");
        printf("  4| Add track at beginning\n");
        printf("  5| Add track at end\n");
        printf("  6| Add track at specified ID\n");
        printf("  7| Delete specified ID\n");
        printf("  8| Reverse list\n");
        printf("  9| Clear list\n");
        printf("  0| Exit\n");
        printf("\nYour selection:\n");
        scanf(" %d", &n);
        switch (n)
        {
        case 1:
            print_list(list1);
            break;
        case 2:
            printf("Search: ");
            scanf("%d", &searched_id);
            search_list(list1, searched_id);
            break;
        case 3:
            sort_list_by_id(list1);
            printf("List sorted.\n");
            break;
        case 4:
            push_front(list1, input_track());
            break;
        case 5:
            push_back(list1, input_track());
            break;
        case 6:
            input_track(&track_id, track_name, composer, media_type, album, &duration);
            printf("Insert ID to insert new track:");
            scanf("%d", &specified_id);
            insert_at_specified_id(list1, track_id, track_name, composer, media_type, album, duration, specified_id);
            break;
        case 7:
            printf("Insert ID to be deleted:");
            scanf("%d", &specified_id);
            delete_specified_id(list1, specified_id);
            break;
        case 8:
            print_reverse(list1);
            break;
        case 9:
            clear_list(list1);
            break;
        case 0:
            printf("exit . . .");
            exit(1);
            break;
        default:
            printf("invalid option.");
            break;
        }
    } while (n != 0);

    return 0;
}