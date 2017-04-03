#include "constante.h"
#ifndef ELEMENT_H
#define ELEMENT_H
int size_tab_node;
int size_tab_way;
int size_tab_relation;

/**
 * \struct Tag
 * \brief Objet contenant un Tag(clé/val).
 * \author Fadyl Bello
 * \date Février 2016
 * \version 1.0
 */
typedef struct Tag Tag;
struct Tag
{
	char *k;/*!< Chaîne avec  caractère contenant la clé. */
	char *v;/*!< Chaîne avec  caractère contenant la valeur. */
};

/**
 * \struct Node
 * \brief Objet contenant un Noeud (identifiant/position/Tag
 * \author Fadyl Bello
 * \date Février 2016
 * \version 1.0
 */
typedef struct Node Node;
struct Node{
	int id; /*!< Entier contenant l'identifiant */
	double lat; /*!< Réelle contenant la latitude */
	double lon; /*!< Réelle contenant la longitude */
	Tag list_tag[MAX_SIZE_TAG]; /*!< Liste de tag */
};

/**
 * \struct bounds
 * \brief Contient les données de la map et de l'écran 
 * \author Fadyl Bello
 * \date Février 2016
 * \version 1.0
 */
typedef struct bounds bounds;
struct bounds{
	/*!< distance de bounds */
	double maxlat;
	double minlat;
	double maxlon;
	double minlon;
	/*!< distance d'affichage*/
	double true_maxlat;
	double true_minlat;
	double true_maxlon;
	double true_minlon;
	/*!< Centre d'affichage */
	double center_x;
	double center_y;
	/*!< Rayon d'affichage */
	double rayon_x;
	double rayon_y;
};

/**
 * \struct Way
 * \brief Contient une Way(identifiant/order/liste des noeuds et liste des tag) 
 * \author Fadyl Bello
 * \date Février 2016
 * \version 1.0
 */
typedef struct Way Way;
struct Way{
	int id;/*!< identifiant de la Way */
	int order; /*!< Ordre d'affichage */
	int list_node[MAX_SIZE_NODE_IN_WAY];/*!< Liste des noeuds */
	Tag list_tag[MAX_SIZE_TAG];/*!< Liste des tags */
};

/**
 * \struct Member
 * \brief Contient un Membre d'une Relation(identifiant way/role de la way)  
 * \author Fadyl Bello
 * \date 11 Mars 2016
 * \version 1.0
 */
typedef struct Member Member;
struct Member{
	char *type;/*!< type du membre */
	int ref;/*!< identifiant du type */
	char *role; /*!< role de la way */
};

/**
 * \struct Relation
 * \brief Contient une Relation(identifiant way/role de la way)  
 * \author Fadyl Bello
 * \date 11 Mars 2016
 * \version 1.0
 */
typedef struct Relation Relation;
struct Relation{
  int id; /*!< identifiant de la relation */
  Tag list_tag[MAX_SIZE_TAG]; /*!< Liste des tags */
  Member list_member[MAX_SIZE_MEMBER]; /*!< Liste des membres */
};

/*!< Variables globale */
Node* tab_node;/*!< Liste des Nodes */
Way* tab_way;/*!< Liste des Ways */
Relation* tab_relation;/*!< Liste des Relations */
bounds mbounds;/*!< Bounds */


void init_tabs(int, int, int);
void add_node(int, double, double, int);
void add_way(int, int);
void add_relation(int, int);
void add_bounds(double, double, double, double);
void add_tag_in_node(char *, char *, int, int);
void add_tag_in_way(char *, char *, int, int);
void add_one_idnode_in_way(int , int , int );
void add_one_member(char *, int , char *, int, int);
void add_tag_in_relation(char *, char *, int, int);
void close_tabs();
int compare_node(const void *, const void *);
int compare_way_by_id(const void *, const void *);
int compare_way_by_order(const void *, const void *);
void tab_node_sort();
void tab_way_sort_by_id();
void tab_way_sort_by_order();
int search_node_i(int);
int search_way_i(int);
double convert_gps_to_meters(short);
int convert_lat_to_pixel(double);
int convert_lon_to_pixel(double);
void add_order_way(char *, char*, int);
int get_order_way(char*, char*);
void check_order_way(int,int);

#endif

