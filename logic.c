#include <stdio.h>
#include <stdlib.h>

#define REACTOR_WIDTH (9)
#define REACTOR_HEIGHT (6)

#define CELL_EMPTY (0)
#define CELL_URANIUM_SINGLE (1)
#define CELL_URANIUM_DOUBLE (2)
#define CELL_URANIUM_QUAD (3)

void initReactor(int *reactor);
void printVector(int* reactor, int width, int height);
void setCell(int * reactor, int x, int y, int cell);
int calcReactor(const int* reactor);

int main(int argc, char** argv)
{
	int code;
	int *reactor = malloc(sizeof(int) * REACTOR_WIDTH * REACTOR_HEIGHT);
	if (NULL == reactor)
	{
		fprintf(stderr, "ERROR: Out of memory\n");
		return 1;
	}

	int x, y;
	initReactor(reactor);
	for (x = 0; x < REACTOR_WIDTH; x++)
	{
		for (y = 0; y < REACTOR_HEIGHT; y++)
		{
			setCell(reactor, x, y, CELL_URANIUM_QUAD);
		}
	}

	printVector(reactor,REACTOR_WIDTH,REACTOR_HEIGHT);
	code = calcReactor(reactor);

	free(reactor);
	return code;
}

void initReactor(int *reactor)
{
	for (int y = 0; y < REACTOR_HEIGHT; y++)
	{
		for (int x = 0; x < REACTOR_WIDTH; x++)
		{
			*(reactor + (y * REACTOR_WIDTH + x)) = CELL_EMPTY;
		}
	}
}

void printVector(int* reactor, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			printf("%d\t", *(reactor + y * width + x));
		}
		printf("\n");
	}
}

void setCell(int* reactor, int x, int y, int cell)
{
	*(reactor + y * REACTOR_WIDTH + x) = cell;
}

int calcReactor(const int* reactor)
{
	// init

	int efficiency; // 효율
	int heat; // 열 (HU/t)
	int eu; // 발전량 (EU/t)
	int eu_total = 0;
	int heat_total = 0;

	char buf[255];
	int i, x, y;
	int w = REACTOR_WIDTH + 2; // add border
	int h = REACTOR_HEIGHT + 2; // add border

	int* field = malloc(sizeof(int) * w * h);
	if (NULL == field) { return 1; }
	int* vectorEU = malloc(sizeof(int) * REACTOR_WIDTH * REACTOR_HEIGHT);
	if (NULL == vectorEU) { free(field); return 1; }
	int* vectorHEAT = malloc(sizeof(int) * REACTOR_WIDTH * REACTOR_HEIGHT);
	if (NULL == vectorHEAT) { free(field); free(vectorEU); return 1; }

	// init border

	for (i = 0; i < w; i++)
	{
		*(field + i) = CELL_EMPTY;
		*(field + (h - 1) * w + i) = CELL_EMPTY;
	}

	for (y = 1; y < h - 1; y++)
	{
		*(field + w * y) = CELL_EMPTY;
		*(field + w * y + w - 1) = CELL_EMPTY;
	}

	for (y = 0; y < REACTOR_HEIGHT; y++)
	{
		for (x = 0; x < REACTOR_WIDTH; x++)
		{
			*(field + (y + 1) * w + x + 1) = reactor[y * REACTOR_WIDTH + x];
		}
	}

	printf("------------------------------------------\n");
	//printVector(field, w, h);

	// calc

	for (y = 1; y <=REACTOR_HEIGHT; y++)
	{
		for (x = 1; x <=REACTOR_WIDTH; x++)
		{
			/// efficiency

			efficiency = 0;

			switch (*(field + y * w + x))
			{
			case CELL_URANIUM_QUAD:
				++efficiency;
			case CELL_URANIUM_DOUBLE:
				++efficiency;
			case CELL_URANIUM_SINGLE:
				++efficiency;
			}

			if (efficiency != 0)
			{
				switch (*(field + (y + 1) * w + (x + 0)))
				{
				case CELL_URANIUM_QUAD:
				case CELL_URANIUM_DOUBLE:
				case CELL_URANIUM_SINGLE:
					++efficiency;
				}
				switch (*(field + (y - 1) * w + (x + 0)))
				{
				case CELL_URANIUM_QUAD:
				case CELL_URANIUM_DOUBLE:
				case CELL_URANIUM_SINGLE:
					++efficiency;
				}
				switch (*(field + (y + 0) * w + (x + 1)))
				{
				case CELL_URANIUM_QUAD:
				case CELL_URANIUM_DOUBLE:
				case CELL_URANIUM_SINGLE:
					++efficiency;
				}
				switch (*(field + (y + 0) * w + (x - 1)))
				{
				case CELL_URANIUM_QUAD:
				case CELL_URANIUM_DOUBLE:
				case CELL_URANIUM_SINGLE:
					++efficiency;
				}
			}

			/// i = cell count

			switch (*(field + y * w + x))
			{
			case CELL_URANIUM_SINGLE:
				i = 1;
				break;
			case CELL_URANIUM_DOUBLE:
				i = 2;
				break;
			case CELL_URANIUM_QUAD:
				i = 4;
				break;
			default:
				i = 0;
				break;
			}

			/// eu

			eu = 5 * efficiency * i;

			/// heat
			
			heat = 2 * efficiency * (efficiency + 1) * i;

			/// output

			eu_total += eu;
			heat_total += heat;

			//printf("%d\t", *(field + y*w+x));
			//printf("%10d ", efficiency);
			//printf("%10d ", i);
			sprintf_s(&buf,sizeof(buf)/sizeof(char),"[%3d %3d]",eu,heat);
			printf("%10s ",buf);
			
		}
		printf("\n");
	}
	printf("\n");

	free(field);
	free(vectorEU);
	free(vectorHEAT);

	return 0;
}
