#include <opencv2/opencv.hpp>
#include "meemd.h"
#include "tools.h"
#include <sstream>
#include <iostream>
#include <ctime>
#include "typedefs.h"

Tools tools;

// Possible input files
const std::string gom_crop = "../data/crop.png";
const std::string gom_crop_sq = "../data/crop_square.png";
const std::string gom_crop_sq1 = "../data/crop_square+1.png";
const std::string gom = "../data/sschlor.ncom.GOMh0.04.012.nest1.2009101000_00000000.nc";
const std::string simple_square = "../data/simple_xy.nc";
const std::string lena_small = "../data/lena_small.bmp";
const std::string lena_big = "../data/lena.bmp";
// End input files

int main() {

    float noise_amplitude = 1.0;
    int nb_noise_iters = 100;
    const std::string input = gom; // Choose the input file here
    MEEMD m;
    if( input == gom || input == simple_square ) {
        m.load( input, MEEMD_NETCDF ); 
    } 
    else {
        m.load( input, MEEMD_IMAGE );
    }

    m.decompose( noise_amplitude, nb_noise_iters );
    std::vector<MAT> results = m.combine();
    m.showInput();
    m.showOutput();

    std::ostringstream ss;
    // Date
    time_t t = time(0);  
    struct tm * now = localtime( & t );
    ss << now->tm_mon+1 << '-' << now->tm_mday << '-' << now->tm_year+1900;
    std::string date( ss.str() );
    ss.str(std::string()); 
    // End Date
     
    // File Name
    std::string name = tools.split( tools.split( input, '/' )[2], '.')[0];
    // End File Name
    
    // Convert noise to string
    ss << noise_amplitude;
    std::string noise( ss.str() ); 
    // End conversion

    std::string save_dir = "../results/"+date+"_"+name+"_noise="+noise+"/";
    printf("save_dir = %s\n", save_dir.c_str() );
    //m.save( save_dir );

    return 0;
}
