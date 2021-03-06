﻿#include <vector>
#include <openpose/utilities/errorAndLog.hpp>
#include <openpose/experimental/3d/cameraParameters.hpp>

namespace op
{
    // User configurable code
    // Intrinsic and distortion parameters
    // Camera 1 parameters
    const cv::Mat INTRINSIC_1 = (cv::Mat_<double>(3, 3) << 817.93481631740565, 0, 600.70689997785121,
        0, 816.51774059837908, 517.84529566329593,
        0, 0, 1);
    const cv::Mat DISTORTION_1 = (cv::Mat_<double>(8, 1) <<
        -1.8102158829399091, 9.1966147162623262, -0.00044293900343777355, 0.0013638377686816653, 1.3303863414979364, -1.418905163635487, 8.4725535468475819, 4.7911023525901033);
    // Camera 2 parameters
    const cv::Mat INTRINSIC_2 = (cv::Mat_<double>(3, 3) << 816.20921132436638, 0, 612.67087968681585,
        0, 816.18292222910486, 530.47901782670431,
        0, 0, 1);
    const cv::Mat DISTORTION_2 = (cv::Mat_<double>(8, 1) <<
        -5.1088507540294881, 133.63995617304997, -0.0010048069080912836, 0.00018825291386406282, 20.688286893903879, -4.7604289550474768, 132.42412342224557, 70.01195364029752);
    const cv::Mat INTRINSIC_3 = (cv::Mat_<double>(3, 3) << 798.42980806905666, 0, 646.48130011561727,
        0, 798.46535448393979, 523.91590563194586,
        0, 0, 1);
    // Camera 3
    const cv::Mat DISTORTION_3 = (cv::Mat_<double>(8, 1) <<
        -0.57530495294002304, -0.54721992620722582, -0.00037614702677289967, -0.00081995658363481598, -0.020321660897680775, -0.18040544059116842, -0.87724444571603022, -0.13136636671099691);

    // Extrinsic parameters - rotation and pose orientation between cameras
    // Camera 1
    const cv::Mat M_1_1 = (cv::Mat_<double>(3, 4) << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0);
    // Not working on Windows
    // const cv::Mat M_1_1 = cv::Mat::eye(3, 4, CV_64F);
    // From camera 1 to 2
    const cv::Mat M_1_2 = (cv::Mat_<double>(3, 4) << 0.999962504862692, -0.00165862051503619, 0.00849928507093793, -238.301309354482,
        0.00176155163779584, 0.999925029704659, -0.0121174215889211, 4.75863886121558,
        -0.00847854967298925, 0.0121319391740716, 0.999890459124058, 15.9219925821916);
    // From camera 1 to 3
    const cv::Mat M_1_3 = (cv::Mat_<double>(3, 4) << 0.995809442124071, -0.000473104796892308, 0.0914512501193800, -461.301274485705,
        0.00165046455210419, 0.999916727562850, -0.0127989806923977, 6.22648121362088,
        -0.0914375794917412, 0.0128962828696210, 0.995727299487585, 63.4911132860733);
    // From camera 2 to 3
    const cv::Mat M_2_3 = (cv::Mat_<double>(3, 4) << 0.999644115423621, -0.00194501088674130, -0.0266056278177532, -235.236375502202,
        0.00201646110733780, 0.999994431880356, 0.00265896462686206, 9.52238656728889,
        0.0266003079592876, -0.00271166755609303, 0.999642471324391, -4.23534963077479);



    // Do not modify this code
    const std::vector<cv::Mat> INTRINSICS{ INTRINSIC_1, INTRINSIC_2, INTRINSIC_3 };
    const std::vector<cv::Mat> DISTORTIONS{ DISTORTION_1, DISTORTION_2, DISTORTION_3 };
    const std::vector<cv::Mat> M{ M_1_1, M_1_2, M_1_3 };
    // Not working on Windows
    // const std::vector<cv::Mat> M_EACH_CAMERA{
    //     INTRINSIC_1 * M_1_1,
    //     INTRINSIC_2 * M_1_2,
    //     INTRINSIC_3 * M_1_3
    // };

    const cv::Mat getIntrinsics(const int cameraIndex)
    {
        try
        {
            return INTRINSICS[cameraIndex];
        }
        catch (const std::exception& e)
        {
            error(e.what(), __LINE__, __FUNCTION__, __FILE__);
            return cv::Mat{};
        }
    }

    const cv::Mat getDistorsion(const int cameraIndex)
    {
        try
        {
            return DISTORTIONS[cameraIndex];
        }
        catch (const std::exception& e)
        {
            error(e.what(), __LINE__, __FUNCTION__, __FILE__);
            return cv::Mat{};
        }
    }

    const cv::Mat getM(const int cameraIndex)
    {
        try
        {
            return INTRINSICS[cameraIndex] * M[cameraIndex];
            // return M_EACH_CAMERA[cameraIndex];
        }
        catch (const std::exception& e)
        {
            error(e.what(), __LINE__, __FUNCTION__, __FILE__);
            return cv::Mat{};
        }
    }
    std::vector<cv::Mat> getMs()
    {
        try
        {
            // Security checks
            if (INTRINSICS.size() != DISTORTIONS.size())
                error("The INTRINSICS and DISTORTIONS vector should have the same size.",
                      __LINE__, __FUNCTION__, __FILE__);
            if (INTRINSICS.size() != M.size())
                error("The INTRINSICS and M_EACH_CAMERA vector should have the same size.",
                      __LINE__, __FUNCTION__, __FILE__);

            std::vector<cv::Mat> result(INTRINSICS.size());
            for (auto i = 0u ; i < result.size(); i++)
                result[i] = getM(i);
            return result;
            // return M_EACH_CAMERA;
        }
        catch (const std::exception& e)
        {
            error(e.what(), __LINE__, __FUNCTION__, __FILE__);
            return{};
        }
    }
    unsigned long long getNumberCameras()
    {
        try
        {
            return INTRINSICS.size();
        }
        catch (const std::exception& e)
        {
            error(e.what(), __LINE__, __FUNCTION__, __FILE__);
            return 0;
        }
    }
}
