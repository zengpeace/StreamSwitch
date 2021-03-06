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


#ifndef FN_FNC_LOG_H
#define FN_FNC_LOG_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdarg.h>


enum {  FNC_LOG_OUT,
        FNC_LOG_SYS,
        FNC_LOG_FILE };

	//level
enum {
    FNC_LOG_FATAL = 0, //!< Fatal error
    FNC_LOG_ERR,        //!< Recoverable error
    FNC_LOG_WARN,       //!< Warning
    FNC_LOG_INFO,       //!< Informative message
    FNC_LOG_CLIENT,     //!< Client response
    FNC_LOG_DEBUG,      //!< Debug
    FNC_LOG_VERBOSE,    //!< Overly verbose debug
};



typedef void (*fnc_log_t)(int, const char *, int, const char*, va_list);




#define fnc_log(level, fmt, str...) \
    fnc_log_internal(level, __FILE__, __LINE__, fmt, ## str)


fnc_log_t fnc_log_init(char *file, int out, int level, char *name);
fnc_log_t fnc_rotate_log_init(char *prog_name, char *file, 
                              int level, int file_size, int rotate_num);
void fnc_log_uninit(void);
void fnc_log_internal(int level, const char * file, int line, const char *fmt, ...);







#ifdef __cplusplus
}
#endif //


#endif // FN_FNC_LOG_H
