#include "Resources.h"

Resources::Resources()
{
    blockTexture1.loadFromFile("Images/Blocks_01_64x64_Alt_00_001.png");
    blockTexture2.loadFromFile("Images/Blocks_01_64x64_Alt_00_002.png");
    blockTexture3.loadFromFile("Images/Blocks_01_64x64_Alt_00_003.png");
    blockTexture4.loadFromFile("Images/Blocks_01_64x64_Alt_00_004.png");
    blockTexture5.loadFromFile("Images/Blocks_01_64x64_Alt_00_005.png");
    blockTexture6.loadFromFile("Images/Blocks_01_64x64_Alt_00_006.png");
    blockTexture7.loadFromFile("Images/Blocks_01_64x64_Alt_00_007.png");
    emptyBlockTexture.loadFromFile("Images/Blocks_01_64x64_Alt_00_008.png");

    font.loadFromFile("Images/AGENCYB.ttf");
}