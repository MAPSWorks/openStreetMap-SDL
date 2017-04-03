#include <libxml/xpath.h>
#include <libxml/parser.h>
#include "element.h"
#include "read_xml.h"
 /**
 	* \param s le nom du document
	* \author Fadyl Bello
	* \brief On regarde le nombre d'élement de chaque element.
	* \date Février 2016
	* \version 1.0
	*/
void read_size_elmt(char *s)
{
		xmlDocPtr doc;
    	xmlNodePtr racine,node;
		int number_node=0, number_way = 0,number_relation=0;

    
    doc = xmlParseFile(s);
    if (doc == NULL) 
    {
    	fprintf(stderr, "Document XML invalide\n");
   		exit(EXIT_FAILURE);
   	}
	 
    racine = xmlDocGetRootElement(doc);
    if (racine == NULL)
    {
      fprintf(stderr, "Document XML vierge\n");
    	exit(EXIT_FAILURE);
   	}

		node = racine->xmlChildrenNode;
		while (node != NULL) 
		{
			if(node->type == XML_ELEMENT_NODE)
			{
				if(strcmp((const char*)node->name,(const char*)"node")==0)number_node++;
				if(strcmp((const char*)node->name,(const char*)"way")==0) number_way++;
				if(strcmp((const char*)node->name,(const char*)"relation")==0) number_relation++;
				if(strcmp((const char*)node->name,(const char*)"bounds")==0)
				{				
						add_bounds(strtof((const char*)xmlGetProp(node,(const xmlChar*)"maxlat"),NULL),strtof((const char*)xmlGetProp(node,(const xmlChar*)"maxlon"),NULL),strtof((const char*)xmlGetProp(node,(const xmlChar*)"minlat"),NULL),strtof((const char*)xmlGetProp(node,(const xmlChar*)"minlon"),NULL));
				}
			}
			node = node->next;
		}
		init_tabs(number_node,number_way,number_relation);
    xmlFreeDoc(doc);  
}

 /**
 	* \param s le nom du document
	* \author Fadyl Bello
	* \brief On met nos élements dans notre tableau de structure
	* \todo Elagage avec 3 sous fonctions(pour way/relation/node)
	* \date Février 2016
	* \version 1.0
	*/
void lib_main(char *s) {
	xmlDocPtr doc;
	xmlNodePtr racine,node,tmp_way,tmp_node,tmp_relation;
	int pos_node=0, pos_way=0, pos_relation=0, pos_tag,pos_idnode,pos_member;
	doc = xmlParseFile(s);
	
	if (doc == NULL) {
		fprintf(stderr, "Document XML invalide\n");
		
	}
   
    racine = xmlDocGetRootElement(doc);
    if (racine == NULL) {
        fprintf(stderr, "Document XML vierge\n");
    }

		node = racine->xmlChildrenNode;
		while (node != NULL) {
			if(node->type == XML_ELEMENT_NODE)
			{
				if(strcmp((const char*)node->name,(const char*)"node")==0)
				{			
					if(strcmp((const char*)xmlGetProp(node,(const  xmlChar*)"visible"),"true")==0)
					{				
						double lat = strtof((const char*)xmlGetProp(node,(const  xmlChar*)"lat"),NULL);
						double lon = strtof((const char*)xmlGetProp(node,(const  xmlChar*)"lon"),NULL);
						add_node(atoi((const char*)xmlGetProp(node,(const xmlChar*)"id")),lat,lon, pos_node); 
					
					}
					tmp_node = node->xmlChildrenNode;
					pos_tag=0;
					while (tmp_node != NULL) 
					{	
						if(tmp_node->type == XML_ELEMENT_NODE)
						{
							if(strcmp((const char*)tmp_node->name,(const char*)"tag")==0)
							{
								add_tag_in_node((char*)xmlGetProp(tmp_node,(const xmlChar*)"k"),(char*)xmlGetProp(tmp_node,(const xmlChar*)"v"),pos_node,pos_tag);
								pos_tag++;
							}
						}
						tmp_node =tmp_node->next;
					}
				}
				pos_node++;
				
				if(strcmp((const char*)node->name,(const char*)"way")==0)
				{				
					add_way(atoi((const char*)xmlGetProp(node,(const xmlChar*)"id")),pos_way);
					tmp_way = node->xmlChildrenNode;
					
					pos_tag=0;
					pos_idnode=0;
					while (tmp_way != NULL) 
					{	
						if(tmp_way->type == XML_ELEMENT_NODE)
						{
							if(strcmp((const char*)tmp_way->name,(const char*)"nd")==0)
							{
								add_one_idnode_in_way(atoi((const char*)xmlGetProp(tmp_way,(const xmlChar*)"ref")),pos_way,pos_idnode);
								pos_idnode++;
							}
							if(strcmp((const char*)tmp_way->name,"tag")==0)
							{
								add_tag_in_way((char*)xmlGetProp(tmp_way,(const xmlChar*)"k"),(char*)xmlGetProp(tmp_way,(const xmlChar*)"v"),pos_way,pos_tag);
								check_order_way(pos_way,get_order_way((char*)xmlGetProp(tmp_way,(const xmlChar*)"k"),(char*)xmlGetProp(tmp_way,(const xmlChar*)"v")));
								pos_tag++;
							}
						}
						tmp_way =tmp_way->next;
					} 
					pos_way++;
				}
				
				if(strcmp((const char*)node->name,(const char*)"relation")==0)
				{				
				
					add_relation(atoi((const char*)xmlGetProp(node,(const xmlChar*)"id")),pos_relation);
					
					tmp_relation = node->xmlChildrenNode;	
					pos_tag=0;
					pos_member=0;
					while (tmp_relation != NULL) 
					{	
						
						if(tmp_relation->type == XML_ELEMENT_NODE)
						{
							if(strcmp((const char*)tmp_relation->name,(const char*)"member")==0)
							{
								
								add_one_member((char*)xmlGetProp(tmp_relation,(const xmlChar*)"type"),atoi((const char*)xmlGetProp(tmp_relation,(const xmlChar*)"ref")),(char*)xmlGetProp(tmp_relation,(const xmlChar*)"role"),pos_relation,pos_member);
								pos_member++;
								
							}
						}
						tmp_relation =tmp_relation->next;
					}
					pos_relation++;
					
				}
				
				
			}
			node = node->next;
		}
		
    xmlFreeDoc(doc);
   
}
 /**
 	* \param k clé du tag
 	* \param v valeur du tag
	* \author Amadou Sy
	* \brief En fonction du tag on donne un ordre d'affichage
	* \date Mars 2016
	* \version 1.0
	*/
