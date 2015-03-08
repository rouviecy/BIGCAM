#include "Altimeter.h"

using namespace std;

Altimeter::Altimeter() : Proprioceptive(){

}

void Altimeter::IO(){
	Link_output("alti", &alti);
}

void Altimeter::Job(){
	alti = 42;
	Critical_send();
}
