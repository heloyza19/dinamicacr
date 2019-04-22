#include "pch.h"
#include "dadosaida.h"


dadosaida::dadosaida(string filename)
{
	myfile.open(filename, ios::out);


}


dadosaida::~dadosaida()
{
	myfile.close();
}

void dadosaida:: salvar(sistema* Dados, int t)
{

	if (t == 0)
	{
		
		myfile << "<?xml version=" << '"' << "1.0" << '"' << " ?>\n" << "<!DOCTYPE Xdmf SYSTEM " << '"' << "Xdmf.dtd" << '"' << " []>\n";
		myfile << "<Xdmf Version = " << '"' << "2.0" << '"' << " xmlns:xi = " << '"' << "[http://www.w3.org/2001/XInclude]" << '"' << ">\n";
		myfile << "<Domain>\n";
		myfile << "<Grid CollectionType=" << '"' << "Temporal" << '"' << " GridType=" << '"' << "Collection" << '"' << " Name=" << '"' << "Collection" << '"' << ">\n";

	}
	myfile << "<Grid Name=" << '"' << "Grid" << '"' << " GridType=" << '"' << "Collection" << '"' << " CollectionType=" << '"' << "Spatial" << '"' << ">\n";
	myfile << "<Time Value=" << '"' << t << '"' << "/>\n";
	//myfile << "<Grid Name = " << '"' << "poligono1" << '" ' << "GridType = " << '"' << "Uniform" << '"' << ">\n";


	for (int i = 0; i < Dados->corpo.size(); i++)
	{
		myfile << "<Grid Name = " << '"' << "corpo" << i << '"' << " GridType = " << '"' << "Uniform" << '"' << ">\n";
		myfile << "<Time Value = " << '"' << t * Dados->dt << '"' << "/>\n";
		myfile << "<Topology TopologyType = " << '"' << "Polygon" << '"' << " NodesPerElement = " << '"' << Dados->corpo[i]->segmento.size()<< '"' << ">\n";
		myfile << "<DataItem Format=" << '"' << "XML" << '"' << " Dimensions=" << '"' << "1 "<< Dados->corpo[i]->segmento.size() << '"' << ">\n";

		for (int j = 0; j < Dados->corpo[i]->posicao.size[0]; j++)
		{
			myfile << j << " ";
		}
		myfile << "\n" << "</DataItem >\n" << "</Topology>\n" << "<Geometry GeometryType=" << '"' << "XY" << '"' << ">\n";
		myfile << "<DataItem Format = " << '"' << "XML" << '"' << " Dimensions = " <<'"'<< "1 " << Dados->corpo[i]->segmento.size() << " 2" << '"' << ">\n";
		for (int j = 0; j < Dados->corpo[i]->posicao.size[0]; j++)
		{
			myfile << Dados->corpo[i]->posicao.M[j][0] << " " << Dados->corpo[i]->posicao.M[j][1] << "\n";
		}
		myfile << "\n" << "</DataItem>\n" << "</Geometry>\n" << "</Grid>\n" << "\n";

	}

	myfile << "</Grid>\n";
	if (t == (ceil(Dados->times / Dados->dt) - 1))
	{
		myfile <<"</Grid>\n" << "</Domain>\n" << "</Xdmf>\n";
		myfile.close();
	}






}