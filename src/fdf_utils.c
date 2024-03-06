#include "../include/fdf.h"

Point3D *store_in_node( int x , int y , int z , int color )
{

    Point3D *node ;

    node = malloc(sizeof(Point3D)) ;
    node->x =  x;
    node->y  = y;
    node->z =  z;
    node->color = color ;
    node->next = NULL; 
    return node;
}

Point3D *setup_first_node ( Point3D **head , Point3D **point , int **map)
{
    int j ;
    int i ;

    i = 0 ;
    j = 0;

    *head = store_in_node(map[i][j] , map[i][j+1] , map[i][j+2] ,map[i][j+3] );  
    *point = *head;
    (*point) -> next = store_in_node( map[i+1][j] ,map[i+1][j+1] ,map[i+1][j+2] , map[i+1][j+3]);   
    j += 4;
    (*point) -> next -> next = store_in_node(map[i][j] ,map[i][j+1] ,map[i][j+2] , map[i][j+3]);
    *point = (*point) -> next -> next;

    return *head ; 

}