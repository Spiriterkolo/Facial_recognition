#include <stdio.h>

int redimx (long int dimx){
	long int xredim;
	int xtrop=0;
	xredim = dimx;
	while ( xredim%10 != 0){
		xredim = xredim-1;
		xtrop += 1;
	}
	return xtrop;
}

int offset_x (int xtrop){
	int xdeb;
	if ( xtrop%2 == 0){
		xdeb = xtrop/2;
		return xdeb;
	}
	else{
		xdeb = (xtrop-1)/2;
		return xdeb;
	}
}

int fin_x (int xtrop){
	int xfin;
	if ( xtrop%2 == 0){
		xfin = xtrop/2;
		return xfin;
	}
	else{
		xfin = (xtrop+1)/2;
		return xfin;
	}
}

int redimy (long int dimy){
	long int yredim;
	int ytrop=0;
	yredim = dimy;
	while ( yredim%10 != 0){
		yredim = yredim-1;
		ytrop += 1;
	}
	return ytrop;
}

int offset_y (int ytrop){
	int ydeb;
	if ( ytrop%2 == 0){
		ydeb = ytrop/2;
		return ydeb;
	}
	else{
		ydeb = (ytrop+1)/2;
		return ydeb;
	}
}

int fin_y (int ytrop){
	int yfin;
	if ( ytrop%2 == 0){
		yfin = ytrop/2;
		return yfin;
	}
	else{
		yfin = (ytrop-1)/2;
		return yfin;
	}
}
