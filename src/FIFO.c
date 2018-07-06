#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *getElement(char *lines, int elementIndex)
{
  char *current;
  for (current = strtok(lines, ",");
       current && *current;
       current = strtok(NULL, ",\n"))
  {
    if (!--elementIndex)
      return current;
  }
  return NULL;
}

int main()
{
  int i, j, k, reader_counter = 0, temp = 0, num_of_pages, queue_of_page_id[500], frame[10], no_of_frames = 5, placesleft = 5, exits_in_frame_flag, faults_count = 0, time_to_enter_for_each_page[500], MR_bit[500], time = 0, quantum_time = 20;
  char inputFileName[256];
  char outputFileName[256];
  printf("Enter input file name (Relative): ");
  scanf("%s", inputFileName);
  FILE *file = fopen(inputFileName, "r");
  if (!file)
  {
    printf("WRONG INPUT FILE - PLEASE SPECIFY A RELATIVE PATH(Copy the input file to the same directory)\n TERMINATING APPLICATION\n");
    return 0;
  }

  char tmpProcess[256];
  while (fgets(tmpProcess, sizeof(tmpProcess), file))
  {
    //Converting each element into an int, and storing them in the appropriate corresponding array cells.
    char *dup = strdup(tmpProcess);
    int page_id = atoi(getElement(dup, 2));
    int time = atoi(getElement(dup, 1));
    queue_of_page_id[reader_counter] = page_id;
    time_to_enter_for_each_page[reader_counter] = time;
    num_of_pages++;
    reader_counter++;
  }
  fclose(file);

  for (i = 0; i < no_of_frames; i++)
    frame[i] = -1;
  j = 0;
  printf("\n");
  printf("\n");
  for (i = 1; i < num_of_pages; i++)
  {
    if (time_to_enter_for_each_page[i] % 20 == 0)
      printf("interrupt here\t");

    printf("time=%d\t\t", time_to_enter_for_each_page[i]);
    printf("page entering=%d\t\t", queue_of_page_id[i]);
    exits_in_frame_flag = 0;
    for (k = 0; k < no_of_frames; k++) //checks continuasly if page is present in frame or not
      if (frame[k] == queue_of_page_id[i])
        exits_in_frame_flag = 1;

    if (exits_in_frame_flag == 0)
    {
      if (placesleft <= 0)
      {

        printf("page to get evicted=%d\t\t", frame[j]);
      }
      else
      {
        placesleft--;
      }
      frame[j] = queue_of_page_id[i];

      j = (j + 1) % no_of_frames;

      printf("frame now\t");
      for (k = 0; k < no_of_frames - placesleft; k++)
        printf("%d\t", frame[k]);
      for (k = 0; k < placesleft; k++)
        printf("X\t");

      printf("\tfault");
      printf("\n");
    }
    else
    {
      printf("exists in frame");
      printf("\n");
    }
    printf("\n");
  }

  return 0;
}
