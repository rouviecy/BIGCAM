#include "Share.h"

using namespace std;

Share::Share(){

}

void Share::Lock(){mu.lock();}
void Share::Unlock(){mu.unlock();}

void Share::Create_data(string key){
	if(data.count(key) == 0){
		data[key] = 0.;
	}
}

void Share::Send(PFloatMap input){
	Lock();
	for(PFloatMap::iterator it = input.begin(); it != input.end(); ++it){
		data[it->first] = *(it->second);
		cout << "writing : " << it->first << " = " << *(it->second) << endl;
	}
	Unlock();
}

FloatMap Share::Receive(StringVec keys){
	Lock();
	FloatMap result;
	for(StringVec::iterator it = keys.begin(); it != keys.end(); ++it){
		result[*it] = data[*it];
		cout << "reading : " << *it << " = " << data[*it] << endl;
	}
	Unlock();
	return result;
}
