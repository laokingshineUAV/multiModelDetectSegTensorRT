//
// Copyright (c) 2018 KDylan Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
* @author: KDylan
* @date: 2020/7/29
* @description:
*/
//

/**
 * @brief A header file with declaration for BaseInput Class
 * @file base_input.h
 */
#ifndef MULTIMODELDETECTSEGTENSORRT_BASE_INPUT_H
#define MULTIMODELDETECTSEGTENSORRT_BASE_INPUT_H
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <std_msgs/Header.h>

#include "ros_interface.h"

/**
 * @class BaseInputInterface
 * @brief this class is an interface for many kinds of
 * input ways: topic, camera, video and image...
 */
namespace Input
{
    struct Config{
        std::string input_path;
    };
    class BaseInputInterface : public RosInterface{
    public:
        virtual ~BaseInputInterface() = default;
        /**
        * @brief Initialize the input way
        * @return whether the input is successfully turned on
        */
        virtual bool initialize() = 0;
        /**
        * @brief initialize the input with given height and height.
        * @return whether the input is successfully turned on.
        */
        virtual bool initialize(int width, int height) = 0;

        /**
        * @brief read next frame, and give the value to argument frame.
        * @return whether the next frame is successfully read.
        */
        virtual bool read(cv::Mat * frame) = 0;
        virtual void config(){}
        /**
        * @brief get the width of the frame read from input.
        * @return the width of the frame.
        */
        inline int getWidth(){
            return width_;
        }
        /**
        * @brief get the height of the frame read from input.
        * @return the height of the frame.
        */
        inline int getHeight(){
            return height_;
        }
        /**
        * @brief set the width of the frame read from input.
        * @param[in] the width to be set for the frame.
        */
        inline void setWidth(int width){
            width_ = width;
        }
        /**
        * @brief set the height of the frame from input.
        * @param[in] the height to be set for the frame.
        */
        inline void setHeight(int height){
            height_ = height;
        }
        /**
        * @brief check whether the input is successfully initated.
         * @return whether the input is successfully initated.
        */
        inline bool isInit(){
            return is_init_;
        }
        /**
        * @brief set the initalization state for input.
        * @param[in] is_init the initalization state to be set.
        */
        inline void setInitStatus(bool is_init){
            is_init_ = is_init;
        }
    private:
        int width_;
        int height_;
        bool is_init_ = false;
    };
} // namespace Input
#endif //MULTIMODELDETECTSEGTENSORRT_BASE_INPUT_H
