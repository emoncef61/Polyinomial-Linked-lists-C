#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

 #include "linkedList.h"

/** TO DO
 * @brief compute 'in place' the derive of a polynomial
 * @param [in, out] xxx address of a polynomial's head pointer
 */
void poly_derive(cell_t **);

/** TO DO
 * @brief compute P1 = P1 + P2, P2 become empty
 * @param xxx [in, out] address of the 1st polynomial's head pointer
 * @param xxx [in, out] address of the 2nd polynomial's head pointer
 */
void poly_add(cell_t **,cell_t **);

/** TO DO
 * @brief P1 * P2
 * @param xxx [in, out] head pointer of the 1st polynomial
 * @param xxx [in, out] head pointer of the 2nd polynomial
 * @return P1*P2
 */

cell_t **poly_prod(cell_t **,cell_t **,int (*f)(monom_t *, monom_t *));


#endif