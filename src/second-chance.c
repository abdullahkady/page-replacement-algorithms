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
  int i, j, k, u, reader_counter = 0, temp = 0, num_of_pages, queue_of_page_id[500], frame[10], no_of_frames = 5, placesleft = 5, exits_in_frame_flag, faults_count = 0, time_to_enter_for_each_page[500], MR_bit[500], time = 0, quantum_time = 20, Rbit[500], Mbit[500];
  char inputFileName[256];
  char outputFileName[256];
  for (i = 0; i < 500; i++)
  {
    Mbit[i] = 0;
    Rbit[i] = 0;
  }
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
    char *dup = strdup(tmpProcess);
    int page_id = atoi(getElement(dup, 2));
    int time = atoi(getElement(dup, 1));

    /////////////////////////////////////////////////////////////////
    char *newDuplicate = strdup(tmpProcess);
    char x = newDuplicate[(int)(strlen(newDuplicate) - 3)];
    if (x == 'R')
      Rbit[reader_counter] = 1;
    if (x == 'W')
      Mbit[reader_counter] = 1;
    /////////////////////////////////////////////////////////////////
    queue_of_page_id[reader_counter] = page_id;
    time_to_enter_for_each_page[reader_counter] = time;
    num_of_pages++;
    reader_counter++;
  }
  fclose(file);
  for (i = 0; i < 500; i++)
    MR_bit[i] = 0;

  //logic part

  for (i = 0; i < no_of_frames; i++)
    frame[i] = -1;
  j = 0;
  printf("\n");
  printf("\n");
  for (i = 1; i < num_of_pages; i++)
  {
    time = time_to_enter_for_each_page[i];
    if (time % 20 == 0)
    {
      printf("interrupt here\t");
      for (time = 0; time < 500; time++)
        Rbit[i] = 0;
    }

    printf("time=%d\t\t", time_to_enter_for_each_page[i]);
    printf("page entering=%d\t\t", queue_of_page_id[i]);
    exits_in_frame_flag = 0;
    for (k = 0; k < no_of_frames; k++) //checks continuasly if page is present in frame or not
      if (frame[k] == queue_of_page_id[i])
      {
        exits_in_frame_flag = 1;
        // MR_bit[k] = 1;
        if (Rbit[i] == 1)
          Rbit[k] = 1;
        if (Mbit[i] == 1)
          Mbit[k] = 1;
      }
    if (exits_in_frame_flag == 0)
    {
      for (u = 0; u < no_of_frames - placesleft; u++)
      {
        while (j < no_of_frames - placesleft)
        {
          if (Rbit[j] == 0)
          {
            printf("will not get evected beacuse R bit=1 of the page\t");
            Rbit[j] = 1;
            j = (j + 1) % no_of_frames;
          }
        }
      }

      frame[j] = queue_of_page_id[i];

      j = (j + 1) % no_of_frames;

      for (k = 0; k < no_of_frames; k++)
        printf("%d\t", frame[k]);

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
