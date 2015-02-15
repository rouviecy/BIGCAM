#include "ComDraw.h"

using namespace std;

// Constructeur
ComDraw::ComDraw(){

}

void ComDraw::Draw_threads(vector <ComThread*> threads){
	string dot_text = "digraph links {\n";
	map <string, vector <int> > map_in;
	map <string, vector <int> > map_out;
	int num_elem = 0;
	for(size_t i = 0; i < threads.size(); i++){
		num_elem++;
		dot_text += "\tsubgraph cluster_" + to_string(num_elem) + " {\n";
		dot_text += "\t\tlabel = \"" + threads[i]->Get_name() + "\";\n";
		dot_text += "\t\tstyle=filled;\n";
		dot_text += "\t\tcolor=lightgrey;\n";
		dot_text += "\t\tnode [style=filled,color=white];\n";
		vector <string> inputs = threads[i]->Get_inputs();
		vector <string> outputs = threads[i]->Get_outputs();
		for(size_t j = 0; j < inputs.size(); j++){
			num_elem++;
			dot_text += "\t\t" + to_string(num_elem) + " [label = \"" + inputs[j] + "\"];\n";
			map_in[inputs[j]].push_back(num_elem);
		}
		for(size_t j = 0; j < outputs.size(); j++){
			num_elem++;
			dot_text += "\t\t" + to_string(num_elem) + " [label = \"" + outputs[j] + "\"];\n";
			map_out[outputs[j]].push_back(num_elem);
		}
		dot_text += "\t}\n";
	}
	for(map <string, vector <int> >::iterator it = map_in.begin(); it != map_in.end(); ++it){
		for(size_t i = 0; i < it->second.size(); i++){
			for(size_t j = 0; j < map_out[it->first].size(); j++){
				dot_text += "\t" + to_string(map_out[it->first][j]) + "->" + to_string(it->second[i]) + ";\n";
			}
		}
	}
	dot_text += "}";
	ofstream dot_file;
	dot_file.open(DOT_PATH);
	dot_file << dot_text;
	dot_file.close();
	string command = "dot -Tpng " + string(DOT_PATH) + " > " + string(PNG_PATH);
	system(command.c_str());
}
