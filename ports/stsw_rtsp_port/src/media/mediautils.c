/**
 * This file is part of stsw_rtsp_port, which belongs to StreamSwitch
 * project. And it's derived from Feng prject originally
 * 
 * Copyright (C) 2015  OpenSight team (www.opensight.cn)
 * Copyright (C) 2009 by LScube team <team@lscube.org>
 * 
 * StreamSwitch is an extensible and scalable media stream server for 
 * multi-protocol environment. 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <stdio.h>

#include "mediaparser.h"

// Ripped from ffmpeg, see sdp.c

static void digit_to_char(char *dst, uint8_t src)
{
    if (src < 10) {
        *dst = '0' + src;
    } else {
        *dst = 'A' + src - 10;
    }
}

char *extradata2config(MediaProperties *properties)
{
    size_t config_len;
    char *config;
    size_t i;

    if ( properties->extradata_len == 0 )
        return NULL;

    config_len = properties->extradata_len * 2 + 1;
    config = g_malloc(config_len);

    if (config == NULL)
        return NULL;

    for(i = 0; i < properties->extradata_len; i++) {
        digit_to_char(config + 2 * i, properties->extradata[i] >> 4);
        digit_to_char(config + 2 * i + 1, properties->extradata[i] & 0xF);
    }

    config[config_len-1] = '\0';

    return config;
}

int getProfileLevelIdFromextradata(MediaProperties *properties)
{
    size_t i;

    if ( properties->extradata_len == 0 || properties->extradata_len < 4)
        return -1;
    
    
    for (i = 3; i < properties->extradata_len; ++i) {
        if (properties->extradata[i] == 0xB0 /*VISUAL_OBJECT_SEQUENCE_START_CODE*/ 
	    && properties->extradata[i-1] == 1 && properties->extradata[i-2] == 0 && properties->extradata[i-3] == 0) {
            break; // The configuration information ends here
        }
    }
    if(i == properties->extradata_len) {
        return -1;
    }
    if((i+1) >= properties->extradata_len) {
        return -1;
    }
    return (int)properties->extradata[i+1]; 

}

