/*
 * @(#)		ComThread.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Thread with message queue communication
 */

#ifndef COMTHREAD
#define COMTHREAD

#include <thread>
#include <unistd.h>
#include <iostream>
#include <string>
#include "../Share.h"

class ComThread{

public:

	ComThread();							// Create the thread
	void Link(								// Link to shared memory
		Share *s);								// Pointer to share object
	void Launch();							// Begin the job
	void Join();							// Wait the end of the thread
	void Set_freq(							// Setup freqency thread
		int dt_microseconds);					// Period between two jobs in μs (-1 for no loop)
	void Set_name(							// Give a string name to the object
		std::string name);						// New name
	std::string Get_name();					// Return the name of the object
	float Get_freq();							// Return the frequency of the thread
	std::vector <std::string> Get_inputs();	// Return the list of inputs
	std::vector <std::string> Get_outputs();// Return the list of outputs

private:

	std::thread thr;
	int dt_microseconds;
	bool job_go_on;
	std::string name;
	
	Share *s;
	PFloatMap critical_input, critical_output;
	
	void Loop_job();

protected:

	virtual void Job() = 0;			// Overwrite : job for the thread
	virtual void IO() = 0;			// Overwrite : input and output links

	void Link_input(std::string key, float *p_float);
	void Link_output(std::string key, float *p_float);
	void Critical_receive();
	void Critical_send();

};

#endif
