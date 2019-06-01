// https://www.onlinegdb.com/online_c_compiler

#include <stdio.h>
#include <time.h>

#define FIELD_WIDTH (3)
#define FIELD_HEIGHT (4)

#define CELL_EMPTY (0)
#define CELL_URANIUM_SINGLE (1)
#define CELL_URANIUM_DOUBLE (2)
#define CELL_URANIUM_QUAD (3)
#define MASK_CELL_URANIUM (3)

void initField(int *FIELD, int width, int height);
void printField(int *FIELD, int width, int height);
//void setFieldEU(enum CellType *FIELD, enum CellType *FIELD_EU);
int getEU(int *field, int width, int height);

int main()
{
    //clock_t t0,t1;
    int *field;
    int EU;
    //enum CellType *FIELD_EU;
    
    field = malloc(sizeof(int)*(FIELD_WIDTH+2)*(FIELD_HEIGHT+2)); // with border
    //FIELD_EU = malloc(sizeof(int) * (FIELD_WIDTH) * (FIELD_HEIGHT)); // border is not used
    initField(field,FIELD_WIDTH+2,FIELD_HEIGHT+2);
    field[1*(FIELD_WIDTH+2)+2]=CELL_URANIUM_DOUBLE;
    field[3*(FIELD_WIDTH+2)+3]=CELL_URANIUM_DOUBLE;
    field[4*(FIELD_WIDTH+2)+1]=CELL_URANIUM_DOUBLE;
    field[3*(FIELD_WIDTH+2)+1]=CELL_URANIUM_SINGLE;
    field[3*(FIELD_WIDTH+2)+2]=CELL_URANIUM_SINGLE;
    field[4*(FIELD_WIDTH+2)+2]=CELL_URANIUM_SINGLE;
    field[2*(FIELD_WIDTH+2)+1]=CELL_URANIUM_QUAD;
    field[2*(FIELD_WIDTH+2)+2]=CELL_URANIUM_QUAD;
    
    printField(field,FIELD_WIDTH+2,FIELD_HEIGHT+2);
    
    EU = getEU(field,FIELD_WIDTH+2,FIELD_HEIGHT+2);
    
    //printf("Runtime: %.06lf",(double)(t1-t0)/CLOCKS_PER_SEC);
    free(field);
    //free(FIELD_EU);
    
    printf("TotalEU: %d\n",EU);
    return 0;
}

void initField(int *FIELD, int width, int height)
{
    int c = 0;
    int x, y;
    
    for( y=0; y<height; y++ )
    {
        for( x=0; x<width; x++ )
        {
            //c++;
            FIELD[y*width+x] = c;
        }
    }
}

void printField(int *FIELD, int width, int height)
{
    int x, y;
    
    for( y=0; y<height; y++ )
    {
        for( x=0; x<width; x++ )
        {
            printf("%d\t", FIELD[y*width+x]);
        }
        printf("\n");
    }
    printf("\n");
}

int getEU(int *field, int width, int height)
{
    int EU = 0;
    int v;
    int x,y;
    int x_max = width-1;
    int y_max = height-1;
    
    //int *ref = malloc(sizeof(int)*(width-2)*(height-2));
    
    for( x=1; x<x_max; x++ ) // without border
    {
        for( y=1; y<y_max; y++ )
        {
            switch( field[y*width+x] )
            {
            case CELL_URANIUM_SINGLE:
                v = 5;
                v += field[(y-1)*width+(x+0)] & MASK_CELL_URANIUM ? 5 : 0;
                v += field[(y+1)*width+(x+0)] & MASK_CELL_URANIUM ? 5 : 0;
                v += field[(y+0)*width+(x-1)] & MASK_CELL_URANIUM ? 5 : 0;
                v += field[(y+0)*width+(x+1)] & MASK_CELL_URANIUM ? 5 : 0;
                break;
            case CELL_URANIUM_DOUBLE:
                v = 20;
                v += field[(y-1)*width+(x+0)] & MASK_CELL_URANIUM ? 10 : 0;
                v += field[(y+1)*width+(x+0)] & MASK_CELL_URANIUM ? 10 : 0;
                v += field[(y+0)*width+(x-1)] & MASK_CELL_URANIUM ? 10 : 0;
                v += field[(y+0)*width+(x+1)] & MASK_CELL_URANIUM ? 10 : 0;
                break;
            case CELL_URANIUM_QUAD:
                v = 60;
                v += field[(y-1)*width+(x+0)] & MASK_CELL_URANIUM ? 20 : 0;
                v += field[(y+1)*width+(x+0)] & MASK_CELL_URANIUM ? 20 : 0;
                v += field[(y+0)*width+(x-1)] & MASK_CELL_URANIUM ? 20 : 0;
                v += field[(y+0)*width+(x+1)] & MASK_CELL_URANIUM ? 20 : 0;
                break;
            default:
                v = 0;
                break;
            }
            
            //ref[(y-1)*(width-2)+(x-1)] = v;
            EU += v;
        }
    }
 
    //printf("\n---------------------------\n");
    //printField(ref,width-2,height-2);
    //free(ref);
    
    return EU;
}


