from GUI				import GUI
from Interface_client	import Interface_client
import sys

if __name__ == '__main__':
	cli = Interface_client(sys.argv[1])
	gui = GUI(cli)
