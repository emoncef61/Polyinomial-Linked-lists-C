#include <stdio.h>
#include <stdlib.h>
#include <float.h>  // FLT_EPSILON DBL_EPSILON LDBL_EPSILON
#include <math.h>

#include "linkedList.h"

/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief compute 'in place' the derive of a polynomial 
 * @param [in, out] xxx address of a polynomial's head pointer
 */

void poly_derive(cell_t **adrHeadPt)
{
    cell_t *curr = *adrHeadPt;
    cell_t **pprev = adrHeadPt;
    while (curr) {
        if (curr->val.degree == 0) {
            LL_del_cell(pprev);
        } else {
            curr->val.coef = (curr->val.coef) * (curr->val.degree);
            curr->val.degree--;
            curr = curr->next;
        }
    }

 }

/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief compute P1 = P1 + P2, P2 become empty
 * @param xxx [in, out] address of the 1st polynomial's head pointer
 * @param xxx [in, out] address of the 2nd polynomial's head pointer
 */


 void poly_add(cell_t **adrHeadPt1,cell_t **adrHeadPt2) {

    cell_t *curr1 = *adrHeadPt1;
    cell_t *curr2 = *adrHeadPt2;
    cell_t **pprev = adrHeadPt1;
    cell_t *new = NULL;

    while (curr1->next && curr2->next) {
        //comparing the two nodes
        int cmp = monom_degree_cmp(&(curr1->val), &(curr2->val));


        if (cmp < 0) {
            //case 1 : node1 degree < node2 degree
            //       => 1) we update the previous and current list1 pointer to the next node
            pprev=&((*pprev)->next);
            curr1 = curr1->next;


        } else if (cmp > 0) {
            //case 2 : node 1 degree > node2 degree
            //       => 1) we add the node 2 behind the node1 using LL_add_cell
            //       => 2) we update the previous list 1 pointer to the next node
            //       => 3) we update the current list 2 pointer to the next node
            new = LL_create_cell(&(curr2->val));
            LL_add_cell (pprev,new);

            pprev=&((*pprev)->next);
            curr2 = curr2->next;

        } else if (cmp == 0) {
            //case 3 :  node 1 degree = node 2 degree
            //       => 1) add both nodes values and store it in list 1
            //       => 2) if the sum ==  0 then we delete the node from list 1
            //       => 3) we update the previous and current list1 pointer to the next node
            //       => 4) we update the current list 2 pointer to the next node

            int new_val = curr1->val.coef + curr2->val.coef;
            curr1->val.coef = new_val;
            if (curr1->val.coef == 0.0) {
                LL_del_cell(pprev);
            }
            pprev = &((*pprev)->next);
            curr1 = curr1->next;
            curr2 = curr2->next;

        }

        // if liste1 shorter than liste2 we add the rest of list2 to list1
        if (!curr1) {
            while (curr2) {
                new = LL_create_cell(&(curr2->val));
                LL_add_cell (pprev,new);
                curr2 = curr2->next;
                pprev = &((*pprev)->next);
            }
        }

    }
    //free list 2;
    LL_free_list(adrHeadPt2);
}

/*---------------------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief compute P1 * P2
 * @param xxx [in, out] head pointer of the 1st polynomial
 * @param xxx [in, out] head pointer of the 2nd polynomial
 * @return P1*P2
 */

 cell_t **poly_prod(cell_t **adrHeadPt1,cell_t **adrHeadPt2, int (*f)(monom_t* m1,monom_t* m2)) {
    //initialization
    cell_t *curr1 = *adrHeadPt1;
    cell_t *curr2 = *adrHeadPt2;
    //new list head node
    cell_t **adrHeadPolyProd = NULL;
    //monom and nodes to be added to the head node
    monom_t *prod = NULL;
    cell_t *prod_cell = NULL;



    if (curr1 == NULL || curr2 == NULL){
        //list 1 or list 2 are empty or equal to 0
        // returning NULL
        return adrHeadPolyProd;

    }else{
        while(curr1!= NULL){
            while(curr2 != NULL){
                    //calculating the monom_t
                    prod->coef = curr1->val.coef * curr2->val.coef;
                    prod->degree = curr1->val.degree + curr2->val.degree;
                    //(re)initializing current and previous pointers to first node
                    prod_cell = LL_create_cell(prod);
                    //adding the new cell to rest of the nodes
                    poly_add(adrHeadPolyProd,&prod_cell);
                    curr2 = curr2->next;
            }

            //list 1 current pointer to the next node
            curr1 = curr1->next;
            //list 2 current pointer to the start of the node
            curr2 = *adrHeadPt2;
        }
        //returning the head pointer
        return adrHeadPolyProd;

    }
 }

/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/

