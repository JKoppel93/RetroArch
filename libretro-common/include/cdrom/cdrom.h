/* Copyright  (C) 2010-2019 The RetroArch team
 *
 * ---------------------------------------------------------------------------------------
 * The following license statement only applies to this file (cdrom.h).
 * ---------------------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __LIBRETRO_SDK_CDROM_H
#define __LIBRETRO_SDK_CDROM_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

#include <libretro.h>
#include <retro_common_api.h>
#include <retro_inline.h>

#include <boolean.h>

RETRO_BEGIN_DECLS

typedef struct
{
   unsigned lba_start;
   unsigned track_size;
   unsigned char track_num;
   unsigned char min;
   unsigned char sec;
   unsigned char frame;
   unsigned char mode;
   bool audio;
} cdrom_track_t;

typedef struct
{
   unsigned char cur_min;
   unsigned char cur_sec;
   unsigned char cur_frame;
   unsigned char num_tracks;
   cdrom_track_t track[99];
} cdrom_toc_t;

void lba_to_msf(unsigned lba, unsigned char *min, unsigned char *sec, unsigned char *frame);

unsigned msf_to_lba(unsigned char min, unsigned char sec, unsigned char frame);

void increment_msf(unsigned char *min, unsigned char *sec, unsigned char *frame);

int cdrom_read_subq(int fd, unsigned char *buf, size_t len);

int cdrom_write_cue(int fd, char **out_buf, size_t *out_len, char cdrom_drive, unsigned char *num_tracks, cdrom_toc_t *toc);

/* needs 32 bytes for full vendor, product and version */
int cdrom_get_inquiry(int fd, char *model, int len);

int cdrom_read(int fd, unsigned char min, unsigned char sec, unsigned char frame, void *s, size_t len);

RETRO_END_DECLS

#endif
