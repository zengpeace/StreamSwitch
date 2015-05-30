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
 * stsw_receiver_listener.h
 *      Define the receiver listener interface 
 * 
 * author: jamken
 * date: 2014-11-8
**/ 


#ifndef STSW_RECEIVER_LISTENER_H
#define STSW_RECEIVER_LISTENER_H

#include<stsw_defs.h>
#include<stdint.h>




namespace stream_switch {




// the Receiver Listener class
//     An interface to handle stream receiver's callback. 
// When some event happens, the stream receiver would 
// invokes the specific method of its listener in its 
// internal thread context. 
// Note: User cannot invoke Init/Uninit/Start/Stop method of the associated stream
// sink in callbacks. Otherwie, a deadlock would occurs. 
class SinkListener{
public:    
    // OnLiveMediaFrame
    // When a live media frame is received, this method would be invoked
    // by the internal thread
    virtual void OnLiveMediaFrame(const MediaFrameInfo &frame_info, 
                                  const char * frame_data, 
                                  size_t frame_size) = 0;    
    
    // OnError()
    // When a un-recover error is met, this method would be invoke d
    // by the internal thread. 
    // Note: never call Stop/Uninit methods of the associated stream sink. 
    // params: 
    //    err_code: the error code of the corresponding err. 
    //              now, the following error code supported:
    //              ERROR_CODE_GENERAL
    //              ERROR_CODE_METADATA_MISMATCH
    // 
    //    err_info: the text with the error
    virtual void OnError(int err_code, std::string err_info) = 0;                                      
 
};

}

#endif