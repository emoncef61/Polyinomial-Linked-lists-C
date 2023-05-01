/**
 * @file valCell.c
 * Implementation file for comparison and display of linked list's cells
 */

#include <stdio.h>
#include "valCell.h"


/*----------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief Compare the degree of two monomials
 * @param [in] xxx address of the first monomial
 * @param [in] xxx address of the second monomial
 * @return <0 if degree1<degree2; =0 if degree1=degree2;  >0 if degree1>degree2
 */ 

int monom_degree_cmp(monom_t *m1, monom_t *m2)
{
    if(m1->degree < m2->degree) {
        return -1;

    }else if(m1->degree > m2->degree) {
        return 1;
    }


	return 0;
}
/*----------------------------------------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------------------------------------*/
/** TO DO
 * @brief write the information of a monomial to the given output stream
 * @param [in] xxx file pointer of an output stream
 * @param [in] xxx address of a monomial
 */

void monom_save2file(FILE *file, monom_t *m)
{

        fprintf(file, "%.3f %d\n", m->coef, m->degree);

}
/*----------------------------------------------------------------------------------------------------------------------*/