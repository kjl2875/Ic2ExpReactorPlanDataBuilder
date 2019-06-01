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
void setNextField(enum CellType *FIELD);
void setFieldEU(enum CellType *FIELD, enum CellType *FIELD_EU);

int main()
{
    // INPUT
    
    clock_t t0,t1;
    enum CellType *FIELD;
    enum CellType *FIELD_EU;
    
    FIELD = malloc(sizeof(enum CellType) * (FIELD_WIDTH+2) * (FIELD_HEIGHT+2)); // border is not used
    FIELD_EU = malloc(sizeof(int) * (FIELD_WIDTH) * (FIELD_HEIGHT)); // border is not used
    initField(FIELD);
    
    // PROCESS
    
    t0 = clock();
    for( int i=0; i<16777215; i++ )
    {
        setNextField(FIELD);
        setFieldEU(FIELD,FIELD_EU);
        setNextField(FIELD_EU);
    }
    t1 = clock();
    
    /// OUTPUT
    
    printField(FIELD);
    printf("Runtime: %.06lf",(double)(t1-t0)/CLOCKS_PER_SEC);
    free(FIELD);
    free(FIELD_EU);
    
    return 0;
}

void initField(enum CellType *FIELD)
{
    int x, y;
    
    for( y=0; y<FIELD_HEIGHT+2; y++ )
    {
        for( x=0; x<FIELD_WIDTH+2; x++ )
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
            printf("%d\t", FIELD[(y+1)*FIELD_WIDTH+(x+1)]);
        }
        printf("\n");
    }
    printf("\n");
}

void setNextField(enum CellType *FIELD)
{
    int x=0,y=0;
    
    while( ++FIELD[(y+1)*FIELD_WIDTH+(x+1)] > CELLTYPE_MAXVAL )
    {
        FIELD[(y+1)*FIELD_WIDTH+(x+1)] = 0;
        
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

void setFieldEU(enum CellType *FIELD, enum CellType *FIELD_EU)
{
    int sum;
    int x, y;
    
    for( y=0; y<FIELD_HEIGHT; y++ )
    {
        for( x=0; x<FIELD_WIDTH; x++ )
        {
            switch( FIELD[(y+1)*FIELD_WIDTH+(x+1)] )
            {
            case URANIUM_CELL_SINGLE:
                sum = 5;
                if( FIELD[(y+2)*FIELD_WIDTH+(x+1)] != EMPTY ) { sum += 5; }
                if( FIELD[(y+0)*FIELD_WIDTH+(x+1)] != EMPTY ) { sum += 5; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+2)] != EMPTY ) { sum += 5; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+0)] != EMPTY ) { sum += 5; }
                break;
            case URANIUM_CELL_DOUBLE:
                sum = 20;
                if( FIELD[(y+2)*FIELD_WIDTH+(x+1)] != EMPTY ) { sum += 10; }
                if( FIELD[(y+0)*FIELD_WIDTH+(x+1)] != EMPTY ) { sum += 10; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+2)] != EMPTY ) { sum += 10; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+0)] != EMPTY ) { sum += 10; }
                break;
            case URANIUM_CELL_QUAD:
                sum = 60;
                if( FIELD[(y+2)*FIELD_WIDTH+(x+1)] != EMPTY ) { sum += 20; }
                if( FIELD[(y+0)*FIELD_WIDTH+(x+1)] != EMPTY ) { sum += 20; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+2)] != EMPTY ) { sum += 20; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+0)] != EMPTY ) { sum += 20; }
                break;
            default:
                sum = 0;
                break;
            }
            
            FIELD_EU[y*FIELD_WIDTH+x] = sum;
        }
    }
}