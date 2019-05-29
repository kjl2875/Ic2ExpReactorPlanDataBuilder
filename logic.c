// https://www.onlinegdb.com/online_c_compiler

#include <stdio.h>

#define FIELD_WIDTH (3)
#define FIELD_HEIGHT (4)

enum CellType {
    EMPTY,
    URANIUM_CELL_SINGLE,
    URANIUM_CELL_DOUBLE,
    URANIUM_CELL_QUAD
};

enum CellType *FIELD;

void initField(void);

int main()
{
    int x, y;
    
    /// FIELD init
    
    FIELD = malloc(sizeof(enum CellType) * FIELD_WIDTH * FIELD_HEIGHT);
    
    for( y=0; y<FIELD_HEIGHT; y++ )
    {
        for( x=0; x<FIELD_WIDTH; x++ )
        {
            switch( x )
            {
            case 2:
                switch( y )
                {
                case 2:
                    FIELD[y*FIELD_WIDTH+x] = URANIUM_CELL_DOUBLE;
                    break;
                }
                break;
            default:
                FIELD[y*FIELD_WIDTH+x] = EMPTY;
                break;
            }
            
            printf("%d\t", FIELD[y*FIELD_WIDTH+x]);
        }
        printf("\n");
    }
    
    /// constructor
    
    free(FIELD);
    
    /// return
    
    return 0;
}