int getEU(int *field, int width, int height)
{
    int EU = 0;
    int v;
    int x,y;
    int x_max = width-1;
    int y_max = height-1;
    
    //int *ref = malloc(sizeof(int)*(width-2)*(height-2));
    
    for( x=1; x<x_max; x++ ) // without border
    {
        for( y=1; y<y_max; y++ )
        {
            switch( field[y*width+x] )
            {
            case CELL_URANIUM_SINGLE:
                v = 5;
                v += field[(y-1)*width+(x+0)] & MASK_CELL_URANIUM ? 5 : 0;
                v += field[(y+1)*width+(x+0)] & MASK_CELL_URANIUM ? 5 : 0;
                v += field[(y+0)*width+(x-1)] & MASK_CELL_URANIUM ? 5 : 0;
                v += field[(y+0)*width+(x+1)] & MASK_CELL_URANIUM ? 5 : 0;
                break;
            case CELL_URANIUM_DOUBLE:
                v = 20;
                v += field[(y-1)*width+(x+0)] & MASK_CELL_URANIUM ? 10 : 0;
                v += field[(y+1)*width+(x+0)] & MASK_CELL_URANIUM ? 10 : 0;
                v += field[(y+0)*width+(x-1)] & MASK_CELL_URANIUM ? 10 : 0;
                v += field[(y+0)*width+(x+1)] & MASK_CELL_URANIUM ? 10 : 0;
                break;
            case CELL_URANIUM_QUAD:
                v = 60;
                v += field[(y-1)*width+(x+0)] & MASK_CELL_URANIUM ? 20 : 0;
                v += field[(y+1)*width+(x+0)] & MASK_CELL_URANIUM ? 20 : 0;
                v += field[(y+0)*width+(x-1)] & MASK_CELL_URANIUM ? 20 : 0;
                v += field[(y+0)*width+(x+1)] & MASK_CELL_URANIUM ? 20 : 0;
                break;
            default:
                v = 0;
                break;
            }
            
            //ref[(y-1)*(width-2)+(x-1)] = v;
            EU += v;
        }
    }
 
    //printf("\n---------------------------\n");
    //printField(ref,width-2,height-2);
    //free(ref);
    
    return EU;
}

/*
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
            case CELL_URANIUM_SINGLE:
                sum = 5;
                if( FIELD[(y+2)*FIELD_WIDTH+(x+1)] != CELL_EMPTY ) { sum += 5; }
                if( FIELD[(y+0)*FIELD_WIDTH+(x+1)] != CELL_EMPTY ) { sum += 5; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+2)] != CELL_EMPTY ) { sum += 5; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+0)] != CELL_EMPTY ) { sum += 5; }
                break;
            case CELL_URANIUM_DOUBLE:
                sum = 20;
                if( FIELD[(y+2)*FIELD_WIDTH+(x+1)] != CELL_EMPTY ) { sum += 10; }
                if( FIELD[(y+0)*FIELD_WIDTH+(x+1)] != CELL_EMPTY ) { sum += 10; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+2)] != CELL_EMPTY ) { sum += 10; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+0)] != CELL_EMPTY ) { sum += 10; }
                break;
            case CELL_URANIUM_QUAD:
                sum = 60;
                if( FIELD[(y+2)*FIELD_WIDTH+(x+1)] != CELL_EMPTY ) { sum += 20; }
                if( FIELD[(y+0)*FIELD_WIDTH+(x+1)] != CELL_EMPTY ) { sum += 20; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+2)] != CELL_EMPTY ) { sum += 20; }
                if( FIELD[(y+1)*FIELD_WIDTH+(x+0)] != CELL_EMPTY ) { sum += 20; }
                break;
            default:
                sum = 0;
                break;
            }
            
            FIELD_EU[y*FIELD_WIDTH+x] = sum;
        }
    }
}
*/