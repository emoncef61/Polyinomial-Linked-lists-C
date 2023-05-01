/**
 * @file linkedList_main.c
 * @brief Programme pour les tests de fonctions de gestion de liste chainee
 * ATTENTION : Il faut creer autant de tests que les cas d'execution pour chaque fonction a tester
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "teZZt.h"


BEGIN_TEST_GROUP(linkedList)

TEST(monom_degree_cmp) {
	monom_t v1 = {5.11, 7};
	monom_t v2 = {3., 5};
	monom_t v3 = {5.25, 7};

	printf("\nGROUP TEST 1: Comparaison des monomes : \n");
	CHECK( monom_degree_cmp(&v1, &v2) > 0 );
	CHECK( monom_degree_cmp(&v2, &v1) < 0 );
	CHECK( monom_degree_cmp(&v1, &v3) == 0 );
}

TEST(monom_save2file) {
	monom_t v = {5., 7};

	// creation du flux de texte => buffer
	char buffer[1024]="";
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	monom_save2file(file, &v);

	fclose(file);

    printf("buffer = %s\n" , buffer );

	CHECK( 0 == strcmp(buffer, "5.000 7\n") );
}


    TEST(LL_init_list) {
        cell_t *list;

        printf("\nInitialization of the linked list : \n");
        LL_init_list(&list);

        REQUIRE ( list == NULL );
    }


TEST(LL_create_cell) { // test de creation de cellule
	cell_t *new = NULL;
	monom_t m1 = {3.245, 17};

	printf("\nCreate a new cell (3.245 17) : \n");
	new = LL_create_cell(&m1);
	REQUIRE ( NULL != new );
	CHECK ( NULL == new->next );

	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	monom_save2file(file, &(new->val));
    printf("\nbuffer = %s\n", buffer );
	fclose(file);
	CHECK( 0 == strcmp(buffer, "3.245 17\n") );
}

// test d'insertion de cellule - liste a une cellule
TEST(LL_add_cell1) {
	cell_t *list = NULL;
	cell_t *new = NULL;
	monom_t m1 = {3.45, 17};

	printf("\nAdd a cell to a linked list : \n");

	new = LL_create_cell(&m1);
	REQUIRE ( new != NULL );

	LL_add_cell(&list, new);
	CHECK( list == new );

	CHECK( list->val.coef == 3.45 );  // 3.45 est une valeur non approchee
	CHECK( list->val.degree == 17 );
	CHECK( list->next == NULL );

	free(list); // liberer la cellule
}

// test d'insertion de cellule - liste a deux cellules
TEST(LL_add_cell2) {
	cell_t *list = NULL;
	cell_t *new = NULL;
	monom_t m1 = {3.45, 17};
	monom_t m2 = {25.8, 9};

	printf("\nAdd two cells to a linked list : \n");

	new = LL_create_cell(&m1);
	REQUIRE ( new != NULL );
	LL_add_cell(&list, new);
	CHECK( list == new );

	new = LL_create_cell(&m2);
	REQUIRE ( new != NULL );
	LL_add_cell(&list, new);
	CHECK( list == new );

	// tester les valeurs de la liste
    CHECK( list->val.coef == 25.8 );
    CHECK( list->val.degree == 9 );
    CHECK( list->next->val.coef == 3.45 );
    CHECK( list->next->val.degree == 17 );
    CHECK( list->next->next == NULL );

	// liberer la liste
    LL_free_list(&list);
}

// test d'insertion de cellule - liste a trois cellules
TEST(LL_add_cell3) {
	cell_t *list = NULL;
	cell_t *new = NULL;
	monom_t m1 = {3.245, 17};
	monom_t m2 = {25.8, 9};
	monom_t m3 = {12.4, 3};

	printf("\nAdd three cells to a linked list : \n");

	new = LL_create_cell(&m1);
	REQUIRE ( new != NULL );
	LL_add_cell(&list, new);
	CHECK( list == new );

	new = LL_create_cell(&m2);
	REQUIRE ( new != NULL );
	LL_add_cell(&list, new);
	CHECK( list == new );

	// ajouter le m3 en tete de la liste
    new = LL_create_cell(&m3);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);
    CHECK( list == new );

	// tester les valeurs de la liste
    CHECK( list->val.coef == 12.4 );
    CHECK( list->val.degree == 3 );
    CHECK( list->next->val.coef == 25.8 );
    CHECK( list->next->val.degree == 9 );
    CHECK( list->next->next->val.coef == 3.245 );
    CHECK( list->next->next->val.degree == 17 );
    CHECK( list->next->next->next == NULL );

	// liberer la liste
    LL_free_list(&list);
}


// test pour la creation d'un polynome a partir d'un fichier - exemple
TEST(LL_create_list_fromFileName0) {

	cell_t *list = NULL;

	printf("\nCreate a linked list from file notExist.txt: \n");

	LL_create_list_fromFileName(&list, "notExist.txt");
	CHECK( NULL == list );


}

// test pour la creation d'un polynome a partir d'un fichier
TEST(LL_create_list_fromFileName) {
	cell_t *list = NULL;

    printf("\nCreate a linked list from file list1: \n");

    LL_create_list_fromFileName(&list, "list1.txt");

    //test values of linked list
    //list1.txt :
    //2.1 1
    //1.3 2
    //3.1 7

    CHECK( list->val.coef == 2.1 );
    CHECK( list->val.degree == 1 );
    CHECK( list->next->val.coef == 1.3 );
    CHECK( list->next->val.degree == 2 );
    CHECK( list->next->next->val.coef == 3.1 );
    CHECK( list->next->next->val.degree == 7 );
    CHECK( list->next->next->next == NULL );

    // free the memory
    LL_free_list(&list);

}

TEST(LL_save_list_toFile) { // test pour l'ecriture d'un polynome sur un flux de sortie
        cell_t *new = NULL;
        char buffer[1024];
        FILE *file = fmemopen(buffer, 1024, "w");

        printf("\n Printing a polynomial on an output stream  \n");

        printf("\n Case 1 : empty list \n :");
        //initializing a linked list
        cell_t *list = NULL;
        LL_save_list_toFile(file, &list, monom_save2file);

        fclose(file);

        CHECK(0 == strcmp(buffer, ""));
    }



    TEST(LL_save_list_toFile) {

    printf("\n Case 2 : non empty list \n :");
    //initializing a linked list of 3 cells

    //initializing a linked list
    cell_t *list = NULL;
    cell_t *new = NULL;
    char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");

    monom_t m1 = {3.245, 17};
    monom_t m2 = {25.8, 9};
    monom_t m3 = {12.4, 3};

    printf("\nAdd three cells to a linked list : \n");

    new = LL_create_cell(&m1);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);


    new = LL_create_cell(&m2);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);



    new = LL_create_cell(&m3);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);

    //printing on output stream

    LL_save_list_toFile(file, &list,monom_save2file);

    //test
    CHECK( 0 == strcmp(buffer, "12.400 3\n25.800 9\n3.245 17\n") );
    printf("buffer : \n%s",buffer);

    // free the memory
    LL_free_list(&list);
    }

TEST(LL_search_prev) { // test pour la fonction de recherche d'une valeur
        cell_t **pprev = NULL;
        cell_t *new = NULL;

        printf("\n Test previous pointer function:  \n");

        printf("\n case 1 : empty list  \n");
        cell_t *list = NULL;
        monom_t *value = NULL;
        pprev = LL_search_prev(&list, NULL, monom_degree_cmp);
        CHECK (NULL == pprev);

    }



TEST(LL_search_prev){
    cell_t *list = NULL;
    cell_t *new = NULL;
    cell_t **pprev = NULL;
    cell_t **pprev2 = NULL;
    monom_t value;
    monom_t value2;

    printf("\n case 2 : previous pointer of an element of a non empty list of 4 nodes \n");


    //initializing a linked list of 4 nodes
    monom_t m1 = {3.245, 17};
    monom_t m2 = {25.8, 9};
    monom_t m3 = {12.4, 3};
    monom_t m4 = {3.4, 1};



    new = LL_create_cell(&m1);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);


    new = LL_create_cell(&m2);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);



    new = LL_create_cell(&m3);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);


    new = LL_create_cell(&m4);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);


    //previous pointer of the node {12.4, 3}
    value.degree = 3;
    value.coef = 12.4;

    pprev = LL_search_prev(&list,&value,monom_degree_cmp);
    printf("\nprevious pointer of the  existing node {12.4, 3}\n");
    CHECK( value.coef == (*pprev)->val.coef );
    CHECK( value.degree == (*pprev)->val.degree );


    //previous pointer of non existing node {20.0, 6}
    printf("\nprevious pointer of the  non existing node {20.0, 6}\n");
    value2.degree = 6;
    value2.coef = 20.0;

    pprev2 = LL_search_prev(&list,&value2,monom_degree_cmp);


    CHECK( NULL == pprev2);

    //free lists
    LL_free_list(&list);

}
/*
TEST(LL_add_celln) { // test d'insertion de cellule - liste a n cellules
	cell_t *list = NULL;

}
 */

