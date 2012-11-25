#include "TGA.h"

namespace revel
{
	
void 
TGA::write(const std::string& filename, const TGAHeader& header, const i8* dataptr, u32 byte)
{
    if (dataptr == nullptr)
        throw TGAException("Invalid data source pointer");
    
    std::ofstream imagefile(filename.c_str(), std::ios::out | std::ios::binary);

    imagefile.write(reinterpret_cast<const i8*>(&header), sizeof(TGAHeader));
    imagefile.write(dataptr, byte);
    imagefile.close();
}


}