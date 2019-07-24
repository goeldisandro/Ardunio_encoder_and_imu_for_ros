#ifndef _ROS_cartographer_ros_msgs_SubmapList_h
#define _ROS_cartographer_ros_msgs_SubmapList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "cartographer_ros_msgs/TrajectorySubmapList.h"

namespace cartographer_ros_msgs
{

  class SubmapList : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t trajectory_length;
      typedef cartographer_ros_msgs::TrajectorySubmapList _trajectory_type;
      _trajectory_type st_trajectory;
      _trajectory_type * trajectory;

    SubmapList():
      header(),
      trajectory_length(0), trajectory(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->trajectory_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->trajectory_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->trajectory_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->trajectory_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->trajectory_length);
      for( uint32_t i = 0; i < trajectory_length; i++){
      offset += this->trajectory[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t trajectory_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      trajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      trajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      trajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->trajectory_length);
      if(trajectory_lengthT > trajectory_length)
        this->trajectory = (cartographer_ros_msgs::TrajectorySubmapList*)realloc(this->trajectory, trajectory_lengthT * sizeof(cartographer_ros_msgs::TrajectorySubmapList));
      trajectory_length = trajectory_lengthT;
      for( uint32_t i = 0; i < trajectory_length; i++){
      offset += this->st_trajectory.deserialize(inbuffer + offset);
        memcpy( &(this->trajectory[i]), &(this->st_trajectory), sizeof(cartographer_ros_msgs::TrajectorySubmapList));
      }
     return offset;
    }

    const char * getType(){ return "cartographer_ros_msgs/SubmapList"; };
    const char * getMD5(){ return "5486c1cb2dbd0e42fa7ce803a38fcb70"; };

  };

}
#endif