TEST(LL_del_cell) { // test de la suppression d'un element
	cell_t *list = NULL;
    cell_t **pprev = NULL;
    cell_t *new = NULL;
    monom_t to_del;
    char buffer[1024];
    FILE *file = fmemopen(buffer, 1024, "w");


    printf("\n Test delete node from linked list of 4 nodes  \n");


    monom_t m1 = {3.245, 17};
    monom_t m2 = {25.8, 9};
    monom_t m3 = {12.4, 3};
    monom_t m4 = {3.4, 1};



    new = LL_create_cell(&m1);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);


    new = LL_create_cell(&m2);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);



    new = LL_create_cell(&m3);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);


    new = LL_create_cell(&m4);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);

    //item to delete given the previous pointer;

    printf("\n case 1 : existing element \n");

    //checking new list
    LL_save_list_toFile(file, &list,monom_save2file);

    printf("buffer :\n%s",buffer);
    CHECK( 0 == strcmp(buffer, "3.400 1\n12.400 3\n25.800 9\n3.245 17\n") );

    //closing file
    fclose(file);


    //Reupdating the buffer
    buffer[1024] = "";
    //opening the buffer as a file stream
    file = fmemopen(buffer, 1024, "w");
    //search for pprev
    to_del.degree = 3;
    to_del.coef = 12.400;
    //finding previous pointer
    pprev = LL_search_prev (&list, &to_del, monom_degree_cmp);
    //deleting the element
    LL_del_cell(pprev);
    //saving the new list to buffer
    LL_save_list_toFile(file, &list,monom_save2file);

    printf("buffer : \n%s",buffer);
    CHECK( 0 == strcmp(buffer, "3.400 1\n25.800 9\n3.245 17\n") );
    //closing the buffer
    fclose(file);

    printf("\n case 2 : non existing element \n");
    //Reupdating the buffer
    buffer[1024] = "";
    //opening the buffer as a file stream
    file = fmemopen(buffer, 1024, "w");
    //search for pprev
    to_del.degree = 2;
    to_del.coef = 10.4;
    //finding previous pointer
    pprev = LL_search_prev (&list, &to_del, monom_degree_cmp);
    //deleting the element
    LL_del_cell(pprev);
    //saving the new list to buffer
    LL_save_list_toFile(file, &list,monom_save2file);
    //checking deletion
    printf("buffer : \n%s",buffer);
    CHECK( 0 == strcmp(buffer, "3.400 1\n25.800 9\n3.245 17\n") );
    //close file
    fclose(file);
    //free list
    LL_free_list (&list);
    }

