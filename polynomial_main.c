/**
 * @file polynomial_main.c
 * @brief Programme pour les tests des operations sur les polynomes
 * ATTENTION : Il faut creer autant de tests que les cas d'execution pour chaque fonction a tester
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "polynomial.h"
#include "teZZt.h"

BEGIN_TEST_GROUP(polynomial)

    TEST(LL_init_list) {
        cell_t *list;

        printf("\nInitialization of the linked list : \n");
        LL_init_list(&list);

        REQUIRE ( list == NULL );
    }


TEST(Poly_derive1) {  // exemple
    cell_t *list = malloc(sizeof(cell_t));;
	FILE   *file = NULL;
	char   buffer[1024];
    char   result[1024];
	printf("\nDerive of polynomial 1 : \n");
    printf("\ncase 1: non NULL linked list and without constant nodes\n");
    //from file to buffer
	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file );
	LL_create_list_fromFileName(&list, "poly1.txt");
	LL_save_list_toFile(file, &list, monom_save2file);
	fclose(file);
	// LL_save_list_toFile(stdout, poly, monom_save2file);
	// printf("\n");
	CHECK( 0 == strcmp(buffer, "5.000 1\n4.000 2\n5.000 3\n6.000 4\n3.000 5\n") );
    //poly_derive on the linked list into the buffer
	file = fmemopen(result, 1024, "w");
	REQUIRE ( NULL != file );
	poly_derive(&list);
	LL_save_list_toFile(file, &list, monom_save2file);
	fclose(file);
	// LL_save_list_toFile(stdout, poly, monom_save2file);
	CHECK( 0 == strcmp(result, "5.000 0\n8.000 1\n15.000 2\n24.000 3\n15.000 4\n") );
	LL_free_list(&list);
}

TEST(Poly_derive) { // test sur la derivation d'un polynome
    cell_t *list = malloc(sizeof(cell_t));;
    FILE   *file = NULL;
    char   poly[1024];
    char   result[1024];
    printf("\nDerive of polynomial 1 : \n");
    printf("\ncase 2: non NULL linked list and with a constant nodes\n");
    //from file to buffer
    file = fmemopen(poly, 1024, "w");
    REQUIRE ( NULL != file );
    LL_create_list_fromFileName(&list, "poly2.txt");
    LL_save_list_toFile(file, &list, monom_save2file);
    fclose(file);
    // LL_save_list_toFile(stdout, poly, monom_save2file);
    // printf("\n");
    CHECK( 0 == strcmp(poly, "5.000 0\n4.000 2\n5.000 3\n6.000 4\n") );
    //poly_derive on the linked list into the buffer
    file = fmemopen(result, 1024, "w");
    REQUIRE ( NULL != file );
    poly_derive(&list);
    LL_save_list_toFile(file, &list, monom_save2file);
    fclose(file);
    // LL_save_list_toFile(stdout, poly, monom_save2file);
    CHECK( 0 == strcmp(result, "8.000 1\n15.000 2\n24.000 3\n") );
    LL_free_list(&list);
}


TEST(Poly_addition) { // test sur l'addition de deux polymones
	cell_t *list1 = NULL;
    cell_t *list2 = NULL;
    FILE   *file1 = NULL ;
    FILE   *file2 = NULL;
    FILE   *file  = NULL;
    char   poly1[1024];
    char   poly2[1024];
    char   result[1024];

    printf("\nSum of two polynomials : \n");
    printf("\ncase 1: lengh of poly1 >= lengh of poly2\n");

    //initializing  2 new lists lengh of poly1 >= lengh of poly2
    file1 = fmemopen(poly1, 1024, "w");
    file2 = fmemopen(poly2, 1024, "w");
    REQUIRE ( NULL != file1 );
    REQUIRE ( NULL != file2 );


    LL_create_list_fromFileName(&list1, "poly1.txt");
    LL_create_list_fromFileName(&list2, "poly2.txt");
    //saving to the buffers


    LL_save_list_toFile(file1, &list1, monom_save2file);
    LL_save_list_toFile(file2, &list2, monom_save2file);
//    //adding the 2 polynomials
//    printf("\n list 1 : 5.000 1 ->  4.000 2 -> 5.000 3 -> 6.000 4 -> 3.000 5\n");
//    printf("\n list 2 : 5.000 0 ->  4.000 2 -> 5.000 3 -> 6.000 4\n");

    CHECK( 0 == strcmp(poly1, "5.000 1\n4.000 2\n5.000 3\n6.000 4\n3.000 5\n") );
    CHECK( 0 == strcmp(poly2, "5.000 0\n4.000 2\n5.000 3\n6.000 4\n") );
    //closing the buffers

    fclose(file1);
    fclose(file2);


    //opening the result buffer

    file = fmemopen(result, 1024, "w");

    //adding the 2 polynomials
    poly_add(&list1,&list2);

    //saving to the buffer
    LL_save_list_toFile(file, &list1, monom_save2file);

    REQUIRE ( NULL != file );


    //checking result
    printf("result = \n%s",result);
    CHECK( 0 == strcmp(result, "5.000 0\n5.000 1\n8.000 2\n10.000 3\n12.000 4\n3.000 5") );

        // closing the file
    fclose(file);


    }

TEST(Poly_addition){
   cell_t *list1 = NULL;
    cell_t *list2 = NULL;
    FILE   *file1 = NULL ;
    FILE   *file2 = NULL;
    FILE   *file  = NULL;
    char   poly1[1024];
    char   poly2[1024];
    char   result[1024];

    printf("\ncase 2: lengh of poly1 <= lengh of poly2\n");

    //initializing  2 new lists lengh of poly1 >= lengh of poly2
    file1 = fmemopen(poly1, 1024, "w");
    file2 = fmemopen(poly2, 1024, "w");
    REQUIRE ( NULL != file1 );
    REQUIRE ( NULL != file2 );


    LL_create_list_fromFileName(&list1, "poly2.txt");
    LL_create_list_fromFileName(&list2, "poly1.txt");
    //saving to the buffers


    LL_save_list_toFile(file1, &list1, monom_save2file);
    LL_save_list_toFile(file2, &list2, monom_save2file);
//    //adding the 2 polynomials
//    printf("\n list 1 : 5.000 1 ->  4.000 2 -> 5.000 3 -> 6.000 4 -> 3.000 5\n");
//    printf("\n list 2 : 5.000 0 ->  4.000 2 -> 5.000 3 -> 6.000 4\n");
    CHECK( 0 == strcmp(poly1, "5.000 0\n4.000 2\n5.000 3\n6.000 4\n") );
    CHECK( 0 == strcmp(poly2, "5.000 1\n4.000 2\n5.000 3\n6.000 4\n3.000 5\n") );
    //closing the buffers

    fclose(file1);
    fclose(file2);


    //opening the result buffer
    file = fmemopen(result, 1024, "w");
    //adding the 2 polynomials
    poly_add(&list1,&list2);

    //saving to the buffer
    LL_save_list_toFile(file, &list1, monom_save2file);

    REQUIRE ( NULL != file );


    //checking result
    printf("result = \n%s",result);
    CHECK( 0 == strcmp(result, "5.000 0\n5.000 1\n8.000 2\n12.000 4\n3.000 5\n") );

    // closing the file
    fclose(file);


    }


TEST(Poly_addition){
   cell_t *list1 = NULL;
   cell_t *list2 = NULL;
   FILE   *file1 = NULL ;
   FILE   *file2 = NULL;
   FILE   *file  = NULL;
   char   poly1[1024];
   char   poly2[1024];
   char   result[1024];

   printf("\ncase 3 : a sum of 2 nodes in 0 \n");

   //initializing  2 new lists lengh of poly1 >= lengh of poly2
   file1 = fmemopen(poly1, 1024, "w");
   file2 = fmemopen(poly2, 1024, "w");
   REQUIRE ( NULL != file1 );
   REQUIRE ( NULL != file2 );


   LL_create_list_fromFileName(&list1, "poly3.txt");
   LL_create_list_fromFileName(&list2, "poly2.txt");
   //saving to the buffers


   LL_save_list_toFile(file1, &list1, monom_save2file);
   LL_save_list_toFile(file2, &list2, monom_save2file);
// adding the 2 polynomials
// intf("\n list 1 : 5.000 1 ->  4.000 2 -> 5.000 3 -> 6.000 4 -> 3.000 5\n");
// intf("\n list 2 : 5.000 0 ->  4.000 2 -> 5.000 3 -> 6.000 4\n");
   CHECK( 0 == strcmp(poly1, "5.000 1\n4.000 2\n-5.000 3\n6.000 4\n3.000 5\n") );
   CHECK( 0 == strcmp(poly2, "5.000 0\n4.000 2\n5.000 3\n6.000 4\n") );
   //closing the buffers

   fclose(file1);
   fclose(file2);


   //opening the result buffer
   file = fmemopen(result, 1024, "w");
   //adding the 2 polynomials
   poly_add(&list1,&list2);

   //saving to the buffer
   LL_save_list_toFile(file, &list1, monom_save2file);

   REQUIRE ( NULL != file );



   //checking result
   printf("result = \n%s",result);
   CHECK( 0 == strcmp(result, "5.000 0\n5.000 1\n8.000 2\n12.000 4\n3.000 5\n") );

   // closing the file
   fclose(file);

   //free the list
   LL_free_list(&list1);

    }

TEST(Poly_produit) { // test sur le calcul du produit de deux polymones
   cell_t **list1 = NULL;
   cell_t **list2 = NULL;
   cell_t **list = NULL;  // result
   cell_t *poly1 = NULL;
   cell_t *poly2 = NULL;
   FILE   *file = NULL;
   char   buffer[1024];
   printf("\nproduct of two polynomials : \n");
   printf("\ncase 1: one polynomial is NULL \n");

   //initializing  2 new lists
   file = fmemopen(buffer, 1024, "w");
   REQUIRE ( NULL != file );
   list1 = LL_create_list_fromFileName(&poly1, "poly3.txt");
   list2 = LL_create_list_fromFileName(&poly2, "notExist.txt");

   //product of  the 2 polynomials
   printf("\n list 1 : 5.000 0 ->  4.000 2 -> -5.000 3 -> 6.000 4\n3.000 5\n");
   printf("\n list 2 :(NULL) \n");

   list = poly_prod(list1, list2,monom_degree_cmp);

   //saving to the buffer
   LL_save_list_toFile(file, list, monom_save2file);
   //checking result
   CHECK( 0 == strcmp(buffer, "\n"));
   // closing the file
   fclose(file);

   //free the list
   LL_free_list(list1);
   LL_free_list(list2);
    }

TEST(Poly_produit) { // test sur le calcul du produit de deux polymones
    cell_t **list1 = NULL;
    cell_t **list2 = NULL;
    cell_t **list = NULL;  // result
    cell_t *poly1 = NULL;
    cell_t *poly2 = NULL;
    FILE   *file = NULL;
    char   buffer[1024];
    printf("\ncase 2: general \n");

    //initializing  2 new lists
    file = fmemopen(buffer, 1024, "w");
    REQUIRE ( NULL != file );
    list1 = LL_create_list_fromFileName(&poly1, "poly1.txt");
    list2 = LL_create_list_fromFileName(&poly2, "poly2.txt");

    //product of  the 2 polynomials
    printf("\n list 1 : 5.000 1 ->  4.000 2 -> 5.000 3 -> 6.000 4 -> 3.000 5\n");
    printf("\n list 2 : 5.000 0 ->  4.000 2 -> 5.000 3 -> 6.000 4\n");

    list = poly_prod(list1, list2,monom_degree_cmp);

    //saving to the buffer
    LL_save_list_toFile(file, list, monom_save2file);
    //checking result
    CHECK( 0 == strcmp(buffer, "25.000 1\n20.000 2\n45.000 3\n71.000 4\n85.000 5\n73.000 6\n72.000 7\n51.000 8\n18.000 9\n"));

    // closing the file
    fclose(file);

    //free the list
    LL_free_list(list1);
    LL_free_list(list2);
    }

TEST(Poly_produit) { // test sur le calcul du produit de deux polymones
    cell_t **list1 = NULL;
    cell_t **list2 = NULL;
    cell_t **list = NULL;  // result
    cell_t *poly1 = NULL;
    cell_t *poly2 = NULL;
    FILE   *file = NULL;
    char   buffer[1024];
    printf("\ncase 3: deleted node after multiplication \n");

    //initializing  2 new lists
    file = fmemopen(buffer, 1024, "w");
    REQUIRE ( NULL != file );
    list1 = LL_create_list_fromFileName(&poly1, "poly5.txt");
    list2 = LL_create_list_fromFileName(&poly2, "poly4.txt");

    //product of  the 2 polynomials
    printf("\n list 1 :  1.000 0-> 1.000 1\n");
    printf("\n list 2 :  1.000 0-> -1.000 1\n");

    list = poly_prod(list1, list2,monom_degree_cmp);

    //saving to the buffer
    LL_save_list_toFile(file, list, monom_save2file);
    //checking result
    CHECK( 0 == strcmp(buffer, "1.000 0\n-1.000 2\n"));

    // closing the file
    fclose(file);
    //free the list
    LL_free_list(list1);
    LL_free_list(list2);
}



TEST(LL_save_list_toFileName) { // test pour l'ecriture d'un polynome dans un fichier
	cell_t *list;

	//TO DO
}


END_TEST_GROUP(polynomial)

int main(void) {
    RUN_TEST_GROUP(polynomial);
    return EXIT_SUCCESS;
}
