/**
 * This file is part of ffmpeg_sender, which belongs to StreamSwitch
 * project. 
 * 
 * Copyright (C) 2014  OpenSight (www.opensight.cn)
 * 
 * StreamSwitch is an extensible and scalable media stream server for 
 * multi-protocol environment. 
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
 * stsw_ffmpeg_sender_global.cc
 *      The header file includes some global definitions and declarations
 * used by other parts of ffmpeg_sender
 * 
 * author: OpenSight Team
 * date: 2015-11-15
**/ 

#ifndef STSW_FFMPEG_SENDER_GLOBAL_H
#define STSW_FFMPEG_SENDER_GLOBAL_H


enum FFmpegSenderErrCode{    
    FFMPEG_SENDER_ERR_OK = 0, 
    FFMPEG_SENDER_ERR_GENERAL = -1, // general error
    FFMPEG_SENDER_ERR_TIMEOUT = -2, // timout
    

    FFMPEG_SENDER_ERR_IO = -64,   // IO operation fail
    FFMPEG_SENDER_ERR_INTER_FRAME_GAP = -65,  // over max inter frame gap
    FFMPEG_SENDER_ERR_EOF = -66,  // stream finish      
    FFMPEG_SENDER_ERR_NOT_SUPPORT = -67,  // codec not support     
    FFMPEG_SENDER_ERR_CODEC = -68,  // encode/decode error             
};


    

#endif