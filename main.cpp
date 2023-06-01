// Silent Pixels, 2023
//

#include <iostream>
#include <queue>
#include "common\Image.h"

#include <d3d11_1.h>
#include <d3d9.h>
#include <dxva.h>
#include <initguid.h>
#include <stdint.h>

using namespace img;

// Prototype of app
int app(float* inBytes, int inW, int inH, DXGI_FORMAT inFmt,
    std::vector<float> & outBytes, int & outW, int & outH, DXGI_FORMAT & outFmt);

int main()
{
    std::vector<uint8_t> bytes;
    uint32_t w=0, h=0, pitch=0;
    Fmt format = img::Fmt::R32G32B32A32;
    
    std::string pngfileName = "256x256-rgb";

    // Returns a vec of float values R32G32B32A32, so just use the data pointer
    img::load(pngfileName+".png", bytes, w, h, pitch, format);

    std::vector<float> outBytes;
    int outW=0, outH=0;
    DXGI_FORMAT outFmt=DXGI_FORMAT_UNKNOWN;

    app((float*)bytes.data(), w, h, DXGI_FORMAT_R32G32B32A32_FLOAT,
        outBytes, outW, outH, outFmt);

    // Save output
    if (outFmt != DXGI_FORMAT_R32G32B32A32_FLOAT) throw "unsupported output format!";

    img::save("silent-"+pngfileName+".png", (uint8_t*)outBytes.data(), outW, outH, 4, outW * 4 * 4, Fmt::R32G32B32A32);
}