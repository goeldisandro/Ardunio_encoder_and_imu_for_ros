#ifndef _ROS_cartographer_ros_msgs_SubmapEntry_h
#define _ROS_cartographer_ros_msgs_SubmapEntry_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace cartographer_ros_msgs
{

  class SubmapEntry : public ros::Msg
  {
    public:
      typedef int32_t _submap_version_type;
      _submap_version_type submap_version;
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;

    SubmapEntry():
      submap_version(0),
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_submap_version;
      u_submap_version.real = this->submap_version;
      *(outbuffer + offset + 0) = (u_submap_version.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_submap_version.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_submap_version.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_submap_version.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->submap_version);
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_submap_version;
      u_submap_version.base = 0;
      u_submap_version.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_submap_version.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_submap_version.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_submap_version.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->submap_version = u_submap_version.real;
      offset += sizeof(this->submap_version);
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "cartographer_ros_msgs/SubmapEntry"; };
    const char * getMD5(){ return "8c0761eec5d33dbed4b5206883fde218"; };

  };

}
#endif