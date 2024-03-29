#ifndef _ROS_SERVICE_StartTrajectory_h
#define _ROS_SERVICE_StartTrajectory_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "cartographer_ros_msgs/TrajectoryOptions.h"
#include "cartographer_ros_msgs/SensorTopics.h"

namespace cartographer_ros_msgs
{

static const char STARTTRAJECTORY[] = "cartographer_ros_msgs/StartTrajectory";

  class StartTrajectoryRequest : public ros::Msg
  {
    public:
      typedef cartographer_ros_msgs::TrajectoryOptions _options_type;
      _options_type options;
      typedef cartographer_ros_msgs::SensorTopics _topics_type;
      _topics_type topics;

    StartTrajectoryRequest():
      options(),
      topics()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->options.serialize(outbuffer + offset);
      offset += this->topics.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->options.deserialize(inbuffer + offset);
      offset += this->topics.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return STARTTRAJECTORY; };
    const char * getMD5(){ return "43bc2f400a20b882d4e814954643af02"; };

  };

  class StartTrajectoryResponse : public ros::Msg
  {
    public:
      typedef int32_t _trajectory_id_type;
      _trajectory_id_type trajectory_id;

    StartTrajectoryResponse():
      trajectory_id(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_trajectory_id;
      u_trajectory_id.real = this->trajectory_id;
      *(outbuffer + offset + 0) = (u_trajectory_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_trajectory_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_trajectory_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_trajectory_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->trajectory_id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_trajectory_id;
      u_trajectory_id.base = 0;
      u_trajectory_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_trajectory_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_trajectory_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_trajectory_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->trajectory_id = u_trajectory_id.real;
      offset += sizeof(this->trajectory_id);
     return offset;
    }

    const char * getType(){ return STARTTRAJECTORY; };
    const char * getMD5(){ return "6e190c4be941828bcd09ea05053f4bb5"; };

  };

  class StartTrajectory {
    public:
    typedef StartTrajectoryRequest Request;
    typedef StartTrajectoryResponse Response;
  };

}
#endif
