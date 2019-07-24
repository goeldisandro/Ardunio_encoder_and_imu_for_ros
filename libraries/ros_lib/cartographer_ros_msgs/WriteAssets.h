#ifndef _ROS_SERVICE_WriteAssets_h
#define _ROS_SERVICE_WriteAssets_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cartographer_ros_msgs
{

static const char WRITEASSETS[] = "cartographer_ros_msgs/WriteAssets";

  class WriteAssetsRequest : public ros::Msg
  {
    public:
      typedef const char* _stem_type;
      _stem_type stem;

    WriteAssetsRequest():
      stem("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_stem = strlen(this->stem);
      varToArr(outbuffer + offset, length_stem);
      offset += 4;
      memcpy(outbuffer + offset, this->stem, length_stem);
      offset += length_stem;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_stem;
      arrToVar(length_stem, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_stem; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_stem-1]=0;
      this->stem = (char *)(inbuffer + offset-1);
      offset += length_stem;
     return offset;
    }

    const char * getType(){ return WRITEASSETS; };
    const char * getMD5(){ return "1ca78fe806c5256bb03c4e35886127f9"; };

  };

  class WriteAssetsResponse : public ros::Msg
  {
    public:

    WriteAssetsResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return WRITEASSETS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class WriteAssets {
    public:
    typedef WriteAssetsRequest Request;
    typedef WriteAssetsResponse Response;
  };

}
#endif
