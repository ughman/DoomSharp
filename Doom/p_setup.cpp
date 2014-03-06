#include "p_setup.hpp"

extern "C" void P_LoadVertexes(int lumpid)
{
	array<unsigned char>^ data = Core::Archives[lumpid]->Read();
	int count = data->Length / 4;
	if (data->Length % 4)
		Core::Console->LogWarning("This map's VERTEXES lump has an irregular length.");
	for (int i = 0;i < count;i++)
	{
		short x = BitConv::FromInt16(data,i * 4 + 0);
		short y = BitConv::FromInt16(data,i * 4 + 2);
		world->Vertices->Add(gcnew DVertex(Fixed::FromInt(x),Fixed::FromInt(y)));
	}
}

extern "C" vertex_t *P_GetVertex(int i)
{
	return ((DVertex^)world->Vertices[i])->ptr;
}

extern "C" int P_CountVertexes()
{
	return world->Vertices->Count;
}
