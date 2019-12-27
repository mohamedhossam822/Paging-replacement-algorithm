#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int Key;
  int priority;
  int SecChanceBit;
} Elem;

void FIFO(int NumberOfFrames);
void Clock(int NumberOfFrames);
void LRU(int NumberOfFrames);
void OPTIMAL(int NumberOfFrames);
void increment(int *arr, int counter);
void bubbleSort(Elem arr[], int n);

int main()
{
  int NumberOfFrames;
  int *Memory;
  char Method[20];

  //Getting Number OF frames and the paging Method
  scanf("%d", &NumberOfFrames);
  getchar();
  fgets(Method, 20, stdin);
  strtok(Method, "\n");

  printf("Replacement Policy = %s", Method);
  printf("\n-------------------------------------\n");
  printf("Page   Content of Frames\n");
  printf("----   -----------------\n");

  if(!strcmp(Method,"FIFO"))         FIFO(NumberOfFrames);
  else if(!strcmp(Method,"CLOCK"))   Clock(NumberOfFrames);
  else if(!strcmp(Method,"LRU"))     LRU(NumberOfFrames);
  else if(!strcmp(Method,"OPTIMAL")) OPTIMAL(NumberOfFrames);
  return 0;
}

void FIFO(int NumberOfFrames)
{
  int Page;
  int Frame[NumberOfFrames];
  int FrameIndex = 0;
  int ReplacementIndex = 0;
  int NumberOfReplacements = 0;
  int Found = -1;
  scanf("%d", &Page);

  while (Page != -1)
  {
    printf("%02d ", Page);

    for (int i = 0; i < FrameIndex; i++)
    {
      if (Frame[i] == Page)
      {
        Found = i;
        break;
      }
      else
      {
        Found = -1;
      }
    }

    if (Found == -1)
    {
      if (FrameIndex < NumberOfFrames)
      {
        printf("    ");
        Frame[FrameIndex] = Page;
        FrameIndex++;
      }
      else
      {
        printf("F   ");
        Frame[ReplacementIndex] = Page;
        ReplacementIndex++;
        NumberOfReplacements++;
        if (ReplacementIndex == NumberOfFrames)
          ReplacementIndex = 0;
      }
    }
    else
      printf("    ");

    for (int i = 0; i < FrameIndex; i++)
    {
      printf("%02d ", Frame[i]);
    }
    printf("\n");
    scanf("%d", &Page);
  }
  printf("-------------------------------------\n");
  printf("Number of page faults = %d", NumberOfReplacements);
}

void Clock(int NumberOfFrames)
{
  int Page;
  int Found = -1;
  int flag = 0;
  int FrameIndex = 0;
  int ReplacementIndex = 0;
  int NumberOfReplacements = 0;
  int flag2 = 0;
  int Frame[NumberOfFrames];
  Elem Element[NumberOfFrames];

  scanf("%d", &Page);

  while (Page != -1)
  {

    bubbleSort(Element, FrameIndex);
    printf("%02d ", Page);

    for (int i = 0; i < FrameIndex; i++)
    {
      Element[i].priority++;
    }

    for (int i = 0; i < FrameIndex; i++)
    {
      if (Frame[i] == Page)
      {
        Found = i;
        for (int j = 0; j < FrameIndex; j++)
        {
          if (Page == Element[j].Key)
          {
            Element[j].SecChanceBit = 1;
            break;
          }
        }
        break;
      }
      else
      {
        Found = -1;
      }
    }

    if (Found == -1)
    {
      if (FrameIndex < NumberOfFrames)
      {
        printf("    ");
        Frame[FrameIndex] = Page;
        Element[FrameIndex].Key = Page;
        Element[FrameIndex].priority = 0;
        Element[FrameIndex].SecChanceBit = 1;
        FrameIndex++;
      }
      else
      {
        flag2 = 0;
        for (int i = 0; i < FrameIndex; i++)
        {
          if (Element[i].SecChanceBit == 0)
            flag2 = 1;
        }
        if (flag2 == 0)
        {
          for (int i = 0; i < FrameIndex; i++)
          {
            Element[i].SecChanceBit = 0;
          }
        }
        printf("F   ");
        NumberOfReplacements++;
        for (int i = 0; i < FrameIndex; i++)
        {
          if (Element[i].SecChanceBit == 1)
            Element[i].SecChanceBit = 0;
          else
          {
            for (int j = 0; j < FrameIndex; j++)
            {
              if (Element[i].Key == Frame[j])
              {
                Frame[j] = Page;
                Element[i].Key = Page;
                Element[i].priority = 0;
                Element[i].SecChanceBit = 1;
                flag = 1;
                break;
              }
            }
            if (flag == 1)
              break;
          }
        }
      }
    }

    else
      printf("    ");

    flag = 0;
    for (int i = 0; i < FrameIndex; i++)
    {
      printf("%02d ", Frame[i]);
    }
    printf("\n");
    scanf("%d", &Page);
  }
  printf("-------------------------------------\n");
  printf("Number of page faults = %d", NumberOfReplacements);
}

