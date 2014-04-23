#include "tests.hpp"
#include <fstream>

class ClinicalTests : public ::testing::Test {
protected:
	virtual void SetUp() {
		parameters = initParameters(PARAMETERS_DIR);
	};
	virtual void TearDown() {

	};
	paramList parameters;
	TubeValidation result;
};

TubeValidation runClinicalData(paramList parameters, std::string name) {
	TSFOutput * output;
	output = run(std::string(TESTDATA_DIR) + std::string("/clinical/") + name + std::string("/input.mhd"), parameters, KERNELS_DIR, OUL_DIR);

	TubeValidation result = validateTube(
			output,
			std::string(TESTDATA_DIR) + std::string("/clinical/") + name + std::string("/segmentation.mhd"),
			std::string(TESTDATA_DIR) + std::string("/clinical/") + name + std::string("/centerline.mhd")
	);

	delete output;
	return result;
}

bool dataExists(std::string name) {
    std::string filepath = std::string(TESTDATA_DIR) + std::string("/clinical/") + name + std::string("/input.mhd");
    std::ifstream file(filepath);
    bool result = file.good();
    if(!result)
		std::cout << "WARNING: Clinical data not found. Aborting clinical test." << std::endl;
    file.close();
    return result;
}

TEST_F(ClinicalTests, LungAirwaysCT) {
    std::string name = "Lung-Airways-CT";
    setParameter(parameters, "parameters", name);

    if(!dataExists(name)) {
        SUCCEED();
        return;
    }
    loadParameterPreset(parameters, PARAMETERS_DIR);
    try {
        result = runClinicalData(parameters, name);
    } catch(SIPL::SIPLException e) {
        // Out of memory on GPU
        // Try to run cropped version instead
        std::cout << "Exception occurred. Trying cropped volume instead." << std::endl;
        setParameter(parameters, "cropping", "no");
        result = runClinicalData(parameters, name+"-cropped");
    }
	EXPECT_GT(1.5, result.averageDistanceFromCenterline);
	EXPECT_LT(75.0, result.percentageExtractedCenterlines);
	EXPECT_LT(0.7, result.precision);
	EXPECT_LT(0.7, result.recall);
	EXPECT_GT(200, result.incorrectCenterpoints);
}

TEST_F(ClinicalTests, NeuroVesselsMRA) {
    std::string name = "Neuro-Vessels-MRA";
    setParameter(parameters, "parameters", name);

    if(!dataExists(name)) {
        SUCCEED();
        return;
    }
    loadParameterPreset(parameters, PARAMETERS_DIR);
    try {
        result = runClinicalData(parameters, name);
    } catch(SIPL::SIPLException e) {
        // Out of memory on GPU
        // Try to run cropped version instead
        std::cout << "Exception occurred. Trying cropped volume instead." << std::endl;
        setParameter(parameters, "cropping", "no");
        result = runClinicalData(parameters, name+"-cropped");
    }
	EXPECT_GT(1.5, result.averageDistanceFromCenterline);
	EXPECT_LT(75.0, result.percentageExtractedCenterlines);
	EXPECT_LT(0.7, result.precision);
	EXPECT_LT(0.7, result.recall);
	EXPECT_GT(200, result.incorrectCenterpoints);
}

TEST_F(ClinicalTests, NeuroVesselsUSA) {
    std::string name = "Neuro-Vessels-USA";
    setParameter(parameters, "parameters", name);

    if(!dataExists(name)) {
        SUCCEED();
        return;
    }
    loadParameterPreset(parameters, PARAMETERS_DIR);
    try {
        result = runClinicalData(parameters, name);
    } catch(SIPL::SIPLException e) {
        // Out of memory on GPU
        // Try to run cropped version instead
        std::cout << "Exception occurred. Trying cropped volume instead." << std::endl;
        setParameter(parameters, "cropping", "no");
        result = runClinicalData(parameters, name+"-cropped");
    }
	EXPECT_GT(1.5, result.averageDistanceFromCenterline);
	EXPECT_LT(75.0, result.percentageExtractedCenterlines);
	EXPECT_LT(0.7, result.precision);
	EXPECT_LT(0.7, result.recall);
	EXPECT_GT(200, result.incorrectCenterpoints);
}

TEST_F(ClinicalTests, PhantomAccUS) {
    std::string name = "Phantom-Acc-US";
    setParameter(parameters, "parameters", name);

    if(!dataExists(name)) {
        SUCCEED();
        return;
    }
    loadParameterPreset(parameters, PARAMETERS_DIR);
	result = runClinicalData(parameters, name);
	EXPECT_GT(1.5, result.averageDistanceFromCenterline);
	EXPECT_LT(75.0, result.percentageExtractedCenterlines);
	EXPECT_LT(0.7, result.precision);
	EXPECT_LT(0.7, result.recall);
	EXPECT_GT(200, result.incorrectCenterpoints);
}

