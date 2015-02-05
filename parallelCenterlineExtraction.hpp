#ifndef PCE_H
#define PCE_H
#include "commons.hpp"
#include "SIPL/Types.hpp"
#include "parameters.hpp"
using namespace cl;

Image3D runNewCenterlineAlg(OpenCL &ocl, SIPL::int3 size, paramList &parameters, Image3D &vectorField, Image3D &TDF, Image3D &radius, std::string kernel_dir, std::string oul_dir);
Image3D runNewCenterlineAlgWithoutOpenCL(OpenCL &ocl, SIPL::int3 size, paramList &parameters, Image3D &vectorField, Image3D &TDF, Image3D &radius);
#endif
