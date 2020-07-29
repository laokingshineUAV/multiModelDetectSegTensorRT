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
 * @brief A header file with declatation for ROS handle
 * @file ros_interface.h
 */
#ifndef MULTIMODELDETECTSEGTENSORRT_ROS_INTERFACE_H
#define MULTIMODELDETECTSEGTENSORRT_ROS_INTERFACE_H

#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <memory>
#include <utility>

namespace Input{
    class RosInterface{
    public:
        void setNodeHandle(const std::shared_ptr<ros::NodeHandle>& node){
            node_ = node;
        }
        std::shared_ptr<ros::NodeHandle> getNodeHandler() const
        {
            return node_;
        }

        /**
         * @brief set the frame_id of input device for topic.
         * @param[in] frame_id the frame of input.
         */
         inline void setFrameId(std::string frame_id){
             header_.frame_id = std::move(frame_id);
             std::chrono::high_resolution_clock::time_point tp = std::chrono::high_resolution_clock::now();
             int64 ns = tp.time_since_epoch().count();
             header_.stamp.sec = ns / 1000000000;
             header_.stamp.nsec = ns % 1000000000;
         }

         inline void setHeader(std_msgs::Header header){
             header_ = std::move(header);
         }
    private:
         std::shared_ptr<ros::NodeHandle> node_;
         std_msgs::Header header_;
    };

} // namespace Input
#endif //MULTIMODELDETECTSEGTENSORRT_ROS_INTERFACE_H