void LRU(int NumberOfFrames)
{
  int Page;
  int Found = -1;
  int flag = 0;
  int FrameIndex = 0;
  int ReplacementIndex = 0;
  int NumberOfReplacements = 0;
  int Frame[NumberOfFrames];
  Elem Element[NumberOfFrames];

  scanf("%d", &Page);

  while (Page != -1)
  {

    bubbleSort(Element, FrameIndex);
    printf("%02d ", Page);

    for (int i = 0; i < FrameIndex; i++)
    {
      Element[i].priority++;
    }

    for (int i = 0; i < FrameIndex; i++)
    {
      if (Frame[i] == Page)
      {
        Found = i;
        for (int j = 0; j < FrameIndex; j++)
        {
          if (Page == Element[j].Key)
          {
            Element[j].priority = 0;
            break;
          }
        }
        break;
      }
      else
      {
        Found = -1;
      }
    }

    if (Found == -1)
    {
      if (FrameIndex < NumberOfFrames)
      {
        printf("    ");
        Frame[FrameIndex] = Page;
        Element[FrameIndex].Key = Page;
        Element[FrameIndex].priority = 0;
        FrameIndex++;
      }
      else
      {
        flag = 0;
        printf("F   ");
        NumberOfReplacements++;

        for (int j = 0; j < FrameIndex; j++)
        {
          if (Element[0].Key == Frame[j])
          {
            Frame[j] = Page;
            Element[0].Key = Page;
            Element[0].priority = 0;
            flag = 1;
            break;
          }
          if (flag == 1)
            break;
        }
      }
    }

    else
      printf("    ");

    flag = 0;
    for (int i = 0; i < FrameIndex; i++)
    {
      printf("%02d ", Frame[i]);
    }
    printf("\n");
    scanf("%d", &Page);
  }
  printf("-------------------------------------\n");
  printf("Number of page faults = %d", NumberOfReplacements);
}

void OPTIMAL(int NumberOfFrames)
{
  int Page;
  int Found = -1;
  int flag = 0;
  int FrameIndex = 0;
  int ReplacementIndex = 0;
  int PagesIncoming[300];
  int NeededIN[NumberOfFrames];
  int PagesCounter;
  int NumberOfReplacements = 0;
  int Frame[NumberOfFrames];
  int BiggestIndex;

  scanf("%d", &Page);
  while (Page != -1)
  {
    PagesIncoming[PagesCounter]=Page;
    PagesCounter++;
    scanf("%d", &Page);
  }

  for(int C=0;C<PagesCounter;C++)
  {
    Page=PagesIncoming[C];
    printf("%02d ", PagesIncoming[C]);


    for (int i = 0; i < FrameIndex; i++)
    {
      if (Frame[i] == Page)
      {
        Found = i;
        NeededIN[i]=0;
        flag=0;
        for(int j=C+1;j<PagesCounter;j++)
        {
          if(Frame[i]==PagesIncoming[j])
          {
            flag=1;
            NeededIN[i]++;
            break;
          }
        }
        if(flag==0) NeededIN[i]=9999;
        break;
      }
      else
      {
        Found = -1;
      }
    }

    if (Found == -1)
    {
      if (FrameIndex < NumberOfFrames)
      {
        printf("    ");
        Frame[FrameIndex] = Page;
        NeededIN[FrameIndex]=0;
        flag=0;
        for(int j=C+1;j<PagesCounter;j++)
        {
          if(Frame[FrameIndex]==PagesIncoming[j])
          {
            flag=1;
            NeededIN[FrameIndex]++;
            break;
          }
        }
        if(flag==0) NeededIN[FrameIndex]=9999;
        FrameIndex++;
      }
      else
      {
        flag = 0;
        printf("F   ");
        NumberOfReplacements++;
        BiggestIndex=0;
        for (int j = 0; j < FrameIndex; j++)
        {
          if(NeededIN[j]==9999)
          {
            BiggestIndex=j;
            break;
          }
          if(NeededIN[j]>NeededIN[BiggestIndex])
          BiggestIndex=j;
        }
        Frame[BiggestIndex]=Page;

        NeededIN[BiggestIndex]=0;
        flag=0;
        for(int j=C+1;j<PagesCounter;j++)
        {
          if(Frame[BiggestIndex]==PagesIncoming[j])
          {
            flag=1;
            NeededIN[BiggestIndex]++;
            break;
          }
        }
        if(flag==0) NeededIN[BiggestIndex]=9999;

      }
    }

    else
      printf("    ");

    flag = 0;
    for (int i = 0; i < FrameIndex; i++)
    {
      printf("%02d ", Frame[i]);
    }
    printf("\n");
  }
  printf("-------------------------------------\n");
  printf("Number of page faults = %d", NumberOfReplacements);
}

void bubbleSort(Elem arr[], int n)
{
  int i, j;
  for (i = 0; i < n - 1; i++)
    for (j = 0; j < n - i - 1; j++)
      if (arr[j].priority < arr[j + 1].priority)
      {
        Elem temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
}
