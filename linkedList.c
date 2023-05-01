/**
 * @file linkedList.c
 * @brief Implementation file of linked list module
 */
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"


/*---------------------------------------------------------------------------------------------------------------------*/
/** Example
 * @fn void LL_init_list(cell_t **adrHeadPt)
 * @brief Initialize a void list
 * @param [in, out] adrHeadPt address of head pointer of the list
 */

void LL_init_list(cell_t **adrHeadPt)
{
    *adrHeadPt = NULL;

}
/*---------------------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief Create a new cell for linked list from its data
 * @param [in] xxx address of the data
 * @return address of the new cell
 */

cell_t*  LL_create_cell(monom_t *m1)
{
    cell_t *new = (cell_t *) malloc((sizeof(cell_t)));
    if (m1->coef != 0.0) {
        new->val.coef = m1->coef;
        new->val.degree = m1->degree;
        new->next = NULL;
        return new;
    }
    if (m1->coef == 0.0){     //polynome null representer par une cellule nulle
        new = NULL;
        return NULL;
    }
}
/*---------------------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief Insert a cell into a linked list at the given position
 * @param [in, out]  xxx address of previous pointer of the cell
 * @param [in]  xxx address of the cell to be added to the linked list
 */

void LL_add_cell(cell_t **pprev,cell_t *new)
{
    //adds the new node after the previous pointer
    new->next = *pprev;
    *pprev = new;

}
/*---------------------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief Create a linked list from a file (in which the data is sorted)
 * @param [in, out] xxx address of head pointer of a linked list
 * @param [in] xxx name of a file containing the data for a linked list
 * @return head pointer of the linked list
 */

cell_t ** LL_create_list_fromFileName(cell_t **adrHeadPt, char * file_name) {
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file. \n");
        *adrHeadPt = NULL;
        return NULL;
    }
    // read the first monomial
    monom_t m;
    if ((fscanf(file, "%lf %d", &m.coef, &m.degree)) != 2) {
        return NULL;
    }
    //initializing the linked list with a first element
    cell_t *curr = malloc(sizeof(cell_t));
    curr->val = m;
    curr->next = NULL;
    *adrHeadPt = curr;
    // notice : a do-while will access a non reserved memory hence segmentation faults
    while ((fscanf(file, "%lf %d", &m.coef, &m.degree)) == 2) {
        cell_t *new = malloc(sizeof(cell_t));
        new->val = m;
        new->next = NULL;

        LL_add_cell(&(curr->next), new); //pprev: &(current->next)
        curr = curr->next;  //move to the next node
    }
    fclose(file);
    return adrHeadPt;
}


/*---------------------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief Write the linked list to an output stream
 * @param [in] xxx file pointer of an output stream
 * @param [in] xxx head pointer of a linked list
 * @param xxx fonction pointer for printing the data of a cell on an output stream
 */

void LL_save_list_toFile(FILE *file, cell_t **adrHeadPt,  void (*f)(FILE *, monom_t *))
{
    //initializing the current node
    cell_t *curr = *adrHeadPt;

    while (curr){
        //f saves the monom to the file
        f(file, &(curr->val));
        //current is set to the next node
        curr = curr->next;
    }

}
/*---------------------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief Save a linked list into a file
 * @param [in, out] xxx head pointer of a linked list
 * @param [in] xxx name of the backup file
 * @param xxx fonction pointer for writing the data of a cell to a output stream
 */

void LL_save_list_toFileName(cell_t **adrHeadPt, char* name)
{
    //opening the file in file pointer named file
    FILE *file = fopen(name, "w");

    //saving the list to the new stream
    LL_save_list_toFile(file , adrHeadPt, monom_save2file);

    //closing the file
    fclose(file);

}

/*---------------------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 *
 * @brief Search a value in a linked list, and return the address of the previous pointer
 * @param [in] xxx address of the head pointer
 * @param [in] xxx address of the value to search
 * @param  xxx fonction pointer for comparison of two values
 * @return the address of the previous pointer
 */

cell_t ** LL_search_prev(cell_t **adrHeadPt, monom_t *value, int (*f)(monom_t *m1, monom_t *m2) )
{
    if (!adrHeadPt) {
        return NULL;
    }

    cell_t *curr = *adrHeadPt;

    while (curr->next != NULL && curr->next->val.degree < value->degree) {

            //while the current degree is < than the value to search
            curr = curr->next;

    }
    //value not found
    if ((curr->next->val.degree != value->degree) || (curr->next->val.coef != value->coef))
        return NULL;

    // value found
    if ((curr->next->val.degree == value->degree) && (curr->next->val.coef == value->coef))
        return &(curr->next);

}
/*---------------------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief Delete a cell from a linked list
 * @param [in, out] xxx address of the previous pointer of the cell to delete
 */

void LL_del_cell(cell_t **pprev )
{

    if (pprev && (*pprev)->next )
    {
        //storing the node to delete adress
        cell_t *to_del = *pprev;
        //prev pointer set to the next element
        *pprev = (*pprev)->next;
        //free the memory
        free(to_del);
    }

}


/*---------------------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief Free the memory location occupied by a linked list
 * @param [in, out] xxx address of head pointer of a linked list
 */
void LL_free_list(cell_t **adrHeadPt)
{
    cell_t *curr = NULL ;

    while (*adrHeadPt != NULL){
        //starting from the head to the end deleting each node
        curr = *adrHeadPt;
        *adrHeadPt = (*adrHeadPt)->next;
        free(curr);
    }
}

/*---------------------------------------------------------------------------------------------------------------------*/