int get_order_way(char* k, char* v)
{
	if(strcmp(k,(const char*)"highway") == 0)
	{
		if(strcmp(v,(const char*)"residential") == 0) return ORDER_RESIDENTIAL;
		if(strcmp(v,(const char*)"cycleway") == 0) return ORDER_CYCLEWAY ;
		if(strcmp(v,(const char*)"tertiary") == 0) return ORDER_TERTIARY ;
		if(strcmp(v,(const char*)"secondary") == 0 ) return ORDER_SECONDARY ;
		if(strcmp(v,(const char*)"primary") ==0) return ORDER_PRIMARY ;
		if(strcmp(v,(const char*)"pedestrian") ==0) return ORDER_PEDESTRIAN ;
		if(strcmp(v,(const char*)"footway") == 0) return ORDER_FOOTWAY ;
		if(strcmp(v,(const char*)"unclassified") ==0) return ORDER_UNCLASSIFIED ;
		if(strcmp(v,(const char*)"service") ==0) return ORDER_SERVICE ;
		if(strcmp(v,(const char*)"motorway") ==0) return ORDER_UNCLASSIFIED ;
		if(strcmp(v,(const char*)"trunk") ==0) return ORDER_UNCLASSIFIED ;
		if(strcmp(v,(const char*)"trak") ==0) return ORDER_UNCLASSIFIED ;
	}
	
	if(strcmp(k,(const char*)"historic") == 0) return ORDER_BUILDING ;
	
	if(strcmp(k,(const char*)"building") == 0)
	{
		if(strcmp(v,(const char*)"yes") ==0) return ORDER_BUILDING ;
		if(strcmp(v,(const char*)"church") ==0) return ORDER_BUILDING ;
	}
	
	if(strcmp(k,(const char*)"barrier") == 0)
	{
		if(strcmp(v,(const char*)"wall") ==0) return ORDER_WALL ;
		if(strcmp(v,(const char*)"fence") ==0) return ORDER_FENCE ;
	}
	
	if(strcmp(k,(const char*)"landuse") == 0)
	{
		if(strcmp(v,(const char*)"grass") ==0) return ORDER_GRASS ;
		if(strcmp(v,(const char*)"forest") ==0) return ORDER_FOREST ;
		if(strcmp(v,(const char*)"construction") ==0) return ORDER_FOREST ;
	}
		
	if(strcmp(k,(const char*)"leisure") == 0)
		if(strcmp(v,(const char*)"park") ==0) return ORDER_PARK ;

	if(strcmp(k,(const char*)"railway") == 0)
	{
		if(strcmp(v,(const char*)"rail") ==0) return ORDER_RAIL ;
		if(strcmp(v,(const char*)"subway") ==0) return ORDER_SUBWAY ;
	}
	
	if(strcmp(k,(const char*)"boundary") == 0)
		if(strcmp(v,(const char*)"administrative") ==0) return ORDER_ADMINISTRATIVE ;

	if(strcmp(k,(const char*)"bridge") == 0)
		if(strcmp(v,(const char*)"yes") ==0) return ORDER_BRIDGE ;
	
	if(strcmp(k,(const char*)"waterway") == 0)
		if(strcmp(v,(const char*)"riverbank") ==0) return ORDER_RIVERBANK ;

	if(strcmp(k,(const char*)"natural") == 0)
		if(strcmp(v,(const char*)"water") ==0) return ORDER_WATER ;
	
	if(strcmp(k,"area") == 0) return ORDER_BUILDING;
	
	if(strcmp(k,"amenity") == 0)
		if(strcmp(v,"source") == 0) return ORDER_BUILDING  ;
	
	return 0;
}



