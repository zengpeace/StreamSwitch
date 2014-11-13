/**
 * StreamSwitch is an extensible and scalable media stream server for 
 * multi-protocol environment. 
 * 
 * Copyright (C) 2014  OpenSight (www.opensight.cn)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
/**
 * stsw_stream_source.h
 *      StreamSource class header file, declare all interfaces of StreamSource.
 * 
 * author: jamken
 * date: 2014-11-8
**/ 


#ifndef STSW_STREAM_SOURCE_H
#define STSW_STREAM_SOURCE_H
#include<map>
#include<stsw_defs.h>
#include<stdint.h>




namespace stream_switch {

class ProtoClientHeartbeatReq;
typedef std::map<int, SourceApiHandlerEntry> SourceApiHanderMap;
struct ReceiversInfoType;
typedef void * SocketHandle;
    
class StreamSource{
public:
    StreamSource();
    virtual ~StreamSource();
    
    // The following methods should be invoked by clients
    
    // init this source
    // Args:
    //     stream_name string in: the stream name of this source, 
    //     which is used to bind the api socket to unix domain address
    //     tcp_port int in: the tcp port of this source, api socket would listen
    //     on this port, and publish socket would listen on tcp_port + 1. If
    //     this param is 0, means this source never listen on tcp
    //
    // return:
    //     0 if successful, or -1 if error;
    virtual int Init(const std::string &stream_name, int tcp_port);
    
    // un-init the source
    virtual void Uninit();
    
    virtual bool IsInit();
    virtual bool IsMetaReady();
    
    
    // configure the meta data of this source. 
    // After meta data change, the statistic in the source would auto clear
    // Args:
    //     stream_meta StreamMetadata in: new stream metatdata
    //
    virtual void set_stream_meta(StreamMetadata & stream_meta);
    
    // get the meta data of this source 
    // Args:
    //     stream_meta StreamMetadata out: the retrieved stream meta data
    //
    virtual void stream_meta(StreamMetadata * stream_meta);
    
    virtual int Start();
    virtual void Stop();
    
    virtual int SendMediaData(void);
    //virtual int SendStreamInfo(void);
    
    virtual void set_stream_state(int stream_state);
    virtual int stream_state(int new_state);

   
    virtual void RegisterApiHandler(int op_code, SourceApiHandler handler, void * user_data);
    virtual void UnregisterApiHandler(int op_code);
    virtual void UnregisterAllApiHandler();    
    
        
    // the following methods need client to override
    // to fulfill its functions. They would be invoked
    // by the internal api thread 
        
    // key_frame
    // When the receiver request a key frame, it would be 
    // invoked
    virtual void KeyFrame(void);
        
    // get_packet_statistic
    // When the control request the statistic info, it would 
    // be invoked for each sub stream
    virtual void GetPacketStatistic(int sub_stream_index, uint64_t * expected_packets, uint64_t * actual_packets);




protected:

    static int StaticMetadataHandler(StreamSource * source, ProtoCommonPacket * request, ProtoCommonPacket * reply, void * user_data);
    static int StaticKeyFrameHandler(StreamSource * source, ProtoCommonPacket * request, ProtoCommonPacket * reply, void * user_data);
    static int StaticStatisticHandler(StreamSource * source, ProtoCommonPacket * request, ProtoCommonPacket * reply, void * user_data);
    static int StaticClientHeartbeatHandler(StreamSource * source, ProtoCommonPacket * request, ProtoCommonPacket * reply, void * user_data);
    
    virtual int MetadataHandler(ProtoCommonPacket * request, ProtoCommonPacket * reply, void * user_data);
    virtual int KeyFrameHandler(ProtoCommonPacket * request, ProtoCommonPacket * reply, void * user_data);
    virtual int StatisticHandler(ProtoCommonPacket * request, ProtoCommonPacket * reply, void * user_data);
    virtual int ClientHeartbeatHandler(ProtoCommonPacket * request, ProtoCommonPacket * reply, void * user_data);

    virtual int RpcHandler();
    virtual int Heartbeat();
    
    static void * ThreadRoutine(void *);
    
private:
    std::string stream_name_;
    int tcp_port_;
    SocketHandle api_socket_;
    SocketHandle publish_socket_;
    LockHandle lock_;
    ThreadHandle * api_thread_;
    SourceApiHanderMap api_handler_map_;
    
// stream source flags
#define STREAM_SOURCE_FLAG_INIT 1
#define STREAM_SOURCE_FLAG_META_READY 2
    uint32_t flags_;      

    SubStreamMediaStatisticVector staitistic_;
    StreamMetadata stream_meta_;
    uint32_t cur_bps_;
    int64_t last_frame_sec_;
    int32_t last_frame_usec_;
    int stream_state_;
    ReceiversInfoType * receivers_info_;
    int64_t last_heartbeat_time;     // in milli-sec
                             
};
}

#endif