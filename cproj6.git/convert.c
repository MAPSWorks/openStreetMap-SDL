#include "constante.h"
#include "convert.h"
#include "element.h"

/**
 * \file convert.c
 * \brief Gestion des distances conversion proportions de la Map
 * \version 2.0
 * \date  17 avril 2016
 *
 */
 
/**
	* \param tlat1 Latitude du point 1
	* \param tlat2 Latitude du point 2
	* \param tlon1 Longitude du point 1
	* \param tlon2 Longitude du point 2
	* \return La distance entre 2 points
	* \author Fadyl Bello
	* \brief Nous donne la distance en kilomètre entre 2 points 
	* \date 17 avril 2016
	* \version 1.0
*/
double distance_calculation(double tlat1, double tlon1, double tlat2, double tlon2) 
{

		double rayon = 6366;
		double lat1 = deg2rad(tlat1);
		double lat2 = deg2rad(tlat2);
		double lon1 = deg2rad(tlon1);
		double lon2 = deg2rad(tlon2);
 	
		double dp= 2 * asin(sqrt(pow (sin((lat1-lat2)/2) , 2) + cos(lat1)*cos(lat2)* pow( sin((lon1-lon2)/2) , 2)));
		double d = dp * rayon;
 
		return d;
 }

/**
	* \param deg Le degré a transformer en radian
	* \return la valeur en degré
	* \author Fadyl Bello
	* \brief Transforme un degré en radian
	* \date 17 avril 2016
	* \version 1.0
*/
double deg2rad(double deg)
{
    return ((deg*3.141592654)/180);
}

/**
	* \return la distance entre deux latitude de la map
	* \author Fadyl Bello
	* \brief la distance entre deux latitude de la map
	* \date 17 avril 2016
	* \version 1.0
*/
double distance_lat()
{
	return distance_calculation(mbounds.minlat,mbounds.minlon,mbounds.maxlat,mbounds.minlon);
}

/**
	* \return la distance entre deux longitude de la map
	* \author Fadyl Bello
	* \brief la distance entre deux longitude de la map
	* \date 17 avril 2016
	* \version 1.0
*/
double distance_lon()
{
	return distance_calculation(mbounds.minlat,mbounds.minlon,mbounds.minlat,mbounds.maxlon);
}

/**
	* \return la hauteur de la map
	* \author Fadyl Bello
	* \brief la hauteur de la map
	* \date 17 avril 2016
	* \version 1.0
*/
double proportion()
{
 return (CP_WIDTH_RENDER*(distance_lat()/distance_lon()));
}
