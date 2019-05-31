// https://www.onlinegdb.com/online_c_compiler

#include <stdio.h>
#include <time.h>

#define FIELD_WIDTH (3)
#define FIELD_HEIGHT (4)
#define CELLTYPE_MAXVAL (3)

enum CellType {
    EMPTY,
    URANIUM_CELL_SINGLE,
    URANIUM_CELL_DOUBLE,
    URANIUM_CELL_QUAD
};

void initField(enum CellType *FIELD);
void printField(enum CellType *FIELD);
void getNextField(enum CellType *FIELD);

int main()
{
    clock_t t0,t1,t2;
    enum CellType *FIELD;
    
    /// FIELD init
    
    FIELD = malloc(sizeof(enum CellType) * FIELD_WIDTH * FIELD_HEIGHT);
    initField(FIELD);
    
    //printField(FIELD);
    //printf("----------------------\n");
    t0 = clock();
    for( int i=0; i<16777215; i++ ) { // 4^12-1=16777215
        getNextField(FIELD);
        //printField(FIELD);
        //printf("----------------------\n");
    }
    t1 = clock();
    //printf("----------------------\n");
    //printField(FIELD);
    
    free(FIELD);
    
    /// return
    
	printf("runtime : %.8lf \n", (((double)t1 - t0)/CLOCKS_PER_SEC));
    
    return 0;
}

void initField(enum CellType *FIELD)
{
    int x, y;
    
    for( y=0; y<FIELD_HEIGHT; y++ )
    {
        for( x=0; x<FIELD_WIDTH; x++ )
        {
            FIELD[y*FIELD_WIDTH+x] = EMPTY;
        }
    }
}

void printField(enum CellType *FIELD)
{
    int x, y;
    
    for( y=0; y<FIELD_HEIGHT; y++ )
    {
        for( x=0; x<FIELD_WIDTH; x++ )
        {
            //printf("%d\t", FIELD[y*FIELD_WIDTH+x]);
            printf(" %2d", FIELD[y*FIELD_WIDTH+x]);
        }
        //printf("\n");
    }
    printf("\n");
}

void getNextField(enum CellType *FIELD)
{
    int x=0,y=0;
    
    while( ++FIELD[y*FIELD_WIDTH+x] > CELLTYPE_MAXVAL )
    {
        FIELD[y*FIELD_WIDTH+x] = 0;
        
        if( ++x == FIELD_WIDTH )
        {
            x = 0;
            if( ++y == FIELD_HEIGHT )
            {
                y = 0;
                return 1;
            }
        }
    }
    
    return 0;
}
