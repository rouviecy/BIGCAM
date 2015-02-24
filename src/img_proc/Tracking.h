/*
 * @(#)		Tracking.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Classe calculant le mouvement entre deux images consécutives
 * 		- Dérivée du projet NAOSLAM https://github.com/rouviecy/NAO_SLAM/blob/master/Visio/cpp/src/Tracking.h
 */

#ifndef TRACKING
#define TRACKING

#include <opencv2/opencv.hpp>
#include "Utils.h"

class Tracking{

public:

	Tracking(const int vitesse_max = 40);

	void Set_img_prev(cv::Mat img_prev);				// setter image N-1
	void Set_img_next(cv::Mat img_next);				// setter image N
	void Set_amers(std::vector <cv::Point2i> amers);	// setter des points à tracker
	std::vector <cv::Point2i> Get_amers();				// getter des points à tracker valides
	std::vector <cv::Point2i> Get_nv();					// getter des points trouvés
	int Get_orientation() const;						// getter de l'orientation pour Try_match()

	void GoodFeatures(const int nb_max_amers);			// générer des amers intéressants
	bool Tracker();										// trouver les points à tracker dans l'image suivante
	bool Try_match(int nb_test, int minimum);			// vérifier si les deux images dans le buffer sont similaires, avec les 4 rotations possibles
	bool Flot_optique();								// rechercher la transformation rigide (après Tracker())

private:

	int vitesse_max;
	cv::TermCriteria critere;

	cv::Mat img_prev;					// image N-1	HSV
	cv::Mat img_next;					// image N		HSV
	cv::Mat img_prev_nvg;				// image N-1	niveaux de gris
	cv::Mat img_next_nvg;				// image N		niveaux de gris
	std::vector <cv::Point2f> amers;	// points à trackers
	std::vector <cv::Point2f> nv;		// points à repérer

	int orientation;		// rotation nécessaire pour le Try_match() ( -1 : no_match | 0 : 0° | 1 : 90° | 2 : 180° | 3 : 270° )

	float dx, dy, dz;		// déplacements calculés de flot optique
	float dthx, dthy, dthz;	// rotations calculées de flot optique

};

#endif