TEST(LL_free_list) { // test de la liberation de liste

    printf("\n Test free list (each cell should be set to NULL)  \n");
    //creating new list
    cell_t *list =NULL;
    cell_t *new =NULL;
    monom_t m1 = {3.245, 17};
    monom_t m2 = {25.8, 9};
    monom_t m3 = {10.7, 5};
    monom_t m4 = {13.9, 10};

    new = LL_create_cell(&m1);
    REQUIRE(new != NULL);
    LL_add_cell(&list , new);
    CHECK(list == new);

    new = LL_create_cell(&m2);
    REQUIRE(new != NULL);
    LL_add_cell(&list , new);
    CHECK(list == new);

    new = LL_create_cell(&m3);
    REQUIRE(new != NULL);
    LL_add_cell(&list , new);
    CHECK(list == new);

    new = LL_create_cell(&m4);
    REQUIRE(new != NULL);
    LL_add_cell(&list , new);
    CHECK(list == new);

    //free list
    LL_free_list(&list);
    //check if each cell is NULL

    CHECK (NULL == list);


    }
/*
TEST(LL_save_list_toFileName) { // BONUS - 3eme Seance
    printf("\n Test list to fileName: list2  \n");
    //initialization new linked list
    cell_t *list_to_file = NULL;
    FILE * file1 = fopen("list2","w");
    cell_t *new = NULL;

    monom_t m1 = {3.245, 17};
    monom_t m2 = {25.8, 9};
    monom_t m3 = {12.4, 3};
    monom_t m4 = {3.4, 1};



    new = LL_create_cell(&m1);
    REQUIRE ( new != NULL );
    LL_add_cell(&list_to_file, new);


    new = LL_create_cell(&m2);
    REQUIRE ( new != NULL );
    LL_add_cell(&list_to_file, new);



    new = LL_create_cell(&m3);
    REQUIRE ( new != NULL );
    LL_add_cell(&list_to_file, new);


    new = LL_create_cell(&m4);
    REQUIRE ( new != NULL );
    LL_add_cell(&list_to_file, new);




    LL_save_list_toFileName(file1, &list_to_file);
    fclose(file1);

    //opening the file into a new list
    cell_t **list_from_file = NULL;
    list_from_file = LL_create_list_fromFileName(list_from_file, "list2");
    //opening the list into a buffer stream
    char buffer[1024];
    FILE* file = fmemopen(buffer, 1024, "w");
    //checking new list
    LL_save_list_toFile(file, &list_from_file,monom_save2file);
    CHECK( 0 == strcmp(buffer, "3.4 1\n12.4 3\n25.8 9\n3.245 17\n") );
    //closing file stream
    fclose(file);
    //free lists
    LL_free_list(&list_to_file);
    LL_free_list(list_from_file);
}
*/

END_TEST_GROUP(linkedList)

int main(void) {
    RUN_TEST_GROUP(linkedList);
    return EXIT_SUCCESS;
}
