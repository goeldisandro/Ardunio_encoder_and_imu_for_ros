#ifndef _ROS_cartographer_ros_msgs_TrajectorySubmapList_h
#define _ROS_cartographer_ros_msgs_TrajectorySubmapList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "cartographer_ros_msgs/SubmapEntry.h"

namespace cartographer_ros_msgs
{

  class TrajectorySubmapList : public ros::Msg
  {
    public:
      uint32_t submap_length;
      typedef cartographer_ros_msgs::SubmapEntry _submap_type;
      _submap_type st_submap;
      _submap_type * submap;

    TrajectorySubmapList():
      submap_length(0), submap(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->submap_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->submap_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->submap_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->submap_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->submap_length);
      for( uint32_t i = 0; i < submap_length; i++){
      offset += this->submap[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t submap_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      submap_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      submap_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      submap_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->submap_length);
      if(submap_lengthT > submap_length)
        this->submap = (cartographer_ros_msgs::SubmapEntry*)realloc(this->submap, submap_lengthT * sizeof(cartographer_ros_msgs::SubmapEntry));
      submap_length = submap_lengthT;
      for( uint32_t i = 0; i < submap_length; i++){
      offset += this->st_submap.deserialize(inbuffer + offset);
        memcpy( &(this->submap[i]), &(this->st_submap), sizeof(cartographer_ros_msgs::SubmapEntry));
      }
     return offset;
    }

    const char * getType(){ return "cartographer_ros_msgs/TrajectorySubmapList"; };
    const char * getMD5(){ return "dbaf63609cc9479c855dae57cd69f372"; };

  };

}
#endif