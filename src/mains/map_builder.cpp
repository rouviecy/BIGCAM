/*
 * @(#)		map_builder.cpp
 * @version	1.0
 * @autor	C. Rouvière
 */

 /**
 * Put grabbed pictures together to build a map
 */

#include "../img_proc/Builder.h"
#include <iostream>

using namespace std;

int main(){
	Builder builder;
	builder.Retrieve_pictures();
	builder.Build();
	return 0;
}
